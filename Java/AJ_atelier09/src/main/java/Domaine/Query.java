package Domaine;

public interface Query {
    boolean isGetMethod();
    String getUrl();
    QueryMethod getQueryMethod();
    //besoin de rajouter un setter pour l'url
    void setUrl(String url);
    //besoin de rajouter un setter pour le QueryMethod
    void setMethod(QueryMethod method);

     public enum QueryMethod {
        GET, POST
    }
}
