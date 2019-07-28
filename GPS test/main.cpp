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
	for(int i=0;i<200;i++){
		
		*str = USART_Receive();
		
		str++;
	}
	*str='\0';
	
}

	char GPRMC[100];
void return_gprmc(char *str){
	char temparr[200];

	for(int i=0;i<200;i++){
		temparr[i]=*str;
		str++;
		
	}

	char *loc = strstr(temparr,"GPRMC");

	
	int i=0;
	if(loc){
		while((*loc!='\n')){
			GPRMC[i]=*loc;
			//USART_Transmit(GPRMC[i]);
			i++;
			loc++;
		}
		GPRMC[i]='\0';

	}
	else{}
	
	
}



int main(void)
{	USART_Init();
    /* Replace with your application code */
    while (1) 
    {
		char str[200];
		
		Return_String(str);
		return_gprmc(str);
			Send_String(GPRMC);
			_delay_ms(1000);
			USART_Transmit('\n');
		
    }
}

