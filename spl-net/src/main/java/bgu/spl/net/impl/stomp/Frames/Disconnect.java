package bgu.spl.net.impl.stomp.Frames;



public class Disconnect extends Frame {
    private int receipt;

    public Disconnect(){
    }
    public int getReceipt(){
        return receipt;
    }
    public void setReceipt(String Receipt){
        receipt = Integer.parseInt(Receipt);
    }
}
