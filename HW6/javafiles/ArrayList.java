


/**
 * implements List functions
 */
public class ArrayList<E> implements List<E> {
	/**
	 * that is array of ArrayList
	 */
	protected E[] array;
	/**
	 * that is size of ArrayList
	 */
	protected int size = 0;
	/**
	 * that is constructor of ArrayList
	 */
	public ArrayList() {
		this.size = 0;
	}
	@Override
	/**
	 * Returns an iterator over the collection
	 */
	public Iter<E> iterator() {
		Iter<E> it= new Iter<E>(this.array,this);
		return it;
	}

	@SuppressWarnings("unchecked")
	@Override
	/**
	 * Ensures that this collection contains the specified element
	 */
	public boolean add(E e) {
		if(array == null) {
			array = (E[]) new  Object[size+1];
			size++;
			array[size-1] = e;
			return true;
		}
		
		E[] temp = (E[]) new Object[size+1];
		for(int i=0;i<size;i++) {
			temp[i] = array[i];
		}
		temp[size] = e;
		array = temp;
		size++;
		return true;
	}

	@Override
	/**
	 * Adds all of the elements in the specified collection to this collection
	 */
	public boolean addAll(Collection<E> c) {
		Iter<E> it = c.iterator();
		while(it.hasNext() != false) {
			this.add(it.next());
		}
		return true;
	}


	@Override
	/**
	 *Removes all of the elements from this collection
	 */
	public void clear() throws Exception{
		if(this.isEmpty() == true) {
			throw new Exception("This list does not have an element!");
		}
		else {
			for(int i=0;i<size;i++) {
				array[i] = null;
			}
			size = 0;
		}
	}

	@Override
	/**
	 * Returns true if this collection contains the specified element 
	 */
	public boolean contains(E e) {
		for(Object i:array) {
			if(e.equals(i)) {
				return true;
			}
		}
		return false;
	}

	@Override
	/**
	 * Returns true if this collection contains all of the elements in the specified collection. 
	 */
	public boolean containsAll(Collection<E> c) {
		Iter<E> it = c.iterator();
		while(it.hasNext() != false) {
			if(this.contains(it.next()) == false) {
				return false;
			}
		}
		return true;
	}

	@Override
	/**
	 * Returns true if this collection contains no elements.
	 */
	public boolean isEmpty() {
		if(size == 0) {
			return true;
		}
		return false;
	}

	@SuppressWarnings("unchecked")
	@Override
	/**
	 *Removes a single instance of the specified element from this collection, if it is present 
	 */
	public boolean remove(E e) throws Exception {
		if(size == 1) {
			array[0] = null;
			array = null;
			size--;
			return true;
		}
		int counter=0;
		boolean flag = false;
		E[] temp = (E[]) new  Object[size-1];
		for(int i=0;i<size;i++) {
			if(counter+1 == size) {
				break;
			}
			if(array[i] != e) {
				temp[counter] = array[i];
				counter++;
			}
			else {
				flag = true;
			}
		}
		if(flag == true) {
			this.array = temp;
			size = counter;
		}
		else {
			throw new Exception("The list does not have the value!");
		}
		return flag;
	}

	@Override
	/**
	 * Removes all of this collection's elements that are also contained in the specified collection
	 */
	public boolean removeAll(Collection<E> c) throws Exception{
		Iter<E> it = c.iterator();
		while(it.hasNext() != false) {
			this.remove(it.next());
		}
		return true;
	}

	@SuppressWarnings("unchecked")
	@Override
	/**
	 * Retains only the elements in this collection that are contained in the specified collection 
	 */
	public boolean retainAll(Collection<E> c) throws Exception {
		E[] temp = (E[]) new  Object[size];
		int counter = 0;
		for(int i=0;i<size;i++) {
			if(c.contains(array[i])) {
				temp[counter] = array[i];
				counter++;
			}
		}
		array = temp;
		size = counter;
		return true;
	}

	@Override
	/**
	 *Returns the number of elements in this collection
	 */
	public int size() {
		
		return size;
	}
}
