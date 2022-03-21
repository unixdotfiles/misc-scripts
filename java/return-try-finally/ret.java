class ret {

	public static int f() {
		try {
			return 1;
		}
		finally {
			return 2;
		}
	}
	public static void main(String[] args) {
		System.out.println(f());
	}
}
