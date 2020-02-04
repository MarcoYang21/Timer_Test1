#include "Arduino.h"
#define pulPin 13 //motor control pulse pin
#define dirPin 12
#define enaPin 11
long int pulseTarget = 268;
long int pulseCount = 0;
bool dirState = false;
bool enaState = false;

void Timer1Init(void)
{
	noInterrupts();
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	OCR1A = 30; /*compare match register 16MHz/65536/0.1Hz*/
	TCCR1B |= (1 << WGM12); /* CTC mode*/
	TCCR1B |= (1 << CS12); /* 256 pre-scalar */
	TIMSK1 |= (1 << OCIE1A); /*Enable timer compare interrupt*/
	interrupts(); 	/*interrupt enable*/
}

ISR(TIMER1_COMPA_vect)
{
	if(pulseTarget != pulseCount && enaState){
	digitalWrite(pulPin,digitalRead(pulPin)^1);
	pulseCount++;
	}
}

void setup()
{
// Add your initialization code here
	pinMode(pulPin, OUTPUT);
	pinMode(dirPin, OUTPUT);
	pinMode(enaPin, OUTPUT);
	digitalWrite(pulPin, LOW);
	digitalWrite(dirPin, LOW);
	enaState = true;
	digitalWrite(enaPin, enaState);
	Timer1Init();
}


// The loop function is called in an endless loop
void loop()
{
//Add your repeated code here
	if(pulseTarget == pulseCount){
	enaState = false;
	digitalWrite(enaPin,enaState);
	delay(250);
	pulseCount = 0;
	dirState =!dirState;
	digitalWrite(dirPin,dirState);
	delay(150);
	enaState = true;
	digitalWrite(enaPin,enaState);
	}

}
