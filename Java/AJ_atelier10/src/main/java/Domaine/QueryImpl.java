package Domaine;

//on enlève le mot clé public pour la rendre package friendly
class QueryImpl implements Query {
    private String url;
    //"HTTP method” (GET, POST) de type QueryMethod (classe interne énuméré)
    private QueryMethod queryMethod;

    public QueryImpl() {
        //vide car on a besoin de la méthode setUrl et setMethod
    }

    //on garde un constructeur avec les paramètres url et queryMethod
    //pour pouvoir les setter
    public QueryImpl(String url, QueryMethod queryMethod) {
        this.url = url;
        this.queryMethod = queryMethod;
    }

    public boolean isGetMethod() {
        return queryMethod == QueryMethod.GET;
    }


    public String getUrl() {
        return url;
    }

    public QueryMethod getQueryMethod() {
        return queryMethod;
    }

    @Override
    public void setUrl(String url) {
        this.url = url;
    }

    @Override
    public void setMethod(QueryMethod method) {
        this.queryMethod = method;
    }

}
