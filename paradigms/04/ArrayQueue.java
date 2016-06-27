public class ArrayQueue extends AbstractQueue {
    private int first;
    private int last;
    private int size;
    private Object[] elements = new Object[10];

    private void enshureCapacity(int capacity) {
        int len = elements.length;
        if (capacity > len) {
            Object[] newElements = new Object[elements.length * 2];
            int i = 0;
            while (last!=first) {
                newElements[i] = elements[first];
                first = (first + 1) % len;
                i++;
            }
            first = 0;
            last = len - 1;
            elements = newElements;
        }
    }

    public void enqueue(Object element) {
        enshureCapacity(size + 2);
        elements[last] = element;
        last = (last + 1) % elements.length;
        size++;
    }

    public Object element() {
        return elements[first];
    }

    public Object[] toArray() {
        Object[] newElements = new Object[elements.length];
        newElements = elements;
        return newElements;
    }

    public Object dequeue() {
        Object ret = element();
        elements[first] = null;
        first = (first + 1) % elements.length;
        size--;
        return ret;
    }

    public void clear() {
        first = 0;
        last = 0;
        size = 0;
    }

    public int size() {
        return size;
    }

    public boolean isEmpty() {
        return (size == 0);
    }


}