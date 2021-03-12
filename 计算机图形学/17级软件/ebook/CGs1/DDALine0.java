import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.Graphics;

public class DDALine0 extends JFrame {
  public DDALine0() {
    setTitle("DDALine0");
    add(new LinePanel());
  }

  /** Main method */
  public static void main(String[] args) {
    DDALine0 frame = new DDALine0();
    frame.setLocationRelativeTo(null); // Center the frame
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frame.setSize(600, 600);
    frame.setVisible(true);
  }
}


class LinePanel extends JPanel {
    public void paintComponent(Graphics g) {
    super.paintComponent(g);
    int x1=0,y1=0,x2=500,y2=200,x;
	float dx,dy,m,b;
	dx=x2-x1;
	dy=y2-y1;				   
	m=dy/dx; 
        b=(x2*y1-x1*y2)/(x2-x1);
        for (x=x1;x<=x2;x++){ 
          g.drawString(".", x, (int)(m*x+b+0.5));      
    }   
  }
}