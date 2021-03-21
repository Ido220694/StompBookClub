package bgu.spl.net.srv;

import java.io.IOException;

public interface Connections<T> {

    boolean send(int connectionId, T msg);

    void send(String channel, T msg);

    void disconnect(int connectionId);

//    void connect(int connectionid, ConnectionHandler<T> connectionHandler);


    int add(ConnectionHandler<T> handler);

    int size();
}
