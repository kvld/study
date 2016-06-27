package ru.ifmo.ctddev.kiryukhin.crawler;

import info.kgeorgiy.java.advanced.crawler.*;
import javafx.util.Pair;

import java.io.File;
import java.io.IOException;
import java.net.MalformedURLException;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.Collectors;

/**
 * Class is the concurrent implementation of {@link info.kgeorgiy.java.advanced.crawler.Crawler} interface.
 * It allows to download the given site recursively with the depth specified in parameter of method {@link #download}.
 *
 * @author Vladislav Kiryukhin
 */
public class WebCrawler implements Crawler {
    private Downloader downloader = null;
    private int perHost = 0;
    private ExecutorService downloadService = null;
    private ExecutorService extractService = null;

    /**
     * Default count threads for downloading
     */
    public static final int DEFAULT_DOWNLOADERS_COUNT = 10;
    /**
     * Default count threads for extracting
     */
    public static final int DEFAULT_EXTRACTORS_COUNT = 10;
    /**
     * Default depth
     */
    public static final int DEFAULT_DEPTH = 2;
    /**
     * Default count connections per host
     */
    public static final int DEFAULT_PER_HOST_COUNT = 10;
    /**
     * Default path for cache
     */
    public static final String DEFAULT_CACHE_PATH = "./cache";

    private final AtomicInteger counter = new AtomicInteger(0);
    private final ConcurrentHashMap<String, Semaphore> semaphores = new ConcurrentHashMap<>();
    private final ConcurrentHashMap<String, ConcurrentLinkedQueue<Pair<String, Integer>>> downloadQueue = new ConcurrentHashMap<>();
    private final ConcurrentHashMap<String, Object> results = new ConcurrentHashMap<>();
    private final ConcurrentHashMap<String, IOException> errors = new ConcurrentHashMap<>();
    private final ConcurrentHashMap<String, Object> visited = new ConcurrentHashMap<>();

    /**
     * Method that accepts the parameters in form:
     * <p>
     * <code>url [downloads [extractors [perHost]]]</code>
     * </p>
     * and starts crawling with {@link info.kgeorgiy.java.advanced.crawler.CachingDownloader}
     * on given url with depth = 1.
     * The files are saved in default directory.
     *
     * @param args command line arguments
     */
    public static void main(String[] args) {
        if (args == null || args.length == 0 || args.length > 4) {
            System.out.println("usage: WebCrawler url [downloads [extractors [perHost]]]");
            return;
        }

        String url = args[0];
        int downloaders = DEFAULT_DOWNLOADERS_COUNT;
        int extractors = DEFAULT_EXTRACTORS_COUNT;
        int perHost = DEFAULT_PER_HOST_COUNT;
        try {
            if (args.length > 3) {
                perHost = Integer.parseInt(args[3]);
            }
            if (args.length > 2) {
                extractors = Integer.parseInt(args[2]);
            }
            if (args.length > 1) {
                downloaders = Integer.parseInt(args[1]);
            }
        } catch (NumberFormatException ignored) {
            System.out.println("usage: WebCrawler url [downloads [extractors [perHost]]]");
            return;
        }

        try (WebCrawler crawler = new WebCrawler(new CachingDownloader(new File(DEFAULT_CACHE_PATH)), downloaders, extractors, perHost)) {
            Result res = crawler.download(url, DEFAULT_DEPTH);
            System.out.println(String.format("%d pages downloaded, %d errors", res.getDownloaded().size(), res.getErrors().size()));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Default constructor
     */
    public WebCrawler() { }

    /**
     * Constructor for WebCrawler.
     * It accepts instance of {@link Downloader} and using it for crawling.
     *
     * @param downloader  the {@link info.kgeorgiy.java.advanced.crawler.Downloader} class
     *                    that specifies how downloading should be done
     * @param downloaders maximum number of threads that can be used to download the page
     * @param extractors  maximum number of threads that can be used to extract links from pages
     * @param perHost     maximum number of threads to download from the same host
     */
    public WebCrawler(Downloader downloader, int downloaders, int extractors, int perHost) {
        this.downloader = downloader;
        this.perHost = perHost;

        this.downloadService = Executors.newFixedThreadPool(downloaders);
        this.extractService = Executors.newFixedThreadPool(extractors);
    }

    private void downloadURLs(String host) {
        try {
            if (semaphores.get(host).tryAcquire()) {
                if (!downloadQueue.get(host).isEmpty()) {
                    Pair<String, Integer> task = downloadQueue.get(host).poll();
                    String url = task.getKey();
                    int depth = task.getValue();
                    if (visited.putIfAbsent(url, new Object()) == null) {
                        try {
                            Document document = downloader.download(url);
                            results.put(url, new Object());
                            incrementCounter();
                            extractService.submit(() -> this.extract(depth, document));
                        } catch (IOException e) {
                            errors.put(url, e);
                        } finally {
                            semaphores.get(host).release();
                            if (!downloadQueue.get(host).isEmpty()) {
                                incrementCounter();
                                downloadService.submit(() -> this.downloadURLs(host));
                            }
                        }
                    }
                } else {
                    semaphores.get(host).release();
                }
            }
        } finally {
            decrementCounter();
        }
    }

    private void extract(int depth, Document doc) {
        try {
            if (depth > 1) {
                List<String> links = doc.extractLinks();
                links.stream().distinct().forEach(url -> {
                    try {
                        String host = addUrlToQueue(url, depth - 1);
                        incrementCounter();
                        downloadService.submit(() -> this.downloadURLs(host));
                    } catch (MalformedURLException e) {
                        e.printStackTrace();
                    }
                });
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            decrementCounter();
        }
    }

    /**
     * Returns the list of visited pages and/or errors.
     *
     * @param url   the starting url for traversal
     * @param depth maximum depth for traversal
     * @return {@link Result} result of traversal given url and child-urls
     */
    @Override
    public Result download(String url, int depth) {
        try {
            String host = addUrlToQueue(url, depth);
            incrementCounter();
            downloadService.submit(() -> this.downloadURLs(host));
        } catch (MalformedURLException e) {
            e.printStackTrace();
            return null;
        }

        try {
            synchronized (counter) {
                while (counter.get() != 0) {
                    counter.wait();
                }
            }
        } catch (InterruptedException e) {
            close();
        }

        return new Result(results.keySet().stream().collect(Collectors.toList()), errors);
    }

    private void decrementCounter() {
        synchronized (counter) {
            counter.decrementAndGet();
            counter.notify();
        }
    }

    private void incrementCounter() {
        synchronized (counter) {
            counter.incrementAndGet();
            counter.notify();
        }
    }

    private String addUrlToQueue(String url, int depth) throws MalformedURLException {
        String host = URLUtils.getHost(url);
        semaphores.putIfAbsent(host, new Semaphore(perHost));
        downloadQueue.putIfAbsent(host, new ConcurrentLinkedQueue<>());
        downloadQueue.get(host).add(new Pair<>(url, depth));

        return host;
    }

    private void shutdownExecutorService(ExecutorService service) {
        service.shutdown();
        if (!service.isShutdown()) {
            try {
                service.awaitTermination(5, TimeUnit.SECONDS);
            } catch (InterruptedException e) {
                e.printStackTrace();
            } finally {
                service.shutdownNow();
            }
        }
    }

    /**
     * Closes instance of {@link WebCrawler}.
     */
    @Override
    public void close() {
        shutdownExecutorService(downloadService);
        shutdownExecutorService(extractService);
    }
}
