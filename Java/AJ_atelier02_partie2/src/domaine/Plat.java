package domaine;

import java.time.Duration;
import java.util.*;

public class Plat {
    public enum Difficulte {
        X, XX, XXX, XXXX, XXXXX;

        @Override
        public String toString() {
            StringBuilder etoiles = new StringBuilder("*");
            for (int i = 0; i < this.ordinal(); i++) {
                etoiles.append("*");
            }
            return etoiles.toString();
        }
    }

    public enum Cout {
        $, $$, $$$, $$$$, $$$$$;

        @Override
        public String toString() {
            StringBuilder euros = new StringBuilder("€");
            for (int i = 0; i < this.ordinal(); i++) {
                euros.append("€");
            }
            return euros.toString();
        }
    }
    public enum Type{
        ENTREE,PLAT, DESSERT;
    }

    private String nom;
    private int nbPersonnes;
    private Difficulte niveauDeDifficulte;
    private Cout cout;
    private Duration dureeEnMinutes;
    private List<Instruction> instructions;
    private Set<IngredientQuantifie> ingredients; // on utilise set car l'ordre des
    // ingredients quantitifiés n'a pas d'importance
    private Type type;

    public Plat(String nom, int nbPersonnes, Difficulte niveauDeDifficulte, Cout cout, Type type) {
        this.nom = nom;
        this.nbPersonnes = nbPersonnes;
        this.niveauDeDifficulte = niveauDeDifficulte;
        this.cout = cout;
        this.dureeEnMinutes = Duration.ofMinutes(0);
        this.instructions = new ArrayList<>();
        this.ingredients = new HashSet<>();
        this.type = type;
    }

    public String getNom() {
        return nom;
    }

    public int getNbPersonnes() {
        return nbPersonnes;
    }

    public Difficulte getNiveauDeDifficulte() {
        return niveauDeDifficulte;
    }

    public Cout getCout() {
        return cout;
    }

    public Duration getDureeEnMinutes() {
        return dureeEnMinutes;
    }

    public Type getType() {
        return type;
    }

    public void checkPosition(int position) {
        if (position <= 0 || position > this.instructions.size()) {
            throw new IllegalArgumentException("la position est incorrecte.");
        }
    }

    public void ajouterDuree(Instruction instruction){
       dureeEnMinutes = dureeEnMinutes.plus(instruction.getDureeEnMinutes());
    }

    public void supprimerDuree(Instruction instruction){
        dureeEnMinutes = dureeEnMinutes.minus(instruction.getDureeEnMinutes());
    }

    public void insererInstruction(int position, Instruction instruction) {
        //insère l'instruction à la position précisée, position commençant à 1
        checkPosition(position);
        instructions.add(position-1, instruction);
        ajouterDuree(instruction);
    }

    public void ajouterInstruction(Instruction instruction) {
        instructions.add(instruction);
        ajouterDuree(instruction);
    }

    public Instruction remplacerInstruction(int position, Instruction instruction) {
        checkPosition(position);
        Instruction supp = instructions.remove(position-1);
        instructions.add(position-1, instruction);
        supprimerDuree(supp);
        ajouterDuree(instruction);
        return supp;
    }

    public Instruction supprimerInstruction(int position) {
        checkPosition(position);
        Instruction supp = instructions.remove(position-1);
        supprimerDuree(supp);
        return supp;
    }

    /* consultation des instructions**/
    public Iterator<Instruction> instructions() {
        return instructions.iterator();
    }


    /* gestion des ingredients quantifiés via méthodes: */
    public boolean ajouterIngredient(Ingredient ingredient, int quantite, Unite unite) {
        IngredientQuantifie nouveauIngredientQuantifie = new IngredientQuantifie(ingredient, quantite, unite);
        if (ingredients.contains(nouveauIngredientQuantifie)) return false;
        ingredients.add(nouveauIngredientQuantifie);
        return true;
    }

    public boolean ajouterIngredient(Ingredient ingredient, int quantite) {
        return ajouterIngredient(ingredient, quantite, Unite.NEANT);
    }

    public boolean modifierIngredient(Ingredient ingredient, int quantite, Unite unite) {
        for (IngredientQuantifie ingreQ :
                ingredients) {
            if(ingreQ.getIngredient().equals(ingredient)){
                ingreQ.setQuantite(quantite);
                ingreQ.setUnite(unite);
                return true;
            }
        }
        return false;
    }
    public boolean supprimerIngredient(Ingredient ingredient){
        for (IngredientQuantifie ingredientList :
                ingredients) {
            if(ingredientList.getIngredient().equals(ingredient)){
                ingredients.remove(ingredientList);
                return true;
            }
        }
        return false;
    }

    public IngredientQuantifie trouverIngredientQuantifie(Ingredient ingredient){
        for (IngredientQuantifie ingredientList :
                ingredients) {
            if(ingredientList.getIngredient().equals(ingredient)){
                return ingredientList;
            }
        }
        return null;
    }


    @Override
    public String toString() {
        String hms = String.format("%d h %02d m", dureeEnMinutes.toHours(), dureeEnMinutes.toMinutes()%60);
        String res = this.nom + "\n\n";
        res += "Pour " + this.nbPersonnes + " personnes\n";
        res += "Difficulté : " + this.niveauDeDifficulte + "\n";
        res += "Coût : " + this.cout + "\n";
        res += "Durée : " + hms + " \n\n";
        res += "Ingrédients :\n";
        for (domaine.IngredientQuantifie ing : this.ingredients) {
            res += ing + "\n";
        }
        int i = 1;
        res += "\n";
        for (Instruction instruction : this.instructions) {
            res += i++ + ". " + instruction + "\n";
        }
        return res;
    }

}

