import java.util.Collections;
import java.util.List;
import java.util.function.Function;

public class CleanerErrors {
  public <T> void play(Function<List<T>, List<T>> doSomething) {
    List<String> myList = Collections.singletonList("string");
    doSomething.apply(myList); // does not work
    doSomething2(myList); // works
  }
  public <T> List<T> doSomething2(List<T> list) {
    return list;
  }
}
