package ru.ifmo.ctddev.kiryukhin.mapper;

import info.kgeorgiy.java.advanced.concurrent.ListIP;
import info.kgeorgiy.java.advanced.mapper.ParallelMapper;

import java.util.*;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.stream.Collectors;

/**
 * Implementation of ListIP.
 * <p>
 * For given number of threads it computes minimum, maximum;
 * checks if all or any elements satisfy predicate; converts list to string.
 * </p>
 *
 * @author Vladislav Kiryukhin
 */
public class IterativeParallelism implements ListIP {
    private ParallelMapper parallelMapper;

    /**
     * Constructor with {@link ParallelMapper}
     * @param parallelMapper mapper
     */
    public IterativeParallelism(ParallelMapper parallelMapper) {
        this.parallelMapper = parallelMapper;
    }

    /**
     * Default constructor.
     */
    public IterativeParallelism() {
        parallelMapper = null;
    }


    /**
     * Convert given {@link List} to {@link String}.
     *
     * @param i    number of threads
     * @param list {@link List} list of elements
     * @return string representation of given list
     * @throws InterruptedException if error occurs
     */
    @Override
    public String join(int i, List<?> list) throws InterruptedException {
        Function<List<?>, String> joiner = objects -> objects.stream().map(Object::toString).collect(Collectors.joining());
        return doItParallel(i, list, joiner, joiner);
    }

    /**
     * Return elements of given list which satisfy given predicate.
     *
     * @param i         number of threads
     * @param list      {@link List} list of elements
     * @param predicate {@link Predicate} predicate for filter
     * @param <T>       given type
     * @return list of elements satisfying predicate
     * @throws InterruptedException if error occurs
     */
    @Override
    public <T> List<T> filter(int i, List<? extends T> list, Predicate<? super T> predicate) throws InterruptedException {
        Function<List<? extends T>, List<T>> listFilter = l -> l.stream().filter(predicate).collect(Collectors.toList());
        return doItParallel(i, list, listFilter, concatter());
    }

    private <T> Function<List<? extends List<T>>, List<T>> concatter() {
        return objects -> objects.stream().flatMap(Collection::stream).collect(Collectors.toList());
    }

    /**
     * Apply given function to elements of given list and return this list.
     *
     * @param i        number of threads
     * @param list     {@link List} list of elements
     * @param function {@link Function} function for apply
     * @param <T>      given type
     * @param <U>      result type
     * @return list of elements after applying given function to it
     * @throws InterruptedException if error occurs
     */
    @Override
    public <T, U> List<U> map(int i, List<? extends T> list, Function<? super T, ? extends U> function) throws InterruptedException {
        Function<List<? extends T>, List<U>> listMap = l -> l.stream().map(function).collect(Collectors.toList());
        return doItParallel(i, list, listMap, concatter());
    }

    /**
     * Return maximum element of given list.
     *
     * @param i          number of threads
     * @param list       {@link List} list of elements
     * @param comparator {@link Comparator} comparator
     * @param <T>        given type
     * @return maximum of all elements
     * @throws InterruptedException if error occurs
     */
    @Override
    public <T> T maximum(int i, List<? extends T> list, Comparator<? super T> comparator) throws InterruptedException {
        Function<List<? extends T>, T> maximum = l -> Collections.max(l, comparator);
        return doItParallel(i, list, maximum, maximum);
    }

    /**
     * Return minimum element of given list.
     * <p>
     * It calls {@link IterativeParallelism#maximum(int, List, Comparator)} and pass reversed comparator.
     * </p>
     *
     * @param i          number of threads
     * @param list       {@link List} list of elements
     * @param comparator {@link Comparator} comparator
     * @param <T>        given type
     * @return minimum of all elements
     * @throws InterruptedException if error occurs
     */
    @Override
    public <T> T minimum(int i, List<? extends T> list, Comparator<? super T> comparator) throws InterruptedException {
        return maximum(i, list, comparator.reversed());
    }

    /**
     * Check if all elements of given list satisfy given predicate.
     *
     * @param i         number of threads
     * @param list      {@link List} list of elements
     * @param predicate {@link Predicate} predicate
     * @param <T>       given type
     * @return <tt>true</tt> if all elements satisfy given predicate
     * @throws InterruptedException if error occurs
     */
    @Override
    public <T> boolean all(int i, List<? extends T> list, Predicate<? super T> predicate) throws InterruptedException {
        Function<List<? extends T>, Boolean> all = l -> l.stream().allMatch(predicate);
        Function<List<Boolean>, Boolean> allJoiner = l -> l.stream().allMatch(Boolean::booleanValue);
        return doItParallel(i, list, all, allJoiner);
    }

    /**
     * Check whether any element from given list satisfy given predicate.
     *
     * @param i         number of threads
     * @param list      {@link List} list of elements
     * @param predicate {@link Predicate} predicate
     * @param <T>       given type
     * @return <tt>true</tt> if any element satisfies given predicate
     * @throws InterruptedException if error occurs
     */
    @Override
    public <T> boolean any(int i, List<? extends T> list, Predicate<? super T> predicate) throws InterruptedException {
        Function<List<? extends T>, Boolean> all = l -> l.stream().anyMatch(predicate);
        Function<List<Boolean>, Boolean> anyJoiner = l -> l.stream().anyMatch(Boolean::booleanValue);
        return doItParallel(i, list, all, anyJoiner);
    }

    private <T> List<List<? extends T>> splitList(int threads, List<? extends T> list) {
        threads = Math.min(Math.max(1, threads), list.size());
        List<List<? extends T>> listParts = new ArrayList<>();
        int mod = list.size() % threads;
        final int chunkSize = list.size() / threads;
        int begin;
        int end = 0;
        while (end != list.size()) {
            begin = end;
            end = begin + chunkSize;
            if (mod > 0) {
                end++;
                mod--;
            }
            listParts.add(list.subList(begin, end));
        }
        return listParts;
    }

    private <T, R> R doItParallel(int threadsCount, List<? extends T> list, Function<List<? extends T>, R> operation, Function<? super List<R>, R> result) throws InterruptedException {
        if (parallelMapper != null) {
            return doItParallelWithMapper(threadsCount, list, operation, result);
        }

        List<List<? extends T>> splitList = splitList(threadsCount, list);

        List<ParallelOperation<List<? extends T>, R>> operations = new ArrayList<>(splitList.size());
        splitList.forEach(objects -> operations.add(new ParallelOperation<>(objects, operation, null)));

        List<Thread> threads = new ArrayList<>();
        operations.forEach(rParallelOperation -> threads.add(new Thread(rParallelOperation)));

        threads.forEach(Thread::start);

        for (Thread t : threads) {
            t.join();
        }

        List<R> operationResults = new ArrayList<>();
        for (ParallelOperation<List<? extends T>, R> op: operations) {
            operationResults.add(op.getResult());
        }

        return result.apply(operationResults);
    }

    private <T, R> R doItParallelWithMapper(int threadsCount, List<? extends T> list, Function<List<? extends T>, R> operation, Function<? super List<R>, R> result) throws InterruptedException {
        List<List<? extends T>> splitList = splitList(threadsCount, list);
        return result.apply(parallelMapper.map(operation, splitList));
    }
}
