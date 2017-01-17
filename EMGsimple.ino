/************************************************David Mortin Final Project*********************************************
  program spends first few seconds setting a zero value*/
  #include <Servo.h>
  #include <compat/deprecated.h>
  #include <FlexiTimer2.h>
  #define SAMPFREQ 256                      // ADC sampling rate 256
  #define TIMER2VAL (1024/(SAMPFREQ))       // Set 256Hz sampling frequency                   

volatile unsigned char CurrentCh=0;         //Current channel being sampled.
volatile unsigned int EMG_Value = 0;    
float EMG_Value10 = 0;              //value smoothed by 90%
float EMG_Value05 = 0;              //value smoothed by 95%
float EMG_Value001 = 0;              //value smoothed by 99.9%

Servo servo1; // create servo object to control servo 1
Servo servo2; // create servo object to control servo 2
Servo servo3; // create servo object to control servo 3
Servo servo4; // create servo object to control servo 4

  float zero = 312.0;  //DC offset
  float EMG_rect, EMG;
  float pos1, pos2, pos3, pos4, ms1, ms2, ms3, ms4;
  int t=0, flag=0, n=0;
  int thresh=10;
  int grabcounter;
  

void setup() {
  Serial.begin(57600);   // initialize serial communications at 9600 bps:
  servo1.attach(9,768,2375);  // attaches the servo on pin 5 and sets the limits
  servo2.attach(10,600,2276);  // attaches the servo on pin 6 and sets the limits
  servo3.attach(11,613,2400);  // attaches the servo on pin 9 and sets the limits
  servo4.attach(6,1538,2100);  // attaches the servo on pin 10 and sets the limits
  //gab0();
  //delay(7500);
}

void loop() {
            
           EMG_Value = analogRead(CurrentCh);
           EMG_Value10 = 0.9*EMG_Value10+0.1*float(EMG_Value);
           //EMG_Value05 = 0.95*EMG_Value05+0.05*float(EMG_Value);
           //EMG_Value001 = 0.999*EMG_Value001+0.001*float(EMG_Value);
           //if(EMG_Value001-zero<-100||EMG_Value001-zero>100) flag=1; attempt at flagging movement artifacts
           //else flag=0;

if(n<1000){
              zero=.9*zero+.1*float(EMG_Value);
              n++;
           }
           else { 
           zero=.99*zero+.01*EMG_Value10;
           }

           EMG_rect = EMG_Value10-zero;
           if(EMG_rect<0) EMG_rect = EMG_rect*(-1);
           //if(flag) EMG_rect = 0;
           EMG = .9*EMG+.1*EMG_rect;
           //if(EMG>thresh) grabcounter++; // Artifacts get the signal stuck high, thus I limit grabbing time
           //if(EMG<thresh) grabcounter--;
           //if(grabcounter>=3000) EMG=0;
           t++;
           if(EMG>200){
           n=0;
           EMG=100;
           while(n<10000){
            controlmotors();
            n++;
           }
           n=0;
           EMG=0;
           while(n<10000){
            controlmotors();
            n++;
           }
           }

}

void controlmotors() { 
             if(EMG>thresh){
            pos1=0.0;
            pos2=.99*pos2+.01*15.0;
            //pos3=.99*pos3+.01*25.0;
            pos4=.99*pos4+.01*25.0;
           }
           else {
            pos1=0.0;
            pos2=.99*pos2+.01*-15.0;
            //pos3=.99*pos3+.01*-25.0;
            pos4=.99*pos4+.01*-35.0;
           }

           servo();
}

void printallvalues() {
           Serial.print(EMG_Value); Serial.print("\t"); 
           Serial.print(EMG_Value10); Serial.print("\t");
           Serial.print(EMG_Value05); Serial.print("\t");
           Serial.print(zero); Serial.print("\t");
           Serial.print(EMG_rect); Serial.print("\t");
           Serial.println(); 
}

void printgraph() {
  Serial.print(EMG);
  Serial.println(t);
}

void printprimaryvalues() {
  Serial.print(EMG); Serial.print("\t");
  Serial.print(pos2); Serial.print("\t");
  Serial.println(); 
}

void servo() {
  ms1 = pos1*10.0 + 1661.5; 
  ms2 = pos2*10.0 + 2136; 
  ms3 = pos3*10.0 + 1146; 
  ms4 = pos4*10.0 + 1885;
  servo1.writeMicroseconds(int(ms1));  // tell servo to go to microseconds
  servo2.writeMicroseconds(int(ms2)); 
  servo3.writeMicroseconds(int(ms3)); 
  servo4.writeMicroseconds(int(ms4));
}

