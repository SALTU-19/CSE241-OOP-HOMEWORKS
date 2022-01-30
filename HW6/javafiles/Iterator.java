	/**
	 * That is iterator interface
	 */
public interface Iterator<E> {
	/**
	 * Returns true if the iteration has more elements.
	 */
	boolean hasNext();
	/**
	 * Returns the next element in the iteration and advances the iterator.
	 */
	E next();
	/**
	 * Removes from the underlying collection the last element returned by this iterator. This method does not work for Queues, it throws an exception.
	 */
	void remove() throws Exception;
}
