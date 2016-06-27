import javax.swing.text.Segment;
import java.util.*;
import java.io.*;

public class RSQ {
    FastScanner in;
    PrintWriter out;

    class SegmentTree {
        long tree[];
        int maxSize;

        SegmentTree(int size) {
            long atree[] = new long[4 * size];
            tree = atree;
            maxSize = size;
        }

        void updateSum(int index, long delta) {
            updateSum(index, delta, 0, 0, maxSize - 1);
        }

        long getSum(int l, int r) {
            return getSum(l, r, 0, 0, maxSize - 1);
        }

        long getSum(int cl, int cr, int i, int l, int r) {
            if (cl <= l && r <= cr) {
                return tree[i];
            }
            if (r < cl || cr < l) {
                return 0;
            }
            int mid = (l + r) / 2;
            return getSum(cl, cr, 2 * i + 1, l, mid) + getSum(cl, cr, 2 * i + 2, mid + 1, r);
        }

        void updateSum(int index, long delta, int i, int l, int r) {
            if (l == r) {
                tree[i] = delta;
                return;
            }
            int mid = (l + r) / 2;
            if (index <= mid) {
                updateSum(index, delta, 2 * i + 1, l, mid);
            } else {
                updateSum(index, delta, 2 * i + 2, mid + 1, r);
            }
            tree[i] = tree[2 * i + 1] + tree[2 * i + 2];
        }
    }

    public void solve() throws IOException {
        int n = in.nextInt();
        SegmentTree t = new SegmentTree(n + 1);
        for (int i = 0; i < n; i++) {
            int tmp = in.nextInt();
            t.updateSum(i, tmp);
        }
        String command;
        while (true) {
            try {
                command = in.next();
            } catch (Exception e) {
                break;
            }
            int x = in.nextInt();
            if (command.equals("set")) {
                long y = in.nextLong();
                t.updateSum(--x, y);
            } else if (command.equals("sum")) {
                int y = in.nextInt();
                out.println(t.getSum(--x, --y));
            }
        }
    }

    public void run() {
        try {
            in = new FastScanner(new File("rsq.in"));
            out = new PrintWriter(new File("rsq.out"));

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

        long nextLong() { return Long.parseLong(next()); }
    }

    public static void main(String[] arg) {
        new RSQ().run();
    }
}