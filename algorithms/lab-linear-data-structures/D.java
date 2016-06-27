import java.io.*;
import java.util.StringTokenizer;

public class Queue2 {
    FastScanner in;
    PrintWriter out;

    public class Queue {
        private int size = 0;
        private Node head;
        private Node tail;

        private class Node {
            public int value;
            public Node next;

            public Node(int value, Node next) {
                this.value = value;
                this.next = next;
            }
        }

        public void enqueue(int element) {
            Node oldLast = tail;
            tail = new Node(element, null);
            if (size == 0) {
                head = tail;
            } else {
                oldLast.next = tail;
            }
            size++;
        }

        public int element() {
            return head.value;
        }

        public int dequeue() {
            int result = head.value;
            head = head.next;
            size--;
            if (size == 0) {
                tail = null;
            }
            return result;
        }

        public void clear() {
            size = 0;
            head = null;
            tail = null;
        }
    }

    public void solve() throws IOException {
        Queue q = new Queue();
        int m = in.nextInt();
        for (int i = 0; i < m; i++) {
            char c = in.next().charAt(0);
            if (c == '-') {
                out.println(q.element());
                q.dequeue();
            } else {
                q.enqueue(in.nextInt());
            }
        }
    }

    public void run() {
        try {
            in = new FastScanner(new File("queue2.in"));
            out = new PrintWriter(new File("queue2.out"));

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
        new Queue2().run();
    }
}