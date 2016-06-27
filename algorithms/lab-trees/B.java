import java.io.*;
import java.util.StringTokenizer;

public class BST {
    FastScanner in;
    PrintWriter out;

    class RedBlackTree {
        final int LEAF = 1000000001;
        final int RED = 0;
        final int BLACK = 1;
        private Node root;

        public class Node {
            public int value;
            public int color;
            public Node left;
            public Node right;
            public Node parent;

            Node(int value, int color) {
                this.value = value;
                this.color = color;
                if (!isLeaf()) {
                    setLeftChild(new Node());
                    setRightChild(new Node());
                }
            }

            Node(int value) {
                this(value, BLACK);
            }

            Node() {
                this(LEAF, BLACK);
            }

            boolean isLeaf() {
                return this.value == LEAF;
            }

            public boolean hasParent() {
                return parent != null;
            }

            Node getGrandparent() {
                if (hasGrandparent()) {
                    return parent.parent;
                } else {
                    return null;
                }
            }

            boolean hasGrandparent() {
                return hasParent() && parent.hasParent();
            }

            void changeColor(boolean need) {
                this.color = (need ? BLACK : RED);
            }

            void setLeftChild(Node leftChild) {
                this.left = leftChild;
                if (hasLeftChild()) {
                    leftChild.parent = this;
                }
            }

            void setRightChild(Node rightChild) {
                this.right = rightChild;
                if (hasRightChild()) {
                    rightChild.parent = this;
                }
            }

            boolean hasLeftChild() {
                return !left.isLeaf();
            }

            boolean hasRightChild() {
                return !right.isLeaf();
            }

            Node find(int i) {
                if (isLeaf()) {
                    return null;
                } else if (value == i) {
                    return this;
                } else {
                    if (i < value && hasLeftChild()) {
                        return this.left.find(i);
                    } else if (hasRightChild()) {
                        return this.right.find(i);
                    }
                }
                return null;
            }

            boolean exists(int i) {
                return find(i) != null;
            }

            boolean assign(Node newNode) {
                if (newNode.value < value) {
                    if (hasLeftChild()) {
                        return this.left.assign(newNode);
                    } else {
                        setLeftChild(newNode);
                        return true;
                    }
                } else if (newNode.value > value) {
                    if (hasRightChild()) {
                        return this.right.assign(newNode);
                    } else {
                        setRightChild(newNode);
                        return true;
                    }
                } else {
                    // return true;
                    return false;
                }
            }

            Node getMinNode() {
                if (hasLeftChild()) {
                    return this.left.getMinNode();
                } else {
                    return this;
                }
            }

            Node getMaxNode() {
                if (hasRightChild()) {
                    return this.right.getMaxNode();
                } else {
                    return this;
                }
            }
        }

        RedBlackTree() {
            this.root = new Node(LEAF);
        }

        boolean empty() {
            return root.isLeaf();
        }

        boolean exists(int i) {
            if (!empty()) {
                return root.exists(i);
            } else {
                return false;
            }
        }

        void insert(int i) {
            Node newNode = new Node(i);
            if (empty()) {
                this.root = newNode;
            } else {
                insert(newNode);
            }
        }

        void insert(Node newNode) {
            Node y;
            if (this.root.assign(newNode)) {
                newNode.color = RED;
                while (newNode != this.root && newNode.parent.color == RED) {
                    if (newNode.parent == newNode.getGrandparent().left) {
                        y = newNode.getGrandparent().right;
                        if (!y.isLeaf() && y.color == RED) {
                            newNode.parent.color = BLACK;
                            y.color = BLACK;
                            newNode.getGrandparent().color = RED;
                            newNode = newNode.getGrandparent();
                        } else {
                            if (newNode == newNode.parent.right) {
                                newNode = newNode.parent;
                                leftRotate(newNode);
                            }
                            if (newNode.hasParent()) {
                                newNode.parent.color = BLACK;
                                if (newNode.hasGrandparent()) {
                                    newNode.getGrandparent().color = RED;
                                    rightRotate(newNode.getGrandparent());
                                }
                            }
                        }
                    } else {
                        y = newNode.getGrandparent().left;
                        if (!y.isLeaf() && y.color == RED) {
                            newNode.parent.color = BLACK;
                            y.color = BLACK;
                            newNode.getGrandparent().color = RED;
                            newNode = newNode.getGrandparent();
                        } else {
                            if (newNode == newNode.parent.left) {
                                newNode = newNode.parent;
                                rightRotate(newNode);
                            }
                            if (newNode.hasParent()) {
                                newNode.parent.color = BLACK;
                                if (newNode.hasGrandparent()) {
                                    newNode.getGrandparent().color = RED;
                                    leftRotate(newNode.getGrandparent());
                                }
                            }
                        }
                    }

                }
                this.root.color = BLACK;
            }
        }

