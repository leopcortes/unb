public class method_test {
  public static void main(String args[]) {
	  System.out.println(Soma(2,3));
	  System.out.println(Soma(35.35,30.35));
	  System.out.println(Soma((long)300000000,(long)700000000));
  }
  
  public static int Soma(int x, int y) {
    return x+y;
  } 
  
  public static double Soma(double x, double y) {
    return x+y;
  } 
  
  public static long Soma(long x, long y) {
    return x-y;
  } 
}
