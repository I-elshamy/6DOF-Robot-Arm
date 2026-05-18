#define dir 19
#define step 18 
int angle=90;
void setup() {
  // put your setup code here, to run once:
  pinMode(dir,OUTPUT);
  pinMode(step,OUTPUT);

  delay(2000);
  digitalWrite(dir,HIGH);
  digitalWrite(step,LOW);

  
}

void loop() {

  for (int i=0;i<int(angle/1.8);i++)
  {
  digitalWrite(step,HIGH);
  delay(10);
  digitalWrite(step,LOW);
  delay(10);
  }
  delay(1000);

  // put your main code here, to run repeatedly:
  
}
