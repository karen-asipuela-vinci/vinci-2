package Server;

import Domaine.Query;
import Domaine.QueryFactory;

import java.util.Scanner;

//s'occupe de lire au clavier, créer Query et démarrer les QueryHandler
public class ProxyServer {
    //necessite une QueryFactory pour créer Query
    QueryFactory queryFactory;

    //constructeur
    public ProxyServer(QueryFactory queryFactory) {
        this.queryFactory = queryFactory;
    }

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
                //démarrer QueryHandler
                QueryHandler queryHandler = new QueryHandler(query);
                queryHandler.start();
            }
        }
    }
}
