package bgu.spl.net.impl.stomp;

import bgu.spl.net.api.StompMessagingProtocol;
import bgu.spl.net.impl.stomp.Frames.*;
import bgu.spl.net.impl.stomp.Frames.Error;
import bgu.spl.net.srv.Connections;
import bgu.spl.net.srv.ConnectionsImpl;
import bgu.spl.net.srv.MyPair;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicInteger;

public class StompMessagingProtocolImpl implements StompMessagingProtocol<Frame> {
    private ConnectionsImpl<Frame> connections;
    private int connectionId;
    private String currentUser;
    private boolean shouldTerminate;
    private LinkedList<String> topics;
    private AtomicInteger msgId = new AtomicInteger(0);



    @Override
    public void start(int connectionId, Connections<Frame> connections) {
        this.shouldTerminate = false;
        this.connectionId = connectionId;
        this.connections = (ConnectionsImpl<Frame>) connections;
        currentUser = null;
        topics = new LinkedList<>();

    }

    public void process(Frame message) {


        if (message instanceof Connect) {
            Connect connect = (Connect) message;
            connect.setHost(connect.getHost());
            String newHost = connect.getHost();
            String newPort = connect.getPort();

            // connection handler
            Connected connected = new Connected();
            connected.setVersion();
            connected.SetFrameType("CONNECTED");
            ConcurrentHashMap<String, Boolean> loggedUsers = connections.getLoggedUsers();
            HashMap<String, String> users = connections.getUsers();

            if(users.get(connect.getLogin()) !=null){
                if (connect.getPasscode().equals(users.get(connect.getLogin()))){
                    if (loggedUsers.get(connect.getLogin())){
                        Error error = new Error();
                        error.setBodyA("You can't re-login after you already logged-in");
                        error.setBody("You can't re-login after you already logged-in");
                        error.setMessage("User already logged in");
                        error.SetFrameType("ERROR");
                        error.setThe_message(translateFrameToString(connect));
                        connections.send(connectionId, error);
                    }
                    else {
                        currentUser = connect.getLogin();
                        loggedUsers.replace(connect.getLogin(), true);
                        currentUser = connect.getLogin();
                        connections.send(connectionId, connected);

                    }
                }
                else {
                    Error error = new Error();
                    error.setBodyA("You enterd a wrong password. try again");
                    error.setBody("You enterd a wrong password. try again");
                    error.setMessage("Wrong password");
                    error.setErrorMsg("You enterd a wrong password. you have other password");
                    error.SetFrameType("ERROR");
                    error.setThe_message(translateFrameToString(connect));
                    connections.send(connectionId, error);
                }
            }
            else {
                users.put(connect.getLogin(),connect.getPasscode());
                loggedUsers.put(connect.getLogin(), true);
                currentUser = connect.getLogin();
                connections.send(connectionId, connected);

            }

        } else if (message instanceof Subscribe) {
            Subscribe subscribe = (Subscribe) message;
            String topic = subscribe.getDestination();
            topics.add(topic);
            connections.getTopicList().putIfAbsent(topic, new LinkedList<>());
            connections.getTopicList().get(subscribe.getDestination()).add(new MyPair<Integer, Integer>(connectionId, subscribe.getId()));
            connections.getTopicsBySubscriptionId().putIfAbsent(subscribe.getId(), topic);

            Receipt receipt = new Receipt();
            receipt.setRecId(subscribe.getRecId());
            receipt.SetFrameType("RECEIPT");
            connections.send(connectionId, receipt);

        } else if (message instanceof Disconnect) {

            for (int i=0; i<topics.size(); i++){
                connections.getTopicList().get(topics.get(i)).removeIf(MyPair -> MyPair.getFirst() == connectionId);
            }

            Disconnect disconnect = (Disconnect) message;
            Receipt receipt = new Receipt();
            receipt.setRecId(disconnect.getReceipt());
            receipt.SetFrameType("RECEIPT");

            connections.getLoggedUsers().replace(currentUser, false);

            connections.send(connectionId, receipt);

            connections.disconnect(connectionId);
//
//            shouldTerminate = true;

        } else if (message instanceof Unsubscribe) {
            Unsubscribe unsubscribe = (Unsubscribe) message;
            String subscribtion = unsubscribe.getId();
            int s = Integer.parseInt(subscribtion);

            String topic = connections.getTopicsBySubscriptionId().get(s);
            connections.getTopicList().get(topic).removeIf(MyPair -> MyPair.getFirst() == connectionId);
            topics.remove(topic);

            Receipt receipt = new Receipt();
            receipt.setRecId(unsubscribe.getRecId());
            receipt.SetFrameType("RECEIPT");

            connections.send(connectionId, receipt);


        } else if (message instanceof Send) {
            Send send = (Send) message;
            String dest = send.getDestination();
            String body = send.getBody();
            Message message1 = new Message();
            message1.SetFrameType("MESSAGE");
            message1.setDestination(dest);
            message1.setBody(body);
            int nextId = msgId.getAndIncrement();;
            message1.setMessage_id(nextId);
            int sub;
            if(connections.getTopicList().containsKey(dest)){
                for (int i=0; i<connections.getTopicList().get(dest).size(); i++){
                    sub = connections.getTopicList().get(dest).get(i).getSecond();
                    message1.setSubscription(sub);
                    int coId = connections.getTopicList().get(dest).get(i).getFirst();
                    connections.send(coId, message1);
                }

            }

        }

    }


    public boolean shouldTerminate() {
        return shouldTerminate;
    }

    private String translateFrameToString(Connect connect){

        String msg = "\r" +"-----" + "\r";
        msg += "CONNECT" + "\r";
        msg += "accept-version:1.2" + "\r";
        msg += "host:" + connect.getHost() + "\r";
        msg += "login:" + connect.getLogin() + "\r";
        msg += "passcode:" + connect.getPasscode() + "\r";
        msg += "-----" ;


        return msg;
    }
}







