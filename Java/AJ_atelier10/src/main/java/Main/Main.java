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
    /*
    remarque pour l'exo sur création de .jar:
    - via IntelliJ, il faut aller dans File -> Project Structure -> Artifacts
    - cliquer sur le + et choisir JAR -> From modules with dependencies...
    - choisir le Main class
    - choisir le répertoire de sortie
    - cliquer sur OK
    - aller dans Build -> Build Artifacts -> Build
    - le .jar se trouve dans le répertoire de sortie

    Pour créer une "automatisation", adapter le fichier pom.xml:
    - ajouter la balise <build>...</build>
    - ajouter la balise <plugins>...</plugins>
    - ajouter la balise <plugin>...</plugin>
    - ajouter la balise <executions>...</executions>
    etc -> voir fichier

    Pour relancer la construction, crtl crtl + mvn clean compile assembly:single
     */
}
