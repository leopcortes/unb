public class long_cast {
	public static void main(String args[]) {
		long a=0xEFFFFFFF;

		short b=(short)a; // l2d
		float c=(float)a; // l2f
		int   d=(int)a;   // l2i
		System.out.println(a);
		System.out.println(b);
		System.out.println(c);
		System.out.println(d);
		
		a = -a;
		
		b=(short)a; //l2d
		c=(float)a; //l2f
		d=(int)a;   //l2i
		System.out.println(a);
		System.out.println(b);
		System.out.println(c);
		System.out.println(d);
	}	
}
