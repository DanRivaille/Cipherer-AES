public class Main {
	public static void main(String[] args) {
		String key = "\u002b\u007e\u0015\u0016\u0028\u00ae\u00d2\u00a6\u00ab\u00f7\u0015\u0088\u0009\u00cf\u004f\u003c";

		Cipher cipher = new Cipher();

		cipher.cifrate("Hola Como estas?", key);
	}
}