package ru.ifmo.ctddev.kiryukhin.mapper;

import info.kgeorgiy.java.advanced.mapper.ParallelMapper;

import java.util.*;
import java.util.function.Function;
import java.util.stream.Collectors;

/**
 * Implementation of {@link info.kgeorgiy.java.advanced.mapper.ParallelMapper}.
 * <p>
 * It provides interface for using concurrency.
 * </p>
 *
 * @author Vladislav Kiryukhin
 */
public class ParallelMapperImpl implements ParallelMapper {
    private final Queue<ParallelOperation> tasks = new LinkedList<>();
    private final List<Thread> threads = new ArrayList<>();
    private volatile boolean isClosed = false;

    /**
     * Create mapper with given number of threads.
     * @param threads threads count
     */
    public ParallelMapperImpl(int threads) {
        for (int i = 0; i < threads; i++) {
            Runnable worker = new Runnable() {
                @Override
                public void run() {
                    while (true) {
                        ParallelOperation currentOperation;
                        synchronized (tasks) {
                            while (tasks.isEmpty()) {
                                try {
                                    tasks.wait();
                                } catch (InterruptedException e) {
                                    Thread.currentThread().interrupt();
                                    return;
                                }
                            }
                            currentOperation = tasks.poll();
                        }

                        if (!isClosed) {
                            currentOperation.run();
                            currentOperation.decCounter();
                        } else {
                            currentOperation.setCounterZero();
                            break;
                        }
                    }
                }
            };

            this.threads.add(new Thread(worker));
            this.threads.get(i).start();
        }
    }

    /**
     * Run function with provided arguments parallel.
     * @param f function which should be computed parallel
     * @param args function args
     * @param <T> type of args
     * @param <R> type of result
     * @return list with results
     * @throws InterruptedException if error occurs
     */
    @Override
    public <T, R> List<R> map(Function<? super T, ? extends R> f, List<? extends T> args) throws InterruptedException {
        if (isClosed) {
            throw new InterruptedException("Mapper is closed");
        }

        final Counter counter = new Counter(args.size());

        List<ParallelOperation<T, R>> operations = args.stream()
                .map(arg -> new ParallelOperation<>(arg, f, counter))
                .collect(Collectors.toList());

        synchronized (tasks) {
            tasks.addAll(operations);
            tasks.notifyAll();
        }

        synchronized (counter) {
            while (counter.getValue() != 0) {
                counter.wait();
            }
        }

        return operations.stream().map(ParallelOperation::getResult).collect(Collectors.toList());
    }

    /**
     * Close mapper.
     * @throws InterruptedException if mapper already closed or thread throw this exception.
     */
    @Override
    public void close() throws InterruptedException {
        if (isClosed) {
            throw new IllegalStateException("Mapper already closed.");
        } else {
            isClosed = true;
        }

        for (Thread thread: threads) {
            thread.interrupt();
            thread.join();
        }
    }
}
