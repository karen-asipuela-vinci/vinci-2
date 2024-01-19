package Main;


import Blacklist.BlacklistService;
import Domaine.QueryFactory;
import Domaine.QueryFactoryImpl;
import Server.ProxyServer;

public class Main {
    public static void main(String[] args) {
        //update début atelier 10
        //injection de dépendance
        //Il faut d'abord créer QueryFactory -> besoin de QueryFactoryImpl
        QueryFactory queryFactory = new QueryFactoryImpl();
        //besoin de vérifier si le domaine est blacklisté -> besoin de BlacklistService
        BlacklistService blacklistService = new BlacklistService();
        //puis ProxyServer -> besoin de QueryFactory
        ProxyServer proxyServer = new ProxyServer(queryFactory, blacklistService);
        //puis démarrer le serveur
        proxyServer.startServer();
    }
}
