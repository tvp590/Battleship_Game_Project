/*

		NAME 		 : TIRTH V PATEL
		SID 		 : ********
		COURSE 		 : ENSE 352
		PROJECT NAME : BATTLESHIP GAME
		DEVICES USED : BREADBOARD, STM32 NUCLEO BOARD, LEDS,RESISTORS , SWTICHES, WIRES.

*/

#include "../include/battleship.h"
//#include <iostream>
#include <string>
#include<cstring>
#include <vector>
#ifdef NO_HARDWARE
#include "../include/io_hw.h"
#else
#include "../include/io.h"
#endif
 

#include "stm32f10x.h"

using namespace std;


static struct Vessel vessels[5];



/*************************************************************************
FUNCTION DECLARATIONS PART
**************************************************************************/
void configureClocks(void);																
void configureIO(void);																		
void turnonLED(int);																			
int Insert(void);
void IsbuttonPressed(void);
void Delay(void);
void setupShips(void);											
int attack(Location location,	vector <string> &sunkboats);
bool checkInputs(Location checkTarget);
/*************************************************************************/




/********************   MAIN FUNCTION  ************************************/

int main()
{
		configureClocks();
 		configureIO();
	
		setupShips();

	
		bool gameplay = true;
		vector <string> allboats;
    struct Location target;
		
		int result = 7;    //decalring as an initial value 
		turnonLED(result);
			while(gameplay)
			{
					
									turnonLED(result);
									Delay();
									IsbuttonPressed();														// waiting untill button is pressed
									target.r = Insert();
									Delay();
				
									IsbuttonPressed();															// waiting untill button is pressed
									target.c = Insert();
								
							
							if(checkInputs(target)){
								 result = attack(target,allboats);
									turnonLED(result);
										Delay();													// to blink LED light
								if(allboats.size() == 5){
										result = 9;
										turnonLED(result);
										gameplay = false;
								}
							}
							else{
								result = 33;
								turnonLED(result);
								Delay();
								continue;											
							}
					}
					
    return 0;
}




/*********************************************************************************
FUNCTION NAME : configureClocks(void)
FUNCTION WORK : The following function is responsible to turn on the clock
								for the port A, Port B , Port C

**********************************************************************************/
void configureClocks(void){
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN |   RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN ;
}  




/**********************************************************************************
FUNCTION NAME : configureIO(void)
FUNCTION WORK : The following function is responsible to set configur bits 
								and mode bits for pins being used on port A, Port B, Port C

Values				: The following fucnction sets 00 as cnf (configure bits)
								which means General purpose output push-pull.
								and sets 11 as mode bits which means=>Output mode, 
																											max speed 50 MHz.  
								
						=> Input ports are already in input mode and floating input state
							which requires no external bit setting.

***********************************************************************************/
void configureIO(void)
{
	
	// FOR OUTPUT LEDS			
				//port A pin 0
				GPIOA->CRL |= GPIO_CRL_MODE0_0; 															
				GPIOA->CRL &=  ~GPIO_CRL_CNF0;																
				
				//port A pin 1
				GPIOA->CRL |= GPIO_CRL_MODE1_0;																 
				GPIOA->CRL &= ~GPIO_CRL_CNF1;																
				
				// port A pin4
				GPIOA->CRL |= GPIO_CRL_MODE4_0;														 
				GPIOA->CRL &= ~GPIO_CRL_CNF4 ;            							
				
					// port A pin5
				GPIOA->CRL |= GPIO_CRL_MODE5_0;														 
				GPIOA->CRL &= ~GPIO_CRL_CNF5 ; 
	
					// port A pin6
				GPIOA->CRL |= GPIO_CRL_MODE6_0;														 
				GPIOA->CRL &= ~GPIO_CRL_CNF6 ; 
			
					// port A pin 9
				GPIOA->CRH |= GPIO_CRH_MODE9_0;														 
				GPIOA->CRH &= ~GPIO_CRH_CNF9 ;            							
				
					// port c pin 7
				GPIOC->CRL |= GPIO_CRL_MODE7_0;														 
				GPIOC->CRL &= ~GPIO_CRL_CNF7 ;            							
				
					// port A pin 8
				GPIOA->CRH |= GPIO_CRH_MODE8_0;														 
				GPIOA->CRH &= ~GPIO_CRH_CNF8 ;            							
				
				
				
				// PORT B pin0
					GPIOB->CRL |= GPIO_CRL_MODE0_0;
					GPIOB->CRL &= ~GPIO_CRL_CNF0;    
		
			// port c pin 1
				GPIOC->CRL |= GPIO_CRL_MODE1_0; 															
				GPIOC->CRL &=  ~GPIO_CRL_CNF1;																
				
				//port c pin 1
			//	GPIOC->CRL |= GPIO_CRL_MODE1_0;																 
				//GPIOC->CRL &= ~GPIO_CRL_CNF1;	
				
	// FOR INPUTS 
				//PORT B PIN 4																	
				//PORT B PIN6
				//PORT B PIN 8
				//PORT B PIN9
				
}




