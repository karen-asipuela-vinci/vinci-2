import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;

public class ControleDAcces {
	private HashMap<Badge, Employe> badges;
	private HashSet<Employe> employesPresents;
	
	public ControleDAcces(){
		badges = new HashMap<Badge, Employe>();
		employesPresents = new HashSet<>();
	}
	
	// associe le badge � un employ�
	public void donnerBadge (Badge b, Employe e){
		badges.put(b, e);
	}
	
	// met � jour les employ�s pr�sents dans le batiment
	public void entrerBatiment (Badge b){
		Employe e = badges.get(b);
		if(e != null){
			employesPresents.add(e);
		}
	}

	// met � jour les employ�s pr�sents dans le batiment
	public void sortirBatiment (Badge b){
		Employe e = badges.get(b);
		if(e != null){
			employesPresents.remove(e);
		}
	}
	
	// renvoie vrai si l'employ� est dans le batiment, faux sinon
	public boolean estDansBatiment (Employe e){
		return employesPresents.contains(e);
	}
}
