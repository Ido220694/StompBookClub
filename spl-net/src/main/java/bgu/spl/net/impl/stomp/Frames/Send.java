package bgu.spl.net.impl.stomp.Frames;



public class Send extends Frame {

    private String destination;
    private String body;


    public Send(){

    }

    public String getDestination(){
        return destination;
    }

    public void  setDestination(String Destination){
        destination=Destination;
    }

    public String getBody(){
        return body;
    }

    public void setBody(String bdy){
        body = bdy ;
    }




}
