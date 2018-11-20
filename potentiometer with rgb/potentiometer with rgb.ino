int sensor = 0 ;

void setup()
{
  pinMode(2,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(13,OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  sensor = analogRead(A0) ;
  Serial.println(sensor);
  if(sensor <250){
      digitalWrite(2,LOW);
      digitalWrite(7,HIGH);
      digitalWrite(13,HIGH);
  }

   else if (sensor>250 && sensor<450) {
        digitalWrite(2,HIGH);
        digitalWrite(7,LOW);
        digitalWrite(13,HIGH);
   }
   
  else if (sensor>450 && sensor<650) {
          digitalWrite(2,HIGH);
          digitalWrite(7,LOW);
          digitalWrite(13,LOW);
  }
   else if (sensor>650 && sensor<850) {
          digitalWrite(2,LOW);
          digitalWrite(7,LOW);
          digitalWrite(13,HIGH);
   }
   
   else {
          digitalWrite(2,LOW);
          digitalWrite(7,LOW);
          digitalWrite(13,LOW);
   } 
}
