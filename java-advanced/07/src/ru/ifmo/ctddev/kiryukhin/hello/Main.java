package ru.ifmo.ctddev.kiryukhin.hello;

public class Main {

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("server/client [prefix requests threads]");
            return;
        }

        if (args[0].equals("server")) {
            HelloUDPServer server = new HelloUDPServer();
            server.start(23123, 1);
        }

        if (args[0].equals("client")) {
            HelloUDPClient client = new HelloUDPClient();
            client.start("localhost", 23123, args[1], Integer.parseInt(args[2]), Integer.parseInt(args[3]));
        }
    }
}
