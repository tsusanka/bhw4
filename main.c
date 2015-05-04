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
        printf("%02x", array[i]);
    }
	printf("\n");
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

/**
 * Creates number^2 and stores output in result
 **/
void square(uint8_t* number, uint8_t* result)
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

    mod(huge, 2*ARRAY_LENGTH, result);
}

/**
 * Adds a + b and stores output in result
 **/
void add(uint8_t* a, uint8_t* b, uint8_t* result)
{
    int i = 0;
    for (i = 0; i < ARRAY_LENGTH; i++)
    {
        result[i] = a[i] ^ b[i];
    }
}

/**
 * Linear feedback shift register implements A=Ax
 **/
void lfsr(uint8_t* number)
{
    uint8_t x9, i, x78, x8, tmp = 0x00;

    x78 = number[0] & pattern[1];
    x8 = number[8] & pattern[7];
    x78 >>= 6;
    x9 = x78 ^ x8;
    x9 <<= 1;

    for(i = 0; i < ARRAY_LENGTH; i++)
    {
        if ((number[i] > 0x00) && (i > 0))
        {
            if ((0x80 & number[i]) > 0x00) number[i-1] += pattern[7];
        }
        number[i] = number[i] << 1;
    }
    tmp = number[8] & ~pattern[6]; // destroys 6. bit
	number[8] = tmp | x9;

	// x&78 is shifted to x^0
	// no need for destroying here because number[9] 7th bit is always 0 due to the shift
    number[9] = number[9] | x78;

	// 1. bit ever needs to be destroyed, the shift could move 1 in here
    number[0] = number[0] & ~pattern[0];
}

/**
 * Multiplies a * b and stores it in result.
 **/
void mult(uint8_t* a, uint8_t* b, uint8_t* result)
{
    uint8_t tmp = 128; // 2^7
    int i, j  = 0;

    for(i = 0; i < ARRAY_LENGTH; i++) 
    {
        for (j = 0; j < 8; j++)
        {
            if (b[i] & tmp)
            {
                add(result, a, result);
            }
            if ((i == ARRAY_LENGTH - 1) && (j == 7))
        	{
        		result[0] = result[0] & ~pattern[0]; // destroys 1 bit. why? does that make any sense?
        		break;
        	}
            lfsr(result);

            tmp = tmp >> 1;
        }
        tmp = 128;
    }
}

int isEqualTo(uint8_t needle, uint8_t * haystack)
{
    int i = 0;
    
    for (i = 0; i < ARRAY_LENGTH - 1; i++)
    {
        if (haystack[i] != 0x00) return 0;
    }
    if (haystack[ARRAY_LENGTH - 1] == needle)
    {
        return 1;
    }
    return 0;
}

