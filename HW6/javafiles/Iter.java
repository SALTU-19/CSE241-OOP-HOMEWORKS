	/**
	 * That is iterator class
	 */

public class Iter<E> implements Iterator<E> {
	private E[] array;
	private int size;
	private int currentIndex;
	private Collection<E> col;
	
	public Iter(E[] arr,Collection<E> c){
		this.array = arr;
		this.size  = arr.length;
		this.currentIndex = 0;
		this.col = c;
	}
	/**
	 * Returns true if the iteration has more elements.
	 */
    public boolean hasNext() {
 
    	return currentIndex < size && array[currentIndex] != null;
    }
	/**
	 * Returns the next element in the iteration and advances the iterator.
	 */
    @Override
    public E next() {
        return (E)array[currentIndex++];
    }
	/**
	 * Removes from the underlying collection the last element returned by this iterator. This method does not work for Queues, it throws an exception.
	 */
    @Override
    public void remove() throws Exception {
       if(col instanceof Queue) {
    	   throw new Exception("Queue can not be removed!");
       }
       else {
    	   col.remove(array[currentIndex]);
       }
    }

}
