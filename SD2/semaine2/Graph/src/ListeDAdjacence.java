import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class ListeDAdjacence extends Graph{
	
	private Map<Airport,Set<Flight>> outputFlights;

	public ListeDAdjacence(){
		super();
		outputFlights=new HashMap<Airport,Set<Flight>>();

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