void ellipticAddition(uint8_t* t9, uint8_t* b, uint8_t* t1, uint8_t* t2, uint8_t* t3, uint8_t* t4, uint8_t* t5, uint8_t* t6, uint8_t* R_x, uint8_t* R_y, uint8_t* R_z)
{
    //uint8_t t1[ARRAY_LENGTH];
    //uint8_t t2[ARRAY_LENGTH];
    //uint8_t t3[ARRAY_LENGTH];
    //uint8_t t4[ARRAY_LENGTH];
    //uint8_t t5[ARRAY_LENGTH];
    //uint8_t t6[ARRAY_LENGTH];
    uint8_t t7[ARRAY_LENGTH];
    uint8_t t8[ARRAY_LENGTH];
    //uint8_t t9[ARRAY_LENGTH];
    //zeroArray(t1,ARRAY_LENGTH);
    //zeroArray(t2,ARRAY_LENGTH);
    //zeroArray(t3,ARRAY_LENGTH);
    //zeroArray(t4,ARRAY_LENGTH);
    //zeroArray(t5,ARRAY_LENGTH);
    //zeroArray(t6,ARRAY_LENGTH);
    zeroArray(t7,ARRAY_LENGTH);
    zeroArray(t8,ARRAY_LENGTH);
    //zeroArray(t9,ARRAY_LENGTH);
    
    int flag = 1;
    
    if (!isEqualTo(1,t6)) flag = 2;
    
   /* t1 = P_x; // copy?
    t2 = P_y;
    t3 = P_z;
    t4 = Q_x;
    t5 = Q_y; */ // step 5
    
    //if (!isEqualTo(0, a))           //Remember 
    //{
    //    t9 = a;
    //}

    if (flag == 2)
    {
        //t6 = Q_z;
        mult(t6, t6, t7); // todo: replace with square?
        mult(t1, t7, t1);
        mult(t6, t7, t7);
        mult(t2, t7, t2);
    }
    mult(t3, t3, t7); // step 8
    mult(t4, t7, t8);
    add(t1, t8, t1);
    mult(t3, t7, t7);
    mult(t5, t7, t8);
    add(t2, t8, t2); // step 13
    
    if (isEqualTo(0, t1))
    {
        if (isEqualTo(0, t2))
        {
            // (0, 0, 0)
            return;
        }
        else
        {
            // (1, 1, 0)
            R_x[ARRAY_LENGTH - 1] = 0x01;
            R_y[ARRAY_LENGTH - 1] = 0x01;
            return;
        }
        
    }

    mult(t2, t4, t4); // step 15
    mult(t1, t3, t3);
    mult(t3, t5, t5);
    add(t4, t5, t4); // step 18
    mult(t3, t3, t5);
    mult(t4, t5, t7);
    
    if (flag == 2)
    {
        mult(t3, t6, t3);
    }
    
    add(t2, t3, t4); // step 22
    mult(t2, t4, t2);
    mult(t1, t1, t5);
    mult(t1, t5, t1); // step 25
    
   // if (!isEqualTo(0, a))             //a mame ine ako 0
    //{
        mult(t3, t3, t8);
        mult(t8, t9, t9);
        add(t1, t9, t1);
    //}
    
    add(t1, t2, t1); // step 27
    mult(t1, t4, t4);
    add(t4, t7, t2);
    R_x = t1;
    R_y = t2;
    R_z = t3;
}

/*****************************************************************************************************************************/
/*****************************************************************************************************************************/

int main(int argc, uint8_t** argv)
{
    uint8_t P_x[ARRAY_LENGTH];
    uint8_t P_y[ARRAY_LENGTH];
    uint8_t P_z[ARRAY_LENGTH];
    uint8_t Q_x[ARRAY_LENGTH];      
    uint8_t Q_y[ARRAY_LENGTH];
    uint8_t Q_z[ARRAY_LENGTH];
    uint8_t R_x[ARRAY_LENGTH];      
    uint8_t R_y[ARRAY_LENGTH];
    uint8_t R_z[ARRAY_LENGTH];  
    uint8_t a[ARRAY_LENGTH] = {0x4A,0x2E,0x38,0xA8,0xF6,0x6D,0x7F,0x4C,0x38,0x5F};      //Defying our EC
    uint8_t b[ARRAY_LENGTH] = {0x2C,0x75,0xA6,0x48,0x59,0x55,0x2F,0x97,0xC1,0x29};      //Defying our EC
	uint8_t temp[ARRAY_LENGTH];
	
	zeroArray(R_x,ARRAY_LENGTH);
	zeroArray(R_y,ARRAY_LENGTH);
	zeroArray(R_z,ARRAY_LENGTH);

    uint8_t result[ARRAY_LENGTH];
    zeroArray(result, ARRAY_LENGTH);

    P_z[ARRAY_LENGTH - 1] = 0x01;
    Q_z[ARRAY_LENGTH - 1] = 0x01;
    loadInput(P_x, P_y, Q_x, Q_y);
    
    ellipticAddition(a, b, P_x, P_y, P_z, Q_x, Q_y, Q_z, R_x, R_y, R_z);

	return 0;
}
