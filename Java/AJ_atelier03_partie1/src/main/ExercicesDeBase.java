package main;

import domaine.Trader;
import domaine.Transaction;

import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

import static java.util.stream.Collectors.toList;

public class ExercicesDeBase {

    /**
     * La liste de base de toutes les transactions.
     */
    private List<Transaction> transactions;

    public static void main(String[] args) {
        Trader raoul = new Trader("Raoul", "Cambridge");
        Trader mario = new Trader("Mario", "Milan");
        Trader alan = new Trader("Alan", "Cambridge");
        Trader brian = new Trader("Brian", "Cambridge");

        List<Transaction> transactions = Arrays.asList(
                new Transaction(brian, 2011, 300),
                new Transaction(raoul, 2012, 1000),
                new Transaction(raoul, 2011, 400),
                new Transaction(mario, 2012, 710),
                new Transaction(mario, 2012, 700),
                new Transaction(alan, 2012, 950)
        );
        System.out.println("Les transactions " + transactions);
        ExercicesDeBase main = new ExercicesDeBase(transactions);
        main.run();
    }



    /**
     * Crée un objet comprenant toutes les transactions afin de faciliter leur usage pour chaque point de l'énoncé
     *
     * @param transactions la liste des transactions
     */
    public ExercicesDeBase(List<Transaction> transactions) {
        this.transactions = transactions;
    }

    /**
     * Exécute chaque point de l'énoncé
     */
    public void run() {
        this.predicats1();
        this.predicats2();
        this.predicats3();
        this.map1();
        this.map2();
        this.map3();
        this.sort1();
        this.sort2();
        this.reduce1();
        this.reduce2();
    }

    //construire la liste de toutes les transactions de 2011
    private void predicats1() {
        System.out.println("predicats1");
        Stream<Transaction> s = transactions
                .stream()
                .filter(e -> e.getYear() == 2011); // TODO filtrer
        System.out.println("sout du Stream brut" + s);
        s.forEach(System.out::println);
    }

    //Construire la liste de toutes les transactions dont la valeur est >600
    private void predicats2() {

        System.out.println("predicats2");
        var s = transactions
                .stream()
                .filter(e -> e.getValue() > 600); // TODO filtrer

        s.forEach(System.out::println);
    }


    //Construire la lise de toutes les transactions de Raoul
    private void predicats3() {

        System.out.println("predicats3");
        var s = transactions
                .stream()
                .filter(e -> e.getTrader().getName().equals("Raoul")); // TODO filtrer
        s.forEach(System.out::println);
    }

    //Construire la liste des villes où travaillent les courtiers (traders)
    private void map1() {
        System.out.println("map1");
        // TODO transformer
        Stream<String> listeVilles = transactions
                .stream()
                .map(t -> t.getTrader().getCity())// si on ne fait que ça : doublons
                .distinct() // du coup, utilisation de distinct
                ;
        listeVilles.forEach(System.out::println);

    }

    //Construire la liste de tous les courtiers de Cambridge
    private void map2() {
        System.out.println("map2");
        // TODO transformer
        List<Trader> listTrader = transactions
                .stream()
                .map(Transaction::getTrader)
                .distinct()
                .filter(trader -> trader.getCity().equals("Cambridge"))
                .toList();
        listTrader.forEach(System.out::println);
    }

    //Construire un string contenant tous les noms des traders séparés par une virgule
    // Comme il s'agit d'une string et non d'une liste, utilisez la méthode joining() dans collect();
    private void map3() {
        System.out.println("map3");
        String nomsTraders = transactions
                .stream()
                .map(Transaction::getTrader)
                .distinct()
                .map(Trader::getName)
                .collect(Collectors.joining(", "));
        System.out.println(nomsTraders);
    }
    //Construire la liste de toutes les transactions triées par ordre décroissant de valeurs
    private void sort1() {
        System.out.println("sort1");
        var transcTriees = transactions
                .stream()
                .sorted(Comparator.comparingInt(Transaction::getValue).reversed())
                .toList(); // TODO trier
        transcTriees.forEach(System.out::println);
    }

    //Construire un String contenant tous les noms de traders triés par ordre alphabétique
    private void sort2() {
        System.out.println("sort2");
        var nomsTries = transactions
                .stream()
                .map(Transaction::getTrader)
                .distinct()
                .map(Trader::getName)
                .sorted()
                .collect(Collectors.joining(", ")); // TODO trier
		System.out.println(nomsTries);
    }
    //Afficher la valeur max des transactions
    private void reduce1() {
        System.out.println("reduce1");
         // TODO reduce
        var max2 = transactions
                .stream()
                .map(Transaction::getValue)
                .reduce(0, Integer::max);
        System.out.println(max2);
    }

    //Afficher la transaction dont la valeur est la plus petite.
    // !! on demande la transaction et non la valeur !!!
    private void reduce2() {
        System.out.println("reduce2");
        //pour comparaison : utiliser une valeur neutre contenant la max_value
        Transaction transNeutre = new Transaction(null, 0000, Integer.MAX_VALUE);
        // TODO reduce
        Transaction transacMin = transactions
                .stream()
                .reduce(transNeutre, (a,b) -> (a.getValue() < b.getValue() ? a:b));
        // traduction : on compare la valeur de a et b : si ok (?) renvoie a, sinon (:) renvoie b

        System.out.println(transacMin);
    }

}