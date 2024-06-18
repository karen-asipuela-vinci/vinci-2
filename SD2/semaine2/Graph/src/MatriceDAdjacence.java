import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class MatriceDAdjacence extends Graph{
	
	private Map<Integer, Airport>  correspondanceIndiceAirport;
	private Map<Airport, Integer>  correspondanceAirportIndice;
	private Flight[][] matrice= new Flight[0][0];
	private int nbAirport=0;

	public MatriceDAdjacence() {
		super();
		correspondanceAirportIndice= new HashMap<Airport,Integer>();
		correspondanceIndiceAirport= new HashMap<Integer,Airport>();
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
