import java.io.*;
import java.util.StringTokenizer;

public class Isheap {
    FastScanner in;
    PrintWriter out;

    public void solve() throws IOException {
        int n = in.nextInt();
        int a[] = new int[n];
        for (int i = 0; i < n; i++) {
            a[i] = in.nextInt();
        }
        for (int i = 0; i < n; i++) {
            if ((2 * i + 1 < n) && (a[2 * i + 1] <= a[i])) {
                out.println("NO");
                return;
            }
            if ((2 * i + 2 < n) && (a[2 * i + 2] <= a[i])) {
                out.println("NO");
                return;
            }
        }
        out.println("YES");
    }

    public void run() {
        try {
            in = new FastScanner(new File("isheap.in"));
            out = new PrintWriter(new File("isheap.out"));

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
        new Isheap().run();
    }
}