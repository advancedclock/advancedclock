/*! ***************************************************************************
 *
 * \brief     Low level driver for the 16x2 LCD
 * \file      lcd.h
 * \author    Hugo Arends, edit by JWI and Anthony
 * \date      June 2021
 *
 * \copyright 2021 HAN University of Applied Sciences. All Rights Reserved.
 *            \n\n
 *            Permission is hereby granted, free of charge, to any person
 *            obtaining a copy of this software and associated documentation
 *            files (the "Software"), to deal in the Software without
 *            restriction, including without limitation the rights to use,
 *            copy, modify, merge, publish, distribute, sublicense, and/or sell
 *            copies of the Software, and to permit persons to whom the
 *            Software is furnished to do so, subject to the following
 *            conditions:
 *            \n\n
 *            The above copyright notice and this permission notice shall be
 *            included in all copies or substantial portions of the Software.
 *            \n\n
 *            THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *            EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *            OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *            NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *            HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *            WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *            FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *            OTHER DEALINGS IN THE SOFTWARE.
 *
 *****************************************************************************/
#ifndef LCD_H
#define LCD_H

#include <MKL25Z4.h>

#include <stdbool.h>

/// \name Defines for the size of the LCD
/// \{

#define LCD_COLUMNS  16   ///< Number of LCD columns in characters
#define LCD_ROWS      2   ///< Number of LCD rows

/// \}

// ----------------------------------------------------------------------------
// LCD interface hardware mappings
/// \name DB4
/// \{
#define PIN_DB4_PORT         PORTC
#define PIN_DB4_PT           PTC
#define PIN_DB4_SHIFT        (0)
#define PIN_DB4              (1 << PIN_DB4_SHIFT)
/// \}

/// \name DB5
/// \{
#define PIN_DB5_PORT          PORTC
#define PIN_DB5_PT            PTC
#define PIN_DB5_SHIFT         (4)
#define PIN_DB5               (1<< PIN_DB5_SHIFT)
/// \}

/// \name DB6
/// \{
#define PIN_DB6_PORT          PORTC
#define PIN_DB6_PT            PTC
#define PIN_DB6_SHIFT         (5)
#define PIN_DB6               (1<< PIN_DB6_SHIFT)
/// \}

/// \name DB7
/// \{
#define PIN_DB7_PORT          PORTC
#define PIN_DB7_PT            PTC
#define PIN_DB7_SHIFT         (6)
#define PIN_DB7               (1<< PIN_DB7_SHIFT)
/// \}

/// \name RS
/// \{
#define PIN_RS_PORT           PORTC
#define PIN_RS_PT             PTC
#define PIN_RS_SHIFT          (11)
#define PIN_RS                (1<< PIN_RS_SHIFT)
/// \}

/// \name RW
/// \{
#define PIN_RW_PORT           PORTC
#define PIN_RW_PT             PTC
#define PIN_RW_SHIFT          (10)
#define PIN_RW                (1<< PIN_RW_SHIFT)
/// \}

/// \name E
/// \{
#define PIN_E_PORT            PORTC
#define PIN_E_PT              PTC
#define PIN_E_SHIFT           (7)
#define PIN_E                 (1<< PIN_E_SHIFT)
/// \}

/// \name Enable Clock for peripheral driving LCD pins
/// \{
#define ENABLE_LCD_PORT_CLOCKS SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK
/// \}


// ----------------------------------------------------------------------------
// Function prototypes
void lcd_init(void);
void lcd_clear(void);
void lcd_set_cursor(const uint8_t column, const uint8_t row);
void lcd_putchar(const char c);
void lcd_print(const char *string);


//JWI added
void backgroundLight(bool);
void lcd_printlines(const char *ln1 ,const char *ln2);
bool isNotEqual(char* str1, char* str2);

#endif // LCD_H
