import java.util.*;
import java.io.*;

public class Solution {
    FastScanner in;
    PrintWriter out;

    public class Stack {
        public class Node {
            public Node next;
            public int value;

            public Node(int value, Node next) {
                this.next = next;
                this.value = value;
            }
        }

        private Node stack;
        private int size;

        void push(int value) {
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

        int pop() {
            int result = stack.value;
            stack = stack.next;
            return result;
        }
    }

    public void solve() throws IOException {
        Stack s = new Stack();
        int m = in.nextInt();
        for (int i = 0; i < m; i++) {
            char c = in.next().charAt(0);
            if (c == '-') {
                out.println(s.pop());
            } else {
                s.push(in.nextInt());
            }
        }
    }

    public void run() {
        try {
            in = new FastScanner(new File("stack2.in"));
            out = new PrintWriter(new File("stack2.out"));

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
        new Solution().run();
    }
}