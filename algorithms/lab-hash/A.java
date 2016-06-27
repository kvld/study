import java.util.*;
import java.io.*;

public class Set {
    FastScanner in;
    PrintWriter out;

    class HashSet {
        public static final int SIZE = 1_000_000;
        public static final int INF = 1_000_000_000 + 1;
        ArrayList<ArrayList<Integer>> d = new ArrayList<ArrayList<Integer>>(SIZE);

        HashSet() {
            for (int i = 0; i < SIZE; i++) {
                d.add(i, new ArrayList<Integer>());
            }
        }

        void insert(int x) {
            if (exists(x)) {
                return;
            }
            int hash = hash(x);
            for (int i = 0; i < d.get(hash).size(); i++) {
                if (d.get(hash).get(i) == x) {
                    return;
                }
            }
            d.get(hash).add(x);
        }

        boolean exists(int x) {
            int hash = hash(x);
            for (int i = 0; i < d.get(hash).size(); i++) {
                if (d.get(hash).get(i) == x) {
                    return true;
                }
            }
            return false;
        }

        void delete(int x) {
            if (!exists(x)) {
                return;
            }
            int hash = hash(x);
            for (int i = 0; i < d.get(hash).size(); i++) {
                if (d.get(hash).get(i) == x) {
                    d.get(hash).remove(i);
                    return;
                }
            }
        }

        public Integer hash(int x) {
            //return Math.abs(~(x << 13) ^ (x >> 5) + (x >> 3));
            //return (x % SIZE + SIZE) % SIZE;
            return Math.abs(31 * x + 239) % SIZE;
        }
    }



    public void solve() throws IOException {
        HashSet t = new HashSet();
        String command;
        int a;
        while (true) {
            try {
                command = in.next();
            } catch (Exception e) {
                break;
            }
            a = in.nextInt();
            if (command.equals("insert")) {
                t.insert(a);
            } else if (command.equals("exists")) {
                out.println(t.exists(a) ? "true" : "false");
            } else if (command.equals("delete")) {
                t.delete(a);
            }
        }
    }

    public void run() {
        try {
            in = new FastScanner(new File("set.in"));
            out = new PrintWriter(new File("set.out"));

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
        new Set().run();
    }
}