package domaine;

import util.Util;

import java.util.*;

public class Livre {
    private Map<Plat.Type, SortedSet<Plat>> livre;

    public Livre() {
        livre = new HashMap<>();
    }

    /**
     * Ajoute un plat dans le livre, s'il n'existe pas déjà dedans.
     * Il faut ajouter correctement le plat en fonction de son type?
     * @param plat le plat à ajouter
     * @return true si le plat a été ajouté, false sinon
     */

    public boolean ajouterPlat(Plat plat){
        Util.checkObject(plat);
        SortedSet<Plat> sousLivre = livre.get(plat.getType());
        if(sousLivre == null){
            Comparator<Plat> comparator = Comparator.comparing(Plat::getNiveauDeDifficulte).thenComparing(Plat::getNom);
            sousLivre = new TreeSet<>(comparator);
            livre.put(plat.getType(), sousLivre);
        }
        sousLivre.add(plat);
        return true;
    }

    /**
     * Supprime un plat du livre, s'il est dedans.
     * Si le plat supprimé est le dernier de ce type de plat, il faut supprimer ce type de plat de la map.
     * @param plat le plat à supprimer
     * @return true si le plat a été supprimé, false sinon.
     */
    public boolean supprimerPlat(Plat plat){
        Util.checkObject(plat); // besoin de checker si plat n'est pas nul ? ---> demander.
        SortedSet<Plat> sousLivre = livre.get(plat.getType());
        if(sousLivre == null) return false;
        boolean deleted = sousLivre.remove(plat);
        if(sousLivre.isEmpty()) livre.remove(plat.getType());
        return deleted;
    }

    @Override
    public String toString() {
        StringBuilder text = new StringBuilder();
        //apprendre a utiliser ceci pour map (et autres) :

        livre.forEach((type, plats) -> {
            text.append(type).append("\n");
            text.append("=====").append("\n");
            for (Plat plat : plats) {
                text.append(plat.getNom()).append("\n");
            }
        });
        return text.toString();
    }

    // méthodes rajoutées en 3.6
    /**
     * Renvoie un ensemble contenant tous les plats d'un certain type.
     * L'ensemble n'est pas modifiable.
     * @param type le type de plats souhaité
     * @return l'ensemble des plats
     */
    public SortedSet<Plat> getPlatsParType(Plat.Type type){
        Util.checkObject(type);
        SortedSet<Plat> platsTypes = livre.get(type);
        if(platsTypes == null) return null;
        return Collections.unmodifiableSortedSet(platsTypes); // besoin de le rendre non modifiable ??
    }
    /**
     * Renvoie true si le livre contient le plat passé en paramètre. False sinon.
     * Pour cette recherche, un plat est identique à un autre si son type, son niveau de difficulté
     * et son nom sont identiques.
     * @param plat le plat à rechercher.
     * @return true si le livre contient le plat, false sinon.
     */
    public boolean contient(Plat plat){
        // Ne pas utiliser 2 fois la méthode get() de la map et ne pas déclarer de variable locale.
        Util.checkObject(plat);
        if(this.livre.containsKey(plat.getType()))
            return this.livre.get(plat.getType()).contains(plat); // on chope le plat
        // selon le type puis on check le plat en lui meme
        return false;
    }
    /**
     * Renvoie un ensemble contenant tous les plats du livre. Ils ne doivent pas être triés.
     * @return l'ensemble de tous les plats du livre.
     */
    public Set<Plat> tousLesPlats() {
        Set<Plat> plats = new HashSet<>();
        //Ne pas utiliser la méthode keySet() ou entrySet() ici !
        for (Set<Plat> platsDunType : this.livre.values()) {
            plats.addAll(platsDunType);
        }
        return plats;
    }
}
