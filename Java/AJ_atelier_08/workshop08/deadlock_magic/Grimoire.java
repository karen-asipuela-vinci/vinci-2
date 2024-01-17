package deadlock_magic;

public class Grimoire {



    public enum Incantation {
        FLAMBOIEMENT_ARDENT,
        DANSE_DES_COMETES,
        ECLAT_DU_PHENIX,
        RESONNANCE_DES_SAGES,
        MURMURES_GIVRES,
        VORTEX_ANCESTRAL
    }

    public enum Ceremonie {
        //Pour régler un deadlock, il faut éviter que l'un se marche sur l'autre :
        // Mettre le meme ordre garantit que tous les threads acquièrent les ressources dans le même ordre,
        // évitant ainsi le scénario où deux threads peuvent être bloqués en attendant la ressource que l'autre détient.
        SYMPOSIUM_DES_ILLUSIONS_PRISMATIQUES(Incantation.FLAMBOIEMENT_ARDENT, Incantation.ECLAT_DU_PHENIX, Incantation.MURMURES_GIVRES),
        ASSEMBLEE_DES_ONDES_FRISSONNATES(Incantation.FLAMBOIEMENT_ARDENT, Incantation.ECLAT_DU_PHENIX, Incantation.MURMURES_GIVRES),
        RITUEL_DU_CREPUSCAL_ABYSSAL(Incantation.FLAMBOIEMENT_ARDENT, Incantation.ECLAT_DU_PHENIX, Incantation.MURMURES_GIVRES);

        final Incantation incantation1;
        final Incantation incantation2;
        final Incantation incantation3;

        Ceremonie(Incantation incantation1, Incantation incantation2, Incantation incantation3) {
            this.incantation1 = incantation1;
            this.incantation2 = incantation2;
            this.incantation3 = incantation3;
        }

        public void debuter(){
            System.out.println(name() + " débute");
            synchronized (incantation1){
                System.out.println(incantation1 + " pris pour " + name());
                mediter();
                synchronized (incantation2){
                    System.out.println(incantation2 + " pris pour " + name());
                    mediter();
                    synchronized (incantation3){
                        System.out.println(incantation3 + " pris pour " + name());
                        mediter();
                        System.out.println(name() + " lancé !");
                    }
                }
            }
        }

        public void mediter(){
            System.out.println("Méditation");
            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }

    }


}
