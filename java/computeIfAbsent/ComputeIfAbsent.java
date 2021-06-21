import java.util.HashMap;
import java.util.Map;


public class ComputeIfAbsent {
	public static void main() {
		Map<String, String> m = new HashMap<>();
		m.putIfAbsent("a", "b");
		m.computeIfAbsent("c", (i) -> "d");
		String w = m.get("e");
		if (w == null) {
			m.put("e", "f");
		}
	}
}
