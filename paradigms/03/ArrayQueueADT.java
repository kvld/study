public class ArrayQueueADT {

    private int size = 0;
    private Object[] elements = new Object[5];
    private int head = 0, tail = 0;

    // pre: capacity = size
    // post: if (capacity > elements.length): elements.length = 2 * elements.length
    private static void ensureCapacity(ArrayQueueADT q, int capacity) {
        if (capacity <= q.elements.length) {
            return;
        }

        Object[] newElements = new Object[2 * capacity];
        for (int i = q.head; i < q.head + q.size; i++) {
            newElements[i - q.head] = q.elements[i % q.elements.length];
        }
        q.elements = newElements;
        q.head = 0;
        q.tail = q.size;
    }

    // pre: 0 <= cur < length, length >= 0
    // post: result <= length
    private static int nextElement(int cur, int length) {
        return (cur + 1) % length;
    }

    // pre: 0 <= cur < length, length >= 0
    // post: result <= length
    private static int prevElement(int cur, int length) {
        return (cur - 1 < 0 ? length - 1 : cur - 1);
    }

    // pre:
    // post: size = size + 1, first element = e, tail = next element
    public static void enqueue(ArrayQueueADT q, Object e) {
        ensureCapacity(q, q.size + 1);
        q.elements[q.tail] = e;
        q.tail = nextElement(q.tail, q.elements.length);
        q.size++;
    }

    // pre:
    // post: size = size + 1, last element = e, head = prev element
    public static void push(ArrayQueueADT q, Object e) {
        ensureCapacity(q, q.size + 1);
        q.size++;
        q.head = prevElement(q.head, q.elements.length);
        q.elements[q.head] = e;
    }

    // pre: size > 0
    // post: last element in queue
    public static Object peek(ArrayQueueADT q) {
        assert q.size > 0;

        return q.elements[prevElement(q.tail, q.elements.length)];
    }

    // pre: size > 0
    // post: result = last element in queue, tail = prev element
    public static Object remove(ArrayQueueADT q) {
        assert q.size > 0;

        q.tail = prevElement(q.tail, q.elements.length);
        Object lastElement = q.elements[q.tail];
        q.size--;

        return lastElement;
    }

    // pre: size > 0
    // post: result = first element in queue, head = next element
    public static Object dequeue(ArrayQueueADT q) {
        assert q.size > 0;

        Object firstElement = q.elements[q.head];
        q.size--;
        q.head = nextElement(q.head, q.elements.length);
        return firstElement;
    }

    // pre: size > 0
    // post: result = first element in queue
    public static Object element(ArrayQueueADT q) {
        assert q.size > 0;

        return q.elements[q.head];
    }

    // pre:
    // post: result = count elements in queue
    public static int size(ArrayQueueADT q) {
        return q.size;
    }

    // pre:
    // post: true, if size == 0; false, if size > 0
    public static boolean isEmpty(ArrayQueueADT q) {
        return (q.size == 0);
    }

    // pre
    // post: size == 0
    public static void clear(ArrayQueueADT q) {
        q.head = 0;
        q.tail = 0;
        q.size = 0;
        q.elements = new Object[5];
    }
}