#define BUTTON_PIN 2

#define pulseGeneratorPin 4
#define TMSMachinePin 3

const int analogInputPin = A4; // analog input pin
const int DelayPin = A3; 
const float threshold = 2.0; // threshold voltage for analog input
const int trials = 25; // number of trials
const int key_delay = 300;
const int DelayValue = 0; //ms


void setup()
{
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  pinMode(pulseGeneratorPin, OUTPUT);
  pinMode(TMSMachinePin, OUTPUT);
}


// the loop function runs over and over again forever
void loop() {

  digitalWrite(pulseGeneratorPin, LOW);
  digitalWrite(TMSMachinePin, LOW);   

  byte buttonstate = digitalRead(BUTTON_PIN);
  delay(key_delay);

    if (analogRead(DelayPin) > 4) {
      DelayValue = 19
  } else if (analogRead(DelayPin) < 1) {
      DelayValue = 9
  } else {
      DelayValue = 14
  }

  
  if(buttonstate == LOW){

    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);

    for (int i = 0; i < trials; i++) {
    
      //digitalWrite(LED_BUILTIN, LOW);  // turn the LED on (HIGH is the voltage level)
      //delay(1000);                      // wait for a second
      //digitalWrite(LED_BUILTIN, HIGH);   // turn the LED off by making the voltage LOW
      //delay(1000);    
      
      //byte buttonState = digitalRead(BUTTON_PIN);
      //if(buttonState == LOW){
          //break;
      //}

      if (analogRead(DelayPin) > 4) {
        DelayValue = 19
    } else if (analogRead(DelayPin) < 1) {
        DelayValue = 9
    } else {
        DelayValue = 14
    }



      Serial.println("Current trial is: ");
      Serial.println(i + 1);

      triggerPulseGenerator(DelayValue);
      
      float delayTime = 4.0 + random(0, 1000) / 1000.0; // random delay between 4 and 5 seconds
      delay(delayTime * 1000);
      
    }

    digitalWrite(LED_BUILTIN, LOW);
    
  }
}



void triggerPulseGenerator(DelayValue) {
  digitalWrite(pulseGeneratorPin, HIGH); // activate pulse generator
  while (analogRead(analogInputPin) < threshold * 1024.0 / 5.0) {} // wait for threshold crossing
  digitalWrite(pulseGeneratorPin, LOW); // deactivate pulse generator
  delay(DelayValue); 
  digitalWrite(TMSMachinePin, HIGH); // activate TMS machine
  delay(20); // wait for 20 ms
  digitalWrite(TMSMachinePin, LOW); // deactivate TMS machine
}
