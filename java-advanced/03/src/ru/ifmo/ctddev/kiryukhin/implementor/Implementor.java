package ru.ifmo.ctddev.kiryukhin.implementor;

import com.sun.org.apache.xpath.internal.operations.Mod;
import info.kgeorgiy.java.advanced.implementor.*;

import javax.tools.JavaCompiler;
import javax.tools.ToolProvider;
import java.io.*;
import java.lang.reflect.Constructor;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.lang.reflect.Parameter;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;
import java.util.jar.Attributes;
import java.util.jar.JarEntry;
import java.util.jar.JarOutputStream;
import java.util.jar.Manifest;
import java.util.stream.Collectors;

/**
 * Implementation of {@link info.kgeorgiy.java.advanced.implementor.JarImpler}.
 * It implements interfaces and classes.
 * <p>
 * It will generate implementations of given class and write it to file for given path.
 * </p>
 * All methods, which don't have valid implementations, will be added to implementation
 * and will return default value.
 *
 * @author Vladislav Kiryukhin
 */
public class Implementor implements JarImpler {
    /**
     * Token of implementable class given by user.
     */
    private Class<?> clazz = null;

    /**
     * Invoke {@link #implement(Class, Path)} or {@link #implementJar(Class, Path)} from command line with parameters
     *
     * @param args arguments from command line. For {@link #implement(Class, Path)} the argument is name of class we
     *             should generate implementation for. For {@link #implementJar(Class, Path)} the first argument is key
     *             "-jar", second is name of class we should generate implementation for, the third is name of jar file
     *             we should build.
     */
    public static void main(String[] args) {
        if (args == null || (args.length == 0)) {
            System.err.println("Wrong usage.");
            return;
        }

        try {
            if (args.length == 1) {
                if (args[0].equals("-jar")) {
                    System.err.println("Wrong usage.");
                } else {
                    new Implementor().implement(Class.forName(args[0]), new File(".").toPath());
                }
            } else {
                if (args[0].equals("-jar") && (args.length == 3 && args[1] != null && args[2] != null)) {
                    new Implementor().implementJar(Class.forName(args[1]), new File(args[2]).toPath());
                } else {
                    System.err.println("Wrong usage.");
                }
            }
        } catch (ClassNotFoundException e) {
            System.err.println("Couldn't find class/interface: " + e.getMessage());
        } catch (ImplerException e) {
            System.err.println("Error while implementing class: " + e.getMessage());
        }
    }

    @Override
    public void implement(Class<?> aClass, Path path) throws ImplerException {
        clazz = aClass;

        if (aClass == null || aClass.isPrimitive() || Modifier.isFinal(aClass.getModifiers())) {
            throw new ImplerException("Class cannot be implemented.");
        }

        try (BufferedWriter out = Files.newBufferedWriter(getPath(path))) {
            ClassImplementationBuilder cb = new ClassImplementationBuilder(clazz);
            out.write(cb.addPackage().addClassImplementation().toString());
        } catch (FileNotFoundException e) {
            throw new ImplerException("Couldn't open file: " + e.getMessage());
        } catch (IOException e) {
            throw new ImplerException("Error while writing class.");
        }
    }

