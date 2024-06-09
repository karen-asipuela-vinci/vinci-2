import java.time.LocalTime;
import java.util.*;

import static java.time.temporal.ChronoUnit.MILLIS;

public class LocationPatins {
    private HashMap<Integer, Integer> pointures;
    private HashMap<Integer, List<Integer>> casiersDisponibles;
    private HashMap<Integer, LocalTime> casiersOccupes;

    public LocationPatins(int[] casiers) {
        pointures = new HashMap<>();
        casiersDisponibles = new HashMap<>();
        casiersOccupes = new HashMap<>();
        for (int i = 0; i < casiers.length; i++) {
            pointures.put(i, casiers[i]);
            casiersDisponibles.computeIfAbsent(casiers[i], k -> new ArrayList<>()).add(i);
        }
    }

    private static double prix(LocalTime date1, LocalTime date2) {
        return MILLIS.between(date1, date2);
    }

    public int attribuerCasierAvecPatins(int pointure) {
        if (pointure < 33 || pointure > 48 || !casiersDisponibles.containsKey(pointure) || casiersDisponibles.get(pointure).isEmpty())
            return -1;
        int casier = casiersDisponibles.get(pointure).remove(0);
        casiersOccupes.put(casier, LocalTime.now());
        return casier;
    }

    public double libererCasier(int numeroCasier) {
        if (!pointures.containsKey(numeroCasier) || !casiersOccupes.containsKey(numeroCasier))
            return -1;
        double prix = prix(casiersOccupes.get(numeroCasier), LocalTime.now());
        casiersOccupes.remove(numeroCasier);
        casiersDisponibles.get(pointures.get(numeroCasier)).add(numeroCasier);
        return prix;
    }
}