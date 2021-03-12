import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.Graphics;

public class PontLine extends JFrame {
  public PontLine() {
    setTitle("PontLine");
    add(new LinePanel());
  }

  /** Main method */
  public static void main(String[] args) {
	PontLine frame = new PontLine();
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
    int x,y,dx,dy,p,x1=0,y1=0,x2=500,y2=300,s,type=2;
    x = x1;
    y = y1;
    dx= x2-x1;
    dy= y2-y1;
    p = 2 * dy - dx;
    s=0;
    for (;x<=x2;x++){
         s=s+1;
         if (type==0)  //画实线
        	 g.drawString(".", x,y);
         if (type==1)  //画虚线
         if ((s%10) != 0) 
        	 g.drawString(".", x,y);                
         if (type ==2)  //画点划线      
         if ((s%10)!=6 && (s%10)!=7 && (s%10)!=8) 
             g.drawString(".", x,y); 
           if (p>=0){
                    y++;
                    p+=2*(dy-dx);
          }
           else{
                 p+=2*dy;
         }
    }
   }
  }
