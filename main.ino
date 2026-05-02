/***************************************************************
 * Project   : IR2106 Gate Driver Tester 
 * Platform  : Arduino Nano (ATmega328P)
 * Author    : Arun.s
 * Date      : May 2026
 *
 * Description:
 * This sketch generates complementary PWM signals on pins 9 (OC1A)
 * and 10 (OC1B) with dead-time insertion, intended for testing the
 * IR2106 half-bridge gate driver on a UPS/inverter PCB.
 *
 * Features:
 * - Hardware Timer1 PWM at ~10 kHz
 * - Complementary outputs with ~2.5 µs dead-time
 * - Duty cycle sweep from 10% to 90% for dynamic testing
 * - On-board LED (pin 13) blinks twice every 5 seconds as a heartbeat
 *
 * Usage:
 * - Connect pin 9 → IR2106 HIN
 * - Connect pin 10 → IR2106 LIN
 * - Supply IR2106 with 12–15 V VCC and bootstrap network
 * - Probe HO and LO outputs with oscilloscope before connecting load
 *
 * Notes:
 * - Start with low DC bus voltage (12–24 V) for safe testing
 * - Adjust ICR1 for frequency changes (e.g., 800 → 20 kHz)
 * - Modify OCR1A/OCR1B for duty cycle and dead-time tuning
 ***************************************************************/

unsigned long lastBlink = 0;
int duty = 160;          // Start at 10% of ICR1 (1600)
int step = 16;           // Step size for duty sweep

void setup() {
  pinMode(9, OUTPUT);   // HO
  pinMode(10, OUTPUT);  // LO
  pinMode(13, OUTPUT);  // On-board LED

  // Stop Timer1
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  // Fast PWM, mode 14 (ICR1 as TOP)
  TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);
  TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS10); // No prescaler

  // Set TOP for frequency
  ICR1 = 1600;   // 10 kHz PWM at 16 MHz clock

  // Initial duty cycle
  OCR1A = duty;
  OCR1B = duty - 40;   // Dead-time offset (~2.5 µs)
}

void loop() {
  // Blink twice every 5 seconds
  if (millis() - lastBlink >= 5000) {
    lastBlink = millis();
    for (int i = 0; i < 2; i++) {
      digitalWrite(13, HIGH);
      delay(200);
      digitalWrite(13, LOW);
      delay(200);
    }
  }

  // Sweep duty cycle between 10% and 90%
  duty += step;
  if (duty >= 1440 || duty <= 160) { // 90% or 10%
    step = -step; // Reverse direction
  }

  OCR1A = duty;
  OCR1B = duty - 40; // Maintain dead-time
  delay(50);         // Smooth sweep
}
