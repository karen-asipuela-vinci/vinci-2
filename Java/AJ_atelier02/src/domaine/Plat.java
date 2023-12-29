package domaine;

import util.Util;

import java.net.CookieHandler;
import java.time.Duration;
import java.util.*;
import java.util.stream.Collector;

public class Plat {
    //2 enums : Difficulte et Cout:
    public enum Difficulte {
        //declaration de toutes les instances/constantes de l'énuméré :
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

    //Attributs :
    private String nom;
    private int nbPersonnes;
    private Difficulte niveauDeDifficulte;
    private Cout cout;
    private Duration dureeEnMinutes;
    private List<Instruction> instructions; //List pour ordre séquentiel
    private Set<IngredientQuantifie> ingredients; // on utilise set car l'ordre des
    // ingredients quantitifiés n'a pas d'importance

    public Plat(String nom, int nbPersonnes, Difficulte niveauDeDifficulte, Cout cout) {
        this.nom = nom;
        this.nbPersonnes = nbPersonnes;
        this.niveauDeDifficulte = niveauDeDifficulte;
        this.cout = cout;
        this.dureeEnMinutes = Duration.ofMinutes(0);
        this.instructions = new ArrayList<>();
        this.ingredients = new HashSet<>();
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


    public void ajouterDuree(Instruction instruction){
       dureeEnMinutes = dureeEnMinutes.plus(instruction.getDureeEnMinutes());
    }

    public void supprimerDuree(Instruction instruction){
        dureeEnMinutes = dureeEnMinutes.minus(instruction.getDureeEnMinutes());
    }

    /** Cette méthode insère l'instruction à la position précisée (la position commence à 1)
     * @param position la position à laquelle l'instruction doit être insérée
     * @param instruction l'instruction à insérer
     * @throws IllegalArgumentException en cas de position invalide ou d'instruction null
     */
    public void insererInstruction(int position, Instruction instruction) {
        //insère l'instruction à la position précisée, position commençant à 1
        Util.checkStrictlyPositive(position);
        if (position > instructions.size()) throw new IllegalArgumentException();
        instructions.add(position-1, instruction);
        ajouterDuree(instruction);
    }

    /**
     * Cette méthode ajoute l'instruction en dernier
     * @param instruction
     * @throws IllegalArgumentException si position invalide ou instruction null
     */
    public void ajouterInstruction(Instruction instruction) {
        Util.checkObject(instruction);
        instructions.add(instruction);
        ajouterDuree(instruction);
    }

    /**
     * Cette méthode remplace une instruction à la position précisée par celle en paramètre
     * @param position
     * @param instruction
     * @return instruction supprimée
     * @throws IllegalArgumentException si position invalide ou instruction null
     */
    public Instruction remplacerInstruction(int position, Instruction instruction) {
        Util.checkStrictlyPositive(position);
        Util.checkObject(instruction);
        if (position > instructions.size()) throw new IllegalArgumentException();
        //Instruction supp = instructions.remove(position-1);
        //instructions.add(position-1, instruction);
        //il existe méthode set !!!
        Instruction supp = instructions.set(position-1, instruction);
        supprimerDuree(supp);
        ajouterDuree(instruction);
        return supp;
    }

    /**
     * Cette méthode supprime l'instruction à la position donnée
     * @param position
     * @return l'instruction supprimée
     * @throws IllegalArgumentException si position invalide
     */
    public Instruction supprimerInstruction(int position) {
        Util.checkStrictlyPositive(position);
        if (position > instructions.size()) throw new IllegalArgumentException();
        Instruction supp = instructions.remove(position-1);
        supprimerDuree(supp);
        return supp;
    }

    /* consultation des instructions sans suppression possible*/
    public Iterator<Instruction> instructions() {
        return Collections.unmodifiableList(instructions).iterator();
    }


    /* gestion des ingredients quantifiés via méthodes: */

    /**
     * Cette méthode crée un ingredient quantité et l'ajoute s'il n'est pas encore existant
     * @param ingredient
     * @param quantite
     * @param unite
     * @return false si ingrédient déjà présent, true sinon
     * @throws IllegalArgumentException si paramètres invalides
     */
    public boolean ajouterIngredient(Ingredient ingredient, int quantite, Unite unite) {
        Util.checkObject(ingredient);
        Util.checkStrictlyPositive(quantite);
        if(trouverIngredientQuantifie(ingredient) != null) return false;
        ingredients.add(new IngredientQuantifie(ingredient, quantite, unite));
        return true;
    }

    /**
     * Créé un ingréfient quantifié et l'ajoute s'il n'est pas encore existant
     * avec l'unité NEANT
     * @param ingredient
     * @param quantite
     * @return false si ingrédient déjà présent, sinon true.
     * @throws IllegalArgumentException si paramètres invalides
     */
    public boolean ajouterIngredient(Ingredient ingredient, int quantite) {
        return ajouterIngredient(ingredient, quantite, Unite.NEANT);
    }

    /**
     * modifie l'unité et la quantité de l'ingrédient quantifié correspondant
     * à l'ingrédient passé en paramètre
     * @param ingredient
     * @param quantite
     * @param unite
     * @return false si l'ingrédient n'est pas présent
     * @throws IllegalArgumentException si paramètres invalides
     */
    public boolean modifierIngredient(Ingredient ingredient, int quantite, Unite unite) {
        Util.checkObject(ingredient);
        Util.checkStrictlyPositive(quantite);
        /*
        il existe méthodes qu'on peut utiliser donc pas de foreach !!
        for (IngredientQuantifie ingreQ :
                ingredients) {
            if(ingreQ.getIngredient().equals(ingredient)){
                ingreQ.setQuantite(quantite);
                ingreQ.setUnite(unite);
                return true;
            }
        }
        return false;
        */
        IngredientQuantifie ingredientQuantifie = trouverIngredientQuantifie(ingredient);
        if(ingredientQuantifie == null) return false;
        ingredientQuantifie.setQuantite(quantite);
        ingredientQuantifie.setUnite(unite);
        return true;
    }

    /**
     * Supprime ingrédient donné en paramètre
     * @param ingredient
     * @return false si ingrédient pas présent//pas supprimé
     * @throws IllegalArgumentException si paramètre invalide
     */
    public boolean supprimerIngredient(Ingredient ingredient){
        Util.checkObject(ingredient);
        IngredientQuantifie ingredientQuantifie = trouverIngredientQuantifie(ingredient);
        if (ingredientQuantifie == null) return false;
        return ingredients.remove(ingredientQuantifie);
    }

    /**
     * Recherche et renvoie l'ingrédient quantifié
     * correspondant à l'ingrédient en paramètre
     * @param ingredient
     * @return l'ingrédient quantifié correspondant ou null si n'existe pas
     * @throws IllegalArgumentException si paramètre null
     */
    public IngredientQuantifie trouverIngredientQuantifie(Ingredient ingredient){
        Util.checkObject(ingredient);
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

    //pas du touuuuuuuuuuuuuuuut sure de ça
    /**
     * renvoie l'ensemble des ingrédients utilisés dans le plat
     * triés par nom d'ingrédient
     * @return ensemble des ingrédients triés
     */
    public SortedSet<Ingredient> ingredients() {
        SortedSet<Ingredient> ingredientsTries = new TreeSet<>();
        for(IngredientQuantifie ingredient : ingredients){
            ingredientsTries.add(ingredient.getIngredient());
        }
        return ingredientsTries;
        }
}

