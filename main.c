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


void printBin(uint8_t x)
{
	int i = 0;
	for (i = sizeof(uint8_t) * 8 - 1; i >= 0; i--)
	{
		(x & (1<<i)) ? putchar('1') : putchar('0');
	}

	printf(" ");
}

void printBinWhole(uint8_t* array)
{
	int i = 0;
	for (i = 0; i < ARRAY_LENGTH; ++i)
	{
		printBin(array[i]);
	}
	printf("\n");
}

void printHexWhole(uint8_t* array)
{
	int i = 0;
	for (i = 0; i < ARRAY_LENGTH; ++i)
	{
		printf("%x ", array[i]);
	}
	printf("\n");
}


/**
 * Sets all elements of array to 0
 */
void zeroArray(uint8_t* array)
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
void setF(uint8_t* f)
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

int main(int argc, uint8_t** argv)
{
	uint8_t f[ARRAY_LENGTH];
	setF(f);

	uint8_t P_x[ARRAY_LENGTH];
	zeroArray(P_x);
	printHexWhole(P_x);

	// x_P = 30CB 127B63E4 2792F10F
	// y_P = 547B 2C88266B B04F713B
	// x_Q = 0020 2A9F0350 14497325
	// y_Q = 5175 A6485955 2F97C129

	return 0;
}
