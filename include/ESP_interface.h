/****************************************************************************************/
/*	Author 					: 				John Atia Nafady							*/
/*	Date					: 				10 NOV 2020									*/	
/*	Version					: 				V01											*/	
/*																						*/
/*																						*/
/****************************************************************************************/

#ifndef _ESP_INTERFACE_H_
#define _ESP_INTERFACE_H_

void ESP_voidInit(void);
void ESP_voidConnectWifi(u8 *WifiName , u8 *WifiPassword);
void ESP_voidConnectToServer(u8 *Copy_u8ProtocolMode , u8 *Copy_u8StaticIP , u8 *Copy_u8PortNumber);
u8 	 ESP_u8GetDataFromServer(void);
u8 	 ESP_u8ValidateCommand(void);

#endif

