/*
 * GPS test.cpp
 *
 * Created: 7/27/2019 3:22:26 PM
 * Author : Hp
 */ 

#include <avr/io.h>
#include "USART.h"
#include <util/delay.h>
#include <string.h>

void Send_String(char ar[]){
	int i;
	i=0;
	while(ar[i]!='\0'){
		USART_Transmit(ar[i]);
		i++;
	}
}


void Return_String(char *str){
	for(int i=0;i<100;i++){

		*str = USART_Receive();
		str++;
	}
	
}
char GPRMC[100];

void Get_gprmc(char *str){
	char tempstr[100];
	char *tempptr = str;
	for(int i=0;i<100;i++){
		tempstr[i] = *str;
		str++;
	}
	char *gprmc = strstr(tempstr,"GPRMC");
	int position = tempptr-gprmc;
	

	while(tempstr[position]!='$'){
		GPRMC[position] = tempstr[position];
		position++;
	}
	GPRMC[position]='\0';
	
}

int main(void)
{	USART_Init();
    /* Replace with your application code */
    while (1) 
    {	
		char str[100];
		
		Return_String(str);
		_delay_ms(5000);
		Get_gprmc(str);
		_delay_ms(1000);
		Send_String(GPRMC);
		
    }
}

