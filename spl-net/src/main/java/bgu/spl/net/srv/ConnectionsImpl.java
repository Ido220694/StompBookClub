package bgu.spl.net.srv;

import bgu.spl.net.impl.stomp.Frames.Message;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicInteger;


public class ConnectionsImpl<T> implements Connections<T> {

    private HashMap<Integer, ConnectionHandler<T>> IdMap;
    private HashMap<String, String> users;
    private ConcurrentHashMap<String, Boolean> LoggedUsers;
    private ConcurrentHashMap<String, LinkedList<MyPair<Integer, Integer>>> topicList;
    private ConcurrentHashMap<Integer, String> topicsBySubscritionId;
    private AtomicInteger id = new AtomicInteger(0);

    public ConnectionsImpl() {
        users = new HashMap<>();
        topicsBySubscritionId = new ConcurrentHashMap<>();
        LoggedUsers = new ConcurrentHashMap<>();
        IdMap = new HashMap<>();
        topicList = new ConcurrentHashMap<>();
    }

    public void disconnect(int connectionId) {
        IdMap.remove(connectionId);
    }

    @Override
    public int add(ConnectionHandler<T> handler) {
        int nextId = id.getAndIncrement();
        IdMap.put(nextId, handler);
        return nextId;
    }

    public boolean send(int connectionId, T msg) {

        if (IdMap.containsKey(connectionId)) {
            IdMap.get(connectionId).send(msg);
            return true;
        }
        return false;
    }

    @Override
    public void send(String channel, T msg) {
        Message message = (Message) msg;

        for (MyPair<Integer, Integer> pair : topicList.get(channel)) {
            int subscriptionId = pair.getFirst();
            int Id = pair.getSecond();
            message.setSubscription(subscriptionId);
            IdMap.get(Id).send(msg);


        }
    }

    public ConcurrentHashMap<String, LinkedList<MyPair<Integer, Integer>>> getTopicList() {
        return topicList;
    }

    public ConcurrentHashMap<String, Boolean> getLoggedUsers() {
        return LoggedUsers;
    }

    public HashMap<String, String> getUsers() {
        return users;
    }

    public ConcurrentHashMap<Integer, String> getTopicsBySubscriptionId() {
        return topicsBySubscritionId;
    }


    public int size() {
        return IdMap.size();
    }
}
