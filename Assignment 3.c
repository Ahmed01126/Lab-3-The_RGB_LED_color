/* Name: Ahmed Abdul Monem Ahmed Radwan
 * BN: 5
 * Lab 3: Assignment 1
 *
 * main.c
 * Author: Ahmed Radwan
 *
 */

#define GPIOA_ADDRESS 0x40020000
#define BIT 0x00
#define GPIOA_MODER (*((volatile unsigned long*)(GPIOA_ADDRESS + 0x00)))
#define GPIOA_OTYPER (*((volatile unsigned long*)(GPIOA_ADDRESS + 0x04)))
#define GPIOA_ODR (*((volatile unsigned long*)(GPIOA_ADDRESS + 0x14)))

#define RCC_AHB1ENR (*((volatile unsigned long*)(0x40023800 + 0x30)))
int main(){
	RCC_AHB1ENR |= (0x1 << BIT); // Enable clock for GPIOA

	GPIOA_MODER &= ~(0x3 << 2*BIT); // Clearing the 0th bit
	GPIOA_MODER |= (0x1 << 2*BIT); // Setting the 0th bit

	GPIOA_OTYPER &= ~(0x1 << BIT); // Clearing the 0th bit
	GPIOA_ODR |= (0x1 << BIT); // Setting the 0th bit

	while (1)
	{
		GPIOA_ODR |= (0x1 << BIT); // Setting the 0th bit
		for (int i = 0; i < 1000000; i++);
		GPIOA_ODR &= ~(0x1 << BIT); // Clearing the 0th bit
		for (int i = 0; i < 1000000; i++);
		/* 
		ANOTHER WAY TO DO IT
		GPIOA_ODR ^= (0x1 << BIT); // Toggle the 0th bit
		for (int i = 0; i < 1000000; i++); // Delay
		*/
	}




	return 0;
}



