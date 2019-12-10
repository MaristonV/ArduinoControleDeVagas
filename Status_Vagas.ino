#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

//Firebase settings
#define FIREBASE_HOST "estacmob.firebaseio.com"
#define FIREBASE_AUTH "72CpuQOXLI9oC1HrGWnFWvv8YiepZMRrVhyPc9OQ"

//Wi-Fi settings
#define WIFI_SSID "SANTANA"
#define WIFI_PASSWORD "franca01"


#define TRIGGER_PIN  5
#define ECHO_PIN     4
#define TRIGGER_PIN_1 12
#define ECHO_PIN_1 13
#define TRIGGER_PIN_2 0
#define ECHO_PIN_2 2
double accuracy    = 0.0;
 int vagaDisponivel1 = 1; 
 int vagaDisponivel = 1;
 int vagasDisponiveis;
 const int led = 16; 
 const int led1 = 15;
void setup() {
  pinMode(led,OUTPUT);
    pinMode(led1,OUTPUT);
  // Connect to Wi-Fi
    Serial.print("Wi-Fi...");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting...");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }
    Serial.println();
    Serial.print("Connected to: ");
    Serial.println(WiFi.localIP());

    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Serial.begin (9600);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
   pinMode(TRIGGER_PIN_1, OUTPUT);
  pinMode(ECHO_PIN_1 , INPUT);
   pinMode(TRIGGER_PIN_2, OUTPUT);
  pinMode(ECHO_PIN_2 , INPUT);
  pinMode(BUILTIN_LED, OUTPUT);
  
  
}

void loop() {
   
  
  sensor1();
  sensor2();
  sensor3();
  vagasDisponiveis = vagaDisponivel + vagaDisponivel1;
   Firebase.setInt("/sensores/vagasDisponiveis",vagasDisponiveis);

}
void sensor1(){
  long duration, distance;
   
  digitalWrite(TRIGGER_PIN, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration/2) / 29.1;
  if(distance < 15 ){
    vagaDisponivel = 0;
    digitalWrite(16, HIGH);
    }else{
       vagaDisponivel = 1;
         digitalWrite(16, LOW);
      }
  Serial.print(distance);
  Firebase.setInt("/sensores/vagaDisponivel",vagaDisponivel);
  Serial.println(" Sensor1 cm");
  delay(1000);
  }

  void sensor2(){
  
  long duration1, distance1;
  digitalWrite(TRIGGER_PIN_1, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(TRIGGER_PIN_1, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(TRIGGER_PIN_1, LOW);
  duration1 = pulseIn(ECHO_PIN_1, HIGH);
  distance1 = (duration1/2) / 29.1;  
  if(distance1 < 15 ){
    vagaDisponivel1 = 0;
    digitalWrite(15, HIGH);
    }else{
      vagaDisponivel1 = 1;
      digitalWrite(15, LOW);
      }
  Serial.print(distance1);
  Firebase.setInt("/sensores/vagaDisponivel1",vagaDisponivel1);
  Serial.println(" Sensor2 cm");
  delay(1500);
  }

  void sensor3(){
  long duration2, distance2;
  digitalWrite(TRIGGER_PIN_2, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(TRIGGER_PIN_2, HIGH);  
  delayMicroseconds(10); // Added this line
  digitalWrite(TRIGGER_PIN_2, LOW);
  duration2 = pulseIn(ECHO_PIN_2, HIGH);
  distance2 = (duration2/2) / 29.1;
  Serial.print(distance2);
  Serial.println(" Sensor3 cm");
  delay(10);
  }

 



