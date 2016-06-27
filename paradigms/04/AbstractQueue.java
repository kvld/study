import java.util.function.Function;
import java.util.function.Predicate;

public abstract class AbstractQueue implements Queue {

    protected int size = 0;

    // pre:
    // post: object at the begin of queue = element, size = size + 1
    public abstract void enqueue(Object element);

    // pre: queue size > 0
    // post: result = object at the begin of queue
    public abstract Object element();

    // pre: queue size > 0
    // post: result = object at the begin of queue, size = size - 1
    public abstract Object dequeue();

    // pre:
    // post: result = queue
    //public abstract Queue makeCopy();

    // pre:
    // post: result = size of queue
    public int size() {
        return size;
    }

    // pre:
    // post: result = true, if queue is empty; result = false, if its size > 0
    public boolean isEmpty() {
        return (size == 0);
    }

    // pre: size > 0
    // post: result = new queue: T is true for all elements in queue
    /*public Queue filter(Predicate t) {
        Queue cpQueue = makeCopy();
        Queue newQueue = makeCopy();
        newQueue.clear();

        while (!cpQueue.isEmpty()) {
            Object element = cpQueue.dequeue();
            if (t.test(element)) {
                newQueue.enqueue(element);
            }
        }
        return newQueue;
    }*/

    // pre: size > 0
    // post: result = new queue: new_queue[i] = f(queue[i])
    /*public Queue map(Function f) {
        Queue cpQueue = makeCopy();
        Queue newQueue = makeCopy();
        newQueue.clear();

        while (!cpQueue.isEmpty()) {
            Object element = cpQueue.dequeue();
            newQueue.enqueue(f.apply(element));
        }
        return newQueue;
    }*/

    public abstract Object[] toArray();

}
