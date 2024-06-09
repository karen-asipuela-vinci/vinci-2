import java.util.*;

public class AcademieAvecDesistement {
    private Map<String, LinkedList<String>> attenteParInstrument;
    private Map<String, String> instrumentParEleve;

    public AcademieAvecDesistement(List<String> instruments) {
        attenteParInstrument = new HashMap<>();
        instrumentParEleve = new HashMap<>();
        for (String instrument : instruments) {
            attenteParInstrument.put(instrument, new LinkedList<>());
        }
    }

    public void mettreEnAttente(String instrument, String eleve) {
        if (attenteParInstrument.containsKey(instrument)) {
            attenteParInstrument.get(instrument).add(eleve);
            instrumentParEleve.put(eleve, instrument);
        }
    }

    public String attribuerPlace(String instrument) {
        if (attenteParInstrument.containsKey(instrument)) {
            String eleve = attenteParInstrument.get(instrument).poll();
            if (eleve != null) {
                instrumentParEleve.remove(eleve);
            }
            return eleve;
        }
        return null;
    }

    public boolean desistement(String instrument, String eleve) {
    if (attenteParInstrument.containsKey(instrument)) {
        boolean removed = attenteParInstrument.get(instrument).remove(eleve);
        if (removed) {
            instrumentParEleve.remove(eleve);
        }
        return removed;
    }
    return false;
}
}