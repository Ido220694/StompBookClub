package bgu.spl.net.impl.stomp;

import bgu.spl.net.srv.ConnectionsImpl;
import bgu.spl.net.srv.Server;

import java.io.FileNotFoundException;

public class StompServer {

    public static void main(String[] args) throws FileNotFoundException {
        if(args[1].equals("Tpc")){
            Server.threadPerClient(Integer.parseInt(args[0]) ,StompMessagingProtocolImpl::new,MessageEncoderDecoderStomp::new).serve();

        }
        else if(args[1].equals("Reactor")){
            Server.reactor(21, Integer.parseInt(args[0]), StompMessagingProtocolImpl::new, MessageEncoderDecoderStomp::new ).serve();
        }

    }
}