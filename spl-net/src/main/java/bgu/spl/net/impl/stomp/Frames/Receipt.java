package bgu.spl.net.impl.stomp.Frames;


import java.util.HashMap;


public class Receipt extends Frame {
    private int receipt_id;

    public Receipt() {
    }

    public int getRecId() {
        return receipt_id;
    }
    public void setRecId(int Receipt_id) {
        receipt_id=Receipt_id;
    }



}
