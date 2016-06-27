package ru.ifmo.ctddev.kiryukhin.walk;

import java.io.*;
import java.nio.file.*;
import java.nio.file.attribute.BasicFileAttributes;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class RecursiveWalk {

    public static final String NULL_HASH = "00000000000000000000000000000000";

    private static String getFileHash(Path path) {
        try {
            MessageDigest digest = MessageDigest.getInstance("MD5");
            digest.reset();

            try (InputStream is = new FileInputStream(path.toFile().getAbsoluteFile())) {
                byte[] buffer = new byte[1024];
                int numBytes;
                while ((numBytes = is.read(buffer)) != -1) {
                    digest.update(buffer, 0, numBytes);
                }

                StringBuilder sb = new StringBuilder();
                for (byte b : digest.digest()) {
                    sb.append(String.format("%02X", b));
                }
                return sb.toString();
            } catch (IOException e) {
                System.err.println("I/O error occurred while calculating hash value: " + e.getMessage());
            }
        } catch (NoSuchAlgorithmException e) {
            System.err.println(e.getMessage());
        }
        return null;
    }


    public static void main(String[] args) {

        try (BufferedReader br = new BufferedReader(new FileReader(args[0]))) {
            try (BufferedWriter bw = new BufferedWriter(new FileWriter(args[1]))) {
                String path;
                SimpleFileVisitor<Path> visitor = new SimpleFileVisitor<Path>() {
                    @Override
                    public FileVisitResult visitFile(Path file, BasicFileAttributes attrs) {
                        String hash = RecursiveWalk.getFileHash(file);
                        try {
                            bw.write(hash + " " + file.toFile().getPath() + "\n");
                        } catch (IOException e) {
                            System.err.print("I/O error occurred while writing in output file: " + e.getMessage());
                        }
                        return FileVisitResult.CONTINUE;
                    }

                    @Override
                    public FileVisitResult visitFileFailed(Path file, IOException exc) {
                        try {
                            bw.write(NULL_HASH + " " + file.toFile().getPath() + "\n");
                        } catch (IOException e) {
                            System.err.print("I/O error occurred while writing in output file: " + e.getMessage());
                        }
                        return FileVisitResult.CONTINUE;
                    }
                };

                while ((path = br.readLine()) != null) {
                    Files.walkFileTree(Paths.get(path), visitor);
                }
            } catch (IOException e) {
                System.err.println("I/O error occurred while reading: " + e.getMessage());
            }
        } catch (IOException e) {
            System.err.println("I/O error occurred while writing: " + e.getMessage());
        }
    }
}
