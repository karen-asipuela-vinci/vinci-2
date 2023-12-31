package employee;

import java.io.IOException;
import java.io.UncheckedIOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Comparator;
import java.util.List;
import java.util.Map;
import java.util.function.BiFunction;
import java.util.function.Consumer;
import java.util.function.Predicate;
import java.util.function.Supplier;
import java.util.stream.Collectors;
import java.util.stream.Stream;

import static java.util.stream.Collectors.summarizingDouble;
import static java.util.stream.Collectors.toList;

public class EmployeeManagement {

    /**
     * Un Supplier est un objet qui fournit des résultats. Appeler sa méthode get()
     * vous fournira le type passé en paramètre, ici un Stream de String.
     * Complétez la fonction pour créer le Stream à partir du fichier streamingvf.cvs
     */
    private static final Supplier<Stream<String>> supplier = () -> {
        //TODO: retourner un stream créer à partir du fichier. Aidez vous de la p.15 : "Créer des streams"
        //      En cas d'IOException, vous devez lancer une UncheckedIOException
        try {
            return Files.lines(Paths.get("./AJ_atelier03_partie2/resources/streamingvf.csv"), Charset.defaultCharset());
        } catch (IOException e) {
            throw new UncheckedIOException(e);
        }
    };

    public static void main(String[] args) {

        System.out.println("1. Première ligne du fichier : [" + firstLine() + "]");
        System.out.println("\n3. Noms de famille de plus de 8 lettres contenant 'K' ou 'O' :\n" + filteredLastnames());
        System.out.println("\n4. Liste des comptes occurences de 'e' :\n" + occurencesOfE());
        System.out.println("\n5. Tous les emails se terminent-ils par 'streamingvf.be' ? :" + allEmailCorrect());
        System.out.println("\n6. Prénom d'un employé au log nom de famille : " + longLastName());
        System.out.println("\n7. Nombre d'employés à mi-temps : " + numbreOfPartTimers());
        System.out.println("\n8. Ids selon plein temps/mi-temps :");
        timeDistrubution().forEach((k, v) -> System.out.println(k + " : " + v));
        System.out.print("\n9. Plus long nom du fichier : ");
        printLongestName();

    }

    /**
     * Utilise le Supplier pour retourner la première ligne du fichier streamingvf.csv
     * N'oubliez pas la gestion des exceptions grâce au try-with-resources
     * @return une String contenant la première ligne du fichier
     */
    private static String firstLine() {
        //TODO
        try (Stream<String> firstLine = supplier.get()) {
            return firstLine.findFirst().get();
        } catch (UncheckedIOException e){
            e.printStackTrace();
        }
        return  "" ;
    }


    /**
     * Filtre le stream pour retourner une liste des noms de famille (lastname) de plus de 8 lettres
     * qui contiennent la lettre 'O' ou la lettre 'K'
     * @return une liste de String de plus de 8 lettres contenant 'O' ou 'K'
     */
    private static List<String> filteredLastnames() {
        Predicate<String> predicate = s -> s.length() > 8;
        //TODO: combiner predicate avec d'autres  (p.7 : "Predicate"), puis le passer en paramètre de
        //      de l'appel filter() pour filtrer les résultats.
        //rajouter "rajouter O et K" :
        predicate = predicate.and(s -> s.contains("O") || s.contains("K"));
        //correctif du prof (meme code dans javadoc) :
        //predicate = predicate.and(s -> s.indexOf('O') > -1 || s.indexOf('K') > -1);
        try (Stream<String> lastNames = supplier.get()){
            return lastNames
                    //besoin de créer des Employés pcq seulement infos/BD dans fichier:
                    .map(Employee::new)
                    //ensuite on peut prendre que les noms :
                    .map(Employee::getLastname)
                    .filter(predicate)
                    .toList();
        } catch (UncheckedIOException e){
            e.printStackTrace();
        }
        return null;
    }

