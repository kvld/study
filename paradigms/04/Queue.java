import java.util.function.Function;
import java.util.function.Predicate;

public interface Queue {

    // pre:
    // post: object at the begin of queue = element, size = size + 1
    void enqueue(Object element);

    // pre: queue size > 0
    // post: result = object at the begin of queue
    Object element();

    // pre: queue size > 0
    // post: result = object at the begin of queue, size = size - 1
    Object dequeue();

    // pre:
    // post: result = size of queue
    int size();

    // pre:
    // post: result = true, if queue is empty; result = false, if its size > 0
    boolean isEmpty();

    // pre:
    // post: size = 0, empty queue
    void clear();

    // pre: size > 0
    // post: result = new queue: T is true for all elements in queue
    //Queue filter(Predicate T);

    // pre: size > 0
    // post: result = new queue: new_queue[i] = F(queue[i])
    //Queue map(Function F);

    // pre:
    // post: result = queue
    //Queue makeCopy();

    Object[] toArray();
}