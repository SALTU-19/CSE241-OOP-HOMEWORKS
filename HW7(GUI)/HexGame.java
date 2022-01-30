import java.util.Random;
import java.io.*;
public class HexGame implements Cloneable{
	private int size ;
	private int gameMod;
	private int move_counter = 0;
	private int comp_x;
	private int comp_y;
	private int player;
	private Random rand = new Random(); 
	private Cell[][] hexCells;
	private Cell Movements[];
	public HexGame(int Size,int gamemod) {
		this.size = Size;
		this.gameMod = gamemod;
		this.player = 1;
		open_board();
	}
	public int getSize() {
		return size;
	}
	public int getPlayer() {
		return player;
	}
	public void resetCompMove() {
		comp_x = 0;
		comp_y = 0;
	}
	public int getMoveCounter() {
		return move_counter;
	}
	public void setSize(int size) {
		this.size = size;
	}
	public void open_board() {
		hexCells = new Cell[size][size];
		fill_board();
	}
	public void fill_board() {
	    int i,j;
	    for (i = 0; i < size; i++) { 
	        for (j = 0; j < size; j++) { 
	           hexCells[i][j] = new Cell(i,j,informations.empty);
	        } 
	    }
	}
	public Cell getCell(int i,int j) {
		return hexCells[i][j];
	}
	public void setCell(int i,int j,informations newinformation) {
		hexCells[i][j].setinformation(newinformation);
	}
	public void print() {
	    int i,j;
		System.out.println(" ");
		for(i=0;i<getSize();i++){
			System.out.printf("%c ",(char)(97+i));
		}
		System.out.printf("\n");
		for(i=0;i<getSize();i++){
			System.out.printf("%d ",i+1);
			for(j=0;j<i;j++){
				System.out.printf(" ");
			}
			for(j=0;j<getSize();j++){
				System.out.printf("%c ",hexCells[i][j].getinformations().c);
			}
			System.out.printf("\n"); 
		}
		System.out.printf("\n");
	}
	public int getGameMod() {
		return gameMod;
	}
	public void setGameMod(int gameMod) {
		this.gameMod = gameMod;
	}
	private boolean within_boundaries (int x,int y)// it controls game table bouundaries
	{

	    return (x > size-1 || y > size - 1 || x < 0 || y < 0); 
	}
	public boolean user_1_win() //it controls user1 win or not
	{
		for(int i =0;i<size;i++)
	    {
	        if(hexCells[i][0].getinformations() == informations.user1)
	        {
	            if(is_finish_x(i,0) == true){
	                hexCells[i][0].setinformation(informations.winx);
	                return true;   
	            }
	        }
	    }
		return false;
	}
	public boolean user_2_win()//it controls user2 win or not
	{
		for(int i =0;i<size;i++)
	    {
	        if(hexCells[0][i].getinformations() == informations.user2)
	        {
	            if(is_finish_y(0,i) == true){
	                hexCells[0][i].setinformation(informations.wino);
	                return true;  
	            }
	        }
	    }
		return false;
	}
	private boolean is_free(int x,int y) // it controls cell is empty or not
	{
	    return (hexCells[x][y].getinformations() == informations.empty);	
	}
	public void reset()
	{
		fill_board();
	}
	public void addMove(Cell c) //the function add movement to movement array
	{
		if(move_counter == 0){
			Movements = new Cell[1];
			Movements[0] = c;
		}
		else{
			Cell temp[] = new Cell[move_counter+1];
			int i;
			for(i=0;i<move_counter;i++){
				temp[i] = Movements[i];
			}
			temp[i] = c;
			Movements = temp;
		}
		move_counter++;

	}
	public Cell play(int x,int y) //the function can set user move
	{
		
	        if(player == 1)
	        {
	            hexCells[x][y].setinformation(informations.user1);
				Cell temp = new Cell(x,y,informations.user1);
				if(gameMod == 1)
					player = 2;
				return temp;

	        }
	        else
			{
	            hexCells[x][y].setinformation(informations.user2);
				Cell temp = new Cell(x,y,informations.user2);
				player = 1;
				return temp;
			}
	        
	}
	public Cell play() //the function can set computer move
	{
	    int a,b;
		if(comp_x == 0 && comp_y == 0){
			if(size % 2 == 0){
				if(is_free(size-1,(size/2)-1)){
					hexCells[size-1][(size/2)-1].setinformation(informations.user2);
					comp_x = size-1;
					comp_y = (size/2)-1;
					Cell temp = new Cell(size-1,(size/2)-1,informations.user2);
					return temp; 
				}
				else{
					hexCells[size-1][(size/2)].setinformation(informations.user2);
					comp_x = size-1;
					comp_y = (size/2);
					Cell temp = new Cell(size-1,(size/2),informations.user2);
					return temp;
				} 
			}
			else{
				if(is_free(size-1,((size+1)/2)-1)){
					hexCells[size-1][((size+1)/2)-1].setinformation(informations.user2);
					comp_x = size-1;
					comp_y = ((size+1)/2)-1;
					Cell temp = new Cell(size-1,((size+1)/2)-1,informations.user2);
					return temp; 
				}
				else{
					hexCells[size-1][((size+1)/2)].setinformation(informations.user2);
					comp_x = size-1;
					comp_y = ((size+1)/2);
					Cell temp = new Cell(size-1,((size+1)/2),informations.user2);
					return temp;
				}
			}
		
		}
		else{
			if(comp_x == 0){
				while(true){
					a = rand.nextInt(size-1)+4; 
			        b = rand.nextInt(size-1);
					if(!within_boundaries(a,b) && is_free(a,b)){
						hexCells[a][b].setinformation(informations.user2);
						comp_x = a;
						comp_y = b;
						Cell temp = new Cell(a,b,informations.user2);
						return temp;
					}
				}
			}
			if(!within_boundaries(comp_x-1,comp_y) && is_free(comp_x-1,comp_y)){
				hexCells[comp_x-1][comp_y].setinformation(informations.user2);
				Cell temp = new Cell((comp_x--)-1,comp_y,informations.user2);
				return temp;
			}
			else if(!within_boundaries(comp_x-1,comp_y+1) && is_free(comp_x-1,comp_y+1)){
				hexCells[comp_x-1][comp_y+1].setinformation(informations.user2);
				Cell temp = new Cell((comp_x--)-1,(comp_y++)+1,informations.user2);
				return temp;
			}
			else if(!within_boundaries(comp_x,comp_y+1) && is_free(comp_x,comp_y+1)){
				hexCells[comp_x][comp_y+1].setinformation(informations.user2);
				Cell temp = new Cell(comp_x,(comp_y++)+1,informations.user2);
				return temp;
			}
			else if(!within_boundaries(comp_x,comp_y-1) && is_free(comp_x,comp_y-1)){
				hexCells[comp_x][comp_y-1].setinformation(informations.user2);
				Cell temp = new Cell(comp_x,(comp_y--)-1,informations.user2);
				return temp;
			}
			else if(!within_boundaries(comp_x+1,comp_y-1) && is_free(comp_x+1,comp_y-1)){
				hexCells[comp_x+1][comp_y-1].setinformation(informations.user2);
				Cell temp = new Cell((comp_x++)+1,(comp_y--)-1,informations.user2);
				return temp;
			}
			else if(!within_boundaries(comp_x+1,comp_y) && is_free(comp_x+1,comp_y)){
				hexCells[comp_x+1][comp_y].setinformation(informations.user2);
				Cell temp = new Cell((comp_x++)+1,comp_y,informations.user2);
				return temp;
			}
			else{
				while(true){
					a = rand.nextInt(size-1)+4; 
			        b = rand.nextInt(size-1);
					if(!within_boundaries(a,b) && is_free(a,b)){
						hexCells[a][b].setinformation(informations.user2);
						comp_x = a;
						comp_y = b;
						Cell temp = new Cell(a,b,informations.user2);
						return temp;
					}
				}
			}
		}
	}
	private boolean is_finish_x(int x,int y) // Examines x from right to left.
	{
	   	if(y == size-1){
			return true;
		}
			if(!within_boundaries(x,y+1) && (hexCells[x][y+1].getinformations() == informations.user1)){	
				hexCells[x][y+1].setinformation(informations.winx);
				if(is_finish_x(x,y+1)){
					return true;
				}
				else{
					hexCells[x][y+1].setinformation(informations.user1) ;	
				}
			}
			else if(!within_boundaries(x-1,y+1) && (hexCells[x-1][y+1].getinformations() == informations.user1)){
				hexCells[x-1][y+1].setinformation(informations.winx);
				if(is_finish_x(x-1,y+1)){
					return true;
				}
				else{
					hexCells[x-1][y+1].setinformation(informations.user1);
				}
			}
			else if(!within_boundaries(x+1,y) && (hexCells[x+1][y].getinformations() == informations.user1)){
				hexCells[x+1][y].setinformation(informations.winx);
				if(is_finish_x(x+1,y)){
					return true;
				}
				else{
					hexCells[x+1][y].setinformation(informations.user1);	
				}
			}
			else if(!within_boundaries(x-1,y) && (hexCells[x-1][y].getinformations() == informations.user1)){
				hexCells[x-1][y].setinformation(informations.winx) ;
				if(is_finish_x(x-1,y)){
					return true;
				}
				else{
					hexCells[x-1][y].setinformation(informations.user1) ;	
				}
			}
			else if(!within_boundaries(x,y-1) && (hexCells[x][y-1].getinformations() == informations.user1)){
				hexCells[x][y-1].setinformation(informations.winx) ;
				if(is_finish_x(x,y-1)){
					return true;
				}
				else{
					hexCells[x][y-1].setinformation(informations.user1);	
				}			
			}
			else if(!within_boundaries(x+1,y-1) && (hexCells[x+1][y-1].getinformations() == informations.user1)){
				hexCells[x+1][y-1].setinformation(informations.winx);
				if(is_finish_x(x+1,y-1)){
					return true;
				}
				else{
				    hexCells[x+1][y-1].setinformation(informations.user1) ;	
				}
			}
			return false; 
	}
	private boolean is_finish_y(int x,int y) //Examines the o from bottom to top.
	{
	   	if(x == size-1){
			return true;
		}
			if(!within_boundaries(x+1,y) && (hexCells[x+1][y].getinformations() == informations.user2)){	
				hexCells[x+1][y].setinformation(informations.wino);
				if(is_finish_y(x+1,y)){
					return true;
				}
				else{
					hexCells[x+1][y].setinformation(informations.user2);	
				}
			}
			else if(!within_boundaries(x+1,y-1) && (hexCells[x+1][y-1].getinformations() == informations.user2)){	
				hexCells[x+1][y-1].setinformation(informations.wino);
				if(is_finish_y(x+1,y-1)){
					return true;
				}
				else{
					hexCells[x+1][y-1].setinformation(informations.user2);	
				}
			}
			else if(!within_boundaries(x,y+1) && (hexCells[x][y+1].getinformations() == informations.user2)){	
				hexCells[x][y+1].setinformation(informations.wino);
				if(is_finish_y(x,y+1)){
					return true;
				}
				else{
					hexCells[x][y+1].setinformation(informations.user2) ;	
				}
			}
			else if(!within_boundaries(x,y-1) && (hexCells[x][y-1].getinformations() == informations.user2)){	
				hexCells[x][y-1].setinformation(informations.wino);
				if(is_finish_y(x,y-1)){
					return true;
				}
				else{
					hexCells[x][y-1].setinformation(informations.user2) ;	
				}
			}
			else if(!within_boundaries(x-1,y+1) && (hexCells[x-1][y+1].getinformations() == informations.user2)){	
				hexCells[x-1][y+1].setinformation(informations.wino);
				if(is_finish_y(x-1,y+1)){
					return true;
				}
				else{
					hexCells[x-1][y+1].setinformation(informations.user2) ;	
				}
			}
			else if(!within_boundaries(x-1,y) && (hexCells[x-1][y].getinformations() == informations.user2)){	
				hexCells[x-1][y].setinformation(informations.wino);
				if(is_finish_y(x-1,y)){
					return true;
				}
				else{
					hexCells[x-1][y].setinformation(informations.user2) ;	
				}
			}
			return false; 
	}
	public void undo_pvc()
	{
		if(move_counter != 0){
			Cell temp[] = new Cell[move_counter-2];
			int i;
			if(move_counter > 2) {
				comp_x = Movements[move_counter-3].getrow();
				comp_y = Movements[move_counter-3].getcolumn();
			}
			hexCells[Movements[move_counter-1].getrow()][Movements[move_counter-1].getcolumn()].setinformation(informations.empty);
			hexCells[Movements[move_counter-2].getrow()][Movements[move_counter-2].getcolumn()].setinformation(informations.empty);
			for(i=0;i<move_counter-2;i++){
				temp[i] = Movements[i];
			}
			Movements = temp;
			move_counter-=2;
			if(move_counter == 0){
				comp_x = 0;
				comp_y = 0;
			}
	    }
	}
	@Override
    protected Object clone() throws CloneNotSupportedException {
        HexGame cloned = (HexGame) super.clone(); 
        cloned.setHexCells((Cell[][]) cloned.getHexCells());
        cloned.setMovements((Cell[]) cloned.getMovements());
        return cloned;
    }
	public void setMovements(Cell[] Move) {
		this.Movements = Move;
	}
	public Cell[] getMovements() {
		return Movements;
	}
	public Cell[][] getHexCells() {
		
		return hexCells;
	}
	public void setHexCells(Cell[][] hexCells) {
		this.hexCells = hexCells;
	}
	public void undo_pvp()
	{
		if(move_counter != 0){

			Cell temp[] = new Cell[move_counter-1];
			int i;
			hexCells[Movements[move_counter-1].getrow()][Movements[move_counter-1].getcolumn()].setinformation(informations.empty);
			for(i=0;i<move_counter-1;i++){
				temp[i] = Movements[i];
			}
			Movements = temp;
			move_counter--;
	    }
		else{
			comp_x = 0;
			comp_y = 0;
		}	
	}
	public void load_file(String filename) throws IOException
	{
		BufferedReader br = new BufferedReader(new FileReader(filename));
		int i=0,j=0,counter = 0,temp,row,column;	
		char x,information;
		temp = Integer.parseInt(br.readLine());
		size = temp;
		open_board();
		while(true){
			x = (char) br.read();
			if(counter == (size)*(size) ){
				gameMod = (int)(x-48);
				if(gameMod == 1){
					x = (char) br.read();
					if((int)(x-48) == 1){
						player = 1;
					}
					else
						player = 2;
				}
				if(gameMod == 2){
					temp = Integer.parseInt(br.readLine());
					comp_x = temp;
					temp = Integer.parseInt(br.readLine());
					comp_y = temp;
				}
				temp = Integer.parseInt(br.readLine());
				for(int a=0;a<move_counter;a++)
					Movements[a] = null;
				Movements = null;
				move_counter = 0;				
				for(i=0;i<temp;i++){
					row = Integer.parseInt(br.readLine());
					column = Integer.parseInt(br.readLine());
					information = (char) br.read();
					if(information == informations.user1.c) {
						Cell c = new Cell(row,column,informations.user1);
						addMove(c);
					}
					else {
						Cell c = new Cell(row,column,informations.user2);
						addMove(c);
					}
									
				}
				break;
			}
			if(j == size){
				i++;
				j=0;
			}
			if(x == informations.user1.c){
				hexCells[i][j].setinformation(informations.user1);
				j++;	
			}
			else if(x == informations.user2.c){
				hexCells[i][j].setinformation(informations.user2);
				j++;	
			}
			else if(x == informations.empty.c){
				hexCells[i][j].setinformation(informations.empty);
				j++;	
			}
				counter++;	 
			}
		br.close();
	}
	public String toString(int x) {
		return String.format("%d",x);
	}
	public String toString(char x) {
		return String.format("%c",x);
	}
	@SuppressWarnings("resource")
	public void save_file(String filename) throws IOException
	{
		FileWriter out = new FileWriter(filename);
		out.write(toString(size));
		out.write("\n");
		for(int i=0;i<size;i++){
			for(int j=0;j<size;j++){
				out.write(toString(hexCells[i][j].getinformations().c));
			}
		}
		out.write(toString(gameMod));
		if(gameMod == 1)
			out.write(toString(player));
		if(gameMod == 2){
			out.write(toString(comp_x));
			out.write("\n");
			out.write(toString(comp_y));
			out.write("\n");
		}
		out.write(toString(move_counter));
		out.write("\n");
		for(int i=0;i<move_counter;i++)
			out.write(toString(Movements[i].getrow())+"\n"+toString(Movements[i].getcolumn())+"\n"+toString(Movements[i].getinformations().c));
		
		out.close();
	}
}
