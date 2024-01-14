package compteur;

public class CompteurThread extends Thread {

    private final String nom;
    private final int max;

    //Cette variable de classe permet de retenir quel CompteurThread
    //a fini de compter le premier.
    private static CompteurThread gagnant;

    public CompteurThread(String nom, int max) {
        this.nom = nom;
        this.max = max;
    }

    public String getNom() {
        return nom;
    }

    @Override
    public void run() {
        //TODO: 1. Compter jusqu'à max
        //         A chaque incrémentation, afficher le nom du compteur et son compte actuel.
        //      2. Quand le compte est terminé, afficher que le compteur a finit de compter

        for (int i = 0; i < max; i++) {
            //rajout de pause entre chaque nombre :
            try {
                Thread.sleep(10);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            //on sout le nombre qu'il vient de compter :
            System.out.println(nom + " : " + i);
        }

        //sout fin de comptage :
        System.out.println(nom + " a fini de compter.");

        synchronized (CompteurThread.class) {
            if (gagnant == null) {
                try {
                    Thread.sleep(10);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                System.out.println(nom + " est la.le gagnant.e.");
                gagnant = this;
            }
        }
    }

    public static CompteurThread getGagnant() {
        return gagnant;
    }
}
