package domaine;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;
import org.mockito.Mockito;
import org.mockito.invocation.MockHandler;
import org.mockito.junit.MockitoJUnit;

import static org.junit.jupiter.api.Assertions.*;

class MoniteurImpTest {
    private Sport sport;
    private Moniteur moniteur;
    private Stage stage;

    @BeforeEach
    void setUp() {
        moniteur = new MoniteurImpl("nomMoniteur");
        //pour "initialiser" depuis mockito :
        sport = Mockito.mock(Sport.class);
        //pour définir le comportement :
        Mockito.when(sport.contientMoniteur(moniteur)).thenReturn(true);

        stage = Mockito.mock(Stage.class);
        //faut que le moniteur soit null, le sport ok et semaine ok
        Mockito.when(stage.getMoniteur()).thenReturn(null);
        Mockito.when(stage.getNumeroDeSemaine()).thenReturn(8);
        Mockito.when(stage.getSport()).thenReturn(sport);
    }

    void amenerALEtat(int etat, Moniteur moniteur) {
        for (int i = 1; i <= etat; i++) {
            Stage stageTest = Mockito.mock(Stage.class);
            Mockito.when(stageTest.getNumeroDeSemaine()).thenReturn(i);
            Mockito.when(stageTest.getMoniteur()).thenReturn(null);
            Mockito.when(stageTest.getSport()).thenReturn(sport);
            moniteur.ajouterStage(stageTest);
        }
    }

    @Test
    void testMoniteurTC1() {
        assertAll(
                () -> assertTrue(moniteur.ajouterStage(stage)),
                () -> assertTrue(moniteur.contientStage(stage)),
                () -> assertEquals(1, moniteur.nombreDeStages()),
                () -> Mockito.verify(stage).enregistrerMoniteur(moniteur)
        );
    }

    @Test
    void testMoniteurTC2() {
        amenerALEtat(1, moniteur);
        assertAll(
                () -> assertTrue(moniteur.ajouterStage(stage)),
                () -> assertTrue(moniteur.contientStage(stage)),
                () -> assertEquals(2, moniteur.nombreDeStages()),
                () -> Mockito.verify(stage).enregistrerMoniteur(moniteur)
        );
    }

    @Test
    void testMoniteurTC3() {
        amenerALEtat(2, moniteur);
        assertAll(
                () -> assertTrue(moniteur.ajouterStage(stage)),
                () -> assertTrue(moniteur.contientStage(stage)),
                () -> assertEquals(3, moniteur.nombreDeStages()),
                () -> Mockito.verify(stage).enregistrerMoniteur(moniteur)
        );
    }

    @Test
    void testMoniteurTC4() {
        amenerALEtat(3, moniteur);
        assertAll(
                () -> assertTrue(moniteur.ajouterStage(stage)),
                () -> assertTrue(moniteur.contientStage(stage)),
                () -> assertEquals(4, moniteur.nombreDeStages()),
                () -> Mockito.verify(stage).enregistrerMoniteur(moniteur)
        );
    }

    @Test
    void testMoniteurTC5() {
        amenerALEtat(3, moniteur);
        moniteur.ajouterStage(stage);
        assertAll(
                () -> assertFalse(moniteur.ajouterStage(stage)),
                () -> assertTrue(moniteur.contientStage(stage)),
                () -> assertEquals(4, moniteur.nombreDeStages()),
                //Vérification que la méthode enregistrerMoniteur a été appelée
                // une seule fois (pour le premier ajout) et non 2
                () -> Mockito.verify(stage).enregistrerMoniteur(moniteur)
        );
    }

    @ParameterizedTest
    @ValueSource(ints = {1,2,3,8})
    void testMoniteurTC6(int semaine) {
        amenerALEtat(3, moniteur);
        moniteur.ajouterStage(stage);
        //pour rappel, stage = semaine 8 (ou semaine < 4)
        Stage stage1 = Mockito.mock(Stage.class);
        Mockito.when(stage1.getSport()).thenReturn(sport);
        Mockito.when(stage1.getNumeroDeSemaine()).thenReturn(semaine);
        Mockito.when(stage1.getMoniteur()).thenReturn(null);

        assertAll(
                () -> assertFalse(moniteur.ajouterStage(stage1)),
                () -> assertFalse(moniteur.contientStage(stage1)),
                () -> assertEquals(4, moniteur.nombreDeStages()),
                //rajouter le never quand ne doit pas passer par une méthode:
                () -> Mockito.verify(stage1, Mockito.never()).enregistrerMoniteur(moniteur)
        );
    }

    @Test
    void testMoniteurTC7() {
         amenerALEtat(4, moniteur);
    Moniteur autreMoniteur = new MoniteurImpl("Snake");
    Stage stageAutreMoniteur = Mockito.mock(Stage.class);
    Mockito.when(stageAutreMoniteur.getSport()).thenReturn(sport);
    Mockito.when(stageAutreMoniteur.getMoniteur()).thenReturn(autreMoniteur);
    Mockito.when(stageAutreMoniteur.getNumeroDeSemaine()).thenReturn(8);
    assertAll(() -> assertFalse(moniteur.ajouterStage(stageAutreMoniteur)),
        () -> assertFalse(moniteur.contientStage(stageAutreMoniteur)),
        () -> assertEquals(4, moniteur.nombreDeStages()),
        () -> Mockito.verify(stageAutreMoniteur, Mockito.never()).enregistrerMoniteur(moniteur)
    );
    }

     @Test
  void testMoniteurTC8() {
    amenerALEtat(4, moniteur);
    Stage stageBonMoniteur = Mockito.mock(Stage.class);
    Mockito.when(stageBonMoniteur.getSport()).thenReturn(sport);
    Mockito.when(stageBonMoniteur.getMoniteur()).thenReturn(moniteur);
    Mockito.when(stageBonMoniteur.getNumeroDeSemaine()).thenReturn(8);
    assertAll(() -> assertTrue(moniteur.ajouterStage(stageBonMoniteur)),
        () -> assertTrue(moniteur.contientStage(stageBonMoniteur)),
        () -> assertEquals(5, moniteur.nombreDeStages()),
        () -> Mockito.verify(stageBonMoniteur, Mockito.never()).enregistrerMoniteur(moniteur)
    );
  }

  @Test
  void testMoniteurTC9() {
    amenerALEtat(4, moniteur);
    Sport sportHorsCompetence = Mockito.mock(Sport.class);
    Mockito.when(sportHorsCompetence.contientMoniteur(moniteur)).thenReturn(false);
    Stage stageMauvaisSport = Mockito.mock(Stage.class);
    Mockito.when(stageMauvaisSport.getSport()).thenReturn(sportHorsCompetence);
    Mockito.when(stageMauvaisSport.getMoniteur()).thenReturn(null);
    Mockito.when(stageMauvaisSport.getNumeroDeSemaine()).thenReturn(8);
    assertAll(() -> assertFalse(moniteur.ajouterStage(stageMauvaisSport)),
        () -> assertFalse(moniteur.contientStage(stageMauvaisSport)),
        () -> assertEquals(4, moniteur.nombreDeStages()),
        () -> Mockito.verify(stageMauvaisSport, Mockito.never()).enregistrerMoniteur(moniteur)
    );
  }
}