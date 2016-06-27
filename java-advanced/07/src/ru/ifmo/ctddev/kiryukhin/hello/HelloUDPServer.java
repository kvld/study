package ru.ifmo.ctddev.kiryukhin.hello;

import info.kgeorgiy.java.advanced.hello.HelloServer;

import java.io.IOException;
import java.net.*;
import java.nio.charset.Charset;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * It implements simple UDP server.
 *
 * @author Vladislav Kiryukhin
 */
public class HelloUDPServer implements HelloServer {
    private ExecutorService pool;
    private DatagramSocket socket;
    private boolean isRunning = false;

    /**
     * Start server with given params
     * @param port Port for server
     * @param threads Threads count
     */
    public void start(int port, int threads) {
        if (isRunning) {
            throw new IllegalStateException("[Server] Server already running.");
        }
        isRunning = true;
        pool = Executors.newFixedThreadPool(threads);
        try {
            socket = new DatagramSocket(port, InetAddress.getByName("localhost"));
            socket.setSoTimeout(500);
            for (int i = 0; i < threads; i++) {
                final int threadNum = i;
                pool.submit(() -> {
                    try {
                        byte[] buffer = new byte[socket.getReceiveBufferSize()];
                        DatagramPacket incomingPacket = new DatagramPacket(buffer, buffer.length);
                        while (isRunning) {
                            try {
                                socket.receive(incomingPacket);
                                byte[] data = incomingPacket.getData();

                                String msg = "Hello, " + new String(data, 0, incomingPacket.getLength(), Charset.forName("UTF-8"));
                                byte[] reply = msg.getBytes("UTF-8");

                                DatagramPacket replyingPacket = new DatagramPacket(reply, reply.length, incomingPacket.getAddress(), incomingPacket.getPort());
                                socket.send(replyingPacket);
                            } catch (IOException ignored) { }
                        }
                    } catch (SocketException e) {
                        System.err.println(String.format("[Server] Socket exception in thread #%d.", threadNum));
                    }

                });
            }
        } catch (SocketException | UnknownHostException e) {
            System.err.println(String.format("[Server] Unable to start server: %s", e.getMessage()));
            isRunning = false;
        }

    }

    /**
     * Close server
     */
    public void close() {
        isRunning = false;
        socket.close();
        pool.shutdown();
    }
}
