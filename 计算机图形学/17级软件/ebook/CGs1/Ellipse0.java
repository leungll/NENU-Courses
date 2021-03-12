import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.Graphics;

public class Ellipse0 extends JFrame {
  public Ellipse0() {
    setTitle("Ellipse0");
    add(new EllipsePanel());
  }

  /** Main method */
  public static void main(String[] args) {
     Ellipse0 frame = new Ellipse0();
    frame.setLocationRelativeTo(null); // Center the frame
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frame.setSize(600, 600);
    frame.setVisible(true);
  }
}

// The class for drawing arcs on a panel
class EllipsePanel extends JPanel {

  protected void paintComponent(Graphics g) {
    super.paintComponent(g);
    int x,Tx=300,Ty=300;
    double d,a=200,b=100,y;
	x=-200;
 	for(;x<=a;x++){		    
            y=(b/a)*(Math.sqrt(a*a-x*x));
             g.drawString(".", (int)(x+Tx),(int)(y+Ty));
             g.drawString(".", (int)(x+Tx),(int)(-y+Ty));
	      }  
      }        
}