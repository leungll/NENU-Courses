import javax.swing.JPanel;
import java.awt.Graphics;

public class Circle1 extends JFrame {
  public Circle1() {
    setTitle("DrawCircle");
    add(new DrawCircle());
  }

  /** Main method */
  public static void main(String[] args) {
	 Circle1 frame = new Circle1();
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
    int x,y,Tx=300,Ty=300,R=100;
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