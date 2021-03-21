package bgu.spl.net.impl.stomp;

import bgu.spl.net.api.MessageEncoderDecoder;
import bgu.spl.net.impl.stomp.Frames.*;
import bgu.spl.net.impl.stomp.Frames.Error;
//import org.graalvm.compiler.core.common.FieldsScanner;

import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.nio.charset.StandardCharsets;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;

public class MessageEncoderDecoderStomp implements MessageEncoderDecoder<Frame> {
    private LinkedList<Byte> bytes = new LinkedList<>();
    private int i = 0;

    @Override
    public Frame decodeNextByte(byte nextByte) {
        if (nextByte == 0) {
            byte[] bytesArr = new byte[bytes.size()];
            bytes.forEach(b -> bytesArr[i++] = b);
            Frame frame = deFrame(bytesArr);

            bytes.clear();
            i = 0;
            return frame;
        } else {
            bytes.add(nextByte);
            return null;
        }
    }

    @SuppressWarnings("unchecked")
    private Frame deFrame(byte[] bytes) {
//        for (int j = 0; j < bytes.length; j++) {
//            System.out.print(byteAsString(bytes[j])+", ");
//        }
//        System.out.println();
        try {

            String str = new String(bytes, StandardCharsets.UTF_8);
            String[] lines = Frame.getStringAsLines(str);

            String str_type = lines[0];
            Class<? extends Frame> msgType = (Class<? extends Frame>) Class.forName(getClassName(str_type));
            Constructor<? extends Frame> constructor = msgType.getConstructor();
            Frame frame = constructor.newInstance();
            Map<Field, Object> map = createFields(msgType, lines);

            for (Map.Entry<Field, Object> entry : map.entrySet()) {
                Field field = entry.getKey();
                Object value = entry.getValue();

                field.setAccessible(true);
                field.set(frame, value);
            }
            //Frame frame = SetFields(lines);
            return frame;

        } catch (ClassNotFoundException | NoSuchMethodException | InstantiationException | IllegalAccessException e) {
            e.printStackTrace();
        } catch (InvocationTargetException e) {
            e.getTargetException().printStackTrace();
        }
        return null;
    }

    private Map<Field, Object> createFields(Class<? extends Frame> msgType, String[] lines) {
        String sfield = "";
        String svalue= "";
        Map<Field, Object> map = new HashMap<>();
        try {
            for (int i=1; i<lines.length; i++) {
                if (lines[i].equals("")) {
                    continue;
                }

                int limit = 2;
                if (!lines[i].contains(":") && !lines[i].equals("")){
                    Field f = msgType.getDeclaredField("body");
//                    Field f = msgType.getField("body");
                    String v = lines[i];
                    map.put(f, v);
                }
                else {
                    sfield = lines[i].split(":", limit)[0];
                    sfield = sfield.replace('-','_');

                    svalue = lines[i].split(":", limit)[1];

                    Field field = msgType.getDeclaredField(sfield);
                    Object value = str2value(svalue, field.getType());

                    map.put(field, value);
                }
            }
        } catch (NoSuchFieldException e) {
            System.out.println(msgType.getSimpleName() + " does NOT has '" + sfield + "' field");
            e.printStackTrace();
        }
        return map;
    }

    @SuppressWarnings("unchecked")
    private <T> T str2value(String svalue, Class<T> type) {
        if (type == Integer.class || type == int.class || type == Integer.TYPE) {
            return (T) (Integer) Integer.parseInt(svalue);
        }
        if (type == Double.class || type == double.class || type == Double.TYPE) {
            return (T) (Double) Double.parseDouble(svalue);
        }
        return (T) svalue;
    }

    public static String getClassName(String typeName) {
        String typeNameLower = typeName.toLowerCase();
        typeName = typeName.charAt(0) + typeNameLower.substring(1);
        return "bgu.spl.net.impl.stomp.Frames." + typeName;
    }

