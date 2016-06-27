import java.io.*;
import java.util.*;

public class Queuemin2 {
    FastScanner in;
    PrintWriter out;

    public class Dequeue {

        private int size = 0;
        private int[] elements = new int[30000001];
        private int head = 0, tail = 0;

        public void enqueue(int e) {
            //ensureCapacity(size + 1);
            elements[tail] = e;
            tail = nextElement(tail);
            size++;
        }

        public void push(int e) {
            //ensureCapacity(size + 1);
            size++;
            head = prevElement(head);
            elements[head] = e;
        }

        public int remove() {
            assert size > 0;

            tail = prevElement(tail);
            int lastElement = elements[tail];
            size--;

            return lastElement;
        }

        public int dequeue() {
            assert size > 0;

            int firstElement = elements[head];
            size--;
            head = nextElement(head);
            return firstElement;
        }

        public int element() {
            assert size > 0;

            return elements[head];
        }

        public int peek() {
            assert size > 0;

            return elements[prevElement(tail)];
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
            elements = new int[30000001];
        }

        private int nextElement(int cur) {
            return (cur + 1) % elements.length;
        }

        private int prevElement(int cur) {
            return (cur - 1 < 0 ? elements.length - 1 : cur - 1);
        }

    }

    public class Queue {
        private Dequeue q = new Dequeue();
        private int size = 0;

        void enqueue(int value) {
            while (!q.isEmpty() && q.peek() > value) {
                q.remove();
            }
            q.enqueue(value);
            size++;
        }

        void dequeue(int removed_element) {
            if (!q.isEmpty() && q.element() == removed_element) {
                q.dequeue();
            }
            size--;
        }

        int size() {
            return size;
        }

        int min() {
            return q.element();
        }

    }

    public void solve() throws IOException {
        Queue q = new Queue();
        int n = in.nextInt();
        int m = in.nextInt();
        int k = in.nextInt();
        int a = in.nextInt();
        int b = in.nextInt();
        int c = in.nextInt();
        int x = 0, y = 0, readed = 0, pm = 0;
        int[] ka = new int[k];
        for (int i = 0; i < k; i++) {
            ka[i] = in.nextInt();
        }
        for (int i = 0; i < Math.min(k, m); i++) {
            int val = ka[i];
            if (i == k - 2) {
                x = val;
            } else if (i == k - 1) {
                y = val;
            }
            readed++;
            q.enqueue(val);
        }
        while (q.size() < m) {
            int newValue;
            if (readed < k) {
                newValue = ka[readed - 1];
                readed++;
            } else {
                newValue = a * x + b * y + c;
            }
            x = y;
            y = newValue;
            q.enqueue(newValue);
        }
        long ans = 0;
        int mx = 0, my = 0;
        for (int i = m; i <= n; i++) {
            ans += q.min();
            //System.out.println("min: " + q.min());
            if (i - m < k) {
                //System.out.println(ka[i - m]);
                q.dequeue(ka[i - m]);
            } else {
                if (i - m == k) {
                    int oldValue = a * ka[k - 2] + b * ka[k - 1] + c;
                    q.dequeue(oldValue);
                    my = oldValue;
                } else if (i - m == k + 1) {
                    int oldValue = a * ka[k - 1] + b * my + c;
                    q.dequeue(oldValue);
                    mx = my;
                    my = oldValue;
                } else {
                    int oldValue = a * mx + b * my + c;
                    q.dequeue(oldValue);
                    mx = my;
                    my = oldValue;
                }
            }
            int newValue;
            if (readed < k) {
                newValue = ka[readed];
                readed++;
            } else {
                newValue = a * x + b * y + c;
            }
            x = y;
            y = newValue;
            //System.out.println("enq: " + newValue);
            q.enqueue(newValue);
        }
        out.println(ans);
    }


    public void run() {
        try {
            in = new FastScanner(new File("queuemin2.in"));
            out = new PrintWriter(new File("queuemin2.out"));

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
        new Queuemin2().run();
    }
}