# Cipherer-AES
_Cifrador que utiliza el algoritmo AES (Rijndael) para cifrar y decifrar texto, posee implementaciones tanto en C++ como en Java_

## Intalación
Simplemente clona el repositorio:
```
git clone https://github.com/DanSantosAA/Cipherer-AES.git
```
y elige la implementacion que deseas utilizar (C++ o Java), copiando la carpeta correspondiente en tu proyecto.

## Modos de uso
En ambas implementaciones se usa el patron Singleton, lo que facilita la utilizacion del cifrador.

_Se tiene que usar una clave de minimo 16 caracteres_

Ademas que usan un sistema de memorizacion de keys, lo que permite al usuario establecer la key una sola vez, y usar esta a lo largo de todo el programa, o por otro lado, ir usando distintas keys especificandola a la hora de cifrar o decifrar informacion

### C++ implementation
_Incluye la biblioteca a tu proyecto_
```
#include "Cipher.h"
```
_Establece la key a utilizar_
```
string key = "DanSantosCiphererAES";
Cipher *cipher = Cipher::getInstance();
cipher->setKey(&key);
```
_Cifra y decifra texto usando la mista clave_
```
string texto_cifrado = cipher->cifrate("Me van a cifrar usando AES");
string texto_claro = cipher->decifrate(texto_cifrado);
```
_O bien cifra y decifra usando claves distintas en cada proceso_
```
string key_1 = "DanSantosCiphererAES";
string key_2 = "CiphererAESDanSantos";

string cifrado_key_1 = cipher->cifrate("Me van a cifrar usando la clave key_1", &key_1);
string cifrado_key_2 = cipher->cifrate("Me van a cifrar usando la clave key_2", &key_2);

string decifrado_key_1 = cipher->decifrate(cifrado_key_1, &key_1);
string decifrado_key_2 = cipher->decifrate(cifrado_key_2, &key_2);
```

### Java implementation
_Incluye la biblioteca a tu proyecto_

_Establece la key a utilizar_
```
String key = "DanSantosCiphererAES";
Cipher cipher = Cipher.getInstance();
cipher.setKey(key);
```
_Cifra y decifra texto usando la mista clave_
```
String texto_cifrado = cipher.cifrate("Me van a cifrar usando AES");
String texto_claro = cipher.decifrate(texto_cifrado);
```
_O bien cifra y decifra usando claves distintas en cada proceso_
```
String key_1 = "DanSantosCiphererAES";
String key_2 = "CiphererAESDanSantos";

String cifrado_key_1 = cipher.cifrate("Me van a cifrar usando la clave key_1", key_1);
String cifrado_key_2 = cipher.cifrate("Me van a cifrar usando la clave key_2", key_2);

String decifrado_key_1 = cipher.decifrate(cifrado_key_1, key_1);
String decifrado_key_2 = cipher.decifrate(cifrado_key_2, key_2);
```

### Ejecutando el codigo de ejemplo
_Ambas implementaciones vienen con un codigo basico de ejemplo, en donde se muestra como usar el cifrador de manera sencilla, para ejecutar estas pruebas ejecuta lo siguiente:_

#### C++ implementation
```
make clean
make
./main
```

#### Java implementation
```
make clean
make
cd binaries/
java Main
```

---
⌨️ Reaizado por [Dan Santos](https://github.com/DanSantosAA)
