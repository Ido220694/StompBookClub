package bgu.spl.net.impl.stomp.Frames;


import java.util.HashMap;
import java.util.Map;

public class Connected extends Frame {

    public double version;

    public Connected(){
    }

    public double getVersion(){
        return version;
    }

    public void setVersion(){
        version=1.2;
    }


}
