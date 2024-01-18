package Main;
import org.apache.http.HttpResponse;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.HttpClients;
import org.apache.http.util.EntityUtils;

import java.io.IOException;

public class Main {
    public static void main(String[] args) {
        String url = "https://duckduckgo.com/";

        // Créer un client HTTP
        HttpClient httpClient = HttpClients.createDefault();
        // Créer une requête GET
        HttpGet httpGet = new HttpGet(url);

        try {
            // Exécuter la requête et obtenir la réponse
            HttpResponse response = httpClient.execute(httpGet);

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
