public class BinarySearchSpan {

    // pre: a[], a.length >= 0
    static int binarySearch(int[] a, int x, boolean leftLess) {
        // a.length >= 0
        if (a.length == 0) {
            return 0;
        }
        int l = 0, r = a.length;
        while (r - l > 1) {
            int mid = (r + l) / 2;
            if (a[mid] < x || (leftLess && a[mid] == x)) {
                r = mid;
            } else {
                l = mid;
            }
        }
        if (a[l] <= x) {
            return l;
        }
        return r;
    }
    // post:
    // if a.length == 0: 0
    // if (a.length > 0 && leftLess): result in [0 .. a.length - 1], result = min i: a[i] <= x
    // if (a.length > 0 && !leftLess): result in [0 .. a.length - 1], result = max i: a[i] <= x

    // pre: a[], a.length >= 0
    static void search(int[] a, int x) {
        int lPos = binarySearch(a, x, true);
        int rPos = binarySearch(a, x, false);

        // lPos in [0 .. a.length]
        if (lPos == a.length) {
            System.out.println(a.length + " 0");
        } else if (a[lPos] != x) {
            System.out.println(lPos + " 0");
        } else {
            System.out.println(lPos + " " + (rPos - lPos + 1));
        }
    }

    public static void main(String[] args) {
        int x = Integer.parseInt(args[0]);
        int[] a = new int[args.length - 1];
        for (int i = 1; i < args.length; i++) {
            a[i - 1] = Integer.parseInt(args[i]);
        }
        search(a, x);
    }
}