package Blacklist;

import Domaine.Query;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.HashSet;
import java.util.Properties;
import java.util.Set;

public class BlacklistService {

    private static Set<String> blacklistedDomains;

    static {
        try (FileInputStream input = new FileInputStream("blacklist.properties")) {
            // Charger le fichier de propriétés
            Properties properties = new Properties();
            //on peut utiliser la méthode load de Properties pour charger le fichier
            properties.load(input);
            //on utilise la méthode Set.of pour créer un Set à partir d'un tableau
            //où on sépare les éléments du tableau par des points-virgules
            blacklistedDomains = Set.of(properties.getProperty("blacklistedDomains").split(";"));
        } catch (IOException e) {
            e.printStackTrace();
        }

    }


    public boolean check(Query query) {
        // Vérifier si le domaine de l'URL de la requête est dans la liste des domaines interdits
        //on peut vérifier le domaine directement grâce au Stream API
        //return blacklistedDomains.stream().noneMatch(query.getUrl()::contains);
        //réponse du prof:
        return !blacklistedDomains.stream().anyMatch(d -> query.getUrl().contains(d));
    }
}
