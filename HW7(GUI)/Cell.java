public class Cell {
	private int row;
	private int column;
	private informations information;
	public Cell(int newRow,int newColumn,informations newinformation) {
		row = newRow;
		column = newColumn;
		information = newinformation;
	}
	public void setinformation(informations newinformation){information = newinformation;}
	public int getrow(){return row;} //it gets row
	public int getcolumn(){return column;}// it gets column 
	public informations getinformations(){return information;} //it gets information the cell (x or o or .)
}

