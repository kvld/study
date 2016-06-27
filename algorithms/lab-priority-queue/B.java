import java.io.*;
import java.util.StringTokenizer;

public class Dsu {
    FastScanner in;
    PrintWriter out;

    int parent[] = new int[100_001];
    int size[] = new int[100_001];
    int min[] = new int[100_001];
    int max[] = new int[100_001];

    void makeSet(int v) {
        parent[v] = v;
        min[v] = v;
        max[v] = v;
        size[v] = 1;
    }

    int findSet(int v) {
        if (v == parent[v]) {
            return v;
        }
        return parent[v] = findSet(parent[v]);
    }

    void unionSets(int u, int v) {
        u = findSet(u);
        v = findSet(v);
        if (u != v) {
            if (size[u] < size[v]) {
                int t = v;
                v = u;
                u = t;
            }
            parent[v] = u;
            size[u] += size[v];
            min[u] = Math.min(min[u], min[v]);
            max[u] = Math.max(max[u], max[v]);
        }
    }


    public void solve() throws IOException {
        int n = in.nextInt();
        for (int i = 0; i < n; i++) {
            makeSet(i + 1);
        }
        String command;
        while (true) {
            try {
                command = in.next();
            } catch (Exception e) {
                break;
            }
            if (command.equals("union")) {
                int arg1 = findSet(in.nextInt()), arg2 = findSet(in.nextInt());
                unionSets(arg1, arg2);
            } else if (command.equals("get")) {
                int arg = findSet(in.nextInt());
                out.println(min[arg] + " " + max[arg] + " " + size[arg]);
            }
        }
    }

    public void run() {
        try {
            in = new FastScanner(new File("dsu.in"));
            out = new PrintWriter(new File("dsu.out"));

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
        new Dsu().run();
    }
}