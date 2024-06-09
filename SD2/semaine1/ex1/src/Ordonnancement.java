import java.util.Comparator;
import java.util.PriorityQueue;

public class Ordonnancement {
	public static final int NIVEAU_PRIORITE_MAX=5;
	private PriorityQueue<Tache> taches;

	public Ordonnancement(){
				taches = new PriorityQueue<Tache>(
				Comparator.comparing(Tache::getPriorite).reversed()
						.thenComparing(Tache::getDate)
		);
	}
	public void ajouterTache (String descriptif, int priorite){
		if(priorite<1 || priorite>NIVEAU_PRIORITE_MAX){
			throw new IllegalArgumentException("Priorité invalide");
		}
		Tache t = new Tache(descriptif, priorite);
		taches.add(t);
	}
	
	//renvoie la tache prioritaire
	//renvoie null si plus de tache presente
	public Tache attribuerTache(){
		// pas besoin de tester si taches est vide
		// car poll renvoie null si vide
		return taches.poll();
	}
}
