/****************************************************************************************/
/*	Author 					: 				John Atia Nafady							*/
/*	Date					: 				10 NOV 2020									*/
/*	Version					: 				V01											*/
/*																						*/
/*																						*/
/****************************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"
#include "USART_interface.h"
#include "ESP_interface.h"

void main(void)
{
	u8 x , i = 0 , Dummy = 0;
	u8 Local_u8Response[100] = {0};
	u8 SSID_PASSWORD[] = "AT+CWJAP_CUR=\"orange-SpaceX\",\"johnnadamama333555777\"\r\n";

	//System Clock Initialization
	RCC_voidInitSysClock();

	//Enable System Clock for GPIOA
	RCC_voidEnableClock(RCC_APB2, 2);

	//Enable System Clock for USART1
	RCC_voidEnableClock(RCC_APB2, 14);
	//Enable System Clock for USART1
	RCC_voidEnableClock(RCC_APB1, 17);

	//Enable PA0 as OUTPUT
	gPIO_voidSetPinDir(GPIOA , PIN0 , 0b0011);
	//Enable Tx1 PA9
	gPIO_voidSetPinDir(GPIOA , PIN9 , 0b1011);
	//Enable Rx1 PA10
	gPIO_voidSetPinDir(GPIOA , PIN10 , IN_FLOATING);
	//Enable Tx2 PA2
	gPIO_voidSetPinDir(GPIOA , PIN2 , 0b1011);
	//Enable Rx2 PA3
	gPIO_voidSetPinDir(GPIOA , PIN3 , IN_FLOATING);

	//SysTick Initialization
	MSTK_voidInit();
	//USART1 Initialization
	MUSART1_voidInit();
	//USART2 Initialization
	MUSART2_voidInit();

	MUSART2_voidTransmitString("Wait 3 sec\n");
	//Wait 1s
	MSTK_voidSetBusyWait(3000000);

	MUSART2_voidTransmitString("ESP8266 Initialization \n");

	//ESP8266 Initialization
	ESP_voidInit();
	MUSART2_voidTransmitString("Initialization Done! \n");
	//Connect to Internet using WIFI
	MSTK_voidSetBusyWait(1000000);
	//MUSART1_voidTransmitString("AT+CWJAP_CUR=\"orange-SpaceX\",\"johnnadamama333555777\"\r\n");
	//ESP_voidConnectWifi("orange-SpaceX","johnnadamama333555777");

	MUSART1_voidTransmitString(SSID_PASSWORD);
	(void)ESP_u8ValidateCommand();
	(void)ESP_u8ValidateCommand();
	(void)ESP_u8ValidateCommand();
	MSTK_voidSetBusyWait(5000000);


	while(1)
	{
		//Connect to Server
		ESP_voidConnectToServer("TCP", "162.253.155.227" ,"80");
		//Read the State from Server
		x = ESP_u8GetDataFromServer();
		MUSART2_voidTransmitString("Data = ");
		MUSART2_voidTransmitChar(x);
		MUSART2_voidTransmitChar('\n');
		gPIO_voidSetPinValue(GPIOA, 0, x);
		//Wait 1s
		//MSTK_voidSetBusyWait(1000000);

	}
}


/*
MUSART1_voidTransmitString("AT+RST\r\n");
while(Dummy != 255)
{
	Local_u8Response[i] = MUSART1_u8ReceiveChar();
	Dummy = Local_u8Response[i];
	if(Local_u8Response[i] == 255)		{Local_u8Response[i] = '\0';}
	i++;
}
Dummy = 0;		i = 0;
//Display the Response
MUSART2_voidTransmitString(Local_u8Response);
voidResetArray(Local_u8Response);
//MSTK_voidSetBusyWait(2000000);
*/
/*
//Send AT Command
MUSART1_voidTransmitString("AT\r\n");
while(Dummy != 255)
{
	Local_u8Response[i] = MUSART1_u8ReceiveChar();
	Dummy = Local_u8Response[i];
	if(Local_u8Response[i] == 255)		{Local_u8Response[i] = '\0';}
	i++;
}
Dummy = 0;		i = 0;
//Display the Response
MUSART2_voidTransmitString(Local_u8Response);
voidResetArray(Local_u8Response);
//MSTK_voidSetBusyWait(100000);

//AT+CWMODE=1
MUSART1_voidTransmitString("AT+CWMODE=1\r\n");
while(Dummy != 255)
{
	Local_u8Response[i] = MUSART1_u8ReceiveChar();
	Dummy = Local_u8Response[i];
	if(Local_u8Response[i] == 255)		{Local_u8Response[i] = '\0';}
	i++;
}
Dummy = 0;		i = 0;
//Display the Response
MUSART2_voidTransmitString(Local_u8Response);
voidResetArray(Local_u8Response);
//MSTK_voidSetBusyWait(1000000);
//AT+CWJAP_CUR="orange-SpaceX","johnnadamama333555777"
MUSART1_voidTransmitString("AT+CWJAP_CUR=\"orange-SpaceX\",\"johnnadamama333555777\"\r\n");
while(Dummy != 255)
{
	Local_u8Response[i] = MUSART1_u8ReceiveChar();
	Dummy = Local_u8Response[i];
	if(Local_u8Response[i] == 255)		{Local_u8Response[i] = '\0';}
	i++;
}
Dummy = 0;		i = 0;
//Display the Response
MUSART2_voidTransmitString(Local_u8Response);
voidResetArray(Local_u8Response);
MSTK_voidSetBusyWait(5000000);
*/


/*
		//AT+CIPSTART="TCP","162.253.155.227",80
		MUSART1_voidTransmitString("AT+CIPSTART=\"TCP\",\"162.253.155.227\",80\r\n");
		while(Dummy != 255)
		{
			Local_u8Response[i] = MUSART1_u8ReceiveChar();
			Dummy = Local_u8Response[i];
			if(Local_u8Response[i] == 255)		{Local_u8Response[i] = '\0';}
			i++;
		}
		Dummy = 0;		i = 0;
		//Display the Response
		MUSART2_voidTransmitString(Local_u8Response);
		voidResetArray(Local_u8Response);
		//MSTK_voidSetBusyWait(8000000);

		//AT+CIPSEND=45
		MUSART1_voidTransmitString("AT+CIPSEND=45\r\n");
		while(Dummy != 255)
		{
			Local_u8Response[i] = MUSART1_u8ReceiveChar();
			Dummy = Local_u8Response[i];
			if(Local_u8Response[i] == 255)		{Local_u8Response[i] = '\0';}
			i++;
		}
		Dummy = 0;		i = 0;
		//Display the Response
		MUSART2_voidTransmitString(Local_u8Response);
		voidResetArray(Local_u8Response);
		//MSTK_voidSetBusyWait(1000000);

		//GET http://smarthome.freeoda.com/status.txt
		MUSART1_voidTransmitString("GET http://smarthome.freeoda.com/status.txt\r\n");
		while(Dummy != 255)
		{
			Local_u8Response[i] = MUSART1_u8ReceiveChar();
			Dummy = Local_u8Response[i];
			if(Local_u8Response[i] == 255)		{Local_u8Response[i] = '\0';}
			i++;
		}
		Dummy = 0;		i = 0;
		//Display the Response
		MUSART2_voidTransmitString(Local_u8Response);
		voidResetArray(Local_u8Response);
		//MSTK_voidSetBusyWait(1000000);

		*/
