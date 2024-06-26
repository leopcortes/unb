public class FibonacciRec {
	int fibo(int n) {
		if (n < 2) {
			return n;
		} else {
			return fibo(n - 1) + fibo(n - 2);
		}
	}
 
	public static void main(String[] args) {   
		FibonacciRec fib = new FibonacciRec();

		for (int i = 0; i < 20; i++) {
			System.out.println(fib.fibo(i));
		}
	}
}
