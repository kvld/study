import java.util.*;
import java.io.*;

public class Crypto {
    FastScanner in;
    PrintWriter out;

    class Matrix {
        int a, b, c, d;

        Matrix(int a, int b, int c, int d) {
            this.a = a;
            this.b = b;
            this.c = c;
            this.d = d;
        }

        boolean isIdentity() {
            return (this.a == 1 && this.d == 1 && this.b == 0 && this.c == 0);
        }

        boolean isZero() {
            return (this.a == 0 && this.b == 0 && this.c == 0 && this.d == 0);
        }

        Matrix multiply(Matrix y, int modulo) {
            if (this.isZero() || y.isZero()) {
                return new Matrix(0, 0, 0, 0);
            }
            if (this.isIdentity()) {
                return y;
            } else if (y.isIdentity()) {
                return this;
            }
            int za = (this.a * y.a + this.b * y.c) % modulo;
            int zb = (this.a * y.b + this.b * y.d) % modulo;
            int zc = (this.c * y.a + this.d * y.c) % modulo;
            int zd = (this.c * y.b + this.d * y.d) % modulo;
            return new Matrix(za, zb, zc, zd);
        }

        void print() {
            out.println(this.a + " " + this.b);
            out.println(this.c + " " + this.d);
        }
    }

    class SegmentTree {
        Matrix tree[];
        int maxSize;
        int modulo;

        SegmentTree(int size, int modulo) {
            Matrix atree[] = new Matrix[4 * size];
            tree = atree;
            maxSize = size;
            this.modulo = modulo;
        }

        void build(Matrix a[]) {
            build(a, 0, 0, maxSize - 1);
        }

        void build(Matrix a[], int i, int tl, int tr) {
            if (tl == tr) {
                tree[i] = a[tl];
            } else {
                int mid = (tl + tr) / 2;
                build(a, 2 * i + 1, tl, mid);
                build(a, 2 * i + 2, mid + 1, tr);
                tree[i] = tree[2 * i + 1].multiply(tree[2 * i + 2], this.modulo);
            }
        }

        Matrix get(int l, int r) {
            return get(l, r, 0, 0, maxSize - 1);
        }

        Matrix get(int cl, int cr, int i, int l, int r) {
            if (cl <= l && r <= cr) {
                return tree[i];
            }
            if (r < cl || cr < l) {
                return new Matrix(1, 0, 0, 1);
            }
            int mid = (l + r) / 2;
            Matrix a = get(cl, cr, 2 * i + 1, l, mid);
            Matrix b = get(cl, cr, 2 * i + 2, mid + 1, r);
            return a.multiply(b, this.modulo);
        }

        void update(int index, Matrix delta) {
            update(index, delta, 0, 0, maxSize - 1);
        }

        void update(int index, Matrix delta, int i, int l, int r) {
            if (l == r) {
                tree[i] = delta;
                return;
            }
            int mid = (l + r) / 2;
            if (index <= mid) {
                update(index, delta, 2 * i + 1, l, mid);
            } else {
                update(index, delta, 2 * i + 2, mid + 1, r);
            }
            tree[i] = tree[2 * i + 1].multiply(tree[2 * i + 2], this.modulo);
        }
    }


    public void solve() throws IOException {
        int r = in.nextInt();
        int n = in.nextInt();
        int m = in.nextInt();
        Matrix inm[] = new Matrix[n];
        SegmentTree t = new SegmentTree(n, r);
        for (int i = 0; i < n; i++) {
            int a = in.nextInt(), b = in.nextInt(), c = in.nextInt(), d = in.nextInt();
            inm[i] = new Matrix(a, b, c, d);
        }
        t.build(inm);
        for (int i = 0; i < m; i++) {
            int x = in.nextInt();
            int y = in.nextInt();
            t.get(--x, --y).print();
            out.println();
        }
    }

    public void run() {
        try {
            in = new FastScanner(new File("crypto.in"));
            out = new PrintWriter(new File("crypto.out"));

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
        new Crypto().run();
    }
}