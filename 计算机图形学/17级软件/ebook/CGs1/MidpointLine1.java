import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.Graphics;

public class MidpointLine1 extends JFrame {
  public MidpointLine1() {
    setTitle("DrawLine");
    add(new LinePanel());
  }

  /** Main method */
  public static void main(String[] args) {
    MidpointLine1 frame = new MidpointLine1();
    frame.setLocationRelativeTo(null); // Center the frame
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frame.setSize(300, 300);
    frame.setVisible(true);
  }
}

// The class for drawing arcs on a panel
class LinePanel extends JPanel {
  // Draw four blazes of a fan
  public void paintComponent(Graphics g) {
    super.paintComponent(g);
    int x0=0,x1=100,y0=0,y1=50,a,b,delta1,delta2,x,y,d;
	a=y0-y1;
	b=x1-x0;
	d=2*a+b;
	delta1=2 * a;
    delta2 = 2 *(a + b);
    x = x0;
    y = y0;
	g.drawString(".", x, y);
	while(x<x1){
         if(d<0 ){
               x++;
               y++;
               d+=delta2;}
	     else  {
	    	     x++;
                 d+= delta1;}
	             g.drawString(".", x, y);
	             }	   
      }        
}