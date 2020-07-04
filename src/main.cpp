#include <avr/io.h>
#include <avr/interrupt.h>
#include <Arduino.h>

void setup()
{
      Serial.begin(9600);
      pinMode(8, INPUT_PULLUP);
      TCCR1A = 0;

      // setup the prescalers to 1024
      TCCR1B |= (1 << CS12);
      TCCR1B &= ~(1 << CS11);
      TCCR1B |= (1 << CS10);

      // enable interupts
      TCNT1 = 0;         // reset timer
      bitSet(TIMSK1, 5); // event interupt
      bitSet(TIMSK1, 0); // overflow interupt
      sei();
}
void loop()
{
      delay(1000); // delay to detecting changes
}

ISR(TIMER1_OVF_vect)
{
      Serial.println("Overflow");
}

ISR(TIMER1_CAPT_vect)
{
      Serial.print("Timer:: ");
      Serial.print(ICR1);
      Serial.print(" , milis:: ");
      Serial.println(millis());
      delay(1000);
}