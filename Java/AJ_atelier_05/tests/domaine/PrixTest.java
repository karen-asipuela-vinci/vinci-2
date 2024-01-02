package domaine;

import exceptions.QuantiteNonAutoriseeException;
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

        prixAucune.definirPrix(1,20);
        prixAucune.definirPrix(10,10);

         //  Dans prixPub, signifiez qu’à partir de 3 unités, le prix est de 15 euros

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
    //pour test avec plusieurs valeurs -> @ValueSource :
    @ValueSource(doubles = {-7,-4,0})
    void testPrix2(double valeur){
        assertThrows(IllegalArgumentException.class, () -> new Prix(TypePromo.SOLDE,valeur));
    }

    //tests des getteurs
    @Test
    @DisplayName("Test Getter : vérifier valeur de getValeurPromo")
    //Pour comparer 2 valeurs (int, double), on utilise assertEquals
    void testGetValeurPromo() {
        assertAll(
                //test 1 : vérifie que renvoie 0 quand constructeur sans paramètre
                () -> assertEquals(0, prixAucune.getValeurPromo()),
                // test 2 : vérifie que renvoie la valeur de la promo à celle en paramètre
                () -> assertEquals(10, prixPub.getValeurPromo()),
                () -> assertEquals(30, prixSolde.getValeurPromo()),
                //test 3 : vérifie que type promo = null pendant instanciation prix
                //quand constructeur sans paramètres :
                () -> assertNull(new Prix().getTypePromo()),
                //test 4 : vérifie que le type de promo correspond à celle passée en paramètre :
                () -> assertEquals(TypePromo.PUB, new Prix(TypePromo.PUB, 10).getTypePromo()),
                () -> assertEquals(TypePromo.SOLDE, new Prix(TypePromo.SOLDE, 30).getTypePromo())
        );
    }

    @ParameterizedTest
    @DisplayName("Tests DéfinirPrix 1 : quantité strict pos ")
    @ValueSource(ints = {-5,-7,0})
    void testDefinirPrixQuantite(int quantite) {
         assertThrows(IllegalArgumentException.class, () -> prixPub.definirPrix(quantite, 15));
    }

    @ParameterizedTest
    @DisplayName("Tests DéfinirPrix 2 : prix unitaire strict pos ")
    @ValueSource(doubles = {-5,-7,0})
    void testDefinirPrixPrixUnit(double prixUnitaire) {
         assertThrows(IllegalArgumentException.class, () -> prixPub.definirPrix(15, prixUnitaire));
    }

    @Test
    @DisplayName("Tests DéfinirPrix 3 : remplacement du prix")
    void testDefinirPrixRemplacement() {
         prixPub.definirPrix(10,6);
         assertEquals(6, prixPub.getPrix(10));
    }


    @ParameterizedTest
    @DisplayName("Test GetPrix 1 : vérifie IllArgE si quantité neg ou nul")
    @ValueSource(ints = {-7,-5,0})
    void testGetPrixQuantite(int quantite) {
        assertThrows(IllegalArgumentException.class, () -> prixPub.getPrix(quantite));
    }

    @ParameterizedTest
    @DisplayName("Test GetPrix 2 : range 1")
    //ValueSource(ints = {1,5,9,10,15,20,25})
    //faut tester les valeurs en plusieurs fois pour test les ranges :
    //range 1 -> 0-9 = 20
    //range 2 -> 10 = 10
    @ValueSource(ints = {1,5,9})
    void testGetPrixAucune1(int quantite) {
        assertEquals(20,prixAucune.getPrix(quantite));
    }

    @ParameterizedTest
    @DisplayName("Test GetPrix 2 : range 2")
    @ValueSource(ints = {10,15,20,25})
    void testGetPrixAucune2(int quantite) {
        assertEquals(10,prixAucune.getPrix(quantite));
    }

    @Test
    @DisplayName("Test GetPrix 3-4 : Exception")
    void testGetPrixPub () {
        assertAll(
                //QuantiteNonAutoriseeException si getPrix = 2 pour prixPub
                () -> assertThrows(QuantiteNonAutoriseeException.class, () -> prixPub.getPrix(2)),
                //same avec prixSolde pour 1 :
                () -> assertThrows(QuantiteNonAutoriseeException.class, () -> prixSolde.getPrix(1))
        );

    }

}