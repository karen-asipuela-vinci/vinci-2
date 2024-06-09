import java.util.*;

public class Academie {
    private Map<String, LinkedList<String>> attenteParInstrument;

    public Academie(List<String> instruments) {
        attenteParInstrument = new HashMap<>();
        for (String instrument : instruments) {
            attenteParInstrument.put(instrument, new LinkedList<>());
        }
    }

    public void mettreEnAttente(String instrument, String eleve) {
        if (attenteParInstrument.containsKey(instrument)) {
            attenteParInstrument.get(instrument).add(eleve);
        }
    }

    public String attribuerPlace(String instrument) {
        if (attenteParInstrument.containsKey(instrument)) {
          return attenteParInstrument.get(instrument).poll();
        }
        return null;
    }
}