    @Override
    public void implementJar(Class<?> aClass, Path jarFile) throws ImplerException {
        Path pathToImplClass;
        try {
            pathToImplClass = Files.createTempDirectory("tmp");
        } catch (IOException e) {
            throw new ImplerException("Couldn't create temporary dir.");
        }

        implement(aClass, pathToImplClass);
        JavaCompiler compiler = ToolProvider.getSystemJavaCompiler();
        try {
            if (compiler.run(null, null, null, getPath(pathToImplClass).toString()) != 0) {
                throw new ImplerException("Error while compiling.");
            }
        } catch (IOException e) {
            throw new ImplerException("Error while compiling.");
        }

        Manifest manifest = new Manifest();
        manifest.getMainAttributes().put(Attributes.Name.MANIFEST_VERSION, "1.0");
        try {
            Path pathToClassFile = changeExtension(getPath(pathToImplClass), ".java", ".class");
            try (JarOutputStream target = new JarOutputStream(new FileOutputStream(jarFile.toAbsolutePath().toString()), manifest);
                 InputStream input = Files.newInputStream(pathToClassFile)) {
                target.putNextEntry(new JarEntry(pathToImplClass.relativize(pathToClassFile).toString()));
                int count;
                byte[] buffer = new byte[1024];
                while ((count = input.read(buffer)) >= 0) {
                    target.write(buffer, 0, count);
                }
                target.closeEntry();
            }
        } catch (IOException e) {
            throw new ImplerException("Error while building jar: " + e.getMessage());
        }
    }

    /**
     * Class which contains methods for generating implementation of class/interface.
     */
    private class ClassImplementationBuilder {
        /**
         * Object of class {@link StringBuilder} which contains class implementation.
         */
        private StringBuilder sb;
        /**
         * Token of class we should implement.
         * @see ru.ifmo.ctddev.kiryukhin.implementor.Implementor#clazz
         */
        private Class<?> clazz;

        /**
         * Constructor for ClassImplementationBuilder.
         * @param aClass token of class we should implement.
         */
        ClassImplementationBuilder(Class<?> aClass) {
            sb = new StringBuilder();
            clazz = aClass;
        }

        /**
         * Add declaration of <code>package</code> to the generating class.
         * @return instance of {@link ru.ifmo.ctddev.kiryukhin.implementor.Implementor.ClassImplementationBuilder} with
         * <code>package</code> declaration.
         */
        private ClassImplementationBuilder addPackage() {
            if (clazz.getPackage() != null) {
                sb.append(String.format("package %s;\n\n", clazz.getPackage().getName()));
            }
            return this;
        }

        /**
         * Add implementation of class.
         * <p>
         * It adds class declaration and run {@link #addConstructors()} for adding constructors
         * and {@link #addMethods()} for adding methods.
         * </p>
         * @return instance of {@link ru.ifmo.ctddev.kiryukhin.implementor.Implementor.ClassImplementationBuilder} with
         * class implementation.
         * @throws ImplerException in case of impossibility to add constructors or methods.
         */
        private ClassImplementationBuilder addClassImplementation() throws ImplerException {
            sb.append(String.format("public class %sImpl %s %s {\n", clazz.getSimpleName(), (clazz.isInterface() ? "implements" : "extends"), clazz.getSimpleName()));
            this.addConstructors().addMethods();
            sb.append("}\n");
            return this;
        }

        /**
         * Add constructors of class.
         * <p>
         * It adds constructor to the generating class, if {@link #clazz} is a class.
         * If {@link #clazz} has default constructor, nothing is added
         * (because Java generates its own default constructor during compilation in this case).
         * </p>
         *
         * @return instance of {@link ru.ifmo.ctddev.kiryukhin.implementor.Implementor.ClassImplementationBuilder} with
         * constructors implementation.
         * @throws ImplerException if no possible constructors have been found
         */
        private ClassImplementationBuilder addConstructors() throws ImplerException {
            if (clazz.isInterface()) {
                return this;
            }

            Constructor<?> ctors[] = clazz.getDeclaredConstructors();

            for (Constructor ctor : ctors) {
                if (Modifier.isPublic(ctor.getModifiers()) || Modifier.isProtected(ctor.getModifiers())) {
                    if (ctor.getParameters().length == 0) {
                        return this;
                    }
                }
            }

            for (Constructor ctor : ctors) {
                if (!Modifier.isPrivate(ctor.getModifiers())) {
                    if (Modifier.isPublic(ctor.getModifiers())) {
                        sb.append("\tpublic ");
                    } else if (Modifier.isProtected(ctor.getModifiers())) {
                        sb.append("\tprotected ");
                    }

                    sb.append(String.format("%sImpl(%s) %s", clazz.getSimpleName(), getParametersRepresentation(ctor.getParameters()), getExceptionsRepresentation(ctor.getExceptionTypes())));
                    sb.append(String.format("{\n\t\tsuper(%s);\n\t}\n", getArgumentsRepresentation(ctor.getParameters())));

                    return this;
                }
            }
            throw new ImplerException("Error while adding ctors!");
        }

