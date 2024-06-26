public class int_cast {
	public static void main(String args[]) {
		int a = 254;
		System.out.println((double)a); // i2d
		System.out.println((float)a);  // i2f
		System.out.println((long)a);   // i2l
		System.out.println((char)a);   // i2c
		System.out.println((byte)a);   // i2b
		System.out.println((short)a);  // i2s
		
		a = -a;
		System.out.println((double)a); // i2d
		System.out.println((float)a);  // i2f
		System.out.println((long)a);   // i2l
		System.out.println((char)a);   // i2c
		System.out.println((byte)a);   // i2b
		System.out.println((short)a);  // i2s
	}	
}
