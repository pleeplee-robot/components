#define MIN_COLORS 0
#define RED 0
#define GREEN 1
#define BLUE 2
#define YELLOW 3
#define PURPLE 4
#define ORANGE 5
#define WHITE 6
#define MAX_COLORS 7

#define PIN_R 9
#define PIN_G 10
#define PIN_B 11

unsigned long myrandom(unsigned long howsmall, unsigned long howbig)
{
 return howsmall + random(5000) % (howbig - howsmall);
}

void set_random()
{
  unsigned value = myrandom(MIN_COLORS, MAX_COLORS);

  switch (value) {
    case RED:
      analogWrite(PIN_R, 255);
      analogWrite(PIN_G, 0);
      analogWrite(PIN_B, 0);
      break;
    case GREEN:
      analogWrite(PIN_R, 40);
      analogWrite(PIN_G, 100);
      analogWrite(PIN_B, 0);
      break;
    case BLUE:
      analogWrite(PIN_R, 0);
      analogWrite(PIN_G, 0);
      analogWrite(PIN_B, 170);
      break;
    case YELLOW:
      analogWrite(PIN_R, 255);
      analogWrite(PIN_G, 42);
      analogWrite(PIN_B, 3);
      break;
    case PURPLE:
      analogWrite(PIN_R, 127);
      analogWrite(PIN_G, 0);
      analogWrite(PIN_B, 40);
      break;
    case ORANGE:
      analogWrite(PIN_R, 255);
      analogWrite(PIN_G, 11);
      analogWrite(PIN_B, 0);
      break;
    case WHITE:
      analogWrite(PIN_R, 200);
      analogWrite(PIN_G, 120);
      analogWrite(PIN_B, 50);
      break;
    default:
      analogWrite(PIN_R, 0);
      analogWrite(PIN_G, 0);
      analogWrite(PIN_B, 0);
  }
}

void setup() {
  // The pins are:
  /*pinMode(PIN_R, OUTPUT); // R
  pinMode(PIN_G, OUTPUT); // G
  pinMode(PIN_B, OUTPUT); // B*/
  // Note that the pin order on the LED is Red/Ground/Green/Blue
  randomSeed(analogRead(7));
  set_random();
}


void loop() {
  delay(1000);
}
