package compteur;

public class CompteurRunnable implements Runnable {

    private String nom;
    private int max;

    //TODO: ajouter un attribut de classe qui retient l'ordre d'arrivée.

    @Override
    public void run() {
        //TODO: 1. Compter jusqu'à max
        //         A chaque incrémentation, afficher le nom du compteur et son compte actuel.
        //      2. Quand le compte est terminé, afficher que le compteur a finit de compter
        //         et indiquer son ordre d'arrivée.
    }

    public CompteurRunnable(String nom, int max) {
        this.nom = nom;
        this.max = max;
    }

    public String getNom() {
        return nom;
    }

}