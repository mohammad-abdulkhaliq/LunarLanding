const int X_pin = 2;
const int Y_pin = 3;

void setup() { 
  Serial.begin(2400);
  pinMode(Y_pin, INPUT);
  pinMode(X_pin, INPUT);
  
}

void loop() {
   int X = analogRead(X_pin);
   int Y = analogRead(Y_pin);
  X = X / 11;
  Y = Y / 11;     
  int OX = X;
  int OY = Y;
 
  if(X > 62)
    OX = X - 62;
  if(X >= 58 && X <= 62)
    OX = 0;
  if(X < 58)
    OX = X - 58;
  
  
  if(Y > 62)
    OY = Y - 62;
  if(Y >= 58 && Y <= 62)
    OY = 0;
  if( Y < 58)
    OY = Y - 58;
  
  
  Serial.print("P:X:");
  Serial.print(OX);
  Serial.print("\n");
  Serial.print("P:Y:");
  Serial.print(OY);
  Serial.print("\n");
  
}

