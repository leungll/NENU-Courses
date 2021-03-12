import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.Graphics;

public class MidpointCircle2 extends JFrame {
  public MidpointCircle2() {
    setTitle("CircleArcs");
    add(new CirclePanel());
  }

  /** Main method */
  public static void main(String[] args) {
	  MidpointCircle2 frame = new MidpointCircle2();
    frame.setLocationRelativeTo(null); // Center the frame
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frame.setSize(300, 300);
    frame.setVisible(true);
  }
}

// The class for drawing arcs on a panel
class CirclePanel extends JPanel {
  // Draw four blazes of a fan
  protected void paintComponent(Graphics g) {
    super.paintComponent(g);
    int x,y,delta1,delta2,d,R=100;
	x=0;y=R;d=1-R;
	delta1=3;
	delta2=5-R-R;	
	g.drawString(".", x,y);
	while(x<y)
	{    if(d<0){
		       d+=delta1;
	           delta1+=2;
	           delta2+=2;
	           x++;  }
	     else
	       {  d+= delta2;
	          delta1+=2;
	          delta2+=4;
	          x++;
	          y--; }	   
	         g.drawString(".", x,y);
	    }
      }        
}