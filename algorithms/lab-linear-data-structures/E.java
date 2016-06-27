import java.io.*;
import java.util.StringTokenizer;

public class Brackets {
    FastScanner in;
    PrintWriter out;

    public class Stack {
        public class Node {
            public Node next;
            public Object value;

            public Node(Object value, Node next) {
                this.next = next;
                this.value = value;
            }
        }

        private Node stack;
        private int size;

        public void push(Object value) {
            if (size == 0) {
                Node newNode = new Node(value, null);
                stack = newNode;
                size++;
            } else {
                size++;
                Node newNode = new Node(value, stack);
                stack = newNode;
            }
        }

        int size() {
            return size;
        }

        Object pop() {
            size--;
            Object result = stack.value;
            stack = stack.next;
            return result;
        }
    }

    public void solve() throws IOException {
        String sequence;
        while (true) {
            try {
                sequence = in.next();
            } catch (NullPointerException e) {
                break;
            }
            Stack s = new Stack();
            for (int i = 0; i < sequence.length(); i++) {
                if (sequence.charAt(i) == '(' || sequence.charAt(i) == '[') {
                    s.push(sequence.charAt(i));
                } else {
                    if (s.size() == 0) {
                        out.println("NO");
                        break;
                    }
                    char lastBracket = (char)s.pop();
                    if ((sequence.charAt(i) == ']' && lastBracket != '[') || (sequence.charAt(i) == ')' && lastBracket != '(')) {
                        out.println("NO");
                        break;
                    }
                }
                if (i == sequence.length() - 1) {
                    out.println(s.size() == 0 ? "YES" : "NO");
                }
            }
        }
    }

    public void run() {
        try {
            in = new FastScanner(new File("brackets.in"));
            out = new PrintWriter(new File("brackets.out"));

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
        new Brackets().run();
    }
}