/*
1. Escriba un programa para codificar archivos de texto. El programa debe recibir un número
entero n que será la semilla de codificación y un número para seleccionar el método de
codificación.

Primer método:
Para codificar se convierte el archivo a binario, luego se separa en bloques de n bits. En el
primer bloque se cambian todos los 1 por 0 y viceversa. Para los grupos siguientes se debe
contar el número de 1s y 0s en el grupo anterior y hacer cambios según la siguiente regla:
- Si hay igual cantidad de 1s y 0s se invierte cada bit del grupo.
- Si hay mayor cantidad de 0s se invierte cada 2 bits.
- Si hay mayor cantidad de 1s se invierte cada 3 bits.

Ej:​ Si se ingresa 4 y el archivo contiene AbCd.
El archivo en binario sería:
01000001011000100100001101100100
El archivo codificado sería:
10110100001111010001011010011011
*Nota: ​ Tener en cuenta cuando se aplican las reglas a partir del segundo bloque, se debe
tomar los grupos de bits del archivo binario sin codificar.

Segundo método:
Para codificar se convierte el archivo a binario, luego se separa en bloques de n bits. Cada
bit dentro de un grupo se desplaza una posición, de manera que el primer bit del grupo
codificado corresponde al último bit del grupo sin codificar, el segundo bit codificado
corresponde al primero sin codificar y así sucesivamente hasta que el último corresponde
al penúltimo sin codificar.
Ej:​ Si se ingresa 4 y el archivo contiene AbCd.
El archivo en binario sería:
01000001011000100100001101100100
El archivo codificado sería:
00101000001100010010100100110010

Nota: El programa debe generar un archivo de salida con la información binaria
codificada​ . ​ El programa debe recibir los nombres del archivo fuente y el archivo de
salida por consola.
*/

#include <fstream>
#include <iostream>
#include <exception>

int main
{	
	ofstream archivo("datos.txt");	


	return 0;			
}
