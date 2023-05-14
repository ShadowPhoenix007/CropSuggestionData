#include <SoftwareSerial.h>
#include <Servo.h>
#include <DHT.h>

#define servoPin 2
#define enA 8
#define enB 5
#define in1 9
#define in2 10
#define in3 7
#define in4 6
#define NPKRE 11  //green
#define NPKDE 12  //orange
#define PHRE 4 //brown
#define PHDE 3 //white
#define DHTPIN 55 //green
//rxd pin = yellow, txd = green
#define DHTTYPE DHT22
 
DHT dht(DHTPIN, DHTTYPE);
Servo servo1;
long elapsedTime;
char dataStr[100] = "";
char buffer[7];

float t = 0;
float h = 0;


const byte ph[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x01, 0x84, 0x0A};
const byte nitro[] = {0x01,0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c};
const byte phos[] = {0x01,0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc};
const byte pota[] = {0x01,0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0};
 
int count = 0;
byte values[11];
SoftwareSerial mod(2,3);

void setup() {
	// Set all the motor control pins to outputs
	pinMode(enA, OUTPUT);
	pinMode(enB, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
  pinMode(NPKRE, OUTPUT);
  pinMode(NPKDE, OUTPUT);
  pinMode(PHRE, OUTPUT);
  pinMode(PHDE, OUTPUT);

	// Turn off motors - Initial state
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  servo1.attach(servoPin, 0, 2300);
  Serial.begin(9600);
  dht.begin();
}

void loop()
{
  // ltoa( millis(),buffer,10); //convert long to charStr
  // strcat(dataStr, buffer); //add it to the end
  // strcat( dataStr, ", "); //append the delimiter
  // MoveMotors(1, 1);
  // delay(4000);
  // MoveMotors(0, 0);
  // DropDown();
  // delay(1500);
  // DropServo(); 
  // delay(1500);
  float N,P,K, pH;
  N = nitrogen();
  P = phosphorous();
  K = potassium();
  pH = ph();
  TemperatureHumidity();
 //dtostrf(floatVal, minimum width, precision, character array);
  //Serial.println(N+ ", "+ P+ ", "+ K);
  Serial.print(N);
  Serial.print(", ");
  Serial.print(P);
  Serial.print(", ");
  Serial.print(K);
  Serial.print(", ");
  Serial.print(pH);
  Serial.print(", ");
  Serial.print(h);
  Serial.print(", ");
  Serial.println(t);
  
  //PickServo();
  delay(1500);  
  // dtostrf(N, 5, 1, buffer); 
  // strcat( dataStr, buffer); 
  // strcat( dataStr, ", "); 

  // dtostrf(P, 5, 1, buffer); 
  // strcat( dataStr, buffer); 
  // strcat( dataStr, ", "); 

  // dtostrf(K, 5, 1, buffer);  
  // strcat( dataStr, buffer); 
  // strcat( dataStr, ", ");

  // dtostrf(pH, 5, 1, buffer);  
  // strcat( dataStr, buffer); 
  // strcat( dataStr, ", ");  

  // dtostrf(t, 5, 1, buffer); 
  // strcat( dataStr, buffer); 
  // strcat( dataStr, ", "); 

  // dtostrf(h, 5, 1, buffer);
  // strcat( dataStr, buffer);
  // strcat( dataStr, ", "); 
  
  // Serial.println(dataStr);

  // if (count == 0)
  // {
    // DropServo();
    // delay(500);
    // PickServo();
    // delay(500);
 // }
  /* if(Serial.available()>0)
  {
    state = Serial.readString()
  }
  if (state == "Forward") //Forward
  {
    MoveMotors(0.7, 0.7)
  }
  else if (state == "Back") //Back
  {
    MoveMotors(-0.7, -0.7)
  }
  else if (state == "Left") //Left
  {
    MoveMotors(-0.7, 0.7)
  }  
  else if (state == "Right") //Right
  {
    MoveMotors(0.7, -0.7)
  }
  else if (state == "DropServo")
  {
    DropServo()
    Serial.print("Nitrogen_Val: ");
    Serial.print(nitrogen_val);]
    Serial.print("Phosphorous_Val: ");
    Serial.print(phosphorus_val);
    Serial.print("Potassium_Val: ");
    Serial.print(potassium_val);
    delay(2000);
    Serial.clearWriteError()
  }
  else if (state == "PickServo")
  {
    PickServo()
  }*/
}

void TemperatureHumidity()
{
  h = dht.readHumidity();
  t = dht.readTemperature(); 
  // Serial.print ("Humidity: ");
  // Serial.print (h);
  // Serial.print (" %\t");
  // Serial.println ("Temperature: ");
  // Serial.print (t);
  // Serial.print (" *C ");  
}

void DropServo()
{  
  servo1.write(110);                           
}

void DropDown()
{
 
  servo1.write(135);                           
  
}

void PickServo()
{
  servo1.write(65);              
}

void MoveMotors(double aPower, double bPower)
{
  if (aPower > 0)
  {
    analogWrite(enA, int(aPower * 255));
    digitalWrite(in1, HIGH);
	  digitalWrite(in2, LOW);
  }
  else if (aPower < 0)
  {
    analogWrite(enA, int(aPower * -255));
	  digitalWrite(in2, HIGH);
    digitalWrite(in1, LOW);  
  }
  else if (aPower == 0)
  {
	  digitalWrite(in2, LOW);
    digitalWrite(in1, LOW);
  }
  if (bPower > 0)
  {
    analogWrite(enB, int(bPower * 255));
    digitalWrite(in3, HIGH);
	  digitalWrite(in4, LOW);
  }
  else if (bPower < 0)
  {
    analogWrite(enB, int(bPower * -255));
    digitalWrite(in3, LOW);
	  digitalWrite(in4, HIGH);
  }
  else if (bPower == 0)
  {
    digitalWrite(in3, LOW);
	  digitalWrite(in4, LOW);
  }
}
float nitrogen(){
  digitalWrite(NPKDE,HIGH);
  digitalWrite(NPKRE,HIGH);
  delay(10);
  if(mod.write(nitro,sizeof(nitro))==8){
    digitalWrite(NPKDE,LOW);
    digitalWrite(NPKRE,LOW);
    for(byte i=0;i<7;i++){
    //Serial.print(mod.read(),HEX);
    values[i] = mod.read();
    }
  }
  return values[4];
}
 
float phosphorous(){
  digitalWrite(NPKDE,HIGH);
  digitalWrite(NPKRE,HIGH);
  delay(10);
  if(mod.write(phos,sizeof(phos))==8){
    digitalWrite(NPKDE,LOW);
    digitalWrite(NPKRE,LOW);
    for(byte i=0;i<7;i++){
    //Serial.print(mod.read(),HEX);
    values[i] = mod.read();
    }
  }
  return float(values[4]);
}
 
float potassium(){
  digitalWrite(NPKDE,HIGH);
  digitalWrite(NPKRE,HIGH);
  delay(10);
  if(mod.write(pota,sizeof(pota))==8){
    digitalWrite(NPKDE,LOW);
    digitalWrite(NPKRE,LOW);
    for(byte i=0;i<7;i++){
    //Serial.print(mod.read(),HEX);
    values[i] = mod.read();
    }
  }
  return float(values[4]);
}

float phlevel()
{
  byte val;
  digitalWrite(PHDE, HIGH);
  digitalWrite(PHRE, HIGH);
  delay(10);
  if (mod.write(ph, sizeof(ph)) == 8)
  {
    digitalWrite(PHDE, LOW);
    digitalWrite(PHRE, LOW);
    for (byte i = 0; i < 11; i++)
    {
      values[i] = mod.read();
      // Serial.print(values[i], HEX);
    }
    return float(values[4]/10);
  }
}