        void delete(int i) {
            Node z = this.root.find(i);
            if (z == null) {
                return;
            } else {
                Node x, y;
                if (!z.hasLeftChild() || !z.hasRightChild()) {
                    y = z;
                } else {
                    y = successor(z);
                }
                if (y.hasLeftChild()) {
                    x = y.left;
                } else {
                    x = y.right;
                }
                x.parent = y.parent;
                if (this.root == y) {
                    this.root = x;
                } else if (y == y.parent.left) {
                    y.parent.setLeftChild(x);
                } else {
                    y.parent.setRightChild(x);
                }
                if (y != z) {
                    z.value = y.value;
                }
                if (y.color == BLACK) {
                    delete(x);
                }
            }
        }

        void delete(Node x) {
            Node w;
            while (this.root != x && x.color == BLACK) {
                if (x == x.parent.left) {
                    w = x.parent.right;
                    if (w.color == RED) {
                        w.color = BLACK;
                        x.parent.color = RED;
                        leftRotate(x.parent);
                        w = x.parent.right;
                    }
                    if (w.left.color == BLACK && w.right.color == BLACK) {
                        w.color = RED;
                        x = x.parent;
                    } else {
                        if (w.right.color == BLACK) {
                            w.left.color = BLACK;
                            w.color = RED;
                            rightRotate(w);
                            w = x.parent.right;
                        }
                        w.changeColor(x.parent.color == BLACK);
                        x.parent.color = BLACK;
                        w.right.color = BLACK;
                        leftRotate(x.parent);
                        x = this.root;
                    }
                } else {
                    w = x.parent.left;
                    if (w.color == RED) {
                        w.color = BLACK;
                        x.parent.color = RED;
                        rightRotate(x.parent);
                        w = x.parent.left;
                    }
                    if (w.right.color == BLACK && w.left.color == BLACK) {
                        w.color = RED;
                        x = x.parent;
                    } else {
                        if (w.left.color == BLACK) {
                            w.right.color = BLACK;
                            w.color = RED;
                            leftRotate(w);
                            w = x.parent.left;
                        }
                        w.changeColor(x.parent.color == BLACK);
                        x.parent.color = BLACK;
                        w.left.color = BLACK;
                        rightRotate(x.parent);
                        x = this.root;
                    }
                }
            }
            x.color = BLACK;
        }

        Node successor(Node x) {
            if (x.hasRightChild()) {
                return x.right.getMinNode();
            } else {
                Node y = x.parent;
                while (!y.isLeaf() && x == y.right) {
                    x = y;
                    y = y.parent;
                }
                return y;
            }
        }

        Node next(int value) {
            Node curNode = this.root, parent = null;
            while (curNode != null && curNode.value != LEAF) {
                if (curNode.value > value) {
                    parent = curNode;
                    curNode = curNode.left;
                } else {
                    curNode = curNode.right;
                }
            }
            return parent;
        }

        Node prev(int value) {
            Node curNode = this.root, parent = null;
            while (curNode != null && curNode.value != LEAF) {
                if (curNode.value < value) {
                    parent = curNode;
                    curNode = curNode.right;
                } else {
                    curNode = curNode.left;
                }
            }
            return parent;
        }

        int getPrevValue(int value) {
            Node prevNode = prev(value);
            if (prevNode == null) {
                return LEAF;
            } else {
                return prevNode.value;
            }
        }

        int getNextValue(int value) {
            Node nextNode = next(value);
            if (nextNode == null) {
                return LEAF;
            } else {
                return nextNode.value;
            }
        }

        void leftRotate(Node x) {
            Node y = x.right;
            x.setRightChild(y.left);
            if (y.hasLeftChild()) {
                y.left.parent = x;
            }
            y.parent = x.parent;
            if (!x.hasParent()) {
                this.root = y;
            } else if (x == x.parent.left) {
                x.parent.setLeftChild(y);
            } else {
                x.parent.setRightChild(y);
            }
            y.setLeftChild(x);
            x.parent = y;
        }

        void rightRotate(Node x) {
            Node y = x.left;
            x.setLeftChild(y.right);
            if (y.hasRightChild()) {
                y.right.parent = x;
            }
            y.parent = x.parent;
            if (!x.hasParent()) {
                this.root = y;
            } else if (x == x.parent.right) {
                x.parent.setRightChild(y);
            } else {
                x.parent.setLeftChild(y);
            }
            y.setRightChild(x);
            x.parent = y;
        }
    }

    public void solve() throws IOException {
        RedBlackTree t = new RedBlackTree();
        while (true) {
            String command;
            Integer arg;
            try {
                command = in.next();
                arg = in.nextInt();
            } catch (Exception e) {
                break;
            }
            switch (command) {
                case "insert":
                    t.insert(arg);
                    break;
                case "delete":
                    t.delete(arg);
                    break;
                case "exists":
                    out.println(t.exists(arg) ? "true" : "false");
                    break;
                case "next":
                    int nextVal = t.getNextValue(arg);
                    out.println((nextVal != t.LEAF) ? nextVal : "none");
                    break;
                case "prev":
                    int prevVal = t.getPrevValue(arg);
                    out.println((prevVal != t.LEAF) ? prevVal : "none");
                    break;
            }
        }

    }

    public void run() {
        try {
            in = new FastScanner(new File("bst.in"));
            out = new PrintWriter(new File("bst.out"));

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
        new BST().run();
    }
}