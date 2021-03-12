import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.Graphics;

public class BresenhamLine1 extends JFrame {
  public BresenhamLine1() {
    setTitle("BresenhamLine1");
    add(new LinePanel());
  }

  /** Main method */
  public static void main(String[] args) {
	BresenhamLine1 frame = new BresenhamLine1();
    frame.setLocationRelativeTo(null); // Center the frame
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frame.setSize(300, 300);
    frame.setVisible(true);
  }
}

// The class for drawing arcs on a panel
class LinePanel extends JPanel {
  // Draw four blazes of a fan
  protected void paintComponent(Graphics g) {
    super.paintComponent(g);
    int x1=0,x2=100,y1=0,y2=30,x,y,dx,dy,p;
	x=x1;
	y=y1;
    dx=x2-x1;
    dy=y2-y1;
	p=2*dy-dx;
	for(;x<=x2;x++){
		   g.drawString(".", x, y);
           if(p>=0){
                   y++;
                   p+=2*(dy-dx); 	}
		    else{
                   p+=2*dy;  	}
        } 
    }        
}