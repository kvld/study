import java.util.function.Function;
import java.util.function.Predicate;
/*
public class LinkedQueue extends AbstractQueue {

    private Node head;
    private Node tail;

    private class Node {
        public Object value;
        public Node next;

        public Node(Object value, Node next) {
            assert value != null;

            this.value = value;
            this.next = next;
        }
    }

    // pre: e != null
    // post: size = size + 1
    //       queue[tail] = e
    //       queue[i] = queue[i - 1] for all i = head..tail - 1
    public void enqueue(Object element) {
        assert element != null;

        Node oldLast = tail;
        tail = new Node(element, null);
        if (size == 0) {
            head = tail;
        } else {
            oldLast.next = tail;
        }
        size++;
    }

    // pre: size > 0
    // post: result = first element in queue: queue[head]
    public Object element() {
        assert size > 0;

        return head.value;
    }


    // pre: size > 0
    // post: result = first element in queue: queue[head],
    //       size = size - 1
    public Object dequeue() {
        assert size > 0;

        Object result = head.value;
        head = head.next;
        size--;
        if (size == 0) {
            tail = null;
        }
        return result;
    }

    // pre
    // post: clear queue
    public void clear() {
        size = 0;
        head = null;
        tail = null;
    }

    // pre: size > 0
    // post: result = queue
    public LinkedQueue makeCopy() {
        LinkedQueue newQueue = new LinkedQueue();

        Node item = head;
        while (item != null) {
            newQueue.enqueue(item.value);
            item = item.next;
        }

        return newQueue;
    }


}
*/