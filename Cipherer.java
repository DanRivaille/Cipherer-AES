class Cipherer {
	
	
	/**
	 * Recorre la columna "column" de la cadena "text"
	 * @param text cadena a ser recorrida
	 * @param column columna de la cadena a ser recorrida
	 * */
	public static void show(String text, int column) {
		for(int i = 0; i < CANT_COLUMNS; ++i) {
			showByte(text.charAt((column * CANT_COLUMNS) + i));
			System.out.print(" ");
		}
		System.out.println();
	}

	/**
	 * Muestra el caracter ingresado en notacion hexadecimal
	 * @param byteToShow caracter a ser mostrado
	 * */
	public static void showByte(char byteToShow) {
		System.out.print(Integer.toHexString(byteToShow));
	}

	/**
	 * Clave de cifrado
	 * */
	public static final String key = "\u002b\u007e\u0015\u0016\u0028\u00ae\u00d2\u00a6\u00ab\u00f7\u0015\u0088\u0009\u00cf\u004f\u003c";
	public static final int CANT_COLUMNS = 4;
}