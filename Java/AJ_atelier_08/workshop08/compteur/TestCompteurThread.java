package compteur;

public class TestCompteurThread {

	public static void main(String[] args) {
		CompteurThread[] compteurs = { new CompteurThread("Bolt", 10), new CompteurThread("Jakson", 10), new CompteurThread("Robert", 10), new CompteurThread("Stéphanie", 10) };

		for(int i = 0; i < compteurs.length; i++) {
			//TODO: lancer les compteurs
		}

		for(int i = 0; i < compteurs.length; i++) {
			//TODO: attendre la fin de l'exécution de tous les compteurs
			//		pour attendre un thread t, utiliser t.join();
		}

		System.out.println("Le(la) gagnant(e) est + " + CompteurThread.getGagnant().getNom());
	}

}
