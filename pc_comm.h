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

#define Q_SIZE (512)

/*!
 * \brief Type definition of a queue
 */
typedef struct
{
    uint8_t data[Q_SIZE];
    uint32_t head; ///< Index of the oldest data element 
    uint32_t tail; ///< Index of the next free space
    uint32_t size; ///< Number of elements in the queue
    
}queue_t;


void SendTemperatureActual(char);
void SendTemperatureReference(char);
void SendTimeSynqState(bool synqed);
void SendErrorMsg(char *);
void SendDebugMsg(char *);

#endif // PC_COMM_H
