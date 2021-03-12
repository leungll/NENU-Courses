import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.Graphics;

public class DDALine1 extends JFrame {
  public DDALine1() {
    setTitle("DDALine1");
    add(new LinePanel());
  }

  /** Main method */
  public static void main(String[] args) {
    DDALine1 frame = new DDALine1();
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
    int x1=0,y1=0,x2=500,y2=200,x;
	float dx,dy,m,y;
	dx=x2-x1;
	dy=y2-y1;				   
	m=dy/dx; 
	y=y1; 					   
        for (x=x1;x<=x2;x++){ 
          g.drawString(".", x, (int)(y+0.5));
        y=y+m;
    }   
  }
}