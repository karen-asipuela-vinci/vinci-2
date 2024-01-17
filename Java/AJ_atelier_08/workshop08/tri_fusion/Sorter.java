package tri_fusion;

/**
 * Sort a table of int. Mono-thread version.
 */
//on rajoute extends Thread pour pouvoir utiliser join()
// (car plusieurs threads)
public class Sorter extends Thread{

	// Table to sort
	private int[] table;
	// Slice of the table to sort
	private int start, end;
	// Number of threads in use
	private int nbThreads;

	//on rajoute nbThreads pour pouvoir l'utiliser dans le main
	public Sorter(int[] table) {
		this(table, 0, table.length - 1, 2);
	}

	//on créé un constructeur avec nbThreads
	public Sorter(int[] table, int nbThreads) {
		this(table, 0, table.length - 1, nbThreads);
	}

	//on créé un constructeur avec start et end
	public Sorter(int[] table, int start, int end) {
		this(table, start, end, 2);
	}

	//constructeur d'origine, on rajoute nbThreads
	public Sorter(int[] t, int start, int end, int nbThreads) {
		this.table = t;
		this.start = start;
		this.end = end;
		this.nbThreads = nbThreads;
	}

	//on pourrait rajouter un DEFAULT_NB_THREADS = 2 pour faciliter écriture

	/**
	 * Sort a table of int in ascending order
	 *
	 */
	public void sort() {
		this.sort(this.start, this.end);
	}

	public void run() {
		this.sort();
	}

	/**
	 * Sort a slice of the table
	 * 
	 * @param start start index of the slice to sort
	 * @param end end index of the slice to sort
	 */
	private void sort(int start, int end) {
		// Si la taille du tableau est inférieure à 2
		if (end - start < 2) {
			if (table[start] > table[end]) {
				swap(start, end);
			}
		} // Si plus grands tableaux
		else {
			//on marque le milieu
			int milieu = start + (end - start) / 2;
			//si on a encore des threads
			if(this.nbThreads > 1) {
				//on créé un thread
				Sorter sorter1 = new Sorter(table, start, milieu, this.nbThreads / 2);
				//on créé un thread
				Sorter sorter2 = new Sorter(table, milieu + 1, end, this.nbThreads / 2);
				//on lance les threads
				sorter1.sort();
				sorter2.sort();
				//on attend la fin des threads
				try {
					sorter1.join();
					sorter2.join();
				} catch (InterruptedException e) {}
				//on fusionne les tableaux
				this.mergeSort(this.start, this.end);
			}
			//sinon on fait un tri classique
			else {
				//on créé les threads
				sort(start, milieu);
				sort(milieu + 1, end);
				//on fusionne les tableaux
				this.mergeSort(start, end);
			}
		}
	}

	/**
	 * Swap t[i] and t[j]
	 */
	private void swap(int i, int j) {
		int value = table[i];
		table[i] = table[j];
		table[j] = value;
	}

	/**
	 * Merge 2 sorted slices of the table.
	 * First slice from start to middle, and second slice from middle + 1 to end.
	 * 
	 * @param start start index of the slice to sort
	 * @param end end index of the slice to sort
	 */
	private void mergeSort(int start, int end) {
		// Table where the merge will be stored
		int[] tMerge = new int[end - start + 1];
		int middle = (start + end) / 2;
		// Indexes of the elements to compare
		int i1 = start;
		int i2 = middle + 1;
		// Index of the next cell of the tMerge table to fill
		int iFusion = 0;
		while (i1 <= middle && i2 <= end) {
			if (table[i1] < table[i2]) {
				tMerge[iFusion++] = table[i1++];
			} else {
				tMerge[iFusion++] = table[i2++];
			}
		}
		// First slice done
		if (i1 > middle) {
			for (int i = i2; i <= end;) {
				tMerge[iFusion++] = table[i++];
			}
		}
		// Second slice done
		else {
			for (int i = i1; i <= middle;) {
				tMerge[iFusion++] = table[i++];
			}
		}
		// Copy tMerge into the table
		for (int i = 0, j = start; i <= end - start;) {
			table[j++] = tMerge[i++];
		}
	}

}
