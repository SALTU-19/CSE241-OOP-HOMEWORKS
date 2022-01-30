/**
 * that is class which test the LinkedList
 */
public class LinkedListTester {
	public static <E> void Print(Collection<E> c) {
		Iter<E> iter = c.iterator();
		while(true) {
			if(iter.hasNext() == false) {
				break;
			}
			System.out.println(iter.next());
		}
	}

	public static void main(String[] args) {
		try {
			LinkedList<Integer> numbers = new LinkedList<Integer>();
			LinkedList<Integer> numbers2 = new LinkedList<Integer>();
			numbers.add(10);
			numbers.add(20);
			numbers.add(30);
			numbers.add(40);
			numbers.add(50);
			System.out.println("*************\nLinkedList:");
			Print(numbers);
			numbers2.add(10);
			numbers2.add(20);
			numbers2.add(30);
			System.out.println("*************\nLinkedList2:");
			Print(numbers2);
			System.out.println("Add 1+2");
			numbers.addAll(numbers2);
			System.out.println("*************\nLinkedList:");
			Print(numbers);
			numbers.removeAll(numbers2);
			System.out.println("Remove 1-2");
			System.out.println("*************\nLinkedList:");
			Print(numbers);
			numbers.remove(40);
			System.out.println("*************\nLinkedList:");
			Print(numbers);
			numbers.addAll(numbers2);
			System.out.println("*************\nLinkedList:");
			Print(numbers);
			System.out.println("*************\nLinkedList2:");
			Print(numbers2);
			System.out.println("*************\nContainAll:"+numbers.containsAll(numbers2));
			System.out.println("*************\nContain 10:"+numbers.contains(10));
			System.out.println("*************\nContain 100:"+numbers.contains(100));
			numbers.retainAll(numbers2);
			System.out.println("*************\nLinkedList:");
			Print(numbers);
			System.out.println("Pol:" + numbers.poll());
			System.out.println("*************\nLinkedList:");
			Print(numbers);
			numbers.clear();
			System.out.println("IsEmpty:" + numbers.isEmpty());
			
			
			
			
			
			
		}
		catch(Exception e) {
            System.out.println(e.getMessage());
        }

	}

}

