package exercice2;

import java.applet.*;
import java.awt.*;
import java.awt.event.*;
import java.net.*;
import exercice1.EuroDollarConverter;

public class Applet1 extends Applet implements MouseListener {

	private static final long serialVersionUID = 1L;
	
	java.awt.Button dollar, euro;
	java.awt.TextField taux, valeur;
	java.awt.Label et1, et2, et3, et4, errMsg;
	
	public void init() {
	
		super.init();
		resize(500, 300);
		setBackground(new Color(2525152));
				
		et1 = new java.awt.Label("Taux de change (dollars par euro");
		et1.setBounds(10, 10, 100, 24);
		add(et1);
		
		taux = new java.awt.TextField();
		taux.setBounds(10, 30, 100, 24);
		taux.setFont(new Font("Dialog", Font.PLAIN, 12));
		add(taux);
		
		et2 = new java.awt.Label("Valeur :");
		et2.setBounds(10, 60, 100, 24);
		add(et2);
		
		valeur = new java.awt.TextField();
		valeur.setBounds(10, 90, 100, 24);
		valeur.setFont(new Font("Dialog", Font.PLAIN, 12));
		add(valeur);
		
		et3 = new java.awt.Label("Équivalent en ");
		et3.setBounds(10, 120, 100, 24);
		add(et3);
		
		errMsg = new java.awt.Label("");
		errMsg.setBounds(144,72,264,24);
		errMsg.setFont(new Font("Dialog", Font.PLAIN, 12));
		errMsg.setForeground(new Color(252));
		add(errMsg);

	}

	public void paint(Graphics g) {}
	public void destroy() {}
	public void stop() {}
	public void start() {}
	
	public void mouseClicked (MouseEvent e) {
		
		try {
			EuroDollarConverter edc = new EuroDollarConverter(Float.valueOf((taux.getText())));
			if () {
				edc.convertirEnDollars();
			} else {
				edc.convertirEnEuros();
			}
		} catch (Exception mee) {
			errMsg.setText("Error taux");
		}
	}
	public void mouseEntered (MouseEvent e) {}
	public void mousePressed (MouseEvent e) {}
	public void mouseReleased (MouseEvent e) {} 
	public void mouseExited (MouseEvent e) {}  

}
