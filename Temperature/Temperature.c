#include "Temperature.h"

// Available Functions:
float get_temp_C(void); // Returns the temperature in celsius 
unsigned int OneWireReset(void); // Sends a reset pulse to the sensor 
void OneWireWriteBit(unsigned char); // write a single bit to the OneWire
unsigned char OneWireReadBit(void); // reads a single bit 
void OneWireWriteByte(unsigned char); // writes a byte 
unsigned char OneWireReadByte(void); // reads a byte 
unsigned char OneWireRead(void); // reads the current status of the bus
void OneWireHigh(void); // sets the bus high
void OneWireRelease(void); // releases the bus 


void temp_init(void)
{
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;//enables clock Port c
	PORTC->PCR[17] = (1UL << 8);// set pin to gpio
	PTC->PSOR = MASK(17);
	}

//function for temperature
float get_temp_C(void)
{
     int i=0;
    OneWireReset(); // Reset Pulse 
    OneWireWriteByte(0xCC); // Issue skip ROM command (CCh)
    OneWireWriteByte(0x44); // Convert T command (44h)
    PTC->PDDR &= ~MASK(17);
		while((PTC->PDIR & (1<<17))== 0)
		{
			i++;
			if(i==10000)
			{
				return -1000;
			}	
			
		}			// DS will hold line low while making measurement
    OneWireReset(); // Start new command sequence 
    OneWireWriteByte(0xCC); // Issue skip ROM command 
    OneWireWriteByte(0xBE); // Read Scratchpad (BEh) - 15 bits
    unsigned char LSB = OneWireReadByte();
    unsigned char MSB = OneWireReadByte();
    OneWireReset(); // Stop Reading 
    unsigned int data = MSB;
    float temperature = (data << 8) | LSB;
    return (temperature/16); 
   
}

void OneWireHigh(void){
    //BUSDIR = 0; // Set as output
    //BUSOUT = 1; // Set high 
	  PTC->PDDR |= MASK(17);	 
	  PTC->PSOR = MASK(17);
}

void OneWireRelease(void){
  
	  PTC->PDDR |= MASK(17);//set as output
	  PTC->PCOR = MASK(17);// set pin low
	  
}

unsigned char OneWireRead(void){
    
	 PTC->PDDR &= ~MASK(17);//set pin to input
	unsigned char data = (GPIOC->PDIR>>17)&1;//read value of pin
	return data;
}

unsigned int OneWireReset(void){
    OneWireRelease();
    delay_us(240); // 480uS Delay
    delay_us(240);
    OneWireHigh();
    delay_us(70); // wait 70 uS before reading
    unsigned int OW = OneWireRead(); // check for OneWire
    delay_us(205); // 410 uS delay
    delay_us(205);
    OneWireHigh(); // give bus back to OneWire
    return OW; 
}


void OneWireWriteBit(unsigned char b){
    if(b){
        OneWireRelease();
        delay_us(6); // wait 6uS
        OneWireHigh();
        delay_us(64); // wait 64uS
    }
    else{
        OneWireRelease();
        delay_us(60); // wait 60uS
        OneWireHigh();
        delay_us(10); // wait 10uS
    }
}

unsigned char OneWireReadBit(void){
    OneWireRelease();
    delay_us(6); // wait 6uS
    OneWireHigh();
    delay_us(9); // wait 9uS
    unsigned char out = OneWireRead();
    delay_us(55); // wait 55uS
    return out;
}

void OneWireWriteByte(unsigned char b){
    for(int i = 0; i < 8; i++){
        OneWireWriteBit(b & 0x01); // send LS bit first 
        b = b >> 1;
    }
}

unsigned char OneWireReadByte(void){
    unsigned char out; 
    for(int i = 0; i < 8; i++){ // read in LS bit first
        out = out >> 1; // get out ready for next bit
        if(OneWireReadBit() & 0x01) // if its a one 
            out = out | 0x80; // place a 1 
    }
    return out;
}
