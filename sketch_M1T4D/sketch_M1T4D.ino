volatile byte r, g, b = 0;
volatile bool br, bg, bb = false;
volatile bool ledEnabled = true;
volatile byte ledState = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("System Initialized...");
  pinMode (2, OUTPUT);
    pinMode (3, OUTPUT);
    pinMode (4, OUTPUT);
    
    
    DDRD |= 0b00011100;//this line sets D2, D3, and D4 as outputs
    
  //this direct register setup is needed to use ISR function
    PCICR  = B00000010;//selects for C to trigger the interups
    PCMSK1  = B00001111;//selects pin A0,A1,A2,A3 in Port C to trigger the interupts
  
  //clear timer registers
  TCCR1A = 0;
    
  TCCR1B = 0b00001101;//timer control register B refers to the second control register for Timer 1
  //this binary literal notation is related to:
  //WGM12 which enables CTC-clear timer on compare match- this is bit 3 in the TCCR1B register and is used to controil the mode of Timer1
  //CS12 - bit 2 in the TCCR1B register- used for setting the timer prescaler
  //CS10 - bit 0 in the register- used to configure Timer1 prescaler
  
  OCR1A = 1*16000000/1024 - 1;//i havnds just to be different
  
  TIMSK1 = 0b00000010;  // Enable Timer1 output compare A match interrupt
    
    updateLED();
  
}


void loop(){
}
  
  void updateLED() {
  digitalWrite(2, g);
  digitalWrite(3, b);
  digitalWrite(4, r);
}


ISR(PCINT1_vect) {
 
  
  g = PINC & B00000001;// Read the state of pin A0 and store it in 'g' 
  b = PINC & B00000010; // Read the state of pin A1 and store it in 'b'
 r = (PINC & B00001100) ? HIGH : LOW;  // Read the state of pin A2, A3 and store it in 'r'
  updateLED();  // Update the LED with the new color values
  Serial.print("Pin change interrupt: r=");
  Serial.print(r);
  Serial.print(", g=");
  Serial.print(g);
  Serial.print(", b=");
  Serial.println(b);
}


 ISR(TIMER1_COMPA_vect) {
  // Cycle: 0 = Red, 1 = Green, 2 = Blue
  ledState = (ledState + 1) % 3;

  r = (ledState == 0);
  g = (ledState == 1);
  b = (ledState == 2);

 Serial.println("Timer interrupt: cycling LED color");
  updateLED();
}
