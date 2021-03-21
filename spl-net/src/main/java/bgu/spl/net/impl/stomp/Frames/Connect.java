package bgu.spl.net.impl.stomp.Frames;


public class Connect extends Frame {
    public double accept_version;
    public String host;
    public String passcode;
    public String login;
    public String port;

    public Connect(){
    }

    public double getAccept_version(){
        return accept_version;
    }

    public String getHost(){
        return host;
    }

    public String getPort(){
        return port;
    }

    public String getLogin(){
        return login;
    }

    public String getPasscode(){
        return passcode;
    }

    public void setAccept_version(double version){
        accept_version = version;
    }

    public void setHost(String Host){
        host = Host.split(";", 2)[0];
        port = Host.split(":", 2)[1];
    }

    public void setlogin(String Login){
        login = Login;
    }

    public void setPasscode(String Passcode){
        passcode = Passcode;
    }


}
