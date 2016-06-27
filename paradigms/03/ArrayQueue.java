public class ArrayQueue {

    private int size = 0;
    private Object[] elements = new Object[5];
    private int head = 0, tail = 0;

    //inv: size >= 0, queue[i] != null

    // pre: e != null
    // post: size = size + 1
    //       queue[tail] = e
    //       queue[i] = queue[i - 1] for all i = head..tail - 1
    public void enqueue(Object e) {
        ensureCapacity(size + 1);
        elements[tail] = e;
        tail = nextElement(tail);
        size++;
    }

    // pre:
    // post: size = size + 1
    //       queue[head] = e
    //       queue[i] = queue[i - 1] for all i = head + 1..tail
    public void push(Object e) {
        ensureCapacity(size + 1);
        size++;
        head = prevElement(head);
        elements[head] = e;
    }

    // pre: size > 0
    // post: result = last element in queue: queue[tail - 1],
    //       size = size - 1
    public Object remove() {
        assert size > 0;

        tail = prevElement(tail);
        Object lastElement = elements[tail];
        size--;

        return lastElement;
    }

    // pre: size > 0
    // post: result = first element in queue: queue[head],
    //       size = size - 1
    public Object dequeue() {
        assert size > 0;

        Object firstElement = elements[head];
        size--;
        head = nextElement(head);
        return firstElement;
    }

    // pre: size > 0
    // post: result = first element in queue: queue[head]
    public Object element() {
        assert size > 0;

        return elements[head];
    }

    // pre: size > 0
    // post: result = last element in queue: queue[tail - 1]
    public Object peek() {
        assert size > 0;

        return elements[prevElement(tail)];
    }

    // pre:
    // post: result = count elements in queue
    public int size() {
        return size;
    }

    // pre:
    // post: result = true, if size == 0; false, if size > 0
    public boolean isEmpty() {
        return (size == 0);
    }

    // pre
    // post: clear queue
    public void clear() {
        head = 0;
        tail = 0;
        size = 0;
        elements = new Object[5];
    }

    private void ensureCapacity(int capacity) {
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

    private int nextElement(int cur) {
        return (cur + 1) % elements.length;
    }

    private int prevElement(int cur) {
        return (cur - 1 < 0 ? elements.length - 1 : cur - 1);
    }

}