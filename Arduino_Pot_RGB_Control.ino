//Code by Evan Roach


//pins connected to the LED colors. Must be pwm pins
int pinR = 6;
int pinG = 10;
int pinB = 9;

//pot pin input, must be an analog input
int knob = A0;

//outputs of each color
float red = 0;
float green = 0;
float blue = 0;

//current pot value
int pot = 0;

//highest values of pwm output and pot input
int highpwm = 255;
int highPot = 675;

//seperates the pot inputs into 3 sections for rgb separation
int firstthird = highPot/3;
int lastthird = highPot - firstthird;

//variables for the remapped output values
int mappedgrow = 0;
int mappeddie = 0;

// no setup needed
void setup() {
}

// loop to change the color every run through. This section is slightly inefficient due to writing to the LED every run through instead of checking to see if the pot value has changed and doing nothing if it has not
void loop() {
//reads the pot value and stores it in the variable "pot"
  pot = analogRead(knob);

//remaps the input values range to be in the output value range
  mappedgrow = map(pot%firstthird, 0, firstthird, 0, highpwm);
  mappeddie = map(pot%firstthird, 0, firstthird, highpwm, 0);

//if the pot value is low, start decreasing red and increasing green
  if (pot < firstthird){
    red = mappeddie;
    green = mappedgrow;
    blue = 0;
    analogWrite(pinR, red);
    analogWrite(pinG, green);
    analogWrite(pinB, blue);
  }
//if the pot value is near the middle, start decreasing green and increasing the blue
  else if (pot >= firstthird && pot < lastthird){
    green = mappeddie;
    blue = mappedgrow;
    red = 0;
    analogWrite(pinR, red);
    analogWrite(pinG, green);
    analogWrite(pinB, blue);
  }
//if the pot value is near the end, start decreasing the blue and increasing red
  else if (pot >= lastthird){
    blue = mappeddie;
    red = mappedgrow;
    green = 0;
    analogWrite(pinR, red);
    analogWrite(pinG, green);
    analogWrite(pinB, blue);
  }
}
