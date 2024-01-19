package Domaine;

public interface Query {
    QueryMethod getQueryMethod();
    /**
     * Vérifier si la requête est de type GET
     *
     * @return true si la requête est de type GET, false sinon
     */
    boolean isGetMethod();
    /**
     * Getter pour l'URL
     *
     * @return URL
     */
    String getUrl();
    //besoin de rajouter un setter pour l'url
    /**
     * Setter pour l'URL
     *
     * @param url URL
     */
    void setUrl(String url);
    //besoin de rajouter un setter pour le QueryMethod
    /**
     * Setter pour le QueryMethod
     *
     * @param method QueryMethod
     */
    void setMethod(QueryMethod method);

     public enum QueryMethod {
        GET, POST
    }
}
