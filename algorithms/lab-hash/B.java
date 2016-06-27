import java.util.*;
import java.io.*;

public class Map {
    FastScanner in;
    PrintWriter out;

    class HashMap {

        class Node {
            private String key;
            private String value;
            private Node next;
            private Node prev;

            public Node(String key, String value, Node next, Node prev) {
                this.key = key;
                this.value = value;
                this.next = next;
                this.prev = prev;
            }

            public String getKey() {
                return key;
            }

            public void setKey(String key) {
                this.key = key;
            }

            public String getValue() {
                return value;
            }

            public void setValue(String value) {
                this.value = value;
            }

            public Node getNext() {
                return next;
            }

            public void setNext(Node next) {
                this.next = next;
            }

            public Node getPrev() {
                return prev;
            }

            public void setPrev(Node prev) {
                this.prev = prev;
            }
        }

        public static final int MAX = 100019;
        public static final int BASE = 31;
        ArrayList<Node>[] d = new ArrayList[MAX];
        Node first = null;
        Node last = null;


        int hash(String s) {
            int t = 1;
            int res = 0;
            for (int i = 0; i < s.length(); i++) {
                res += t * (s.charAt(i) - '0');
                res %= MAX;
                t *= BASE;
                t %= MAX;
            }
            return res;
        }

        String get(String x) {
            int hash = hash(x);
            if (d[hash] == null) {
                return null;
            }
            for (int i = 0; i < d[hash].size(); i++) {
                if (x.equals(d[hash].get(i).getKey())) {
                    return d[hash].get(i).getValue();
                }
            }
            return null;
        }

        void addAndUpdateOrder(String x, String z) {
            if (first == null) {
                Node element = new Node(x, z, null, null);
                first = element;
                last = element;
                d[hash(x)].add(element);
            } else {
                Node element = new Node(x, z, null, last);
                last.next = element;
                last = element;
                d[hash(x)].add(element);
            }
        }

        void put(String x, String z) {
            int hash = hash(x);
            if (d[hash] == null) {
                d[hash] = new ArrayList();
                addAndUpdateOrder(x, z);
                return;
            }
            for (int i = 0; i < d[hash].size(); i++) {
                if (x.equals(d[hash].get(i).getKey())) {
                    d[hash].get(i).setValue(z);
                    return;
                }
            }
            addAndUpdateOrder(x, z);
        }

        void delete(String x) {
            int hash = hash(x);
            if (d[hash] == null) {
                return;
            }
            for (int i = 0; i < d[hash].size(); i++) {
                if (x.equals(d[hash].get(i).getKey())) {
                    if (d[hash].get(i).getPrev() == null && d[hash].get(i).getNext() == null) {
                        first = null;
                        last = null;
                        d[hash].remove(i);
                        return;
                    } else if (d[hash].get(i).getPrev() == null) {
                        d[hash].get(i).getNext().setPrev(null);
                        first = d[hash].get(i).getNext();
                        d[hash].remove(i);
                        return;
                    } else if (d[hash].get(i).getNext() == null) {
                        d[hash].get(i).getPrev().setNext(null);
                        last = d[hash].get(i).getPrev();
                        d[hash].remove(i);
                        return;
                    }

                    d[hash].get(i).getPrev().setNext(d[hash].get(i).getNext());
                    d[hash].get(i).getNext().setPrev(d[hash].get(i).getPrev());
                    d[hash].remove(i);
                    return;
                }
            }
        }

        String prev(String x) {
            int hash = hash(x);
            if (d[hash] == null) {
                return null;
            }
            for (int i = 0; i < d[hash].size(); i++) {
                if (x.equals(d[hash].get(i).getKey())) {
                    if (d[hash].get(i).getPrev() != null) {
                        return d[hash].get(i).getPrev().getValue();
                    } else {
                        return null;
                    }
                }
            }
            return null;
        }

        String next(String x) {
            int hash = hash(x);
            if (d[hash] == null) {
                return null;
            }
            for (int i = 0; i < d[hash].size(); i++) {
                if (x.equals(d[hash].get(i).getKey())) {
                    if (d[hash].get(i).getNext() != null) {
                        return d[hash].get(i).getNext().getValue();
                    } else {
                        return null;
                    }
                }
            }
            return null;
        }
    }


    public void solve() throws IOException {
        HashMap t = new HashMap();
        String command;
        while (true) {
            try {
                command = in.next();
            } catch (Exception e) {
                break;
            }
            if (command.equals("put")) {
                t.put(in.next(), in.next());
            } else if (command.equals("get")) {
                String result = t.get(in.next());
                out.println((result == null) ? "none" : result);
            } else if (command.equals("delete")) {
                t.delete(in.next());
            } else if (command.equals("prev")) {
                String result = t.prev(in.next());
                out.println((result == null) ? "none" : result);
            } else if (command.equals("next")) {
                String result = t.next(in.next());
                out.println((result == null) ? "none" : result);
            }
        }
    }

    public void run() {
        try {
            in = new FastScanner(new File("map.in"));
            out = new PrintWriter(new File("map.out"));

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
        new Map().run();
    }
}