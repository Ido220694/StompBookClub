package bgu.spl.net.impl.stomp.Frames;


import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Error extends Frame {
    private String message;
    private String The_message;
    private String body;

    public Error(){

    }

    public String getErrorMsg(){
        return body;
    }

//    public String getReceipt() {
//        return receipt_id;
//    }

    public String message() {
        return message;
    }

//    public void setReceipt(String Receipt) {
//        receipt_id=Receipt;
//    }

    public void setMessage(String Message) {
        message=Message;
    }

    //    @Override
    public void setBody(String body) {
        this.body = body;
    }



//
    public void setErrorMsg(String errorMsg) {
        this.body = errorMsg;
    }

    public void setThe_message(String the_message) {
        The_message = the_message;
    }

//
//    public String[] getErr() {
//        return err;
//    }

//    public void setErr(String[] err) {
//        this.err = err;
//    }

}