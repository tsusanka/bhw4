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
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define DEBUG 1

#define LENGTH 79
#define ARRAY_LENGTH 10

#define ONE_NOT_FOUND 9

uint8_t pattern[8] = {0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};


void printBin(uint8_t x)
{
	int i = 0;
	for (i = sizeof(uint8_t) * 8 - 1; i >= 0; i--)
	{
		(x & (1<<i)) ? putchar('1') : putchar('0');
	}

	printf(" ");
}

void printBinWhole(uint8_t* array, int length)
{
	int i = 0;
	for (i = 0; i < length; ++i)
	{
		printBin(array[i]);
	}
	printf("\n");
}

void printHexWhole(uint8_t* array, int length)
{
	int i = 0;
	for (i = 0; i < length; ++i)
	{
		printf("%2x ", array[i]);
	}
}


/**
 * Sets all elements of array to 0
 */
void zeroArray(uint8_t* array, int length)
{
	int i = 0;
	for (i = 0; i < length; ++i)
	{
		array[i] = 0;
	}
}


/**
 * Reads input from stdin
 */
uint8_t loadInput(uint8_t* P_x, uint8_t* P_y, uint8_t* Q_x, uint8_t* Q_y)
{
	zeroArray(P_x,ARRAY_LENGTH);
	zeroArray(P_y,ARRAY_LENGTH);
	zeroArray(Q_x,ARRAY_LENGTH);
	zeroArray(Q_y,ARRAY_LENGTH);
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
	printHexWhole(P_x,ARRAY_LENGTH);
	printf(", ");
	printHexWhole(P_y,ARRAY_LENGTH);
	printf("\nQ: ");
	printHexWhole(Q_x,ARRAY_LENGTH);
	printf(", ");
	printHexWhole(Q_y,ARRAY_LENGTH);
	printf("\n");
}

void shiftOneToLeft(uint8_t* number, int length) {
    int i;
    int n;

    for(i = 0; i < length; i++) {
        if ((number[i] > 0x00) && (i > 0)) {
            if ((0x80 & number[i]) > 0x00) number[i-1] += pattern[7];
        }
        number[i] = number[i] << 1;
    }
}

uint8_t computeC(uint8_t* b) {      //computed from b by m � 2 squarings
    int i = 0;

    for(i = 0; i < LENGTH - 2; i++) {

    }
}


uint8_t doubling(uint8_t* P_x, uint8_t* P_y) {

}

void mod(uint8_t* huge, int hugeLength, uint8_t* smaller)
{
    int i, y, position = 0;
    for (i = 0; i < hugeLength; i++)
    {
        for (y = 0; y < 8; y++)
        {
            if ((huge[i] & pattern[y]) > 0) // looking for 1
            {
                position = (8 * i) + y;
                if (position > (hugeLength*8 - LENGTH))
                {
                    memcpy(smaller, huge + ARRAY_LENGTH*sizeof(uint8_t), ARRAY_LENGTH);
                    return;
                }
                position += 70;
                huge[i] = huge[i] ^ pattern[y];
                huge[position / 8] = huge[position / 8] ^ pattern[position % 8];
                position += 9;
                huge[position / 8] = huge[position / 8] ^ pattern[position % 8];
            }
        }
    }
    memcpy(smaller, huge + ARRAY_LENGTH*sizeof(uint8_t), ARRAY_LENGTH);
}

/**
 * Insert zeros between bits.
 * Eg 00000111 => 00010101
 **/
uint8_t insertZeros(uint8_t input)
{
    return (input & 1)
       | ((input & 2) << 1)
       | ((input & 4) << 2)
       | ((input & 8) << 3)
       | ((input & 16) << 4);
}

void square(uint8_t* number)
{
    uint8_t i, lowNibble, highNibble, temp = 0;

    uint8_t huge[2*ARRAY_LENGTH];
    zeroArray(huge,2*ARRAY_LENGTH);
    
    for(i = 0; i < ARRAY_LENGTH; i++)
    {
        highNibble = (number[i] >> 4) & 0x0F;
        lowNibble = number[i] & 0x0F;
        huge[temp++] = insertZeros(highNibble);
        huge[temp++] = insertZeros(lowNibble);
    }

    mod(huge, 2*ARRAY_LENGTH, number);
}

/*****************************************************************************************************************************/
/*****************************************************************************************************************************/

int main(int argc, uint8_t** argv)
{
    uint8_t P_x[ARRAY_LENGTH];
    uint8_t P_y[ARRAY_LENGTH];      
    uint8_t Q_x[ARRAY_LENGTH];      
    uint8_t Q_y[ARRAY_LENGTH];      
    uint8_t a[ARRAY_LENGTH] = {0x4A,0x2E,0x38,0xA8,0xF6,0x6D,0x7F,0x4C,0x38,0x5F};      //Defying our EC
	uint8_t b[ARRAY_LENGTH] = {0x2C,0x75,0xA6,0x48,0x59,0x55,0x2F,0x97,0xC1,0x29};      //Defying our EC
	uint8_t temp[ARRAY_LENGTH];


    // loadInput(P_x, P_y, Q_x, Q_y);

    uint8_t num[ARRAY_LENGTH] = {0x4A,0x2E,0x38,0xA8,0xF6,0x6D,0x7F,0x4C,0x38,0x5F};

    printf("We're saying that\n");
    printBinWhole(num, ARRAY_LENGTH);
    printf("^2 mod (x^79 + x^9 + 1) is:\n");
    
    square(num);

    printBinWhole(num, ARRAY_LENGTH);

	return 0;
}