/**********************************************************************************
FUNCTION NAME : IsbuttonPressed(void)
FUNCTION WORK : The following function is responsible to check if button is pressed.
Button        : Port C pin 13 (blue button on STM 32 nucleo board)
Return Value 	: boolean type. 
***********************************************************************************/


void IsbuttonPressed(void){
		bool input = false;
		int result = 10;
		turnonLED(result);
	while(input == false)
	{	
			if((GPIOC->IDR & GPIO_IDR_IDR13)==0x0){
						Delay();
							input = true; 			
			}
	}
}




/**********************************************************************************
FUNCTION NAME : Delay(void)
FUNCTION WORK : The following function is used to creat some delay between user inputs
								and outputs.
***********************************************************************************/

void Delay(void)
{	
	unsigned volatile int i,j;
	for( i = 0; i<3000;i++)
	{
		for( j =0;j<3000;j++)
		{	}
	}
}





/**********************************************************************************
FUNCTION NAME : Insert(void)
FUNCTION WORK :This function is used to read the user input through dip switches 
							 .The user input is in binary pattern and this function convert the 
							binary pattern into decimal value for ship location.
							
***********************************************************************************/


int Insert(){
		int switch_0 = 0;
		int switch_1 = 0;
		int switch_2 = 0;
		int switch_3 = 0;
	
		int switch0 = 0;
	 int switch1 = 0;
	 int switch2 = 0;
	 int switch3 = 0;
	//	int portB_idr = GPIOB->IDR; 
		int Calculate = 0;
	
		switch_0 =	GPIOB->IDR & GPIO_IDR_IDR4 ;
		switch_1 = GPIOB->IDR & GPIO_IDR_IDR6;
		switch_2 = GPIOB->IDR & GPIO_IDR_IDR8;
		switch_3 = GPIOB->IDR & GPIO_IDR_IDR9;
	
/*		switch_0 =	GPIOB->IDR & GPIO_IDR_IDR9 ;
		switch_1 = GPIOB->IDR & GPIO_IDR_IDR8;
		switch_2 = GPIOB->IDR & GPIO_IDR_IDR6;
		switch_3 = GPIOB->IDR & GPIO_IDR_IDR4;*/
	
		if(switch_0!=0x0){switch0 = 1;} 
		else {switch0 =0;}
		
		if(switch_1!=0x0){switch1 = 1;}
		else {switch1 =0;}
		
		if(switch_2!=0x0){switch2 = 1;} 
		else {switch2 =0;}
		
		if(switch_3!=0x0){switch3 = 1;} 
		else {switch3 =0;}

		Calculate = (8* switch0) + (4*switch1) +  (2*switch2) +   switch3;
	 
	return Calculate;
		
}


/**********************************************************************************
FUNCTION NAME : turnonLED(int)
FUNCTION WORK : This function is used to turnon the respective Led after the
							 specific event occurs.
output 				: 
								Error Case : first two LED will be on. (two Green LED)
								Waiting for input : first LED will be on and stays on unless you enter 
																	 value for Row and Column.(Green LED)
								Miss case 				: second led will be on. (Green LED)
								Hit case 					:  Third Led will be turn on (Red LED) 
								Hit and Sunk Case : Fourth LED will be turn on (RED LED)
							ALL sunk (Game over):  All first Four LEDs stays on.

						=> The other set of 5 Leds will be turn on whenever a ship is sunk 
							and stays on until game over.
***********************************************************************************/

