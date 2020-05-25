import java.util.ArrayList;

public class Cipher {

	public static void showByte(char byteToShow) {
		System.out.print(String.format("%2x ", (int) byteToShow));
	}
	
	//Atributos
	private char[][] key;

	/**
	 * Constructor por defecto de la clase, dimensiona la matriz que guardara tanto la clave como las subclaves.
	 * */
	public Cipher() {
		this.key = new char[MATRIX_ORDER * (CANTS_ROUNDS + 1)][MATRIX_ORDER];
	}

	/**
	 * Metodo que establece una nueva clave, valida que no sea null y que contenga almenos 16 caracteres.
	 * @param new_key la nueva clave que se usara y sobre la cual se calcularan las demas subclaves.
	 * */
	public void setKey(String new_key) {
		if((new_key != null) && (new_key.length() >= 16)) {

			for(int i = 0; i < MATRIX_ORDER; ++i) {
				for(int j = 0; j < MATRIX_ORDER; ++j) {
					this.key[i][j] = new_key.charAt((i * MATRIX_ORDER) + j);

					showByte(new_key.charAt((i * MATRIX_ORDER) + j));
				}
				System.out.println();
			}
		}

		showByte(Tables.sbox[5]);
	}

	private static final byte MATRIX_ORDER = 4;
	private static final byte CANTS_ROUNDS = 10;
	public static final byte CIFRATE_MODE = 1;
	public static final byte DECIFRATE_MODE = 2;
}