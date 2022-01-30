/**
 * Queues order elements in a FIFO (first-in-first-out) manner. There is no random access with this Collection. Some functions throw exceptions.
 */
public interface Queue<E> extends Collection<E> {
	/**
	 * Inserts the specified element into this queue 
	 */
	boolean	add(E e);
	/**
	 * Retrieves, but does not remove, the head of this queue.
	 */
	E element();
	/**
	 * inserts the specified element into this queue
	 */
	boolean	offer(E e);
	/**
	 * Retrieves and removes the head of this queue, or throws if this queue is empty
	 */
	E poll()throws Exception;
	
}
