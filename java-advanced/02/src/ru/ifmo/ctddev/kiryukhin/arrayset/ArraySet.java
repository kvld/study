package ru.ifmo.ctddev.kiryukhin.arrayset;

import java.util.*;

public class ArraySet<E extends Comparable> extends AbstractSet<E> implements NavigableSet<E> {
    private List<E> list;
    private Comparator<? super E> comparator;

    public ArraySet() {
        this.list = Collections.emptyList();
        this.comparator = null;
    }

    public ArraySet(ArraySet<E> set) {
        this.list = set.list;
        this.comparator = set.comparator;
    }

    public ArraySet(Collection<E> collection) {
        this(collection, null);
    }

    public ArraySet(Collection<E> collection, Comparator<? super E> comparator) {
        this.list = new ArrayList<>();
        TreeSet<E> s = new TreeSet<>(comparator);
        s.addAll(collection);
        this.list.addAll(s);

        this.comparator = comparator;
    }

    @Override
    public Iterator<E> iterator() {
        return Collections.unmodifiableCollection(list).iterator();
    }

    @Override
    public int size() {
        return list.size();
    }

    private int lowerInd(E e) {
        int index = Collections.binarySearch(list, e, comparator);
        if (index >= 0) {
            return index - 1;
        }
        return -(index + 1) - 1;
    }

    private int floorInd(E e) {
        int index = Collections.binarySearch(list, e, comparator);
        if (index < 0) {
            return -(index + 1) - 1;
        }
        return index;
    }

    private int ceilingInd(E e) {
        int index = Collections.binarySearch(list, e, comparator);
        if (index < 0) {
            return -(index + 1);
        }
        return index;
    }

    private int higherInd(E e) {
        int index = Collections.binarySearch(list, e, comparator);
        if (index >= 0) {
            return index + 1;
        }
        return -(index + 1);
    }


    @Override
    public E lower(E e) {
        return get(lowerInd(e));
    }

    @Override
    public E floor(E e) {
        return get(floorInd(e));
    }

    @Override
    public E ceiling(E e) {
        return get(ceilingInd(e));
    }

    @Override
    public E higher(E e) {
        return get(higherInd(e));
    }

    private E get(int pos) {
        return (pos >= 0 && pos < list.size()) ? list.get(pos) : null;
    }


    @Override
    public E pollFirst() {
        throw new UnsupportedOperationException();
    }

    @Override
    public E pollLast() {
        throw new UnsupportedOperationException();
    }

    @Override
    public NavigableSet<E> descendingSet() {
        return new ArraySet<>(new ReversedList<>(list), Collections.reverseOrder(comparator));
    }

    @Override
    public Iterator<E> descendingIterator() {
        return new ReversedList<>(list).iterator();
    }

    @Override
    public NavigableSet<E> subSet(E fromElement, boolean fromInclusive, E toElement, boolean toInclusive) {
        return headSet(toElement, toInclusive).tailSet(fromElement, fromInclusive);
    }

    @Override
    public NavigableSet<E> headSet(E toElement, boolean inclusive) {
        int pos = inclusive ? floorInd(toElement) : lowerInd(toElement);

        ArraySet<E> newSet = new ArraySet<>();
        newSet.list = this.list.subList(0, pos + 1);
        newSet.comparator = comparator;

        return newSet;
    }

    @Override
    public NavigableSet<E> tailSet(E fromElement, boolean inclusive) {
        int pos = inclusive ? ceilingInd(fromElement) : higherInd(fromElement);

        ArraySet<E> newSet = new ArraySet<>();
        newSet.list = this.list.subList(pos, list.size());
        newSet.comparator = comparator;

        return newSet;
    }

    @Override
    public SortedSet<E> subSet(E fromElement, E toElement) {
        return subSet(fromElement, true, toElement, false);
    }

    @Override
    public SortedSet<E> headSet(E toElement) {
        return headSet(toElement, false);
    }

    @Override
    public SortedSet<E> tailSet(E fromElement) {
        return tailSet(fromElement, true);
    }

    @Override
    public Comparator<? super E> comparator() {
        return comparator;
    }

    @Override
    public E first() {
        if (isEmpty()) {
            throw new NoSuchElementException();
        }
        return list.get(0);
    }

    @Override
    public E last() {
        if (isEmpty()) {
            throw new NoSuchElementException();
        }
        return list.get(list.size() - 1);
    }

    @SuppressWarnings("unchecked")
    @Override
    public boolean contains(Object o) {
        return Collections.binarySearch(list, (E) o, comparator) >= 0;
    }

    public boolean isEmpty() {
        return this.size() == 0;
    }

    private static class ReversedList<E> extends AbstractList<E> implements RandomAccess {
        private List<E> list;
        private boolean reversed = false;

        public ReversedList(List<E> list) {
            if (list instanceof ReversedList) {
                this.list = list;
                reversed = !((ReversedList<E>)list).reversed;
            } else {
                this.list = list;
                reversed = false;
            }
        }

        @Override
        public int size() {
            return list.size();
        }

        @Override
        public E get(int index) {
            return reversed ? list.get(index) : list.get(list.size() - index - 1);
        }
    }
}
