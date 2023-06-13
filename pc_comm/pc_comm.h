/*! ***************************************************************************
 *
 * \brief     Implementatioon of a queue
 * \file      queue.h
 * \author    Jeroen Wijnands
 * \date      May 2023
 *
 * \copyright AdvancedClock project
 *
 *****************************************************************************/
#ifndef PC_COMM_H
#define PC_COMM_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datetime.h"

#include "uart0.h"

#define Q_SIZE (512)

/*!
 * \brief Type definition of a queue
 */
 

//CONSTRUCTOR
void pc_comm_init(void);

//SET
void SendTemperatureActual(int);
void SendTemperatureReference(int);
void SendTimeSynqState(bool synqed);
void SendErrorMsg(char *);
void SendDebugMsg(char *);

//GET
void processCommData(void);
signed int GetUnixTime(void);
int GetReferenceTemperature(void);
void GetDateTime(datetime_t * datetime);


//PRIVATE
static void getValue(const char* , char* );
static void getCommand(const char* , char* );
static int UnixTime = 0;
static int RefTemp = 0;
#endif // PC_COMM_H