    @Override
    public byte[] encode(Frame frm) {

        String msg = "";
        Class<? extends Frame> frameType = frm.getClass();
        byte[] encodedBytes = null;

        String line;
        try {
//            Field[] fields = frameType.getFields();
            Field[] fields = null;
            String s = frm.getFrameType();
            if (s.equals("CONNECTED")){
                fields = Connected.class.getDeclaredFields();
            }
            else if(s.equals("RECEIPT")){
                fields = Receipt.class.getDeclaredFields();
            }
            else if(s.equals("MESSAGE")){
                fields = Message.class.getDeclaredFields();
            }
            else if(s.equals("ERROR")){
                fields = Error.class.getDeclaredFields();
            }
//            Field[] fields = frameType.class.getDeclaredFields();

//            Field [] fields = frameType.getFields();
            msg += frm.getClass().getSimpleName().toUpperCase() + "\r";
//            if (frm.getFrameType().equals("CONNECTED")){
//                msg += "version:1.2";
//            }
//            else if(frm.getFrameType().equals("RECEIPT")){
//                line = Integer.toString(frm.getRecId());
//                msg+= line;
//            }
//            else if(frm.getFrameType().equals("MESSAGE")){
//                msg+= Integer.toString(frm.getSubIdA()) + "\r";
//                msg+= Integer.toString(frm.getMsgIdA()) + "\r";
//                msg+=  frm.getDestinationA() +"\r";
//            }
//            else if(frm.getFrameType().equals("ERROR")){
//                msg+=
//            }
            for (Field field : fields) {
                field.setAccessible(true);
                if(field.getName()!="body"){
                    line = field.getName().replace('_','-') + ":" + field.get(frm);
                    msg += line + "\r";
                }
            }

            line = frm.getBody();
            msg += "\r" + line;

            String str = "\0";
            msg += str;

            encodedBytes = msg.getBytes(StandardCharsets.UTF_8);
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        }
//        for (int j = 0; j < encodedBytes.length; j++) {
//            System.out.print(byteAsString(encodedBytes[j])+", ");
//        }
//        System.out.println();
        return encodedBytes;
    }
//
//    private Frame SetFields(String[] lines){
//        int limit = 2;
//        Frame f = null;
//
//        if (lines[0].equals("CONNECT")){
//            Connect connect = new Connect();
//            connect.setAccept_version(1.2);
//            String pa = lines[4].split(":", limit)[1];
//            connect.setPasscode(pa);
//            String lo = lines[3].split(":", limit)[1];
//            connect.setlogin(lo);
//            String ho = lines[2].split(":", limit)[1];
//            connect.setHost(ho);
//            f = (Frame) connect;
//            return f;
//        }
//        else if(lines[0].equals("DISCONNECT")){
//            Disconnect disconnect = new Disconnect();
//            String re = lines[1].split(":", limit)[1];
//            disconnect.setReceipt(re);
//            f = (Frame) disconnect;
//            return f;
//        }
//
//        else if(lines[0].equals("SEND")){
//            Send send = new Send();
//            String de = lines[1].split(":", limit)[1];
//            send.setDestination(de);
//            send.setBody(lines[3]);
//            f = (Frame) send;
//            return f;
//
//        }
//        else if(lines[0].equals("SUBSCRIBE")){
//            Subscribe subscribe = new Subscribe();
//            String de = lines[1].split(":", limit)[1];
//            subscribe.setDest(de);
//            String i = lines[2].split(":", limit)[1];
//            subscribe.setID(i);
//            String re = lines[3].split(":", limit)[1];
//            subscribe.setRECID(re);
//            f = (Frame) subscribe;
//            return f;
//
//        }
//        else if(lines[0].equals("UNSUBSCRIBE")){
//            Unsubscribe unsubscribe = new Unsubscribe();
//            String i = lines[1].split(":", limit)[1];
//            unsubscribe.setId(i);
//            String re = lines[2].split(":", limit)[1];
//            unsubscribe.setReceipt(re);
//            f = (Frame) unsubscribe;
//            return f;
//        }
//
//        return f;
//    }
}