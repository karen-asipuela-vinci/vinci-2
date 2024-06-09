import java.util.*;

public class Doodle {
    private List<PlageHoraire> plages;
    private Map<String, boolean[]> disponibilites;
    private int[] compteurParticipants;

    public Doodle(PlageHoraire... plages) {
        this.plages = new ArrayList<>(List.of(plages));
        this.disponibilites = new HashMap<>();
        this.compteurParticipants = new int[plages.length];
    }

    public void ajouterDisponibilites(String participant, boolean[] disponibilites) {
        if (disponibilites.length != plages.size())
            throw new IllegalArgumentException();
        this.disponibilites.put(participant, disponibilites);
        for (int i = 0; i < disponibilites.length; i++) {
            if (disponibilites[i]) {
                compteurParticipants[i]++;
            }
        }
    }

    public boolean estDisponible(String participant, PlageHoraire plage) {
        int index = plages.indexOf(plage);
        if (index == -1 || !disponibilites.containsKey(participant)) {
            return false;
        }
        return disponibilites.get(participant)[index];
    }

    public PlageHoraire trouverPlageQuiConvientLeMieux() {
        int maxParticipants = -1;
        PlageHoraire bestPlage = null;
        for (int i = 0; i < plages.size(); i++) {
            if (compteurParticipants[i] > maxParticipants) {
                maxParticipants = compteurParticipants[i];
                bestPlage = plages.get(i);
            }
        }
        bestPlage.setNbParticipantPresent(maxParticipants);
        return bestPlage;
    }
}