        /**
         * Wrapper for {@link Method}.
         * <p>
         * It overrides methods
         * {@link MethodWrapper#equals(Object)} and {@link MethodWrapper#hashCode()} for using in HashSet
         * </p>
         */
        private class MethodWrapper {
            /**
             * Wrapped method.
             */
            public Method method;

            /**
             * Constructor for wrapper.
             * @param m wrapped method
             */
            private MethodWrapper(Method m) {
                this.method = m;
            }

            /**
             * Hash for method using hashes of its name and parameters.
             * {@inheritDoc}
             */
            @Override
            public int hashCode() {
                int hash = method.getReturnType().hashCode() ^ method.getName().hashCode();
                for (Parameter param: method.getParameters()) {
                    hash ^= param.getType().hashCode();
                }
                return hash;
            }

            /**
             * Two methods are equals if they have equals names and types of parameters.
             * {@inheritDoc}
             */
            @Override
            public boolean equals(Object rhs) {
                if (!(rhs instanceof MethodWrapper)) {
                    return false;
                }

                Method unwrappedMethod = ((MethodWrapper) rhs).method;
                return method.getName().equals(unwrappedMethod.getName()) && Arrays.equals(method.getParameterTypes(), unwrappedMethod.getParameterTypes());
            }
        }

        /**
         * Collects all abstract methods from classes and interfaces which are super to {@link #clazz} to
         * the {@link java.util.List} <tt>list</tt>.
         * @param clazz class for which we must collect methods.
         * @return list {@link java.util.List} with abstract methods.
         */
        private List<Method> collectMethodsForImplementation(Class<?> clazz) {
            Set<MethodWrapper> abstractMethods = new HashSet<>();

            if (clazz == null || !Modifier.isAbstract(clazz.getModifiers())) {
                return Collections.emptyList();
            }

            for (Method m : clazz.getMethods()) {
                if (Modifier.isAbstract(m.getModifiers())) {
                    abstractMethods.add(new MethodWrapper(m));
                }
            }

            while (clazz != null) {
                if (!Modifier.isAbstract(clazz.getModifiers())) {
                    break;
                }

                for (Method m : clazz.getDeclaredMethods()) {
                    abstractMethods.add(new MethodWrapper(m));
                }
                clazz = clazz.getSuperclass();
            }

            abstractMethods.removeIf(method -> !Modifier.isAbstract(method.method.getModifiers()));
            return abstractMethods.stream().map(wrapper -> wrapper.method).collect(Collectors.toList());
        }

        /**
         * Add methods of class.
         * <p>
         * It collects all methods we should implement and call {@link #addMethod(Method)} for everyone of them.
         * </p>
         * @return instance of {@link ru.ifmo.ctddev.kiryukhin.implementor.Implementor.ClassImplementationBuilder} with
         * methods.
         */
        private ClassImplementationBuilder addMethods() {
            List<Method> abstractMethods = collectMethodsForImplementation(clazz);
            abstractMethods.forEach(this::addMethod);
            return this;
        }

