package Domaine;

public class QueryFactoryImpl implements QueryFactory {

    @Override
    public Query getQuery() {
        return new QueryImpl();
    }
}
