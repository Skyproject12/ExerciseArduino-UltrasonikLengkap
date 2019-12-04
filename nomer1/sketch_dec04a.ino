// trigger pin 
const int pingPin = 13; 
// echo pin  
const int echoPin= 12;
void setup() {
  Serial.begin(9600);
}

void loop() {
  // mendefinisikan durasi dan jarak dari object
  long duration, cm; 
  pinMode(pingPin, OUTPUT);  
  // mendefiniskan triggrer sebagai output 
  // membuat sensor ultrasonik hidup 
  digitalWrite(pingPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(pingPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(pingPin, LOW); 
  pinMode(echoPin, INPUT);  
  // mengambil durasi dari sensor ultrasonik
  duration=pulseIn(echoPin, HIGH);  
  // memberi jarak dari sensor ultrasonik 
  cm= microsecondsToCentimeters(duration); 
  Serial.print("Jarak :"); 
  Serial.print("\t"); 
  Serial.print(cm); 
  Serial.print("cm"); 
  Serial.println();  
  // diberi delay sebanya 500 untuk setiap proses
  delay(500); 
}
long microsecondsToCentimeters(long microseconds){ 
  // jarak sama dengan position di bagi 29 dibagi 2 
  return microseconds/29/2;  
}
