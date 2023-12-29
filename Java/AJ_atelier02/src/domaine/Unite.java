package domaine;

public enum Unite {
        //declaration de toutes les instances/constantes de l'énuméré :
        GRAMME("gr"), KILOGRAMME("kg"), LITRE("l"), MILLILITRE("ml"),
    CENTILITRE("cl"), DECILITRE("dl"), CUILLER_A_CAFE ("cc"), CUILLER_A_THE("ct"),
    CUILLER_A_DESSERT("cd"), CUILLER_A_SOUPE("cs"), PINCEE("pincee"), UN_PEU("peu"),
    NEANT("");

        private String abrv ;

        Unite(String abrv) {
            this.abrv = abrv;
        }

        public String getAbrv() {
            return abrv;
        }

        @Override
        public String toString() {
            return abrv ;
        }
    }
