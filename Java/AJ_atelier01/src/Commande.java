import util.Util;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.time.format.FormatStyle;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Objects;

public class Commande implements Iterable<LigneDeCommande>{
    private static int numeroSuivant = 1;
    private int numero;
    private Client client;
    private LocalDateTime date;
    private ArrayList<LigneDeCommande> lignesCommande;

    public Commande(Client client) {
        this.client = client;
        if(client.getCommandeEnCours() != null) throw new IllegalArgumentException("Impossible de créer une commande pour n client ayant une commande en cours");
        this.numero = numeroSuivant;
        numeroSuivant++;
        this.date = LocalDateTime.now();
        lignesCommande = new ArrayList<>();
        client.enregistrerCommande(this);
    }

    public int getNumero() {
        return numero;
    }

    public Client getClient() {
        return client;
    }

    public LocalDateTime getDate() {
        return date;
    }

    @Override
    public Iterator<LigneDeCommande> iterator() {
        return lignesCommande.iterator();
    }

    //Méthodes ajouter : échouent si la commande n'est pas la commande en cours du client
    public boolean ajouter(Pizza pizza, int quantite ){
        Util.checkObject(pizza);
        Util.checkStrictlyPositive(quantite);
        if(client.getCommandeEnCours() != this) return false;
        for (LigneDeCommande ligneCommande :
                lignesCommande) {
            if (ligneCommande.getPizza().equals(pizza)){
                ligneCommande.setQuantite(ligneCommande.getQuantite() + quantite);
                return true;
            }
        }
        return lignesCommande.add(new LigneDeCommande(pizza, quantite));
    }
    //comme fait appel à la première méthode, pas besoin de vérifier 2x
    public boolean ajouter(Pizza pizza){
        return ajouter(pizza, 1);
    }

    public double calculerMontantTotal(){
        double calcul = 0;
        for (LigneDeCommande ligneCommande :
                lignesCommande) {
            calcul += ligneCommande.calculerPrixTotal();
        }
        return calcul;
    }


    public String detailler() {
        String lignes = "";
        for (LigneDeCommande l : lignesCommande){
            lignes += l.toString() + "\n";
        }
        if (lignes.equals("")) return lignes;
        return lignes.substring(0,lignes.length()-1);
    }

    public String toString() {
        DateTimeFormatter formater = DateTimeFormatter.ofLocalizedDateTime(FormatStyle.MEDIUM);
        String encours = "";
        if (client.getCommandeEnCours() == this)
            encours = " (en cours)";
        return "Commande n° " + numero + encours + " du " + client + "\ndate : " + formater.format(date);
    }
    public boolean retirer(Pizza pizza, int quantite){
        Util.checkObject(pizza);
        Util.checkStrictlyPositive(quantite);
        if(client.getCommandeEnCours() != this) return false;
        for (LigneDeCommande ligneDeCommande :
             lignesCommande ) {
            if(ligneDeCommande.getPizza().equals(pizza)){
                if(ligneDeCommande.getQuantite() < quantite) return false;
                if(ligneDeCommande.getQuantite()==quantite) {
                    lignesCommande.remove(ligneDeCommande);
                } else {
                    ligneDeCommande.setQuantite(ligneDeCommande.getQuantite() - quantite);
                }
                return true;
            }
        }
        return false;
    }

    public boolean retirer(Pizza pizza){
        return this.retirer(pizza, 1);
    }

    public boolean supprimer(Pizza pizza) {
        Util.checkObject(pizza);
        if(client.getCommandeEnCours() != this) return false;
        for (LigneDeCommande ligneDeCommande :
                lignesCommande) {
            if (ligneDeCommande.getPizza().equals(pizza)) {
                lignesCommande.remove(ligneDeCommande);
                return true;
            }
        }
        return false;
    }

    
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Commande commande = (Commande) o;
        return numero == commande.numero;
    }

    @Override
    public int hashCode() {
        return Objects.hash(numero);
    }
}
