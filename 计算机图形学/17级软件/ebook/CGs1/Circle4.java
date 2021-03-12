import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.Graphics;
public class Circle4 extends JFrame {
  public Circle4() {
    setTitle("DrawCircle");
    add(new DrawCircle());
  }

  /** Main method */
  public static void main(String[] args) {
    Circle4 frame = new Circle4();
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
    double x,y,R=100,Tx=300,Ty=300,Sx=0.5,Sy=1.5;
    double d=.0;
	x=0.;
	y=0.;
	d=.0;
	while(d<=6.28){
		x=R*Math.cos(d);
		y=R*Math.sin(d);
            g.drawString(".", (int)(x+Tx),(int)(y+Ty));	        
	        d=d+.01;
	      }  
      }        
}