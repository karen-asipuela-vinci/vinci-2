package Server;

import Domaine.Query;
import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;
import org.apache.http.util.EntityUtils;
import org.apache.http.io.*;

import java.io.IOException;

//besoin de Thread pour pouvoir faire plusieurs requetes en même temps
public class QueryHandler extends Thread {
    private Query query;

    //ne pas oublier constructeur
    public QueryHandler(Query query) {
        this.query = query;
    }
    //fait la requete avec le httpClient et écrit la réponse à l'écran
    public void run() {
        try(CloseableHttpClient httpclient = HttpClients.createDefault()) {
            HttpResponse response = null;
            if (this.query.isGetMethod()) {
                HttpGet httpGet = new HttpGet(this.query.getUrl());
                response = httpclient.execute(httpGet);
            }

            // Afficher le code de statut
                System.out.println("Status Code: " + response.getStatusLine().getStatusCode());

            // Afficher le contenu HTML avec EntityUtils
            String htmlContent = EntityUtils.toString(response.getEntity());
            System.out.println("HTML :\n" + htmlContent);

        } catch (ClientProtocolException e) {
                System.err.println("Erreur de protocole client: " + e.getMessage());
        } catch (IOException e) {
            System.err.println("Erreur d'entrée/sortie: " + e.getMessage());
        }
    }

}
