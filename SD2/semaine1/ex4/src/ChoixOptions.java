import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ChoixOptions {

	// Map associant le nom d'une option à son objet Option correspondant
	private Map<String, Option> options;
	// Ajoutez ici les autres attributs si nécessaire
	private Map<Etudiant, List<Option>> preferences;

	// Constructeur prenant un entier et une suite de chaînes de caractères en paramètres
	// Ces chaînes de caractères représentent les noms des différentes options possibles
	public ChoixOptions(int nbEtudiantsParOption, String... nomsOption) {
		this.options = new HashMap<String, Option>();
		if (nomsOption.length < 3)
			throw new IllegalArgumentException();
		for (int i = 0; i < nomsOption.length; i++) {
			String nomOption = nomsOption[i];
			options.put(nomOption, new Option(nomOption, nbEtudiantsParOption));
		}
		// Initialisez les nouveaux attributs ici
		preferences = new HashMap<Etudiant, List<Option>>();
	}

	// Cette méthode enregistre les préférences des étudiants
	// Il n'est pas nécessaire de vérifier la validité de ces choix à ce stade
	public void ajouterPreferences(Etudiant etu, String choix1, String choix2, String choix3) {
		List<Option> list = new ArrayList<>(List.of(options.get(choix1), options.get(choix2), options.get(choix3)));
		preferences.put(etu, list);
	}

	// Cette méthode est appelée après que les étudiants aient donné leurs préférences
	// Elle attribue les options aux étudiants, en privilégiant les étudiants ayant les meilleures moyennes
	// Si certaines options sont complètes, les étudiants avec des moyennes plus faibles peuvent se voir attribuer leur troisième choix
	// Cette méthode doit faire appel à la méthode inscrireEtudiant de la classe Option
	public void attribuerOptions() {
		// on prend tous les étudiants (de la map) et on les trie par ordre décroissant de moyenne
		List<Etudiant> etudiants = new ArrayList<Etudiant>(preferences.keySet());
		etudiants.sort((e1, e2) -> e2.getMoyenne() - e1.getMoyenne());

		// on trie les options par disponibilité
		List<Option> allOptions = new ArrayList<>(options.values());
    allOptions.sort((o1, o2) -> o1.getNbMaxEtudiant() - o2.getNbMaxEtudiant());

		for (Etudiant etu : etudiants) {
			List<Option> list = preferences.get(etu);
			list.sort(Comparator.comparing(allOptions::indexOf));
			for (Option option : list) {
				if (option.inscrireEtudiant(etu)) {
					break;
				}
			}
		}
	}

	// Cette méthode retourne une représentation sous forme de chaîne de caractères de l'objet ChoixOptions
	// Elle affiche chaque option suivie d'une ligne de séparation
	public String toString(){
		String s="";
		for (Option o:options.values()){
			s=s+o+"\n"+"-----------------"+"\n";
		}
		return s;
	}
}