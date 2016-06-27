package ru.ifmo.ctddev.kiryukhin.mapper;

/**
 * Simple counter for multithreading
 */
public class Counter {
    private int c = 0;

    /**
     * Ctor for counter
     * @param size counter's size
     */
    public Counter(int size) {
        this.c = size;
    }

    /**
     * Get counter value
     * @return counter value
     */
    public synchronized int getValue() {
        return c;
    }

    /**
     * Set counter value
     * @param value new value for counter
     */
    public synchronized void setValue(int value) {
        c = value;
    }

    /**
     * Decrement counter
     */
    public synchronized void dec() {
        c--;
        if (getValue() == 0) {
            notify();
        }
    }

    /**
     * Set counter to 0
     */
    public synchronized void setZero() {
        setValue(0);
        notify();
    }
}
