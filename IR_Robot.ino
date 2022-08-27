#include <AFMotor.h> 
#include <IRremote.h>

// Motor Tanımlamaları
AF_DCMotor motor_sol(3); 
AF_DCMotor motor_sag(4);

// IR Kod Tanımlamaları
const int ileri = 0xFF18E7; 

const int geri = 0xFF4AB5;

const int sag = 0xFF5AA5;  

const int sol = 0xFF10EF;

const int code0 = 0xFFFFFFFF;  //herhangi bir tuşa basılı tutma durumunda gelen kod

int RECV_PIN = 5;
IRrecv irrecv(RECV_PIN);
decode_results results;


int lastCode = 0; // butona sürekli basılması durumunda gelen 0xFFFFFFFF kodunu düzgün kullanabilmek amacıyla tanımlama yaptık. 

void setup()
{
    
  motor_sol.run(RELEASE);
  motor_sag.run(RELEASE);
  
  motor_sol.setSpeed(255);
  motor_sag.setSpeed(255);
  
  Serial.begin(9600);   
  irrecv.enableIRIn();  
 
  pinMode(output1, OUTPUT);
  pinMode(output2, OUTPUT);
}

void loop() {


    if (irrecv.decode(&results))
  {
    uint16_t resultCode = (results.value & 0xFFFFFFFF);


 
    if (resultCode == code0) { //code0 alınması durumunda son alınan kodun kontrolü sağlanıyor 
        if (lastCode == ileri)
        {
          goto a1;
        }
        if (lastCode == geri)
        {
          goto a2;
        }
         if (lastCode == sag)
        {
          goto a3;
        }
         if (lastCode == sol)
        {
          goto a4;
        }
    }    

    if (resultCode == ileri) {
    
      a1:
      motor_sol.run(FORWARD);
      motor_sag.run(FORWARD);
      delay(300); 
      motor_sol.run(RELEASE);
      motor_sag.run(RELEASE);
      lastCode=ileri;
    } 

    
    if (resultCode == geri) {
      a2:
      motor_sol.run(BACKWARD);
      motor_sag.run(BACKWARD);
            delay(300); 
      motor_sol.run(RELEASE);
      motor_sag.run(RELEASE);
      lastCode=geri;    
    } 

    if (resultCode == sag) {
      a3:
      motor_sol.run(FORWARD);
      motor_sag.run(BACKWARD);
            delay(300); 
      motor_sol.run(RELEASE);
      motor_sag.run(RELEASE);
      lastCode=sag;    
    } 

    if (resultCode == sol) {
      a4:
      motor_sol.run(BACKWARD);
      motor_sag.run(FORWARD);
            delay(300); 
      motor_sol.run(RELEASE);
      motor_sag.run(RELEASE);

      lastCode=sol;    
    }     
    
    Serial.println(resultCode); 
    irrecv.resume(); 
  }


}
