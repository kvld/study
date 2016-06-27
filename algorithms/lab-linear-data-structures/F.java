import javafx.util.Pair;

import java.io.*;
import java.util.StringTokenizer;

 public class Postfix {
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

        void push(Object value) {
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
        String symbol;
        Stack s = new Stack();
        while (true) {
            try {
                symbol = in.next();
            } catch (NullPointerException e) {
                break;
            }
            if (symbol.equals("+") || symbol.equals("-") || symbol.equals("*")) {
                int x = Integer.parseInt((String)s.pop());
                int y = Integer.parseInt((String) s.pop());
                if (symbol.equals("+")) {
                    s.push(Integer.toString(x + y));
                } else if (symbol.equals("-")) {
                    s.push(Integer.toString(y - x));
                } else {
                    s.push(Integer.toString(x * y));
                }
            } else {
                s.push(symbol);
            }
        }
        out.println(Integer.parseInt((String)s.pop()));
    }

    public void run() {
        try {
            in = new FastScanner(new File("postfix.in"));
            out = new PrintWriter(new File("postfix.out"));

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
        new Postfix().run();
    }
}