void turnonLED(int outcome)
{
		switch(outcome){
			case 33 : //for error in input
							GPIOA->ODR |= GPIO_ODR_ODR0 ;
							GPIOA->ODR |= GPIO_ODR_ODR1 ;
							GPIOA->ODR &= ~GPIO_ODR_ODR4;
							GPIOB->ODR &= ~GPIO_ODR_ODR0 ;
		
							Delay();
								break;
							
			case 10 : //for waiting for input
								GPIOA->ODR &= ~GPIO_ODR_ODR4;
							  GPIOB->ODR &= ~GPIO_ODR_ODR0 ;
								GPIOA->ODR &= ~GPIO_ODR_ODR1;
								GPIOA->ODR |= GPIO_ODR_ODR0 ;
								
								Delay();
								break;
			
			
			case -1: 	//when missed  
								GPIOA->ODR &= ~GPIO_ODR_ODR0 ;
								GPIOA->ODR &= ~GPIO_ODR_ODR4;
								GPIOB->ODR &= ~GPIO_ODR_ODR0 ;
								GPIOA->ODR |= GPIO_ODR_ODR1 ;
								
								Delay();
								break;
			
			
			case 0: //when hit
								GPIOA->ODR &= ~GPIO_ODR_ODR1;
								GPIOB->ODR &= ~GPIO_ODR_ODR0 ;
								GPIOA->ODR &= ~GPIO_ODR_ODR0 ;
								GPIOA->ODR |= GPIO_ODR_ODR4 ;
								Delay();
								break;
			
			case 1: //when one ship sunk
								GPIOA->ODR &= ~GPIO_ODR_ODR0 ;
								GPIOA->ODR &= ~GPIO_ODR_ODR1;
								GPIOA->ODR &= ~GPIO_ODR_ODR4;
								GPIOB->ODR |= GPIO_ODR_ODR0 ;
								Delay();
								break;
			
			case 9 : //when all ships sunk and game over
								GPIOA->ODR |= GPIO_ODR_ODR0 ;
								GPIOA->ODR |= GPIO_ODR_ODR1 ;
								GPIOA->ODR |= GPIO_ODR_ODR4 ;
								GPIOB->ODR |= GPIO_ODR_ODR0 ;
								Delay();
								break;
			
			case 7 :
							GPIOA->ODR |= GPIO_ODR_ODR5 ;
							break;
			
			case 15 :GPIOA->ODR |= GPIO_ODR_ODR6 ;  break;
			case 16 : GPIOA->ODR |= GPIO_ODR_ODR8 ; break;
			case 17 : GPIOA->ODR |= GPIO_ODR_ODR9 ; break;
			case 18:  GPIOC->ODR |= GPIO_ODR_ODR7 ; break;
			case 19 :  GPIOC->ODR |= GPIO_ODR_ODR1; 
								//GPIOA->ODR |= GPIO_ODR_ODR6 ;
						break;
			default :
							break;
		}

}


/**********************************************************************************
FUNCTION NAME : setupShips(void)
FUNCTION WORK :This function is used to set ships in different location inside
								a 10 X 10 grid. 
							
***********************************************************************************/

