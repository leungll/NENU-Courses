import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.Graphics;

public class Ellipse4 extends JFrame {
  public Ellipse4() {
    setTitle("DrawArcs");
    add(new ArcsPanel());
  }

  /** Main method */
  public static void main(String[] args) {
    Ellipse4 frame = new Ellipse4();
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
    double x,y,a=100.,b=40.,Tx=300,Ty=300,Sx=2,Sy=2;
    double d=.0,st=-3.14/6;
	x=0.;
	y=0.;
	d=.0;
	while(d<=1.57*4){
		x=a*Math.cos(d);
		y=b*Math.sin(d);
		g.drawString(".", (int)x,(int)y);
        g.drawString(".", (int)(x+Tx),(int)(y+Ty));      
        g.drawString(".", (int)(Sx*x+Tx),(int)(Sy*y+Ty));
        g.drawString(".", (int)((x*Math.cos(st)-y*Math.sin(st))+Tx),(int)((x*Math.sin(st)+y*Math.cos(st))+Ty));
	    d=d+.01;
	      }  
      }        
}