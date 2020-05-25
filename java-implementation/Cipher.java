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
		if(key != null)
			setKey(key);

		char states[][][] = expandBlocks(text, CIFRATE_MODE);

		for(char state[][] : states) {
			addRoundKey(state, 0);

			for(int round = 1; round < CANTS_ROUNDS; ++round) {
				subBytes(state);
				shiftRows(state);
				mixColumns(state);
				addRoundKey(state, round);
			}

			subBytes(state);
			shiftRows(state);
			addRoundKey(state, CANTS_ROUNDS);
		}

		return getText(states, CIFRATE_MODE);
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

	/**
	 * Metodo que expandira el texto ingresado en bloques de 128 bits, donde cada uno sera cifrado, dependiendo del modo
	 * le agregara un bloque extra de relleno si esta en modo de cifrado.
	 * */
	private char[][][] expandBlocks(String text, byte mode) {
		//Indica cuantos bloques van a ser cifrados o decifrados
		int cants_blocks = (text.length() / RADIX);

		//Si esta en modo cifrado, se le agrega el bloque de relleno
		if(CIFRATE_MODE == mode)
			cants_blocks++;

		//Se dimensiona la matriz de bloques con el tamaño establecido previamente
		char states[][][] = new char[cants_blocks][MATRIX_ORDER][MATRIX_ORDER];

		//Guardara la posicion del caracter actual del texto a expandir
		int currentChar = 0;

		for(int i = 0; i < cants_blocks; ++i) {
			for(int j = 0; j < MATRIX_ORDER; ++j) {
				for(int k = 0; k < MATRIX_ORDER; ++k) {

					//Si todavia quedan caracteres en el texto se ingresa en el estado actual sino se guarda el relleno
					if(currentChar < text.length()) {
						states[i][j][k] = text.charAt(currentChar);
						currentChar++;
					}
					else {
						states[i][j][k] = (char) ((RADIX * cants_blocks) - currentChar);
					}
				}
			}
		}

		return states;
	}

	/**
	 * Metodo que obtiene el texto a partir de la matriz de estados, dependiendo del modo ingresado, si es modo de cifrado
	 * le agraga todos los caracteres, sino le agrega los caracteres validos.
	 * */
	private String getText(char states[][][], int mode) {
		String text = "";

		for(char state[][] : states)
		{
			for(char column[] : state)
			{
				for(char character : column)
				{
					if(DECIFRATE_MODE == mode) {
						if(character > 16){
							text += character;
							showByte(character);
						}
					}
					else {
						text += character;
						showByte(character);
					}
				}
				System.out.println();
			}
			System.out.println();
		}

		return text;
	}

	private void rotWord(char columnOrigin[], char columnDestiny[]) {
		columnDestiny[MATRIX_ORDER - 1] = columnOrigin[0];

		for(int i = 1; i < MATRIX_ORDER; ++i) {
			columnDestiny[i - 1] = columnOrigin[i];
		}
	}

	private void rotColumnLeft(char vector[][], int column)
	{
		char aux = vector[0][column];

		for(int i = 1; i < MATRIX_ORDER; ++i) {
			vector[i - 1][column] = vector[i][column];
		}

		vector[MATRIX_ORDER - 1][column] = aux;
	}

	private void rotColumnRight(char vector[][], int column)
	{
		char aux = vector[MATRIX_ORDER - 1][column];

		for(int i = MATRIX_ORDER - 1; i > 0; --i) {
			vector[i][column] = vector[i - 1][column];
		}

		vector[0][column] = aux;
	}

	private void xorBtweenVector(char vector1[], char vector2[], char vectorRestult[]) {
		for(int i = 0; i < MATRIX_ORDER; ++i) {
			vectorRestult[i] = (char) (vector1[i] ^ vector2[i]);
		}
	}

	/* --------------------------------- Funciones del algoritmo AES ---------------------------------- */
	private void addRoundKey(char state[][], int currentRound) {
		for(int i = 0; i < MATRIX_ORDER; ++i) {
			xorBtweenVector(state[i], this.key[(currentRound * MATRIX_ORDER) + i], state[i]);
		}
	}

	private void shiftRows(char state[][])
	{
		for(int i = 1; i < MATRIX_ORDER; ++i) {
			for(int j = 0; j < i; ++j) {
				rotColumnLeft(state, i);
			}
		}
	}

	private void subBytes(char state[][])
	{
		for(char column[] : state) {
			for(char character : column) {
				character = Tables.sbox[character];
			}
		}
	}

	private void mixColumns(char state[][])
	{
		char aux[] = new char[MATRIX_ORDER];
		char temp[] = new char[MATRIX_ORDER];

		for (int j = 0; j < MATRIX_ORDER; j++)
		{
			for(int i = 0; i < MATRIX_ORDER; ++i) {
				aux[i] = state[j][i];
			}

			temp[0] = (char) (Tables.mul2[aux[0]] ^ Tables.mul3[aux[1]] ^ aux[2] ^ aux[3]);
			temp[1] = (char) (aux[0] ^ Tables.mul2[aux[1]] ^ Tables.mul3[aux[2]] ^ aux[3]);
			temp[2] = (char) (aux[0] ^ aux[1] ^ Tables.mul2[aux[2]] ^ Tables.mul3[aux[3]]);
			temp[3] = (char) (Tables.mul3[aux[0]] ^ aux[1] ^ aux[2] ^ Tables.mul2[aux[3]]);

			for(int i = 0; i < MATRIX_ORDER; ++i) {
				state[j][i] = temp[i];
			}
		}
	}


	private static final byte MATRIX_ORDER = 4;
	private static final byte CANTS_ROUNDS = 10;
	private static final byte RADIX = 16;
	public static final byte CIFRATE_MODE = 1;
	public static final byte DECIFRATE_MODE = 2;
}