package domaine;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

import static org.junit.jupiter.api.Assertions.*;

class PrixTest {
    private Prix prixAucune;
    private Prix prixPub;
    private Prix prixSolde;

    @BeforeEach
    void setUp() {
        //faut instancier les attributs ici :
        prixAucune = new Prix();
        prixPub = new Prix(TypePromo.PUB, 10);
        prixSolde = new Prix(TypePromo.SOLDE, 30);

        //Dans prixAucune définissez 2 prix : l’un pour signifier qu’à partir d’une unité,
        // le prix unitaire est de 20 euros et l’autre pour signifier qu’à partir de 10 unités (quantité),
        // le prix unitaire devient 10 euros.
        //  Dans prixPub, signifiez qu’à partir de 3 unités, le prix est de 15 euros

        prixAucune.definirPrix(1,20);
        prixAucune.definirPrix(10,10);

        prixPub.definirPrix(3,15);
    }

    @Test
    @DisplayName("Test 1 : constructeur avec Promo NULL")
    void testPrix1(){
        assertThrows(IllegalArgumentException.class, () -> new Prix(null, 15));
    }

// attention aux @ !!
    @ParameterizedTest
    @DisplayName("Test 2 : constructeur avec val neg (val <= 0)")
    @ValueSource(doubles = {-7,-4,0})
    void testPrix2(double valeur){
        assertThrows(IllegalArgumentException.class, () -> new Prix(TypePromo.SOLDE,valeur));
    }

    //tests des getteurs
    @Test
    @DisplayName("vérifier valeur de getValeurPromo")
    //Pour comparer 2 valeurs (int, double) , on utilise assertEquals
    void testGetValeurPromo() {
        assertAll(() -> assertEquals(0, prixAucune.getValeurPromo()),
                //vérifie que renvoie 0 quand constructeur sans paramètre
                () -> assertEquals(10, prixPub.getValeurPromo()),
                //vérifie que renvoie la valeur de la promo à celle en paramètre
                () -> assertEquals(30, prixSolde.getValeurPromo())
        );
    }

    @Test
    @DisplayName("vérifier valeur de getTypePromo")
    //Pour comparer null -> assertNull
    //Pour comparer ET doivent être les memes -> assertSame (pour string et objets)
    void testGetTypePromo() {
        assertAll(() -> assertNull(prixAucune.getTypePromo()),
                //doit renvoyer null si on instancie un prix dans paramètre
                //doit renvoyer le meme type
                () -> assertSame(TypePromo.SOLDE, prixSolde.getTypePromo()),
                () -> assertSame(TypePromo.PUB, prixPub.getTypePromo())
        );
    }

    // Test de définirPrix
    //



    void getTypePromo() {
    }

    @Test
    void getValeurPromo() {
    }

    @Test
    void definirPrix() {
    }

    @Test
    void getPrix() {
    }
}