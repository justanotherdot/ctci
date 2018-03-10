import java.util.*;

public class StackStack<T> {
  private final int LIMIT;
  private ArrayList<Stack<T>> stacks;
  private Stack<T> currStack;

  public StackStack() {
    LIMIT = 15;
    stacks = new ArrayList<>();
    currStack = new Stack<>();
    stacks.add(currStack);
  }

  public void push(T val) {
    if ((currStack.size()+1)%(LIMIT+1) == 0) {
      currStack = new Stack<>();
      currStack.push(val);
      stacks.add(currStack);
    } else {
      currStack.push(val);
    }
  }

  public Optional<T> peek() {
    return currStack.peek();
  }

  public Optional<T> pop() {
    // Never get rid of last stack.
    if ((currStack.size()-1) == 0 && stacks.size() > 1) {
      int top = stacks.size() - 1;
      Optional<T> rv = currStack.pop();
      stacks.remove(top);
      currStack = stacks.get(top-1);
      return rv;
    } else {
      return currStack.pop();
    }
  }

  public Optional<T> popAt(int ix) {
    if (ix < 0 || ix >= stacks.size()) {
      return Optional.empty();
    } else {
      return stacks.get(ix).pop();
    }
  }

  public void printSizes() {
    int i = 0;
    for (Stack<T> s : stacks) {
      System.out.print(s.size());
      if (i+1 != stacks.size()) {
        System.out.print(", ");
      }
      ++i;
    }
    System.out.println();
  }

  public int size() {
    int rv = 0;
    for (Stack<T> s : stacks) {
      rv += s.size();
    }
    return rv;
  }
}
