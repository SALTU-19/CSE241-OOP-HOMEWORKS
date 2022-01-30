
/**
 * This is a generic class with one generic parameter which is the generic type E.
 */
public interface Collection<E> {
	/**
	 * Returns an iterator over the collection
	 */
	public Iter<E> iterator();
	/**
	 * Ensures that this collection contains the specified element
	 */
	public boolean add(E e);
	/**
	 * Adds all of the elements in the specified collection to this collection
	 */
	public boolean addAll(Collection<E> c);
	/**
	 *Removes all of the elements from this collection
	 */
	public void clear()throws Exception;
	/**
	 * Returns true if this collection contains the specified element 
	 */
	public boolean contains(E e);
	/**
	 * Returns true if this collection contains all of the elements in the specified collection. 
	 */
	public boolean containsAll(Collection<E> c);
	/**
	 * Returns true if this collection contains no elements.
	 */
	public boolean isEmpty();
	/**
	 *Removes a single instance of the specified element from this collection, if it is present 
	 */
	public boolean remove(E e) throws Exception;
	/**
	 * Removes all of this collection's elements that are also contained in the specified collection
	 */
	public boolean removeAll(Collection<E> c)throws Exception;
	/**
	 * Retains only the elements in this collection that are contained in the specified collection 
	 */
	public boolean retainAll(Collection<E> c)throws Exception;
	/**
	 *Returns the number of elements in this collection
	 */
	public int size();

}
