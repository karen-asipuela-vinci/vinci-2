package Server;

import Blacklist.BlacklistService;
import Domaine.Query;
import Domaine.QueryFactory;

import java.util.Scanner;

//s'occupe de lire au clavier, créer Query et démarrer les QueryHandler
public class ProxyServer {
    //necessite une QueryFactory pour créer Query
    QueryFactory queryFactory;
    //necessite un BlacklistService pour vérifier si le domaine est blacklisté
    BlacklistService blacklistService;

    //constructeur
    //on rajoute le BlacklistService
    /**
     * Constructeur
     *
     * @param queryFactory Factory de requêtes
     * @param blacklistService Service de blacklistage
     */
    public ProxyServer(QueryFactory queryFactory, BlacklistService blacklistService) {
        this.queryFactory = queryFactory;
        this.blacklistService = blacklistService;
    }

    /**
     * Démarrer le serveur
     */
    public void startServer() {
        //pour corriger mon erreur, changer l'ordre du while et du try
        try(Scanner sc = new Scanner(System.in)) {
            while(true) {
                //lire au clavier
                System.out.println("Veuillez saisir une URL :");
                String url = sc.nextLine();
                //créer Query
                Query query = this.queryFactory.getQuery();
                //besoin de setter l'url et le QueryMethod
                query.setUrl(url);
                query.setMethod(Query.QueryMethod.GET);
                //vérifier si le domaine est blacklisté
                if(blacklistService.check(query)) {
                    //démarrer QueryHandler
                    QueryHandler queryHandler = new QueryHandler(query);
                    queryHandler.start();
                } else {
                    System.err.println("Query rejected : domain blacklisted !");
                }

            }
        }
    }
}
