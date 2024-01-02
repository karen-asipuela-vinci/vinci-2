package domaine;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class MoniteurImplTest {
    // on choppe les attributs nécessaires au test:
    private Sport sport;
    private Moniteur moniteur;
    private Stage stage;

    @BeforeEach
    void setUp() {
        //on a besoin d'un sport avec bon moniteur, moniteur competent et stage sans moniteur
        sport = new SportStub(true);
        moniteur = new MoniteurImpl("moniteurTest");
        stage = new StageStub(8, sport, null);
    }

    private void amenerALEtat(int etat, Moniteur moniteur){
        //pour ramener à l'état : on ajoute le nombre de stages correspondants :
        for (int i = 1; i <= etat; i++) {
            moniteur.ajouterStage(new StageStub(i,sport, null));
        }
    }

    @Test
    void testMoniteurTC1() {
        //besoin de tester plusieurs choses:
        assertAll(
                //D'abord, la méthode ajouterStage doit renvoyer un true:
                () -> assertTrue(moniteur.ajouterStage(stage)),
                //Ensuite, le moniteur doit renvoyer le stage (true):
                () -> assertTrue(moniteur.contientStage(this.stage)),
                //puis faut check l'état=nombre de stages qui doit être à 1:
                () -> assertEquals(1, moniteur.nombreDeStages())
        );
    }

    @Test
    void testMoniteurTC2() {
        //besoin d'être en état 1 pour test:
        amenerALEtat(1, moniteur);
        assertAll(
                () -> assertTrue(moniteur.ajouterStage(stage)),
                () -> assertTrue(moniteur.contientStage(stage)),
                () -> assertEquals(2, moniteur.nombreDeStages())
        );
    }

    @Test
    void TestMoniteurTC3() {
        //en état 2:
        amenerALEtat(2, moniteur);
        assertAll(
                () -> assertTrue(moniteur.ajouterStage(stage)),
                () -> assertTrue(moniteur.contientStage(stage)),
                () -> assertEquals(3, moniteur.nombreDeStages())
        );
    }

    @Test
    void TestMoniteurTC4(){
        //en état 3 :
        amenerALEtat(3, moniteur);
        assertAll(
                () -> assertTrue(moniteur.ajouterStage(stage)),
                () -> assertTrue(moniteur.contientStage(stage)),
                () -> assertEquals(4, moniteur.nombreDeStages())
        );
    }

    @Test
    void TestMoniteurTC5() {
        /* Ma réponse :
            //en état 4:
            amenerALEtat(4, moniteur);
            //on récup un stage :
            Stage stageTest = moniteur.stages().get(0);
        */
        /*
        Mais on peut éviter de passer par la création d'un stage,
        en passant par l'état 3 puis en rajoutant le stage:
         */
        amenerALEtat(3, moniteur);
        moniteur.ajouterStage(stage);
        assertAll(
                () -> assertTrue(moniteur.supprimerStage(stage)),
                () -> assertFalse(moniteur.contientStage(stage)),
                () -> assertEquals(3, moniteur.nombreDeStages())
        );
    }

    @Test
    void TestMoniteurTC6() {
        //en état 3:
        amenerALEtat(2, moniteur);
        moniteur.ajouterStage(stage);
        assertAll(
                () -> assertTrue(moniteur.supprimerStage(stage)),
                () -> assertFalse(moniteur.contientStage(stage)),
                () -> assertEquals(2, moniteur.nombreDeStages())
        );
    }

    @Test
    void TestMoniteurTC7() {
        //en état 2:
        amenerALEtat(1, moniteur);
        moniteur.ajouterStage(stage);
        assertAll(
                () -> assertTrue(moniteur.supprimerStage(stage)),
                () -> assertFalse(moniteur.contientStage(stage)),
                () -> assertEquals(1, moniteur.nombreDeStages())
        );
    }

    @Test
    void TestMoniteurTC8() {
        //en état 1:
        moniteur.ajouterStage(stage);
        assertAll(
                () -> assertTrue(moniteur.supprimerStage(stage)),
                () -> assertFalse(moniteur.contientStage(stage)),
                () -> assertEquals(0, moniteur.nombreDeStages())
        );
    }

    @Test
    void TestMoniteurTC9() {
        //en état 4:
        amenerALEtat(3, moniteur);
        moniteur.ajouterStage(stage);
        assertAll(
                () -> assertFalse(moniteur.ajouterStage(stage)),
                () -> assertEquals(4, moniteur.nombreDeStages())
        );
    }

    @Test
    void TestMoniteurTC10() {
        //en état 4:
        amenerALEtat(4, moniteur);
        Stage stageWeek = new StageStub(1,sport, null);
        assertAll(
                () -> assertFalse(moniteur.ajouterStage(stageWeek)),
                () -> assertFalse(moniteur.contientStage(stageWeek)),
                () -> assertEquals(4, moniteur.nombreDeStages())
        );
    }

    @Test
    void TestMoniteurTC11() {
        //en état 4:
        amenerALEtat(4, moniteur);
        assertAll(
                () -> assertFalse(moniteur.supprimerStage(stage)),
                () -> assertEquals(4, moniteur.nombreDeStages())
        );
    }

    @Test
    void TestMoniteurTC12() {
        //en état 4:
        amenerALEtat(4, moniteur);
        Moniteur moniteur1 = new MoniteurImpl("test");
        Stage stage1 = new StageStub(8,sport, moniteur1);

        assertAll(
                () -> assertFalse(moniteur.ajouterStage(stage1)),
                () -> assertFalse(moniteur.contientStage(stage1)),
                () -> assertEquals(4, moniteur.nombreDeStages())
        );
    }

    @Test
    void TestMoniteurTC13() {
        //en état 4:
        amenerALEtat(4, moniteur);
        Stage stage1 = new StageStub(5,sport, moniteur);
        assertAll(
                () -> assertTrue(moniteur.ajouterStage(stage1)),
                () -> assertTrue(moniteur.contientStage(stage1)),
                () -> assertEquals(5, moniteur.nombreDeStages())
        );
    }

    @Test
    void TestMoniteurTC14() {
        //en état 4:
        amenerALEtat(4, moniteur);
        Sport sport1 = new SportStub(false);
        Stage stage1 = new StageStub(5,sport1,null);
        assertAll(
                () -> assertFalse(moniteur.ajouterStage(stage1)),
                () -> assertFalse(moniteur.contientStage(stage1)),
                () -> assertEquals(4, moniteur.nombreDeStages())
        );
    }

}