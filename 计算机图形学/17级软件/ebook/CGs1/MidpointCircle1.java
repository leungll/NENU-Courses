import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.Graphics;

public class MidpointCircle1 extends JFrame {
  public MidpointCircle1() {
    setTitle("DrawArcs");
    add(new ArcsPanel());
  }

  /** Main method */
  public static void main(String[] args) {
	  MidpointCircle1 frame = new MidpointCircle1();
    frame.setLocationRelativeTo(null); // Center the frame
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frame.setSize(300, 300);
    frame.setVisible(true);
  }
}

// The class for drawing arcs on a panel
class ArcsPanel extends JPanel {
  // Draw four blazes of a fan
  protected void paintComponent(Graphics g) {
    super.paintComponent(g);
    int x,y,R=100;
	double d;
	x=0; y=R; d=1.25-R;
	System.out.printf("("+x+","+y+","+d+")");
	System.out.printf(" ");
	g.drawString(".", x,y);
	while(x<y){
               if(d<0){
                 d+=2*x+3;
                 x++;   }
               else{
                d+=2*(x-y)+5;
                x++;
                y--;  }
		    System.out.printf("("+x+","+y+","+d+")");
	        System.out.printf(" ");
	        g.drawString(".", x,y);
	      }  
      }        
}