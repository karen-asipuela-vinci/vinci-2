import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.time.format.FormatStyle;

public class PizzaComposable extends Pizza{
    private Client createur;
    private LocalDateTime date;

    public PizzaComposable(Client createur) {
        super("Pizza du client " + createur.getNumero(), "Pizza de " + createur.getPrenom() + " " + createur.getNom());
        this.date = LocalDateTime.now();
    }

    public Client getCreateur() {
        return createur;
    }

    public LocalDateTime getDate() {
        return date;
    }

    @Override
    public String toString() {
        DateTimeFormatter formater = DateTimeFormatter.ofLocalizedDateTime(FormatStyle.MEDIUM);
        return super.toString() + "\nPizza créée le " + formater.format(date);
    }
}
