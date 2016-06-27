package ru.ifmo.ctddev.kiryukhin.hello;

import info.kgeorgiy.java.advanced.hello.HelloClient;

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.net.*;
import java.nio.charset.Charset;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

/**
 * It implements simple UDP client.
 *
 * @author Vladislav Kiryukhin
 */
public class HelloUDPClient implements HelloClient {

    /**
     * Start client with given params
     * @param host Host
     * @param port Port
     * @param prefix Prefix
     * @param requests Requests per thread
     * @param threads Threads count
     */
    public void start(String host, int port, String prefix, int requests, int threads) {
        ExecutorService pool = Executors.newFixedThreadPool(threads);
        try {
            InetAddress addr = InetAddress.getByName(host);
            for (int i = 0; i < threads; i++) {
                final int threadNum = i;
                pool.submit(() -> {
                    try (final DatagramSocket socket = new DatagramSocket()) {
                        socket.setSoTimeout(500);
                        byte[] buffer = new byte[socket.getReceiveBufferSize()];
                        int current = 0;
                        while (current != requests) {
                            byte[] message = String.format("%s%d_%d", prefix, threadNum, current).getBytes("UTF-8");
                            System.out.println(String.format("%s%d_%d", prefix, threadNum, current));

                            DatagramPacket replyingPacket = new DatagramPacket(buffer, buffer.length);

                            String requiredResponse = String.format("Hello, %s%d_%d", prefix, threadNum, current);
                            String response = "";
                            while (!response.equals(requiredResponse)) {
                                try {
                                    socket.send(new DatagramPacket(message, message.length, addr, port));
                                    socket.receive(replyingPacket);
                                    response = new String(replyingPacket.getData(), 0, replyingPacket.getLength(), Charset.forName("UTF-8"));
                                } catch (IOException ignored) { }
                            }
                            current++;
                            System.out.println(response);
                        }
                    } catch (SocketException | UnsupportedEncodingException e) {
                        System.err.println(String.format("[Client] Socket exception in thread #%d.", threadNum));
                    }
                });
            }
            pool.shutdownNow();
            pool.awaitTermination(5, TimeUnit.DAYS);
        } catch (UnknownHostException e) {
            System.err.println(String.format("[Client] Unable to start client: %s", e.getMessage()));
        } catch (InterruptedException e) {
            System.err.println(String.format("[Client] Unable to close client: %s", e.getMessage()));
        } finally {
            pool.shutdownNow();
        }
    }
}
