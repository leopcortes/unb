public class long_logico {
	public static void main(String args[]) {
		long a = 0;
		long b = 1;
		
		long c = a & b; // land
		System.out.println(c);
		
		c = a | b; // lor
		System.out.println(c);

		c = a ^ b; // lxor
		System.out.println(c);
		
		c= a<<2;
		c= a>>2;
		System.out.println(c);
		
		// lcmp
		if (b>a)  System.out.println(b);
		if (a<b)  System.out.println(a);
		if (a!=b) System.out.println(0);
	}
}
