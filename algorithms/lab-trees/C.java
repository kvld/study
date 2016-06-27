import java.io.*;
import java.util.StringTokenizer;

public class Movetofront {
    FastScanner in;
    PrintWriter out;

    class ImplicitSplayTree {
        class Node {
            Node left;
            Node right;
            Node parent;
            int key;

            Node(int key, Node left, Node right, Node parent) {
                this.key = key;
                this.left = left;
                this.right = right;
                this.parent = parent;
            }
        }

        void setParent(Node child, Node parent) {
            if (child != null) {
                child.parent = parent;
            }
        }

        void keepParent(Node curNode) {
            setParent(curNode.left, curNode);
            setParent(curNode.right, curNode);
        }

        void rotate(Node parent, Node child) {
            Node grandparent = parent.parent;
            if (grandparent != null) {
                if (grandparent.left == parent) {
                    grandparent.left = child;
                } else {
                    grandparent.right = child;
                }
            }
            if (parent.left == child) {
                parent.left = child.right;
                child.right = parent;
            }
            keepParent(child);
            keepParent(parent);
            child.parent = grandparent;
        }

        Node splay(Node curNode) {
            if (curNode.parent == null) {
                return curNode;
            }
            Node parent = curNode.parent, grandparent = curNode.parent.parent;
            if (grandparent == null) {
                rotate(parent, curNode);
                return curNode;
            } else {
                boolean zigzig = (grandparent.left == parent) == (parent.left == curNode);
                if (zigzig) {
                    rotate(grandparent, parent);
                    rotate(parent, curNode);
                } else {
                    rotate(parent, curNode);
                    rotate(grandparent, curNode);
                }
            }
            return splay(curNode);
        }

        Node find(Node curNode, int key) {
            if (curNode == null) {
                return null;
            }
            if (key == curNode.key) {
                return splay(curNode);
            }
            if (key < curNode.key && curNode.left != null) {
                return find(curNode.left, key);
            }
            if (key > curNode.key && curNode.right != null) {
                return find(curNode.right, key);
            }
            return splay(curNode);
        }

        void split(Node root, int key, Node t1, Node t2) {
            if (root == null) {
                t1 = null;
                t2 = null;
                return;
            }
            root = find(root, key);
            if (root.key == key) {
                setParent(root.left, null);
                setParent(root.right, null);

            }
        }
    }

    public void solve() throws IOException {

    }

    public void run() {
        try {
            in = new FastScanner(new File("movetofront.in"));
            out = new PrintWriter(new File("movetofront.out"));

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
        new Movetofront().run();
    }
}