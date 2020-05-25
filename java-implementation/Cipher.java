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
				}
			}

			calculateSubKeys();
		}
	}

	public String cifrate(String text, String key) {
		return null;
	}

	public String decifrate(String text, String key) {
		return null;	
	}

	/* ------------------------- Funciones auxiliares -------------------------- */
	private void calculateSubKeys() {
		for(int currentKey = 1; currentKey <= CANTS_ROUNDS; ++currentKey) {
			rotWord(this.key[(currentKey * MATRIX_ORDER) - 1], this.key[currentKey * MATRIX_ORDER]);

			for(int j = 0; j < MATRIX_ORDER; ++j) {
				this.key[currentKey * MATRIX_ORDER][j] = Tables.sbox[this.key[currentKey * MATRIX_ORDER][j]];

				this.key[currentKey * MATRIX_ORDER][j] ^= this.key[(currentKey - 1) * MATRIX_ORDER][j];
			}

			this.key[currentKey * MATRIX_ORDER][0] ^= Tables.rcon[currentKey - 1];

			for(int j = 1; j < MATRIX_ORDER; ++j) {
				xorBtweenVector(
					this.key[(currentKey * MATRIX_ORDER) + j - 1],
					this.key[((currentKey - 1) * MATRIX_ORDER) + j],
					this.key[(currentKey * MATRIX_ORDER) + j]);
			}
		}
	}

	private void rotWord(char columnOrigin[], char columnDestiny[]) {
		columnDestiny[MATRIX_ORDER - 1] = columnOrigin[0];

		for(int i = 1; i < MATRIX_ORDER; ++i) {
			columnDestiny[i - 1] = columnOrigin[i];
		}
	}

	private void xorBtweenVector(char vector1[], char vector2[], char vectorRestult[]) {
		for(int i = 0; i < MATRIX_ORDER; ++i) {
			vectorRestult[i] = (char) (vector1[i] ^ vector2[i]);
		}
	}

	private static final byte MATRIX_ORDER = 4;
	private static final byte CANTS_ROUNDS = 10;
	public static final byte CIFRATE_MODE = 1;
	public static final byte DECIFRATE_MODE = 2;
}