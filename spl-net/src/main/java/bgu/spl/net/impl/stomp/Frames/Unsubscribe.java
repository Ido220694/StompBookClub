package bgu.spl.net.impl.stomp.Frames;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Unsubscribe extends Frame{
    private String id;
    private int receipt;


    public Unsubscribe(){
    }

    public String getId(){
        return id;
    }

    public void setId(String ID){
        id=ID;
    }


    public int getRecId() {
        return receipt;
    }

    public void setReceipt(String receipt1) {
        receipt = Integer.parseInt(receipt1);
    }
}
