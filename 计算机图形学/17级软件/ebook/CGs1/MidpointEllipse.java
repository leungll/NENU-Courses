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

class LinePanel extends JPanel {
  public void paintComponent(Graphics g) {
    super.paintComponent(g);
        int x,y;
	double d1,d2,a=100.,b=40.,Tx=300,Ty=300;
	x=0;y=40;
        d1=b*b+a*a*(-b+0.25);
	g.drawString(".", x, y);
	while(b*b*(x+1)<a*a*(y-0.5)){
    	if(d1<0){
                  d1+=b*b*(2*x+3);
                  x++;
                 }
	else{
                    d1+=(b*b*(2*x+3)+a*a*(-2*y+2));
                    x++;
                    y--;  }
	            g.drawString(".", x, y);
	}
        d2=b*b*(x+0.5)*(x+0.5)+a*a*(y-1)*(y-1)-a*a*b*b;
	while(y>0){
    	if(d2<0){
                    d2+=b*b*(2*x+2)+a*a*(-2*y+3);
                    x++;
                    y--;
                }
	else{
                   d2+=a*a*(-2*y+3);
                   y--;
             }
	 g.drawString(".", x, y);
	}
   }
} 