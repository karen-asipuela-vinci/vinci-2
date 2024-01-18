package Server;

import Domaine.Query;
import Domaine.QueryFactory;

import java.util.Scanner;

//s'occupe de lire au clavier, créer Query et démarrer les QueryHandler
public class ProxyServer {
    public void startServer() {
        while(true) {
            //lire au clavier
            try(Scanner sc = new Scanner(System.in)) {
                System.out.println("Veuillez saisir une URL :");
                String url = sc.nextLine();
                //créer Query
                Query query = QueryFactory.getQuery(url, Query.QueryMethod.GET);
                //démarrer QueryHandler
                QueryHandler queryHandler = new QueryHandler(query);
                queryHandler.start();
            }
        }
    }
}
