import java.io.*;
import java.util.StringTokenizer;

public class Queue1 {
    FastScanner in;
    PrintWriter out;

    public class Queue {
        private int size = 0;
        private int elements[] = new int[5];
        private int head = 0, tail = 0;

        public void enqueue(int e) {
            ensureCapacity(size + 1);
            elements[tail] = e;
            tail = nextElement(tail);
            size++;
        }

        public Object dequeue() {
            assert size > 0;

            shrinkCapacity(size);
            Object firstElement = elements[head];
            size--;
            head = nextElement(head);
            return firstElement;
        }

        public Object element() {
            assert size > 0;

            return elements[head];
        }

        public int size() {
            return size;
        }

        public boolean isEmpty() {
            return (size == 0);
        }

        public void clear() {
            head = 0;
            tail = 0;
            size = 0;
            elements = new int[5];
        }

        private void ensureCapacity(int capacity) {
            if (capacity <= elements.length) {
                return;
            }

            int[] newElements = new int[2 * capacity];
            for (int i = head; i < head + size; i++) {
                newElements[i - head] = elements[i % elements.length];
            }
            elements = newElements;
            head = 0;
            tail = size;
        }

        private void shrinkCapacity(int capacity) {
            if (4 * capacity > elements.length) {
                return;
            }
            int[] newElements = new int[capacity + 1];
            for (int i = head; i < head + size; i++) {
                newElements[i - head] = elements[i % elements.length];
            }
            elements = newElements;
            head = 0;
            tail = size;
        }

        private int nextElement(int cur) {
            return (cur + 1) % elements.length;
        }

        private int prevElement(int cur) {
            return (cur - 1 < 0 ? elements.length - 1 : cur - 1);
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
            in = new FastScanner(new File("queue1.in"));
            out = new PrintWriter(new File("queue1.out"));

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
        new Queue1().run();
    }
}