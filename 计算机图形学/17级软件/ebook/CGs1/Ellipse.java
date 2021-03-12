import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.Graphics;

public class Ellipse extends JFrame {
  public Ellipse() {
    setTitle("DrawArcs");
    add(new ArcsPanel());
  }

  /** Main method */
  public static void main(String[] args) {
    Ellipse frame = new Ellipse();
    frame.setLocationRelativeTo(null); // Center the frame
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frame.setSize(600, 600);
    frame.setVisible(true);
  }
}

// The class for drawing arcs on a panel
class ArcsPanel extends JPanel {

  protected void paintComponent(Graphics g) {
    super.paintComponent(g);
    int Tx=300,Ty=300;
    double x,y,a=200.,b=100.;
    double d=.0;
	x=0.;
	y=0.;
	d=.0;
	while(d<=3.14){
		x=a*Math.cos(d);
		y=b*Math.sin(d);
		g.drawString(".", (int)(x+Tx),(int)(y+Ty));
        g.drawString(".", (int)(x+Tx),(int)(-y+Ty));
	        d=d+.01;
	      }  
      }        
}