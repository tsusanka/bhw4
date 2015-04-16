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
		printf("%2x ", array[i]);
	}
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
		printf("\n");
	}
}

/**
 * Reads input from stdin
 */
uint8_t loadInput(uint8_t* P_x, uint8_t* P_y, uint8_t* Q_x, uint8_t* Q_y)
{
	zeroArray(P_x);
	zeroArray(P_y);
	zeroArray(Q_x);
	zeroArray(Q_y);
	int res = 0;

	printf("Enter P_x:");
	res += scanf("%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x", &P_x[0], &P_x[1], &P_x[2], &P_x[3], &P_x[4], &P_x[5], &P_x[6], &P_x[7], &P_x[8], &P_x[9]);
	printf("\nEnter P_y:");
	res += scanf("%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x", &P_y[0], &P_y[1], &P_y[2], &P_y[3], &P_y[4], &P_y[5], &P_y[6], &P_y[7], &P_y[8], &P_y[9]);
	printf("\nEnter Q_x:");
	res += scanf("%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x", &Q_x[0], &Q_x[1], &Q_x[2], &Q_x[3], &Q_x[4], &Q_x[5], &Q_x[6], &Q_x[7], &Q_x[8], &Q_x[9]);
	printf("\nEnter Q_y:");
	res += scanf("%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x", &Q_y[0], &Q_y[1], &Q_y[2], &Q_y[3], &Q_y[4], &Q_y[5], &Q_y[6], &Q_y[7], &Q_y[8], &Q_y[9]);
	printf("\n");

	return res;
}

/**
 * Prints P, Q in hex
 */
void printCoordinates(uint8_t* P_x, uint8_t* P_y, uint8_t* Q_x, uint8_t* Q_y)
{
	printf("P: ");
	printHexWhole(P_x);
	printf(", ");
	printHexWhole(P_y);
	printf("\nQ: ");
	printHexWhole(Q_x);
	printf(", ");
	printHexWhole(Q_y);
	printf("\n");
}

/*****************************************************************************************************************************/
/*****************************************************************************************************************************/

int main(int argc, uint8_t** argv)
{
	uint8_t f[ARRAY_LENGTH];
	uint8_t P_x[ARRAY_LENGTH];
	uint8_t P_y[ARRAY_LENGTH];
	uint8_t Q_x[ARRAY_LENGTH];
	uint8_t Q_y[ARRAY_LENGTH];

	setF(f);
	loadInput(P_x, P_y, Q_x, Q_y);

	printCoordinates(P_x, P_y, Q_x, Q_y);

	

	return 0;
}
