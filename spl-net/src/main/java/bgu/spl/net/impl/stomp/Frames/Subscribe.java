package bgu.spl.net.impl.stomp.Frames;


import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Subscribe extends Frame{
    private String destination;
    private int id;
    private int receipt;

    public Subscribe(){
    }

    public int getId(){
        return id;
    }

    public String getDestination(){
        return destination;
    }


    public int getRecId(){
        return receipt;
    }

    public void setDest(String des){
        destination = des;
    }

    public void setID(String id1){
        id = Integer.parseInt(id1);
    }

    public void setRECID(String id1){
        receipt = Integer.parseInt(id1);
    }



}
