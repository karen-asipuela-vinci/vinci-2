package tri_fusion;

import java.time.LocalDateTime;
import java.time.temporal.ChronoUnit;
import java.util.Random;

public class Main {
	
	public static void main(String[] args) {
		int[] table = new Random().ints(100000000, 1, 100000000).toArray();
		LocalDateTime start = LocalDateTime.now();
		//on rajoute nbThreads
		Sorter sorter = new Sorter(table,8);
		/* Quand mono thread, juste le démarrer c'est ok :
		sorter.sort();
		*/
		//mais pour multi thread, il faut le démarrer et attendre qu'il se termine
		//faut adapter la méthode run()//start() de Sorter.java
		sorter.start();
		try {
			sorter.join();
		} catch (InterruptedException ignore) {
		}
		System.out.println("\n" + ChronoUnit.MILLIS.between(start, LocalDateTime.now()));
		// Vérification tri de la table
		for (int i = 0; i < table.length-1; i++) {
			if(table[i] > table[i+1]){
				System.out.println("Table non triée correctement");
				return;
			}
		}
		System.out.println("Table triée correctement");
	}
	
}
