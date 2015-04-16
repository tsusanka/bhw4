/**
 * MI-BHW ukol 4
 * gf(2^m) AVR projective
 *
 * Tomas Susanka & Peter Poljak
 *
 **/

 /**
  * We're using polynomial base to represent f, eg: (101001) = x^5 + x^3 + 1
  * 
  */

#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#define DEBUG 1

#define LENGTH 79
#define ARRAY_LENGTH 10


void printBin(char x)
{
	int i = 0;
	for (i = sizeof(char) * 8 - 1; i >= 0; i--)
	{
		(x & (1<<i)) ? putchar('1') : putchar('0');
	}

	printf(" ");
}

void printBinWhole(char* array)
{
	int i = 0;
	for (i = 0; i < ARRAY_LENGTH; ++i)
	{
		printBin(array[i]);
	}
}

/**
 * Sets all elements of array to 0
 */
void zeroArray(char* array)
{
	int i = 0;
	for (i = 0; i < ARRAY_LENGTH; ++i)
	{
		array[i] = 0;
	}
}

/**
 * A little bit of magic to sets f to x^79 + x^9 + 1 according to assignment
 */
void setF(char* f)
{
	zeroArray(f);
	f[0] |= 1 << 7;
	f[9] |= 1 << 0;
	f[8] |= 1 << 1;
	if (DEBUG) {
		printf("f is: ");
		printBinWhole(f);
	}
}

/*****************************************************************************************************************************/
/*****************************************************************************************************************************/

int main(int argc, char** argv)
{
	char f[ARRAY_LENGTH];
	setF(f);

	return 0;
}
