public class ArrayQueueModule {

    private static int size = 0;
    private static Object[] elements = new Object[5];
    private static int head = 0, tail = 0;

    // pre: capacity = size
    // post: if (capacity > elements.length): elements.length = 2 * elements.length
    private static void ensureCapacity(int capacity) {
        if (capacity <= elements.length) {
            return;
        }

        Object[] newElements = new Object[2 * capacity];
        for (int i = head; i < head + size; i++) {
            newElements[i - head] = elements[i % elements.length];
        }
        elements = newElements;
        head = 0;
        tail = size;
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
    public static void enqueue(Object e) {
        ensureCapacity(size + 1);
        elements[tail] = e;
        tail = nextElement(tail, elements.length);
        size++;
    }

    // pre:
    // post: size = size + 1, last element = e, head = prev element
    public static void push(Object e) {
        ensureCapacity(size + 1);
        size++;
        head = prevElement(head, elements.length);
        elements[head] = e;
    }

    // pre: size > 0
    // post: result = last element in queue
    public static Object peek() {
        assert size > 0;

        return elements[prevElement(tail, elements.length)];
    }

    // pre: size > 0
    // post: result = last element in queue, tail = prev element
    public static Object remove() {
        assert size > 0;

        tail = prevElement(tail, elements.length);
        Object lastElement = elements[tail];
        size--;

        return lastElement;
    }

    // pre: size > 0
    // post: result = first element in queue, head = next element
    public static Object dequeue() {
        assert size > 0;

        Object firstElement = elements[head];
        size--;
        head = nextElement(head, elements.length);
        return firstElement;
    }

    // pre: size > 0
    // post: result = first element in queue
    public static Object element() {
        assert size > 0;

        return elements[head];
    }

    // pre:
    // post: result = count elements in queue
    public static int size() {
        return size;
    }

    // pre:
    // post: result = true, if size == 0; false, if size > 0
    public static boolean isEmpty() {
        return (size == 0);
    }

    // pre
    // post: size == 0
    public static void clear() {
        head = 0;
        tail = 0;
        size = 0;
        elements = new Object[5];
    }
}