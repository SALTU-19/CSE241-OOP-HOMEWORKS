import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

public class HexEngine implements ActionListener{
	private JButton[][] buttonGrid;
	private JPanel panel;
	private HexGame game;
	private JButton reset = new JButton("RESET");
	private JButton undo = new JButton("UNDO");
	private JButton save = new JButton("SAVE");
	private JButton load = new JButton("LOAD");
	private int GameMod;
	private int Size;
	private JFrame frame;
	private ActionListener buttonListener;
	private int r = 0;
	private int c=0;
	HexEngine(JFrame Frame,int size,int gamemod){
		panel = new JPanel();
	    panel.setLayout(null);
		frame = Frame;
		game = new HexGame(size,gamemod);
        GameMod = gamemod;
        Size = size;
        buttonListener = new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent evt) {
               JButton selectedBtn = (JButton) evt.getSource();
               for (int row = 0; row < buttonGrid.length; row++) {
                  for (int col = 0; col < buttonGrid[row].length; col++) {
                     if (buttonGrid[row][col] == selectedBtn) {
                        System.out.printf("Selected row and column: %d %d%n", row, col);
                        if(GameMod == 1) {
	                        if(game.getPlayer() == 1) {
	                        	if(game.getCell(row, col).getinformations().c == '.') {
	                        		buttonGrid[row][col].setBackground(Color.yellow);
	                        		game.addMove(game.play(row, col));
	                        	}
	                        }
	                        else {
	                        	if(game.getCell(row, col).getinformations().c == '.') {
	                        		buttonGrid[row][col].setBackground(Color.blue);
	                        		game.addMove(game.play(row, col));
	                        	}
	                        }
                        }
                        else {
                        	if(game.getCell(row, col).getinformations().c == '.') {
                        		buttonGrid[row][col].setBackground(Color.yellow);
                        		game.addMove(game.play(row, col));
                        		Cell temp = game.play();
                        		game.addMove(temp);
                        		game.setCell(temp.getrow(),temp.getcolumn(),informations.user2);
                        		buttonGrid[temp.getrow()][temp.getcolumn()].setBackground(Color.blue);
                        	}
                        }
                     }
                  }
               }
               	if(game.user_1_win() == true) {
               		JOptionPane.showMessageDialog(frame,"User1 won!","Game end!", GameMod);
        			for (int row = 0; row < buttonGrid.length; row++) {
                        for (int col = 0; col < buttonGrid[row].length; col++) {
                        	buttonGrid[row][col].setEnabled(false);
                        }
        			}
               	}
               	if(game.user_2_win() == true) {
               		if(GameMod == 1)
               			JOptionPane.showMessageDialog(frame,"User2 won!","Game end!", GameMod);
               		else
               			JOptionPane.showMessageDialog(frame,"Computer won!","Game end!", GameMod);
        			for (int row = 0; row < buttonGrid.length; row++) {
                        for (int col = 0; col < buttonGrid[row].length; col++) {
                        	buttonGrid[row][col].setEnabled(false);
                        }
        			}
               	}
            }
         };         
         CreateFrame();
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		
		if(e.getActionCommand() == "RESET") {
			for (int row = 0; row < buttonGrid.length; row++) {
                for (int col = 0; col < buttonGrid[row].length; col++) {
                	buttonGrid[row][col].setBackground(Color.gray);
                	game.setCell(row, col,informations.empty);
                	game.resetCompMove();
                	buttonGrid[row][col].setEnabled(true);
                }
			}
		}
		if(e.getActionCommand() == "UNDO") {
			if(GameMod == 1) {
				game.undo_pvp();
				UpdateTable();
			}
			else {
				game.undo_pvc();
				UpdateTable();
			}
		}
		if(e.getActionCommand() == "SAVE") {
			String filename =  JOptionPane.showInputDialog("Enter a filename");
			try {
				game.save_file(filename);
			}catch (IOException e1) {
				e1.printStackTrace();
			}
		}
		if(e.getActionCommand() == "LOAD") {
			String filename =  JOptionPane.showInputDialog("Enter a filename");
			try {
				game.load_file(filename);
				GameMod = game.getGameMod();
				CreateFrame();
				UpdateTable();
			}catch (IOException e1) {
				e1.printStackTrace();
			}
		}
	}
	public void CreateFrame() {
		r=0;
		c=0;
		buttonGrid = new JButton[game.getSize()][game.getSize()];
        for (int row = 0; row < buttonGrid.length; row++) {
        	c = 15*row;
            for (int col = 0; col < buttonGrid[row].length; col++) {
               buttonGrid[row][col] = new JButton();
               buttonGrid[row][col].setLayout(null);
               buttonGrid[row][col].setBounds(c, r, 30, 30);
               buttonGrid[row][col].setBackground(Color.gray);
               buttonGrid[row][col].addActionListener(buttonListener);
               panel.add(buttonGrid[row][col]);
               c+=30;
               
            }
            r+=30;
            
         }
       
		reset.setLayout(null);
		reset.setBounds(c+30, r/2, 90, 60);
		undo.setLayout(null);
		undo.setBounds(c+120, r/2, 90, 60);
		save.setLayout(null);
		save.setBounds(c+210, r/2, 90, 60);
		load.setLayout(null);
		load.setBounds(c+300, r/2, 90, 60);
        reset.addActionListener(this);
        undo.addActionListener(this);
        save.addActionListener(this);
        load.addActionListener(this);
        panel.add(reset);
        panel.add(undo);
        panel.add(save);
        panel.add(load);
        frame.add(panel);
        frame.setSize(200, 300);  
        frame.setLocationRelativeTo(null);  
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);  
        frame.setVisible(true); 
	}
	public void UpdateTable() {
		for (int row = 0; row < buttonGrid.length; row++) {
            for (int col = 0; col < buttonGrid[row].length; col++) {
            	if(game.getCell(row, col).getinformations().c == '.') {
            		buttonGrid[row][col].setBackground(Color.gray);
            	}
            	else if(game.getCell(row, col).getinformations().c == 'x') {
            		buttonGrid[row][col].setBackground(Color.yellow);
            	}
            	else if(game.getCell(row, col).getinformations().c == 'o') {
            		buttonGrid[row][col].setBackground(Color.blue);
            	}
            }
		}
	}
}
