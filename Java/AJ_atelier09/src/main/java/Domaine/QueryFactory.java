package Domaine;

public class QueryFactory {
    //méthode statique qui créé une Query(Impl)
    public static Query getQuery(String url, QueryImpl.QueryMethod queryMethod) {
        return new QueryImpl(url, queryMethod);
    }
}
