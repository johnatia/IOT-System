/****************************************************************************************/
/*	Author 					: 				John Atia Nafady							*/
/*	Date					: 				10 NOV 2020									*/	
/*	Version					: 				V01											*/	
/*																						*/
/*																						*/
/****************************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "USART_interface.h"
#include "STK_interface.h"

#include "ESP_interface.h"
#include "ESP_private.h"
#include "ESP_config.h"

void ESP_voidInit(void)
{
	u8 Local_u8Result = 0;
	//u8 Local_u8Response[100]={0};
	//u8 i = 0;

/*
	//Rest ESP8266
	while(Local_u8Result == 0)
	{
		//Sending AT Command
		MUSART1_voidTransmitString("AT+RST\r\n");
		Local_u8Result = ESP_u8ValidateCommand();
	}
	Local_u8Result = 0;
*/
	//Send AT Command
	//while(Local_u8Result == 0)
	//{
		//Sending AT Command
		MUSART1_voidTransmitString("AT\r\n");
		(void)ESP_u8ValidateCommand();
	//	Local_u8Result = ESP_u8ValidateCommand();
	//}
	//Local_u8Result = 0;

/*
	//Stop Echo
	while(Local_u8Result == 0)
	{
		//Disable Echo by sending ATE0 Command
		MUSART1_voidTransmitString((u8*)"ATE0\r\n");
		Local_u8Result = ESP_u8ValidateCommand();
	}
	Local_u8Result = 0;
*/
	//Set Station Mode
	//while(Local_u8Result == 0)
	//{
		MUSART1_voidTransmitString("AT+CWMODE=1\r\n");
		(void)ESP_u8ValidateCommand();
	//	Local_u8Result = ESP_u8ValidateCommand();
	//}
	//Local_u8Result = 0;
}

void ESP_voidConnectWifi(u8 *WifiName ,u8 *WifiPassword)
{
	u8 Local_u8Result = 0;
//	while(Local_u8Result == 0)
//	{
		MUSART1_voidTransmitString("AT+CWJAP_CUR=\"");
		MUSART1_voidTransmitString(WifiName);
		MUSART1_voidTransmitString("\",\"");
		MUSART1_voidTransmitString(WifiPassword);
		MUSART1_voidTransmitString("\"\r\n");
	//MUSART1_voidTransmitString("AT+CWJAB_CUR=\"orange-SpaceX\",\"johnnadamama333555777\"\r\n");
		(void)ESP_u8ValidateCommand();
		(void)ESP_u8ValidateCommand();
		(void)ESP_u8ValidateCommand();
	//	MSTK_voidSetBusyWait(3000000);
	//	Local_u8Result = ESP_u8ValidateCommand();
//	}

}

void ESP_voidConnectToServer(u8 *Copy_u8ProtocolMode , u8 *Copy_u8StaticIP , u8 *Copy_u8PortNumber)
{
	u8 Local_u8Result = 0;
	//while(Local_u8Result == 0)
	//{
		MUSART1_voidTransmitString("AT+CIPSTART=\"");
		MUSART1_voidTransmitString(Copy_u8ProtocolMode);
		MUSART1_voidTransmitString("\",\"");
		MUSART1_voidTransmitString(Copy_u8StaticIP);
		MUSART1_voidTransmitString("\",");
		MUSART1_voidTransmitString(Copy_u8PortNumber);
		MUSART1_voidTransmitString("\r\n");
		(void)ESP_u8ValidateCommand();
	//	Local_u8Result = ESP_u8ValidateCommand();
	//}
}

u8 ESP_u8GetDataFromServer(void)
{
	u8 Data[100] , i , Result;
	MUSART1_voidTransmitString("AT+CIPSEND=45\r\n");
	(void)ESP_u8ValidateCommand();
	MUSART1_voidTransmitString("GET http://smarthome.freeoda.com/status.txt\r\n");
	for(i=0; i<100; i++)
	{
		Data[i] = MUSART1_u8ReceiveChar();
		if(Data[i] == 255)
		{
			Data[i] = '\0';
			break;
		}
	}
	MUSART2_voidTransmitString(Data);

	if(Data[37] == '1')
	{
		Result = 1;
	}
	if(Data[37] == '0')
	{
		Result = 0;
	}

	return Result ;
}

u8 ESP_u8ValidateCommand(void)
{
	u8 Local_u8Response[100]={0} , Dummy = 0;
	u8 i = 0 , Result = 0;
	
	while(Dummy != 255)
	{
		Local_u8Response[i] = MUSART1_u8ReceiveChar();
		Dummy = Local_u8Response[i];
		if(Local_u8Response[i] == 255)		{Local_u8Response[i] = '\0';}
		i++;
	}

	/*
	 * is that not good to make while(1) inside my code?
	 		while(1)
				{
					Local_u8Response[i] = MUSART1_u8ReceiveChar();
					if(Local_u8Response[i] == 255)
					{
						Local_u8Response[i] = '\0';
						i = 0;
						break;
					}
					i++;
				}
	 */

	//Display the Response
	MUSART2_voidTransmitString(Local_u8Response);

	//Check if OK
	for(i=0; i<100; i++)
	{

		if( Local_u8Response[i] == 'O' )
		{
			if( Local_u8Response[i+1] == 'K' )
			{
				Result = 1;
				break;
			}
		}
	}
	
	return Result;
}
