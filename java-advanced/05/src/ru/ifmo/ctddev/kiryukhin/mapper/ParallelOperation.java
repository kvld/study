package ru.ifmo.ctddev.kiryukhin.mapper;

import java.util.function.Function;

/**
 * Implementation for operation. Saves argument, operation and result.
 * <p>
 * It implements {@link Runnable}.
 * </p>
 * @param <T> type of argument
 * @param <R> type of result
 *
 * @author Vladislav Kiryukhin
 */
public class ParallelOperation<T, R> implements Runnable {
    private R result = null;
    private Function<? super T, ? extends R> operation;
    private T arg;
    private Counter counter;

    /**
     * Create operation with given argument and function and attach counter to this.
     * @param arg argument
     * @param operation function
     * @param counter counter
     */
    public ParallelOperation(T arg, Function<? super T, ? extends R> operation, Counter counter) {
        this.operation = operation;
        this.arg = arg;
        this.counter = counter;
    }

    @Override
    public void run() {
        result = operation.apply(arg);
    }

    /**
     * Return result of function.
     * @return result of operation
     */
    public R getResult() {
        return result;
    }

    /**
     * Return counter attached to operation.
     * @return counter for operation
     */
    public Counter getCounter() {
        return counter;
    }

    /**
     * Decrement attached counter
     */
    public void decCounter() {
        getCounter().dec();
    }

    /**
     * Set attached counter to zero
     */
    public void setCounterZero() {
        getCounter().setZero();
    }

}