/*! ***************************************************************************
 *
 * \brief     pc communicatio module
 * \file      pc_comm.c
 * \author    Jeroen Wijnands
 * \date      May 2023
 *
 * \copyright 
 *
 *
 *****************************************************************************/
#include "pc_comm.h"


void pc_comm_init(void)
{
	uart0_init();
	uart0_send_string("Starting Advanced clock\r\n");
}

void processCommData(void)
{
	char buff[255], cmd[25],val[10];
	int i = 0;
	int dataSize = 0;
	
	dataSize = uart0_num_rx_chars_available(); 
	if(	dataSize > 0)
	{
		for(i = 0; i < dataSize; i++)
		{
				 buff[i] = uart0_get_char();
		}


		getCommand(buff,cmd);
		getValue(buff,val);

		if (strcmp(cmd, "UNIX") == 0) {
			UnixTime = atoi(val);
		} 
		else if (strcmp(cmd, "REF_TEMP") == 0) {
			RefTemp = atoi(val);
		} 

		else if (strlen(cmd) >0)
		{
			char msg[80];
			strcpy(msg, "cmd:");
			strcat(msg, cmd);
			strcpy(msg, "val:");
			strcat(msg, val);
			SendErrorMsg(msg);
		}

		SendDebugMsg(buff);
	}
	else
	{
		buff[0] = '\0';
	}
	
}

void SendTemperatureActual(int val)
{
	char msg[80];
	char sVal[5];
	sprintf(sVal, "%d", val);
	
	strcpy(msg, "ACT_TEMP:");
	strcat(msg, sVal);
	strcat(msg, "|\r\n");	

	uart0_send_string(msg);
}
	
void SendTemperatureReference(int val)
{
	char msg[80];
	char sVal[5];
	sprintf(sVal, "%d", val);
	
	strcpy(msg, "ACT_REF_TEMP:");
	strcat(msg, sVal);
	strcat(msg, "|\r\n");	

	uart0_send_string(msg);
}
	
void SendTimeSynqState(bool synqed)
{
	synqed ? uart0_send_string("SYNC:1|"):uart0_send_string("SYNC:0|");
}
	
void SendErrorMsg(char* val)
{
	char msg[80];
	strcpy(msg, "ERROR:");
	strcat(msg, val);
	strcat(msg, "|");	

	uart0_send_string(msg);
}
	
void SendDebugMsg(char* str)
{
	char msg[255];
	
	strcat(msg, str);
	strcat(msg, "|\r\n");	
	
	uart0_send_string(str);
}

signed int GetUnixTime(void)
{
	return UnixTime;
}

/***********************************************/
/*Helpers																			 */
/***********************************************/

static void getCommand(const char* source, char* destination)
{
    size_t length = strcspn(source, ":");  // Find the length until the first occurrence of ':'
    strncpy(destination, source, length);  // Copy the substring to the destination array
    destination[length] = '\0';  // Add the null terminator to the destination array
}
	
static void getValue(const char* source, char* destination) {
    const char* start = strchr(source, ':');  // Find the first occurrence of ':'
    const char* end = strchr(source, '|');    // Find the first occurrence of '|'

    if (start && end && end > start) {
        size_t length = end - start - 1;  // Calculate the length of the substring between ':' and '|'
        strncpy(destination, start + 1, length);  // Copy the substring to the destination array
        destination[length] = '\0';  // Add the null terminator to the destination array
    } 
		else 
		{
        destination[0] = '\0';  // Empty string if the delimiters are not found or in the wrong order
    }
}
