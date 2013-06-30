package exercice1;

import java.util.Scanner;
//import java.io.*;

/**
 * Exercice 1
 * @author Jin Sun & Antoine Hars
 *
 */
public class exercice1 {

		public static void main (String[] args) {
			
			Scanner sc = new Scanner(System.in);
			float in = 0;
			EuroDollarConverter edc;
			String scan;
			
			System.out.println("Exercice 1\n");
			
			while (in < 1) {
				
				/* Récupération du taux de change. */
				System.out.println("taux de change (dollars par euro) : ");
				scan = sc.next();
				try {
					in = Float.valueOf(scan);
				} catch (Exception e) {
					System.out.println("Error taux");
					in = 0;
				}
			}
			
			edc = new EuroDollarConverter(in);
			
			do {

				System.out.println("\nvaleur : ");
				scan = sc.next();
				
				/* Conversion du String en Float. */
				try {
					in = Float.valueOf(scan);
				} catch (Exception e) {
					System.out.println("Error valeur");
				}
				if (in > -1) {
				
					/* Récupération du type de monnaie. */
					scan = sc.next();
					if (scan.contains("€"))
						System.out.print("équivalent en Dollars : " + edc.convertirEnDollars(in));
					else if (scan.contains("$"))
						try {
							System.out.print("équivalent en Euros : " + edc.convertirEnEuros(in));
						} catch (ArithmeticException e) {
							System.out.println("Division par zéro");
						}
					else
						System.out.print("Error type monnaie");
					/* On vide la ligne. */
					sc.nextLine();
				}
			} while (in > -1);
			System.out.println("\nFin");
		}
}
