import java.util.ArrayList;
import java.util.Iterator;

public abstract class Pizza implements Iterable<Ingredient> {
    public static double PRIX_BASE = 5.0;
    private String titre, description;
    private ArrayList<Ingredient> ingredients;

    public Pizza(String titre, String description) {
        this.titre = titre;
        this.description = description;
        ingredients = new ArrayList<>();
    }

    public Pizza(String titre, String description, ArrayList<Ingredient> ingredients){
        this(titre, description);
        if(!verifIngredients(ingredients)) throw new IllegalArgumentException("Pas deux fois le même ingrédient");
        this.ingredients = ingredients;
    }
    public boolean verifIngredients(ArrayList<Ingredient> ingredients){
        ArrayList<Ingredient> copie = ingredients;
        for (Ingredient ingredient : copie) {
            int copies = 0;
            for (Ingredient ingredient2 : ingredients) {
                if(ingredient == ingredient2) copies++;
            }
            if(copies>1) return false;
        }
        return true;
    }

    public String getTitre() {
        return titre;
    }

    public String getDescription() {
        return description;
    }
    public boolean ajouter(Ingredient ingredient){
        if(ingredient == null) throw new IllegalArgumentException("Ne peut être null");
        return this.ingredients.add(ingredient);
    }
    public boolean supprimer(Ingredient ingredient ){
        if(ingredient == null) throw new IllegalArgumentException("Ne peut être null");
        return this.ingredients.remove(ingredient);
    }
    public double calculerPrix(){
        double prixTotal = 0 ;
        for (Ingredient ingredient :
                ingredients) {
            prixTotal += ingredient.getPrix();
        }
        return prixTotal + PRIX_BASE;
    }

    @Override
    public Iterator<Ingredient> iterator() {
        return null;
    }

    @Override
    public String toString() {
        String infos = titre + "\n" + description + "\nIngrédients : ";
        for (Ingredient ingredient : ingredients){
            infos +="\n" + ingredient.getNom();
        }
        infos +="\nprix : " + calculerPrix() + " euros";
        return infos;
    }
}
