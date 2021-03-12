import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.Graphics;

public class BresenhamCircle1 extends JFrame {
  public BresenhamCircle1() {
    setTitle("CircleArcs");
    add(new CirclePanel());
  }

  /** Main method */
  public static void main(String[] args) {
	  BresenhamCircle1 frame = new BresenhamCircle1();
    frame.setLocationRelativeTo(null); // Center the frame
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frame.setSize(300, 300);
    frame.setVisible(true);
  }
}


class CirclePanel extends JPanel {
  protected void paintComponent(Graphics g) {
    super.paintComponent(g);
    int x,y,p,R=200;
	x=0;
        y=R;
	p=3-2*R;
	for(;x<=y;x++){   
		g.drawString(".", x,y);
                if(p>=0)
		{     p+=4*(x-y)+10;
		       y--;
		 }
                else{
		     p +=4*x+6;		
   	          }
            }  
      }        
}