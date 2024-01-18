package Domaine;

//on enlève le mot clé public pour la rendre package friendly
class QueryImpl implements Query {
    private String url;
    //"HTTP method” (GET, POST) de type QueryMethod (classe interne énuméré)
    private QueryMethod queryMethod;

    public boolean isGetMethod() {
        return queryMethod == QueryMethod.GET;
    }

    public QueryImpl(String url, QueryMethod queryMethod) {
        this.url = url;
        this.queryMethod = queryMethod;
    }

    public String getUrl() {
        return url;
    }

    public QueryMethod getQueryMethod() {
        return queryMethod;
    }

}
