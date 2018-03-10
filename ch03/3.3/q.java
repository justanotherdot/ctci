import java.util.Optional;

public class q {
  public static void main(String args[]) {
    StackStack<Integer> ss = new StackStack<>();
    for (int i = 0; i < 100; ++i) {
      ss.push(i);
    }
    for (int i = 0; i < 50; ++i) {
      ss.pop();
    }
    ss.popAt(0);
    ss.printSizes();
    System.out.println(ss.size());
  }
}
