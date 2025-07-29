# SIT315-M1.T4D
**Task M1.T1D**
**Overview**
This Arduino project demonstrates a concurrent system that uses:
A Timer1 Compare Match interrupt to cycle through red, green, and blue LEDs at fixed intervals.
A Pin Change Interrupt (PCI) on analog input pins A0–A3 (PORTC) overrides the automatic LED sequence based on sensor input.
This setup ensures both periodic behavior using Timer1 and event-driven logic using PCI.



**Features**
Timer1 CTC Mode used for LED colour cycling (red → green → blue).
Pin Change Interrupt on PCINT[11:8] (A0–A3) used to update LED colors directly based on input pins.
Uses volatile global variables for safe sharing between ISRs and main code.


**Hardware Setup**
Pin	Role	Description
D2	Green LED Output	Controlled by g
D3	Blue LED Output	Controlled by b
D4	Red LED Output	Controlled by r
A0	Input	Enables green LED via interrupt
A1	Input	Enables blue LED via interrupt
A2/A3	Input	Enables red LED via interrupt


**Behavior Summary**
Startup: LEDs are initially OFF.
Timer Logic (every ~1 second):
Cycles through red → green → blue using a ledState counter.
Interrupt Logic (PCI on A0–A3):
If any of the pins A0–A3 change state, the LED colour is immediately updated based on which pin is HIGH:
A0 → green
A1 → blue
A2 or A3 → red

**Technical Details**
Timer Configuration:
TCCR1B = 0b00001101 sets:
CTC mode (WGM12 = 1)
Prescaler 1024 (CS12 = 1, CS10 = 1)
OCR1A = 15624 gives ~1 second interval:
(16,000,000/1024)−1=15624
Interrupts:
ISR(TIMER1_COMPA_vect) updates ledState and LED colors.
ISR(PCINT1_vect) overrides LED color using A0–A3 inputs.

**Files**
sketch.M1T4d.ino: Complete source code
M1T4d.spp
README.md: This documentation

**How to Use**
Upload the code to an Arduino Uno.
Connect LEDs to pins D2, D3, D4 via 220Ω resistors.
Connect buttons to A3 and PIR sensors to A0, A1, A2.
Triggering PIR or pressing the button will override the timer colour briefly; timer resumes cycling through colours automatically.



