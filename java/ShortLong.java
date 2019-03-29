/** https://lemire.me/blog/2019/03/28/java-is-not-a-safe-language/ **/
public class ShortLong {
	public static void main(String[] args) {
		short x = Short.MAX_VALUE;
		short y = 2;
		System.out.println(x+y);
		int ix = Integer.MAX_VALUE;
		int iy = 2;
		System.out.println(ix+iy);
	}
}
