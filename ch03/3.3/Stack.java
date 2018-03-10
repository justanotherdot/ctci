import java.util.ArrayList;
import java.util.Optional;

public class Stack<T> {
  private ArrayList<T> store;

  public Stack() {
    store = new ArrayList<>();
  }

  public Optional<T> pop() {
    int top = store.size() - 1;
    if (inBounds(top)) {
      T el = store.remove(top);
      return Optional.of(el);
    } else {
      return Optional.empty();
    }
  }

  public Optional<T> peek() {
    int top = store.size() - 1;
    if (inBounds(top)) {
      return Optional.of(store.get(top));
    } else {
      return Optional.empty();
    }
  }

  public void push(T val) {
    store.add(val);
  }

  public int size() {
    return store.size();
  }

  public void print() {
    System.out.print("[");
    int i = 0;
    int len = size();
    for (T s : store) {
      System.out.print(s);
      if ((i+1) != len) {
        System.out.print(", ");
      }
      ++i;
    }
    System.out.println("]");
  }

  private boolean inBounds(int ix) {
    return !(ix < 0);
  }
}
