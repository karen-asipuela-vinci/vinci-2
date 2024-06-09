import java.util.*;

public class GestionImpression {
    private Queue<Impression> queue;
    private Map<String, Impression> lastImpressionByUser;

    public GestionImpression() {
        this.queue = new LinkedList<>();
        this.lastImpressionByUser = new HashMap<>();
    }

    public void ajouterImpression(Impression impr) {
        queue.add(impr);
        lastImpressionByUser.put(impr.getIdUtilisateur(), impr);
    }

    public Impression selectionnerImpression() {
        Impression nextImpression;
        while ((nextImpression = queue.poll()) != null) {
            if (nextImpression == lastImpressionByUser.get(nextImpression.getIdUtilisateur())) {
                return nextImpression;
            }
        }
        return null;
    }
}