package Domaine;

//!!!!! ici c'est une interface et non une classe
public interface QueryFactory {
    //doit juste avoir méthode getQuery qui est implémentée dans QueryFactoryImpl
    /**
     * Créer une requête
     *
     * @return Requête
     */
    Query getQuery();

}
