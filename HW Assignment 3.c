/* Name: Ahmed Abdul Monem Ahmed Radwan
 * BN: 5
 * Assignment 3
 *
 * main.c
 * Author: Ahmed Radwan
 *
 */

#define BUTTON_PIN 3
#define RED_PIN 5
#define GREEN_PIN 6
#define BLUE_PIN 7

#define RED_ON (GPIOB_BSRR = (1 << RED_PIN))
#define RED_OFF (GPIOB_BSRR = (1 << (RED_PIN + 16)))
#define GREEN_ON (GPIOB_BSRR = (1 << GREEN_PIN))
#define GREEN_OFF (GPIOB_BSRR= (1 << (GREEN_PIN + 16)))
#define BLUE_ON (GPIOB_BSRR = (1 << BLUE_PIN))
#define BLUE_OFF (GPIOB_BSRR = (1 << (BLUE_PIN + 16)))

#define GPIOB_ADDRESS 0x40020400
#define GPIOB_MODER (*((volatile unsigned long*)(GPIOB_ADDRESS + 0x00)))
#define GPIOB_OTYPER (*((volatile unsigned long*)(GPIOB_ADDRESS + 0x04)))
#define GPIOB_IDR (*((volatile unsigned long*)(GPIOB_ADDRESS + 0x10)))
#define GPIOB_ODR (*((volatile unsigned long*)(GPIOB_ADDRESS + 0x14)))
#define GPIOB_PUPDR (*((volatile unsigned long*)(GPIOB_ADDRESS + 0x0C)))
#define GPIOB_BSRR (*((volatile unsigned long*)(GPIOB_ADDRESS + 0x18)))

#define RCC_AHB1ENR (*((volatile unsigned long*)(0x40023800 + 0x30)))
int main(){
	RCC_AHB1ENR |= (0x1 << 1); // Enable clock for GPIOB
	// Configure button pin as input
	GPIOB_MODER &= ~(0x3 << (2 * BUTTON_PIN));
	GPIOB_OTYPER |= (0x1 << BUTTON_PIN);
	GPIOB_PUPDR |= (0x1 << (2 * BUTTON_PIN));

	// Configure RGB LED pins as outputs
	GPIOB_MODER |= (0x1 << (2 * RED_PIN)) | (0x1 << (2 * GREEN_PIN)) | (0x1 << (2 * BLUE_PIN)); 
	GPIOB_OTYPER &= ~((0x1 << RED_PIN) | (0x1 << GREEN_PIN) | (0x1 << BLUE_PIN));
	RED_OFF; GREEN_OFF; BLUE_OFF;

	int button_state = 0;
	int prev_button_state = 1;
	int color = 0;
	 while(1)
    {
        button_state = (GPIOB_IDR >> BUTTON_PIN) & 0x01;
        
        // Check for falling edge on button
        if(button_state == 0 && prev_button_state == 1)
        {
            for(int i = 0; i < 1000000; i++); // Delay
            
            // Change LED color
            color = (color + 1) % 8;

            switch(color)
            {
                case 0:
                    RED_OFF; GREEN_OFF; BLUE_OFF;
                    break;
                case 1:
                    RED_ON; GREEN_OFF; BLUE_OFF;
                    break;
                case 2:
                    RED_OFF; GREEN_ON; BLUE_OFF;
                    break;
                case 3:
                    RED_ON; GREEN_ON; BLUE_OFF;
                    break;
                case 4:
                    RED_OFF; GREEN_OFF; BLUE_ON;
                    break;
                case 5:
                    RED_ON; GREEN_OFF; BLUE_ON;
                    break;
                case 6:
                    RED_OFF; GREEN_ON; BLUE_ON;
                    break;
                case 7:
                    RED_ON; GREEN_ON; BLUE_ON;
                    break;
            }
        }
        
        prev_button_state = button_state;
    }


	return 0;
}