        /**
         * Add method.
         * @param method {@link Method} method that we should add to class implementation
         * @return instance of {@link ru.ifmo.ctddev.kiryukhin.implementor.Implementor.ClassImplementationBuilder} with
         * given method.
         */
        private ClassImplementationBuilder addMethod(Method method) {
            sb.append("\n\t");
            sb.append(Modifier.toString(((method.getModifiers() & Modifier.methodModifiers()) & (~Modifier.ABSTRACT)))).append(" ");

            if (method.getReturnType().isArray()) {
                sb.append(method.getReturnType().getComponentType().getName()).append("[] ");
            } else {
                sb.append(method.getReturnType().getName()).append(" ");
            }
            sb.append(String.format("%s(%s) %s", method.getName(), getParametersRepresentation(method.getParameters()), getExceptionsRepresentation(method.getExceptionTypes())));

            if (Modifier.isNative(method.getModifiers())) {
                sb.append(";\n\n");
            } else {
                sb.append(String.format(" {\n\t\treturn %s;\n\t}\n", getDefaultType(method.getReturnType())));
            }

            return this;
        }

        /**
         * Return string representation of parameters.
         * @param parameters array of parameters {@link Parameter}.
         * @return {@link String} string representation of method's parameters.
         */
        private String getParametersRepresentation(Parameter[] parameters) {
            if (parameters.length != 0) {
                StringBuilder sb = new StringBuilder();
                for (int i = 0; i < parameters.length; i++) {
                    sb.append(String.format("%s %s", parameters[i].getType().getCanonicalName(), parameters[i].getName()));
                    if (i != parameters.length - 1) {
                        sb.append(", ");
                    }
                }
                return sb.toString();
            }
            return "";
        }

        /**
         * Return string representation of arguments.
         * @param parameters array of parameters {@link Parameter}.
         * @return {@link String} string representation of method's arguments.
         */
        private String getArgumentsRepresentation(Parameter[] parameters) {
            if (parameters.length != 0) {
                StringBuilder sb = new StringBuilder();
                sb.append(parameters[0].getName());
                for (int i = 1; i < parameters.length; i++) {
                    sb.append(String.format(", %s", parameters[i].getName()));
                }
                return sb.toString();
            }
            return "";
        }

        /**
         * Return string representation of exceptions.
         * @param exceptions array of exceptions {@link Class}.
         * @return {@link String} string representation of method's exceptions.
         */
        private String getExceptionsRepresentation(Class<?>[] exceptions) {
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < exceptions.length; i++) {
                if (i > 0) {
                    sb.append(", ");
                } else {
                    sb.append("throws ");
                }
                sb.append(exceptions[i].getName());
            }
            return sb.toString();
        }

        /**
         * Returns default values for primitive types, <code>null</code>,
         * for other types and nothing for <code>void</code>.
         * @param type type class token we want to get default value for.
         * @return default value of this type.
         */
        private String getDefaultType(Class type) {
            if (type.equals(void.class)) {
                return "";
            } else if (!type.isPrimitive()) {
                return "null";
            } else if (type.equals(boolean.class)) {
                return "false";
            } else {
                return "0";
            }
        }

        /**
         * @see StringBuilder#toString()
         */
        @Override
        public String toString() {
            return sb.toString();
        }
    }

    /**
     * Replace filename extension in filepath.
     * @param f given filepath.
     * @param old old filename extension.
     * @param nw new filename extension.
     * @return path with new extension if given filepath contained old extension,
     * otherwise given filepath.
     */
    private Path changeExtension(Path f, String old, String nw) {
        if (f.toString().endsWith(old)) {
            String p = f.toString();
            f = new File((p.substring(0, p.lastIndexOf(old)) + nw)).toPath();
            return f;
        }
        return f;
    }

    /**
     * Create necessary directories and return full path for class by given root directory.
     *
     * @param root root directory.
     * @return full path for java class.
     * @throws IOException in case of impossibility to create directories.
     */
    private Path getPath(Path root) throws IOException {
        if (clazz.getPackage() != null) {
            Path p = Paths.get(root.toString(), clazz.getPackage().getName().replace('.', File.separatorChar) + File.separator);
            Files.createDirectories(p);
            root = p;
        }
        return Paths.get(root.toString(), clazz.getSimpleName() + "Impl.java");
    }

    /**
     * Default constructor.
     */
    public Implementor() {
        super();
    }

}
