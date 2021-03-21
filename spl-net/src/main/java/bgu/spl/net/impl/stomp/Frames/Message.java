package bgu.spl.net.impl.stomp.Frames;


import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Message extends Frame {

    private Integer subscription;
    private Integer Message_id;
    private String destination;
    private String body;

    public Message(){

    }

    public Integer getMessage_id() {
        return Message_id;
    }

    public int getSubscription() {
        return subscription;
    }
    public String getDestination(){
        return destination;
    }

    public void setMessage_id(Integer Message) {
        Message_id=Message;
    }

    public void setSubscription(Integer Subscription) {
        subscription=Subscription;
    }

    public void setDestination(String Destination) {
        destination=Destination;
    }

//    @Override
    public void setBody(String body) {
        this.body = body;
    }

    @Override
    public String getBody() {
        return body;
    }



}

