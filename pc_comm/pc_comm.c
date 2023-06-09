/*! ***************************************************************************
 *
 * \brief     Implementation of the pc communication with uart
 * \file      pc_comm.c
 * \author    Jeroen Wijnands
 * \date      May 2023
 *
 * \copyright 
 *
 *
 *****************************************************************************/
 
/********************************************************************/
/*Includes																													*/
/********************************************************************/
#include "pc_comm.h"

//#define DEBUG


/********************************************************************/
/*Variable defenition																								*/
/********************************************************************/
datetime_t pcDateTime;

bool _newUnixTimeAvailable = false;
char prevDbgMsg[255] = "";

/********************************************************************/
/*Private function prototyping																			*/
/********************************************************************/
static void getValue(const char* , char* );
static void getCommand(const char* , char* );
static bool isNotEqual(char* str1, char* str2);
static int UnixTime = 0;
static int RefTemp = 0;


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
			RTC_HAL_ConvertSecsToDatetime(&UnixTime, &pcDateTime);
			_newUnixTimeAvailable = true;		
			
		} 
		else if (strcmp(cmd, "REF_TEMP") == 0) {
			RefTemp = atoi(val);
		} 

		else if (strlen(cmd) >0)
		{
			char msg[80];
			
			sprintf(msg,"Unknown cmd:%s val:%s\r\n\0",cmd,val);
			
			SendErrorMsg(msg);
		}
		#ifdef DEBUG
			SendDebugMsg(buff);
		#endif
	}
	else
	{
		buff[0] = '\0';
	}
	
}

void SendTemperatureActual(float val)
{
	char msg[80] = "\0";
	
	sprintf(msg,"ACT_TEMP:%.1f|\r\n\0",val);

	uart0_send_string(msg);
}
	
void SendTemperatureReference(int val)
{
	char msg[80] = "\0";

	sprintf(msg,"ACT_REF_TEMP:%d|\r\n\0",val);

	uart0_send_string(msg);
}
	
void SendTimeSynqState(bool synqed)
{
	char msg[80] = "\0";
	synqed ? strcpy(msg,"SYNC:1|\r\n\0"):strcpy(msg,"SYNC:0|\r\n\0");
	
	uart0_send_string(msg);
}
	
void SendErrorMsg(char* val)
{
	char msg[80];

	sprintf(msg,"ERROR:%s|\r\n\0",val);

	uart0_send_string(msg);
}
	
void SendDebugMsg(char* str)
{
	char msg[255];
	
	sprintf(msg,"%s\r\n",str);
	
	if(isNotEqual(str,prevDbgMsg))	
	{
		sprintf(prevDbgMsg,msg);
		uart0_send_string(msg);
	}
}

signed int GetUnixTime(void)
{
	return UnixTime;
}


bool newUnixTimeAvailable()
{	
	return _newUnixTimeAvailable;
}

void ProcessedNewUnixTime(bool){
	_newUnixTimeAvailable = false;
	SendTimeSynqState(true);
}
	

void SetReferenceTemperature(int value)
{
	RefTemp = value;
}

int GetReferenceTemperature(void)
{
	return RefTemp;
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

static bool isNotEqual(char* str1, char* str2)
{
	
	bool nEq = false;
	int i = 0;
	
	for(i=0; i<16; i++)
	{		
		if(str1[i] != str2[i])
		{
			nEq = true;
			break;
		}	
	}
	return nEq;
}

/********************************************************************/
/*END																																*/
/********************************************************************/

