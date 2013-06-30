package exercice2;

import java.applet.*;
import java.awt.*;
import java.awt.event.*;

public class Applet2 extends Applet implements MouseListener {

	private static final long serialVersionUID = 1L;
	
	int nbClick = 0;
	
	public void init() {
		super.init();
		addMouseListener(this);
	}

	public void paint(Graphics g) {
		super.paint(g);
		g.drawString("Nombre de clics : " + nbClick, 10, 10);
	}
	
	public void destroy() {}
	public void stop() {}
	public void start() {}
	
	
	public void mouseClicked(MouseEvent e) {
		nbClick++;
		repaint();
	}
	
	public void mouseEntered(MouseEvent e) {}
	public void mousePressed(MouseEvent e) {}
	public void mouseReleased(MouseEvent e) {} 
	public void mouseExited(MouseEvent e) {} 
}
