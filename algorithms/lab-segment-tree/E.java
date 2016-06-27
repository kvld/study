import java.util.*;
import java.io.*;

public class ParkingST {
    FastScanner in;
    PrintWriter out;

    class SegmentTree {
        int tree[];
        int maxSize;

        SegmentTree(int size) {
            int atree[] = new int[4 * size];
            tree = atree;
            maxSize = size;
        }

        void updateMin(int index, int delta) {
            updateMin(index, delta, 0, 0, maxSize - 1);
        }

        int getMin(int l, int r) {
            return getMin(l, r, 0, 0, maxSize - 1);
        }

        int getMin(int cl, int cr, int i, int l, int r) {
            if (cl <= l && r <= cr) {
                return tree[i];
            }
            if (r < cl || cr < l) {
                return Integer.MAX_VALUE;
            }
            int mid = (l + r) / 2;
            return Math.min(getMin(cl, cr, 2 * i + 1, l, mid), getMin(cl, cr, 2 * i + 2, mid + 1, r));
        }

        void updateMin(int index, int delta, int i, int l, int r) {
            if (l == r) {
                tree[i] = delta;
                return;
            }
            int mid = (l + r) / 2;
            if (index <= mid) {
                updateMin(index, delta, 2 * i + 1, l, mid);
            } else {
                updateMin(index, delta, 2 * i + 2, mid + 1, r);
            }
            tree[i] = Math.min(tree[2 * i + 1], tree[2 * i + 2]);
        }
    }

    public void solve() throws IOException {
        int n = in.nextInt();
        SegmentTree t = new SegmentTree(n);
        for (int i = 0; i < n; i++) {
            t.updateMin(i, i);
        }
        int m = in.nextInt();
        for (int i = 0; i < m; i++) {
            String command = in.next();
            int arg = in.nextInt() - 1;
            if (command.equals("enter")) {
                int q = t.getMin(arg, n - 1);
                if (q == Integer.MAX_VALUE) {
                    q = t.getMin(0, n - 1);
                }
                out.println(q + 1);
                t.updateMin(q, Integer.MAX_VALUE);
            } else if (command.equals("exit")) {
                t.updateMin(arg, arg);
            }
        }
    }

    public void run() {
        try {
            in = new FastScanner(new File("parking.in"));
            out = new PrintWriter(new File("parking.out"));

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
        new ParkingST().run();
    }
}