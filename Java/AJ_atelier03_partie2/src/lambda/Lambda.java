package lambda;

import java.util.ArrayList;
import java.util.List;
import java.util.function.Function;
import java.util.function.Predicate;

public class Lambda {

    /**
     * Retourne une liste contenant uniquement les Integer qui correspondent
     * au predicat match
     * @param list La liste d'Integer originale
     * @param match le predicat à respecter
     * @return une liste contenant les integer qui respectent match
     */
    public static List<Integer> allMatchesInteger(List<Integer> list, Predicate<Integer> match) {
        //TODO
        List<Integer> listInt = new ArrayList<>();
        list.forEach(a -> {
            if(match.test(a)) listInt.add(a);
        });
        return listInt;
    }

     /**
     * Retourne une liste contenant uniquement les Integer qui correspondent
     * au predicat match
     * @param list La liste de T originale
     * @param match le predicat à respecter
     * @return une liste contenant les integer qui respectent match
     */
    public static <T> List<T> allMatches(List<T> list, Predicate<T> match) {
        //TODO
        List<T> listInt = new ArrayList<>();
        list.forEach(a -> {
            if(match.test(a)) listInt.add(a);
        });
        return listInt;
    }

    /**
     * Retourne une liste contenant tous les éléments de la liste originale, transformés
     * par la fonction transform
     * @param list La liste d'Integer originale
     * @param transform la fonction à appliquer aux éléments
     * @return une liste contenant les integer transformés par transform
     */
    public static List<Integer> transformAllInteger(List<Integer> list, Function<Integer, Integer> transform) {
        //TODO
        List<Integer> listTransform = new ArrayList<>();
        list.forEach(a -> listTransform.add(transform.apply(a)));
        return listTransform;
    }


    /**
     * Retourne une liste contenant tous les éléments de la liste originale, transformés
     * par la fonction transform
     * @param list La liste d'Integer originale
     * @param transform la fonction à appliquer aux éléments
     * @return une liste contenant les integer transformés par transform
     */
    public static <P, R> List<R> transformAll(List<P> list, Function<P, R> transform) {
        //TODO
        List<R> listTransform = new ArrayList<>();
        list.forEach(a -> listTransform.add(transform.apply(a)));
        return listTransform;
    }

    /**
     * même chose que allMatches
     * mais en utilisant API Stream
     */
    public static <T> List<T> filter(List<T> list, Predicate<T> match){
        return list.stream().filter(match).toList();
    }

    /**
     * même chose que transform all
     * mais avec API Stream
     */
    public static <P,R> List<R> map(List<P> list, Function<P,R> function){
        return list.stream().map(function).toList();
    }
}
