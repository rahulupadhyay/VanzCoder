/**
 * Marcos Paulo de Souza
 * José Guilherme Vanz
 *
 * Huffman
 */


#include <stdio.h>
#include <string.h>

/* quantidade de vezes que acontece cada caracter */
int caracteres[200];

int main(int argc, char *argv[])
{
	char c;
	int i;
	memset(caracteres, 0, sizeof(caracteres));

	while (scanf("%c", &c) != EOF)
		if (c != '\n')
			caracteres[c - '0']++;

	for (i = 0; i < 200; i++)
		if (caracteres[i])
			printf("Caracter '%c' aparece %d vezes\n", i + '0', caracteres[i]);

	return 0;
}
