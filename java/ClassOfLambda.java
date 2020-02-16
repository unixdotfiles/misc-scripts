import java.lang.Runnable;

class a {
	public static void main(String[] args) {
		Runnable r = () -> System.out.println("hi");
		System.out.println(r.getClass());
	}
}
