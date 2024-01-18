package Domaine;

public interface Query {
    public boolean isGetMethod();
    public String getUrl();
    public QueryImpl.QueryMethod getQueryMethod();

     public enum QueryMethod {
        GET, POST
    }
}