    /**
     * Calcule les occurrences du carcatère 'e' dans les prénoms des employés
     * @return une liste contenant le nombre d'occurrences de 'e' pour chaque prénom d'employé.
     */
    private static List<Integer> occurencesOfE() {
        //TODO: Construire une BiFunction qui prend comme premier type de paramètre un Employee,
        //      comme deuxième type de paramètre un Character, et qui prend Integer comme type de retour.
        //      Cette BiFunction doit retourner le nombre d'occurrences du char passé en paramètre dans le
        //      prénom (firstname) de l'Employee passé en paramètre.
        //      Retourner une liste contenant le nombre d'occurences du caractère 'e' dans les
        //      prénoms de tous les employés en utilisant votre BiFunction.
        BiFunction<Employee, Character, Integer> functionNbrOccurrence = (employee, car) -> (int) employee.getFirstname().chars().filter(c -> c == car).count();
        return supplier.get()
                .map(Employee::new)
                .map(e -> functionNbrOccurrence.apply(e, 'e'))
                .toList();
    }

    /**
     * Vérifie que tous les emails des employés se terminent par "streamingvf.be"
     * @return true si tous les emails se terminent par "streamingvf.be", false sinon
     */
    private static boolean allEmailCorrect() {
        //TODO
        Predicate<String> predicate = s -> s.endsWith("@streamingvf.be");
        return supplier.get()
                .map(Employee::new)
                .map(Employee::getEmail)
                .allMatch(predicate);
    }

    /**
     * Retourne le prénom d'un employé dont le nom de famille a une longueur supérieure à 14,
     * ou une String contenant "None" si aucun ne correspond.
     * @return une String contenant un prénom ou "None"
     */
    private static String longLastName() {
        //TODO
        //autre façon de faire que allEmailCorrect():
        Predicate<Employee> predicate = e -> e.getLastname().length() > 14;
        return supplier.get()
                .map(Employee::new)
                .filter(predicate)
                .map(Employee::getFirstname)
                .findAny()
                .orElse("None");
    }

    /**
     * Calcule le nombre d'employé à mi-temps de la boîte
     * @return le nombre d'employé à mi-temps de la boîte
     */
    private static long numbreOfPartTimers() {
        //TODO
        Predicate<Employee> predicate = e -> !e.isFullTime();
        return supplier.get()
                .map(Employee::new)
                .filter(predicate)
                .count();
    }

    /**
     * Catégorise les employés selon qu'ils travaillent à mi-temps ou à plein temps.
     * @return une map de liste des id des employés selon qu'ils travaillent à mi-temps (false)
     *         ou à plein temps (true)
     */
    private static Map<Boolean, List<Integer>> timeDistrubution() {
        //TODO
        return supplier.get()
                .map(Employee::new)
                .collect(Collectors.partitioningBy(
                        //on les regroupe par fulltime or not:
                        Employee::isFullTime,
                        //deuxième partie : list avec ID :
                        Collectors.mapping(Employee::getId, toList())
                    )
                );
    }

    /**
     * Permet au Consumer d'utiliser le supplier défini en début de classe pour
     * effectuer ses opérations.
     * @param consumer un consommateur de Stream de String.
     */
    private static void withLines(Consumer<Stream<String>> consumer) {
        //TODO: try-with-resources avec le Supplier. Le consumer doit utiliser (en utilisant sa méthode accept())
        //      le résultat du Supplier.
        try(Stream<String> lines = supplier.get()){
            //pour "accepter" opération :
            consumer.accept(lines);
        } catch (UncheckedIOException e){
            e.printStackTrace();
        }
    }

    /**
     * Fournit un Consumer à withLines. Le Consumer doit print le plus long nom de famille du fichier
     */
    private static void printLongestName() {
        withLines( lines -> {
            //TODO: print le plus long nom de famille du fichier
            System.out.println(lines
                    //on utilise e pour créer un employé et on prend son nom de famille :
                    .map(e -> new Employee(e).getLastname())
                    //on compare la longueur du string avec comparing et on veut le max:
                    .max(Comparator.comparing(String::length))
                    //si on met pas le get : "optional" ???
                    .get()
                );
        });
    }



}
