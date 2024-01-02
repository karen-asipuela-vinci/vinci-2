package domaine;

import exceptions.DateDejaPresenteException;
import exceptions.PrixNonDisponibleException;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;
import usecase.ListeProduits;

import java.time.DateTimeException;
import java.time.LocalDate;

import static org.junit.jupiter.api.Assertions.*;

class ProduitTest {
    private Prix prixAucune;
    private Prix prixPub;
    private Prix prixSolde;
    private Produit produit1All;
    private Produit produit2;
    private static final LocalDate DATE_ANNEE_PASSEE = LocalDate.now().minusYears(1);
    private static final LocalDate DATE_MOIS_PASSEE = LocalDate.now().minusMonths(7);
    private static final LocalDate DATE_AUJOURDHUI = LocalDate.now();

    @BeforeEach
    void setUp() {
        prixAucune = new Prix();
        prixPub = new Prix(TypePromo.PUB, 10);
        prixSolde = new Prix(TypePromo.SOLDE, 30);

        prixAucune.definirPrix(1,20);
        prixAucune.definirPrix(10,10);
        prixPub.definirPrix(3,15);

        //on initialise :
        produit1All = new Produit("Produit1", "Marque1", "Rayon1");
        produit2 = new Produit("Produit2", "Marque2", "Rayon2");
        //ajouter 3 prix dans produit 1 :
        produit1All.ajouterPrix(DATE_ANNEE_PASSEE, prixAucune);
        produit1All.ajouterPrix(DATE_MOIS_PASSEE, prixPub);
        produit1All.ajouterPrix(DATE_AUJOURDHUI, prixSolde);
    }

    //Tests constructeurs :
    @ParameterizedTest
    @DisplayName("Test constructeur:")
    @ValueSource(strings = {"", " \n", " \t"})
    void testConstructeur (String vides) {
        assertAll(
                //test du nom :
                () -> assertThrows(IllegalArgumentException.class, () -> new Produit(null, "cc", "dd")),
                () -> assertThrows(IllegalArgumentException.class, () -> new Produit(vides, "cc", "dd")),
                //test de marque :
                () -> assertThrows(IllegalArgumentException.class, () -> new Produit("null", null, "dd")),
                () -> assertThrows(IllegalArgumentException.class, () -> new Produit(vides, vides, "dd")),
                //test de rayon :
                () -> assertThrows(IllegalArgumentException.class, () -> new Produit("null", "cc", null)),
                () -> assertThrows(IllegalArgumentException.class, () -> new Produit("vides", "cc", vides))
        );
    }
    //Test des valeurs en paramètres = celles des getters !!!!!
    @Test
    @DisplayName("test getMarque")
    void getMarque() {
        assertEquals("marque", new Produit("nom", "marque", "rayon").getMarque());
    }

    @Test
    @DisplayName("test getNom")
    void getNom() {
        assertEquals("nom", new Produit("nom", "marque", "rayon").getNom());
    }

    @Test
    @DisplayName("test getRayon")
    void getRayon() {
        assertEquals("rayon", new Produit("nom", "marque", "rayon").getRayon());
    }

    //tests des prix :
    @Test
    @DisplayName("Test prix : exceptions")
    void ajouterPrixExceptions() {
        assertAll(
                //si prix null :
                () -> assertThrows(IllegalArgumentException.class, () -> produit1All.ajouterPrix(LocalDate.now(), null)),
                //si date null:
                () -> assertThrows(IllegalArgumentException.class, () -> produit1All.ajouterPrix(null, prixSolde)),
                //si date existe déjà :
                () -> assertThrows(DateDejaPresenteException.class, () -> produit1All.ajouterPrix(DATE_AUJOURDHUI, prixAucune)
                )
        );
    }

    @Test
    @DisplayName("test prix 2 : ajouterPrix + getPrix")
    void testAjouterPrix(){
        LocalDate dateTest = LocalDate.now();
        LocalDate dateTest2 = LocalDate.now().minusMonths(3);
        produit2.ajouterPrix(dateTest, prixPub);
        produit2.ajouterPrix(dateTest2, prixAucune);
        assertAll(
                () -> assertEquals(prixPub, produit2.getPrix(dateTest)),
                () -> assertEquals(prixAucune, produit2.getPrix(dateTest2))
        );
    }

    @Test
    @DisplayName("Test prix 3 : ajouter Prix à date antérieure")
    void testAjouterPrixAnterException() {
        assertThrows(PrixNonDisponibleException.class,
                () -> produit2.getPrix(DATE_AUJOURDHUI.minusMonths(8)));
    }

    @Test
    @DisplayName("Test prix 4 : exception quand pas de prix")
    void testGetPrixPasPrix() {
        assertThrows(PrixNonDisponibleException.class, () -> produit2.getPrix(LocalDate.now()));
    }

    @Test
    @DisplayName("Test prix 5 : Vérifier que prix ok entre 2 dates")
    void testGetPrix2dates() {
        /*
        produit1All.ajouterPrix(DATE_ANNEE_PASSEE, prixAucune);
        produit1All.ajouterPrix(DATE_MOIS_PASSEE, prixPub);
        produit1All.ajouterPrix(DATE_AUJOURDHUI, prixSolde);
         */
        assertAll(
                () -> assertEquals(prixAucune, produit1All.getPrix(DATE_ANNEE_PASSEE.plusDays(1))),
                () -> assertEquals(prixAucune, produit1All.getPrix(DATE_MOIS_PASSEE.minusDays(3))),
                () -> assertEquals(prixPub, produit1All.getPrix(DATE_AUJOURDHUI.minusDays(2))),
                () -> assertEquals(prixSolde, produit1All.getPrix(DATE_AUJOURDHUI.plusDays(3)))
        );
    }

    //test des méthodes equals et hashcode :
    @Test
    @DisplayName("Test E/#code : ")
    void testEqualsHashcode1() {
        String nom = "nomA", marque = "marqueA", rayon = "rayonA";
        Produit produitTest = new Produit(nom, marque, rayon);
        Produit produitTest2 = new Produit(nom,marque, rayon);
        Produit produitNomDiff = new Produit("lambda",marque, rayon);
        Produit produitMarqueDiff = new Produit(nom, "marqueeee", rayon);
        Produit produitRayonDiff = new Produit(nom, marque, "rayyyon");

        assertAll(
                () -> assertEquals(produitTest, produitTest2),
                () -> assertNotEquals(produitTest, produitNomDiff),
                () -> assertNotEquals(produitTest, produitMarqueDiff),
                () -> assertNotEquals(produitTest, produitRayonDiff),
                //test hashcode :
                () -> assertEquals(produitTest.hashCode(), produitTest2.hashCode())
        );
    }


}