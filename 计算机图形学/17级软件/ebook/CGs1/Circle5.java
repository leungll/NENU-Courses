import javax.swing.*;
import java.awt.Graphics;

public class Circle5 extends JFrame {
  public Circle5() {
    setTitle("DrawCircle5");
    add(new DrawCircle());
  }

  /** Main method */
  public static void main(String[] args) {
    Circle5 frame = new Circle5();
    frame.setLocationRelativeTo(null); // Center the frame
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frame.setSize(600, 600);
    frame.setVisible(true);
  }
}

// The class for drawing arcs on a panel
class DrawCircle extends JPanel {

  protected void paintComponent(Graphics g) {
    super.paintComponent(g);
    int x,y,Tx=300,Ty=300,R=200;
    double d;
	x=0; y=R;
 
	for(x=-R;x<=R;x++){
		    d=R*R-x*x;
             y=(int)(Math.sqrt(d));{
             //g.drawString(".", x,y);
             g.drawString(".", (int)(x+Tx),(int)(y+Ty));
             g.drawString(".", (int)(x+Tx),(int)(-y+Ty));}
	      }  
      }        
}