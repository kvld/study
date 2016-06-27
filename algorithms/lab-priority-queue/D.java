import java.io.*;
import java.util.StringTokenizer;

public class Parking {
    FastScanner in;
    PrintWriter out;

    int parent[] = new int[600_002];

    void makeSet(int v) {
        parent[v] = v;
    }

    int findSet(int v) {
        if (v == parent[v]) {
            return v;
        }
        return parent[v] = findSet(parent[v]);
    }

    int unionWithNext(int v, int n) {
        int find = findSet(v);
        parent[find] = findSet(next(find, n));
        return find;
    }

    int next(int v, int n) {
        return (v + 1 > n) ? 1 : v + 1;
    }

    public void solve() throws IOException {
        int n = in.nextInt();
        for (int i = 0; i < n; i++) {
            makeSet(i + 1);
        }
        for (int i = 0; i < n; i++) {
            int t = in.nextInt();
            out.print(unionWithNext(t, n) + " ");
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
        new Parking().run();
    }
}