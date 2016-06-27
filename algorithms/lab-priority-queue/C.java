import java.io.*;
import java.util.ArrayList;
import java.util.Map;
import java.util.StringTokenizer;

public class Priorityqueue {
    FastScanner in;
    PrintWriter out;

    class PQueue {
        int size = 0;
        Integer heap[] = new Integer[600001];
        Integer pos[] = new Integer[600001];
        ArrayList<Integer> id = new ArrayList<>();

        void buildHeap() {
            for (int i = size / 2; i > 0; i--) {
                siftDown(i);
            }
        }

        void swap(int i, int j) {
            pos[id.get(i)] = j;
            pos[id.get(j)] = i;
            Integer tmp = heap[i];
            heap[i] = heap[j];
            heap[j] = tmp;
            tmp = id.get(i);
            id.set(i, id.get(j));
            id.set(j, tmp);
        }

        void siftDown(int i) {
            while (2 * i + 1 < size) {
                int j = 2 * i + 1;
                if (2 * i + 2 < size && heap[2 * i + 2] < heap[2 * i + 1]) {
                    j = 2 * i + 2;
                }
                if (heap[i] <= heap[j]) {
                    break;
                }
                swap(i, j);
                i = j;
            }
        }

        void siftUp(int i) {
            while (heap[i] < heap[(i - 1) / 2]) {
                swap(i, (i - 1) / 2);
                i = (i - 1) / 2;
            }
        }

        void insert(int key, int p) {
            heap[size] = key;
            pos[p] = size;
            id.add(p);
            //System.out.println(key + " " + p + " " + (size + 1));
            size++;
            siftUp(size - 1);
        }

        int extractMinimum() {
            int min = heap[0];
            size--;
            heap[0] = heap[size];
            //size--;
            id.remove(id.size() - 1);
            siftDown(0);
            return min;
        }

        boolean isEmpty() {
            return (size == 0);
        }

        void decreaseKey(int oldKey, int newKey) {
            int posKey = pos[oldKey];
            heap[posKey] = newKey;
            siftUp(posKey);
            siftDown(posKey);
        }

    }

    public void solve() throws IOException {
        PQueue q = new PQueue();
        String command;
        int c = 0;
        while (true) {
            try {
                command = in.next();
            } catch (Exception e) {
                break;
            }
            //System.out.println(command + " " + c);
            if (command.equals("push")) {
                int a = in.nextInt();
                q.insert(a, c);
            } else if (command.equals("extract-min")) {
                if (q.isEmpty()) {
                    out.println("*");
                } else {
                    out.println(q.extractMinimum());
                }
            } else if (command.equals("decrease-key")) {
                int a = in.nextInt(), b = in.nextInt();
                q.decreaseKey(--a, b);
            }
            c++;
        }
    }

    public void run() {
        try {
            in = new FastScanner(new File("priorityqueue.in"));
            out = new PrintWriter(new File("priorityqueue.out"));

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
        new Priorityqueue().run();
    }
}