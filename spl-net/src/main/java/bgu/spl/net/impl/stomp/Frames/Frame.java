package bgu.spl.net.impl.stomp.Frames;



public abstract class Frame {

    /*
    todo:
        A. add fields for all classes extends {@link: Frame} fields should match "headers" (if field has a "-"(dash), just without it.
        B. if a class has "body" field, call it "body"
        C. for any class the server get (Connect, Send etc.) can has more fields, the frame server send can NOT.
        D. delete "getBody" from all classes(except Frame)
        E. add "getters" for all classes of frames the body recieves, and setters on the others
        F. After there are no more compilation errors, add an empty constructor to to Frame
     */

    private String body="";
    private String frameType;
    private int recId;
    private int SubIdA;
    private int MsgIdA;
    private String destinationA;

    public Frame() {
    }

    public static String[] getStringAsLines(String str) {
        str = str.replaceAll("\n\r", "\r").replaceAll("\n", "\r");
        String[] toSend = str.split("\r",0);
        if(toSend.length>1 && toSend[toSend.length-2].equals("")){
            toSend[toSend.length-1] = "body:"+toSend[toSend.length-1];
        }
        str = str.replaceAll("-", "_");
        return toSend;
    }

    public void setBodyA(String body) {
        this.body = body;
    }

    public String getBody(){
        return body;
    }

    public String getFrameType() {
        return frameType;
    }


    public void SetFrameType(String s){
        frameType = s;
    }


    public int getRecId() {
        return recId;
    }

    public void setRecIdA(int recId) {
        this.recId = recId;
    }


    public int getSubIdA() {
        return SubIdA;
    }

    public void setSubIdA(int subIdA) {
        SubIdA = subIdA;
    }

    public int getMsgIdA() {
        return MsgIdA;
    }

    public void setMsgIdA(int msgIdA) {
        MsgIdA = msgIdA;
    }

    public String getDestinationA() {
        return destinationA;
    }

    public void setDestinationA(String destinationA) {
        this.destinationA = destinationA;
    }
}
