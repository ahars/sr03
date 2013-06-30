package exercice1;
// enrico.natalizio@hds.utc.fr
// B154

/**
 * Classe de conversion de l'Euro au Dollar
 * @author Jin Sun & Antoine Hars
 * 
 */
public class EuroDollarConverter {

	/**
	 * Constructeur
	 * @param taux
	 */
	public EuroDollarConverter(float taux) {
		this.taux = taux;
	}

	private float taux;
	
	/**
	 * Getter de taux
	 * @return le taux 
	 */
	public float getTaux(){
		return this.taux;
	}
	
	/**
	 * Setter de taux
	 * @param t le taux
	 */
	public void setTaux(float t) {
		this.taux = t;
	}
	
	/**
	 * Conversion d'euros en dollars
	 * @param euros
	 * @return la conversion des euros en dollars
	 */
	public float convertirEnDollars(float euros) {
		return euros * this.taux;
	}
	
	/**
	 * Conversion de dollars en euros
	 * @param dollars
	 * @return la conversion des dollars en euros
	 */
	public float convertirEnEuros(float dollars) {
		return dollars / this.taux;
	}
}
