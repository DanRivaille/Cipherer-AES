import java.io.*;

public class Main {
	public static void main(String[] args) {
		String key = "\u002b\u007e\u0015\u0016\u0028\u00ae\u00d2\u00a6\u00ab\u00f7\u0015\u0088\u0009\u00cf\u004f\u003c";

		String texto;
		String texto_cifrado;
		String texto_decifrado;

		BufferedReader lector = new BufferedReader(new InputStreamReader(System.in));

		System.out.print("Ingrese el texto a cifrar: ");

		try {
			texto = lector.readLine();
		}
		catch (IOException e) {
			texto = "Hola";
		}

		Cipher cipher = new Cipher();

		texto_cifrado = cipher.cifrate(texto, key);
		texto_decifrado = cipher.decifrate(texto_cifrado, null);

		System.out.println("Texto          : -" + texto + "-");
		//System.out.println("Texto cifrado: " + texto_cifrado);
		System.out.println("Texto decifrado: -" + texto_decifrado + "-");
	}
}