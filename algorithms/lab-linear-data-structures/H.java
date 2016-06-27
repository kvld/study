import java.util.*;
import java.io.*;

public class Quack {
    FastScanner in;
    PrintWriter out;

    long[] queue = new long[10000000];
    long[] register = new long[26];
    String[] commands = new String[100000];
    String[] labelsName = new String[100000];
    int[] labelsPoint = new int[100000];
    int labelsCount = 0;
    int head = 0;
    int tail = 0;
    int commandsSize = 0;

    public long modulo(long x) {
        return (x + 65536L) % 65536L;
    }

    public void put(long element) {
        queue[tail] = element;
        tail++;
        if (tail == queue.length) {
            tail = 0;
        }
    }

    public long get() {
        long res = queue[head];
        head++;
        if (head == queue.length) {
            head = 0;
        }
        return res;
    }

    public void add() {
        long x = get(), y = get();
        put(modulo(modulo(x) + modulo(y)));
    }

    public void sub() {
        long x = get(), y = get();
        put(modulo(modulo(x) - modulo(y)));
    }

    public void mul() {
        long x = get(), y = get();
        long mult = modulo(modulo(x) * modulo(y));
        put((int)mult);
    }

    public void div() {
        long x = get(), y = get();
        if (x == 0 && y == 0) {
            put(0);
        } else {
            put(modulo(modulo(x) / modulo(y)));
        }
    }

    public void mod() {
        long x = get(), y = get();
        if (x == 0 && y == 0) {
            put(0);
        } else {
            put(modulo(x % y));
        }
    }

    public void putToRegister(String reg) {
        register[reg.charAt(0) - 'a'] = get();
    }

    public void getFromRegister(String reg) {
        put(register[reg.charAt(0) - 'a']);
    }

    public void print(String reg) {
        if (reg.isEmpty()) {
            out.println(get());
        } else {
            out.println(register[reg.charAt(0) - 'a']);
        }
    }

    public void cprint(String reg) {
        if (reg.isEmpty()) {
            out.print((char) (get() % 256L));
        } else {
            out.print((char) (register[reg.charAt(0) - 'a'] % 256L));
        }
    }

    public int findLabel(String label) {
        for (int i = 0; i < labelsCount; i++) {
            if (labelsName[i].equals(label)) {
                return labelsPoint[i];
            }
        }
        return -1;
    }

    public void solve() throws IOException {
        String command;
        while (true) {
            try {
                command = in.next();
                if (command.startsWith(":")) {
                    labelsName[labelsCount] = command.substring(1);
                    labelsPoint[labelsCount] = commandsSize;
                    labelsCount++;
                }
                commands[commandsSize++] = command;
            } catch (Exception e) {
                break;
            }
        }
        for (int i = 0; i < commandsSize; i++) {
            if (commands[i].startsWith("J")) {
                commands[i] = "J" + findLabel(commands[i].substring(1));
            } else if (commands[i].startsWith("Z")) {
                commands[i] = "Z" + commands[i].charAt(1) + findLabel(commands[i].substring(2));
            } else if (commands[i].startsWith("E")) {
                commands[i] = "E" + commands[i].charAt(1) + commands[i].charAt(2) + findLabel(commands[i].substring(3));
            } else if (commands[i].startsWith("G")) {
                commands[i] = "G" + commands[i].charAt(1) + commands[i].charAt(2) + findLabel(commands[i].substring(3));
            }
        }
        int currentCommandNum = 0;
        while (currentCommandNum < commandsSize) {
            //System.out.println(currentCommandNum+1 + " " + commands[currentCommandNum]);
            command = commands[currentCommandNum++];
            if (command.equals("+")) {
                add();
            } else if (command.equals("-")) {
                sub();
            } else if (command.equals("*")) {
                mul();
            } else if (command.equals("/")) {
                div();
            } else if (command.equals("%")) {
                mod();
            } else if (command.startsWith(">")) {
                putToRegister(command.substring(1));
            } else if (command.startsWith("<")) {
                getFromRegister(command.substring(1));
            } else if (command.startsWith("P")) {
                print(command.substring(1));
            } else if (command.startsWith("C")) {
                cprint(command.substring(1));
            } else if (command.startsWith(":")) {
                // label - ignore
            } else if (command.startsWith("J")) {
                // jump
                currentCommandNum = Integer.parseInt(command.substring(1));
            } else if (command.startsWith("Z")) {
                char reg = command.charAt(1);
                if (register[reg - 'a'] == 0) {
                    currentCommandNum = Integer.parseInt(command.substring(2));
                }
            } else if (command.startsWith("E")) {
                char reg1 = command.charAt(1);
                char reg2 = command.charAt(2);
                //System.out.println(register[reg1 - 'a'] + " " + register[reg2 - 'a']);
                if (register[reg1 - 'a'] == register[reg2 - 'a']) {
                    currentCommandNum = Integer.parseInt(command.substring(3));
                }
            } else if (command.startsWith("G")) {
                char reg1 = command.charAt(1);
                char reg2 = command.charAt(2);
                //System.out.println(register[reg1 - 'a'] + " " + register[reg2 - 'a']);
                if (register[reg1 - 'a'] > register[reg2 - 'a']) {
                    currentCommandNum = Integer.parseInt(command.substring(3));
                }
            } else if (command.startsWith("Q")) {
                return;
            } else {
                // number
                put(modulo(Long.parseLong(command)));
            }
        }
    }

    public void run() {
        try {
            in = new FastScanner(new File("quack.in"));
            out = new PrintWriter(new File("quack.out"));

            solve();

            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    class FastScanner {
        BufferedReader br;
        StringTokenizer st;

        FastScanner(File f) {
            try {
                br = new BufferedReader(new FileReader(f));
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
        }

        String next() {
            while (st == null || !st.hasMoreTokens()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }

        int nextInt() {
            return Integer.parseInt(next());
        }
    }

    public static void main(String[] arg) {
        new Quack().run();
    }
}