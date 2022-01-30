
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;


import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JTextField;
import javax.swing.ButtonGroup;
import javax.swing.JButton;

@SuppressWarnings("serial")
public class HexSettings extends JPanel implements ActionListener{
	private JFrame frame= new JFrame();
	private JPanel panel;
	private JTextField t1;
	private JRadioButton r1;
	private JRadioButton r2;
	private ButtonGroup group;
	public HexSettings(){
		panel = new JPanel();
		JLabel label = new JLabel("Please Enter the game size:");
		JLabel label2 = new JLabel("Please Enter the game option:");
		panel.setLayout(new FlowLayout());
	    JButton b1=new JButton("Play Game!");
	    r1=new JRadioButton("1.Player vs Player");    
	    r2=new JRadioButton("2.Player vs Computer");
	    group = new ButtonGroup();
	    group.add(r1);
	    group.add(r2);
	    t1=new JTextField();
	    t1.setColumns(15);
	    t1.setBounds(500,500, 80,40);
	    b1.addActionListener(this);   
	    panel.add(label);panel.add(t1); panel.add(label2);panel.add(r1);panel.add(r2); panel.add(b1);
        frame.add(panel);
        frame.setSize(200, 300);  
        frame.setLocationRelativeTo(null);  
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);  
        frame.setVisible(true);
	    
	}
	public void actionPerformed(ActionEvent e) {
		panel.setVisible(false);
		HexEngine t;
		String a = t1.getText();
		if(r1.isSelected())
			t = new HexEngine(frame,Integer.parseInt(a),1);
		if(r2.isSelected())
			t = new HexEngine(frame,Integer.parseInt(a),2);
	}




}
