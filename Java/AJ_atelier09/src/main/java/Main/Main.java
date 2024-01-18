package Main;


import Server.ProxyServer;

public class Main {
    public static void main(String[] args) {
        //Créer proxyServer
        ProxyServer proxyServer = new ProxyServer();
        //Démarrer proxyServer
        proxyServer.startServer();
    }
}
