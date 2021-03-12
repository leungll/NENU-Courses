import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.Graphics;

public class PontLinek extends JFrame {
  public PontLinek() {
    setTitle("PontLine");
    add(new LinePanel());
  }

  /** Main method */
  public static void main(String[] args) {
    PontLinek frame = new PontLinek();
    frame.setLocationRelativeTo(null); // Center the frame
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frame.setSize(600, 600);
    frame.setVisible(true);
  }
}

// The class for drawing arcs on a panel
class LinePanel extends JPanel {
    public void paintComponent(Graphics g) {
    super.paintComponent(g);
    int x,y,dx,dy,p,x1=20,y1=20,x2=500,y2=300,s,type=2;
   
    s=1;
    for (;s<=50;s++){
    	x = x1;
  	    y = y1;
  	    dx= x2-x1;
  	    dy= y2-y1;
  	    p = 2 * dy - dx;
     for (;x<=x2;x++){
    	  g.drawString(".", x,y); 
           if (p>=0){
                    y++;
                    p+=2*(dy-dx);
          }
           else{
                 p+=2*dy;
         }
    }
     x1=x1;y1=y1+1;
     x2=x2;y2=y2+1;
  }
 }
}