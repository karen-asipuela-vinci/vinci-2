import java.util.ArrayList;
import java.util.Iterator;

public class Client implements Iterable<Commande>{
    private static int  numeroSuivant = 1;
    private int numero;
    private String nom, prenom, telephone;
    private Commande commandeEnCours;
    private ArrayList<Commande> historiqueCommande;

    public Client(String nom, String prenom, String telephone) {
        this.nom = nom;
        this.prenom = prenom;
        this.telephone = telephone;
        this.numero = numeroSuivant;
        numeroSuivant++;
        historiqueCommande = new ArrayList<>();
    }

    public int getNumero() {
        return numero;
    }

    public String getNom() {
        return nom;
    }

    public String getPrenom() {
        return prenom;
    }

    public String getTelephone() {
        return telephone;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Client client = (Client) o;

        return numero == client.numero;
    }

    @Override
    public int hashCode() {
        return numero;
    }
    @Override
    public String toString() {
        return "client n° " + numero + " (" + prenom  + " " + nom + ", telephone : " + telephone +")";
    }

    public Commande getCommandeEnCours() {
        return commandeEnCours;
    }
    public boolean enregistrer(Commande commande) {
        if (commandeEnCours == null && commande.getClient() == this && !historiqueCommande.contains(commande)) {
            commandeEnCours = commande;
            return true;
        } else {
            return false;
        }
    }

    public boolean cloturerCommandeEnCours(){
        if(commandeEnCours == null) return false;
        historiqueCommande.add(commandeEnCours);
        commandeEnCours = null;
        return true;
    }

    @Override
    public Iterator<Commande> iterator() {
        return null;
    }
}
