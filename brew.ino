

int data =1;
int i =0;

byte statusLed    = 5;

byte sensorInterrupt = 0;
byte sensorPin       = 12;

float calibrationFactor = 4.5;

volatile byte pulseCount;  

float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;

unsigned long oldTime;

int valve1 = 5;
int valve2 = 6;
int coil = 7;
int valve[2] = {valve1,valve2};

Servo servo;

void reset();
void pour();

void setup()
{
  Serial.begin(9600);
  pinMode(coil,OUTPUT);  
  pinMode(sensorPin, INPUT);
  digitalWrite(sensorPin, HIGH);
  servo.attach(8);  
  servo.write(angle);

  pulseCount        = 0;
  flowRate          = 0.0;
  flowMilliLitres   = 0;
  totalMilliLitres  = 0;
  oldTime           = 0;

  attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
  Serial.println("start");
}

void loop()
{
   if(Serial.available()>0)
   {     
     { char data1= Serial.read();
      switch(data1)
      {
        case 'r':{
          digitalWrite(coil,HIGH);
          
          break;
          }
        case '4':{
          pour();
          for(angle = 10; angle < 60; angle++)  
          {                                  
            servo.write(angle);               
            delay(500);                   
          } 
          pour();
          for(angle = 60; angle < 120; angle++)  
          {                                  
            servo.write(angle);               
            delay(500);                   
          } 
          pour();
          for(angle = 120; angle < 180; angle++)  
          {                                  
            servo.write(angle);               
            delay(500);                   
          } 
          pour();
          for(angle = 180; angle < 10; angle--)  
          {                                  
            servo.write(angle);               
            delay(500);                   
          } 
          break;
          }
        case '3':{
          pour();
          for(angle = 10; angle < 60; angle++)  
          {                                  
            servo.write(angle);               
            delay(500);                   
          } 
          pour();
          for(angle = 60; angle < 120; angle++)  
          {                                  
            servo.write(angle);               
            delay(500);                   
          } 
          pour();
          for(angle = 120; angle < 10; angle--)  
          {                                  
            servo.write(angle);               
            delay(500);                   
          } 
          break;          
          }
        case '2':{
          pour();
          for(angle = 10; angle < 60; angle++)  
          {                                  
            servo.write(angle);               
            delay(500);                   
          } 
          pour();
          for(angle = 60; angle < 10; angle--)  
          {                                  
            servo.write(angle);               
            delay(500);                   
          } 
          break;
          }
          case '1':{
              pour();
              delay(500);
              break;
            }
        default : break;
            }
            Serial.println(data1);
   }
   if(data==1){
      pour(); 
   }
  }
 }
   
void pour(){
      if((millis() - oldTime) > 1000){
          digitalWrite(valve[i],HIGH); 
      
          detachInterrupt(sensorInterrupt);
              
          flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;
      
          oldTime = millis();
          flowMilliLitres = (flowRate / 60) * 1000;
          totalMilliLitres += flowMilliLitres;
            
          unsigned int frac;
          pulseCount = 0;
          attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
           if(i==0){
            if(totalMilliLitres>20)
              digitalWrite(valve[i],LOW);
              ++i;
              digitalWrite(valve[i],HIGH);
                }
            if(i==1){
              if(totalMilliLitres>120)
              digitalWrite(valve[i],LOW);
              reset();
            }
          }
        }

void reset(){
  pulseCount        = 0;
  flowRate          = 0.0;
  flowMilliLitres   = 0;
  totalMilliLitres  = 0;
  oldTime           = 0;
  data=0;
  }
/*
Insterrupt Service Routine
 */
void pulseCounter()
{
  // Increment the pulse counter
  pulseCount++;
}
