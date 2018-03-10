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
    System.out.println(ss.size());
  }
}
