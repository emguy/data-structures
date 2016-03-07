import java.util.Comparator;

public class MinHeap<E extends Comparable<E>> {
  private E[] array = null;
  private int size = 0;
  private Comparator<E> cmp = null;

  @SuppressWarnings("unchecked")
  public MinHeap(int capacity) {
    this.size = 0;
    this.array = (E[]) new Object[capacity];
  }

  @SuppressWarnings("unchecked")
  public MinHeap(int capacity, Comparator<E> cmp) {
    this.size = 0;
    this.array = (E[]) new Object[capacity];
    this.cmp = cmp;
  }

  public MinHeap(E[] arr) {
    this.array = arr;
    this.size = array.length;
    heapify();
  }

  public MinHeap(E[] arr, Comparator<E> cmp) {
    this.array = arr;
    this.size = array.length;
    this.cmp = cmp;
    heapify();
  }

  public int size() {
    return this.size;
  }

  private void percolateUp(int index) {
    if (index <= 0) {
      return;
    }
    int parent = (index - 1) / 2;
    boolean doSwap = cmp == null ? array[index].compareTo(array[parent]) < 0 
                         : cmp.compare(array[index], array[parent]) < 0;
    if (doSwap) {
      E tmp = array[index];
      array[index] = array[parent];
      array[parent] = tmp;
      percolateUp(parent);
    }
  }

  private void percolateDn(int index) {
    int child1 = index * 2 + 1;
    int child2 = index * 2 + 2;
    int min = index;
    boolean updateMin = false;
    if (child1 < this.size) {
      updateMin = cmp == null ? array[child1].compareTo(array[min]) < 0 
                     :cmp.compare(array[child1], array[min]) < 0;
    }
    if (updateMin) {
      min = child1;
    }
    updateMin = false;
    if (child2 < this.size) {
      updateMin = cmp == null ? array[child2].compareTo(array[min]) < 0 
                     :cmp.compare(array[child2], array[min]) < 0;
    }
    if (updateMin) {
      min = child2;
    }
    if (min != index) {
      E tmp = array[index];
      array[index] = array[min];
      array[min] = tmp;
      percolateDn(min);
    }
  }

  private void heapify() {
    for (int index = this.size / 2 - 1; index >= 0; --index) {
      percolateDn(index);
    }
  }

  public MinHeap<E> offer(E obj) {
    if (this.size >= array.length) {
      System.err.println("Array index out of bound.");
      System.exit(1);
    }
    array[this.size++] = obj;
    percolateUp(this.size - 1);
    return this;
  }

  public E peek() {
    if (this.size == 0) {
      return null;
    }
    return array[0];
  }

  public E poll() {
    if (this.size == 0) {
      return null;
    }
    E tmp = array[0];
    array[0] = array[--this.size];
    array[this.size] = tmp;
    percolateDn(0);
    return tmp;
  }

  public static void main(String[] args) {
    // initial array
    Integer[] arr = {2, 7, 3, 1, 5, 2, 9, 8, 2};

    for (int val : arr) {
      System.out.print(val + " ");
    }
    System.out.println();

    class MyReverseComparator implements Comparator<Integer> {
      @Override
        public int compare(Integer a, Integer b) {
          if (a == b) {
            return 0;
          }
          return a < b ? 1 : -1;
        }
    }
    MinHeap<Integer> minHeap = new MinHeap<>(arr, new MyReverseComparator());
    //MinHeap<Integer> minHeap = new MinHeap<>(arr);
    while (minHeap.size() > 0) {
      System.out.print(minHeap.poll() + " ");
    }
    System.out.print("\n");
    System.exit(0);
  }
}