void setupShips(void)
{
	strcpy(vessels[0].name, "aircraftCarrier");
	vessels[0].sunk = false;
	vessels[0].length = 5;
	vessels[0].hits = 0;
	vessels[0].vesselLocations[0].c = 0;
	vessels[0].vesselLocations[0].r = 2;
	vessels[0].vesselLocations[1].c = 1;
	vessels[0].vesselLocations[1].r = 2;
	vessels[0].vesselLocations[2].c = 2;
	vessels[0].vesselLocations[2].r = 2;
	vessels[0].vesselLocations[3].c = 3;
	vessels[0].vesselLocations[3].r = 2;
	vessels[0].vesselLocations[4].c = 4;
	vessels[0].vesselLocations[4].r = 2;

	strcpy(vessels[1].name, "Battleship");
	vessels[1].sunk = false;
	vessels[1].length = 4;
	vessels[1].hits = 0;
	vessels[1].vesselLocations[0].c = 4;
	vessels[1].vesselLocations[0].r = 3;
	vessels[1].vesselLocations[1].c = 5;
	vessels[1].vesselLocations[1].r = 3;
	vessels[1].vesselLocations[2].c = 6;
	vessels[1].vesselLocations[2].r = 3;
	vessels[1].vesselLocations[3].c = 7;
	vessels[1].vesselLocations[3].r = 3;

	
	
	strcpy(vessels[2].name, "Submarine");
	vessels[2].sunk = false;
	vessels[2].length = 3;
	vessels[2].hits = 0;
	vessels[2].vesselLocations[0].c = 7;
	vessels[2].vesselLocations[0].r = 6;
	vessels[2].vesselLocations[1].c = 7;
	vessels[2].vesselLocations[1].r = 7;
	vessels[2].vesselLocations[2].c = 7;
	vessels[2].vesselLocations[2].r = 8;
	

	strcpy(vessels[3].name, "Destroyer");
	vessels[3].sunk = false;
	vessels[3].length = 3;
	vessels[3].hits = 0;
	vessels[3].vesselLocations[0].c = 4;
	vessels[3].vesselLocations[0].r = 8;
	vessels[3].vesselLocations[1].c = 5;
	vessels[3].vesselLocations[1].r = 8;
	vessels[3].vesselLocations[2].c = 6;
	vessels[3].vesselLocations[2].r = 8;
;

	strcpy(vessels[4].name, "Patrol Boat");
	vessels[4].sunk = false;
	vessels[4].length = 2;
	vessels[4].hits = 0;
	vessels[4].vesselLocations[0].c = 9;
	vessels[4].vesselLocations[0].r = 5;
	vessels[4].vesselLocations[1].c = 9;
	vessels[4].vesselLocations[1].r = 6;
	

	
	
}


/***********************************************************************************************
FUNCTION NAME : setupShips(struct , vector)
FUNCTION WORK :This function will check that user entered location has any part 
							of any ship. if it encounters any part of a ship then it will return hit (0 as hit)
							if not found anything on the entered location, it will return -1 (-1 as miss)
							and if hit and sunk then it will return 1.

							this function keeps track about the previously hit location and if user entered 
							again those location the function will not increament the hits of the specific vessel
							which prevents from early sunk even thoungh it is not.
							
*************************************************************************************************/



int attack(Location location,	vector <string> &sunkboats)
{
	unsigned int i;
	unsigned int j;
	int index = 0;
	
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < vessels[i].length; j++)
		{
			if ((location.c == vessels[i].vesselLocations[j].c) && (location.r == vessels[i].vesselLocations[j].r))
			{
		
				for (int k = 0; k<5 ; k++ )
				{
					if((vessels[i].alreadyHit[k].c ==  location.c ) && (vessels[i].alreadyHit[k].r ==location.r))
					{
						return 0;
					}
				}
				while(index<5)
				{	
					if((vessels[i].alreadyHit[index].c==NULL) &&  (vessels[i].alreadyHit[index].r == NULL))
					{
						break;
					}
					index++;
				}
				vessels[i].hits++;														// for hit 
				vessels[i].alreadyHit[index].c= location.c;
				vessels[i].alreadyHit[index].r= location.r; 
				
				
				
				if (vessels[i].hits == vessels[i].length)
				{
						vessels[i].sunk = true;																	//when hit and sunk
            sunkboats.push_back(vessels[i].name);
						int value = 15;
						int temp =0;
						while(temp < sunkboats.size())
						{
							turnonLED(value);
							value++;
							temp++;
						}
					return 1;
				}
				else
				{
					return 0;
				}
			}
		}
	}
    	return -1;							//when missed

}


/**********************************************************************************
FUNCTION NAME : checkInputs(struct)
FUNCTION WORK :This function checks the error in user inputs. 
							
***********************************************************************************/

bool checkInputs(Location checkTarget)
{
	if(checkTarget.c>=10 || checkTarget.c<0 || checkTarget.r>=10 || checkTarget.r<0)
	{
		return false;										//if wrong input entered
	}
	return true;				
}

