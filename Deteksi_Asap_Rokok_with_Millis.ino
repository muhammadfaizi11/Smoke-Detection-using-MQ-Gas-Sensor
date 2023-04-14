//Deklarasi pin Sensor MQ-135
#define analogPin A0
#define digitalPin 2
#define lampPin 4
#define buzzerPin 3

unsigned int sensorValue;
unsigned int outputValue;
int digValue;

//Variabel Millis
unsigned long currentTime;
unsigned long prevTime, prevTime2, prevTime3;
unsigned long readTime;
unsigned long buzzerTime;
unsigned long relayTime;

int stateRelay, stateSensor, stateBuzzer, stateNilai;
int timer1, timer2, timer3;

//Sensor MQ2
void readSensor(){
  sensorValue = analogRead(analogPin);
  Serial.print("Analog Output Sensor : ");
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  Serial.println(outputValue);
  return outputValue;
}

void readValueDigital(){
  digValue = digitalRead(digitalPin);
  Serial.print("Digital Output Sensor : ");
  Serial.println(digValue);
}

void kondisi(){
  if(outputValue > 200 || digValue == 0){
    Serial.println("Smoke Detected !!!");
    digitalWrite(buzzerPin, LOW);
    digitalWrite(lampPin, HIGH);
  }
  else if(outputValue <= 200 && digValue == 1){
    Serial.println("Safety Air");
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(lampPin, LOW);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  pinMode(lampPin, OUTPUT);
  digitalWrite(buzzerPin, HIGH);
  digitalWrite(lampPin, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  currentTime = millis();
  timer1 = 1000;
  timer2 = 10000;
  if(currentTime - readTime >= timer1 && stateSensor == 0){
    prevTime = currentTime;
    Serial.println("Baca Sensor");
    readSensor();
    readValueDigital();
    kondisi();
    Serial.println("Relay On");
    stateSensor = 1;
  }

  if(stateSensor == 1){
    buzzerTime = currentTime;
    if(buzzerTime - prevTime >= timer2 && stateBuzzer == 0){
      stateBuzzer = 1;
    }

    if(stateBuzzer == 1){
      Serial.println("Kembali ke Awal");
      stateSensor = 0;
      stateBuzzer = 0;
      readTime = currentTime;
    }
  }
}
