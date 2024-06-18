import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;

public class ListeDArc extends Graph{
	
	private ArrayList<Flight> flights;

	public ListeDArc() {
		super();
		flights=new ArrayList<Flight>();
	}

	@Override
	// Complexité: ?
	protected void ajouterSommet(Airport a) {	
		//à compléter

	}

	@Override
	// Complexité: ?
	protected void ajouterArc(Flight f) {
		//à compléter
	}

	@Override
	// Complexité: ?
	public Set<Flight> arcsSortants(Airport a) {
		//à compléter
		return null;
	}

	@Override
	// Complexité: ?
	public boolean sontAdjacents(Airport a1, Airport a2) {
		// à compléter
		return false;
	}

}
