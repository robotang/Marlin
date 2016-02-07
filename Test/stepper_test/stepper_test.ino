/* Stepper test */

#include <AccelStepper.h>

#define XSTEP_PIN    54
#define XDIR_PIN     55
#define YSTEP_PIN    60
#define YDIR_PIN     61
#define ZSTEP_PIN    46
#define ZDIR_PIN     48

#define XMIN_PIN     3
#define XMAX_PIN     2
#define YMIN_PIN     14
#define YMAX_PIN     15
#define ZMIN_PIN     18
#define ZMAX_PIN     19

AccelStepper xstepper(1, XSTEP_PIN, XDIR_PIN);
AccelStepper ystepper(1, YSTEP_PIN, YDIR_PIN);
AccelStepper zstepper(1, ZSTEP_PIN, ZDIR_PIN);
int xspeed = 0, yspeed = 0, zspeed = 0;

void setup(void) 
{
    Serial.begin(9600);
    
    /* Setup stepper motors */
    xstepper.setMaxSpeed(10000);
    xstepper.setSpeed(xspeed);
    ystepper.setMaxSpeed(10000);
    ystepper.setSpeed(yspeed);
    zstepper.setMaxSpeed(10000);
    zstepper.setSpeed(zspeed);
    
    /* Setup limit switches */
    pinMode(XMIN_PIN, INPUT_PULLUP);
    //pinMode(XMAX_PIN, INPUT);
    pinMode(YMIN_PIN, INPUT_PULLUP);
    //pinMode(YMAX_PIN, INPUT);
    pinMode(ZMIN_PIN, INPUT_PULLUP);
    //pinMode(ZMAX_PIN, INPUT);
}

#if 0
void loop(void)
{
    Serial.println(digitalRead(XMIN_PIN));
    delay(500);
}
#else
void loop(void) 
{
    if(Serial.available() > 0) 
    {
        int rx = Serial.read();    
        if(rx == '6') xspeed += 100;
        else if(rx == '4') xspeed -= 100;
        else if(rx == '8') yspeed += 100;
        else if(rx == '2') yspeed -= 100;
        else if(rx == '+') zspeed += 100;
        else if(rx == '-') zspeed -= 100;
        else
        { 
            xspeed = 0;
            yspeed = 0;  
            zspeed = 0;
        } 
        xstepper.setSpeed(xspeed);
        ystepper.setSpeed(-1*yspeed); //reverse direction
        zstepper.setSpeed(-1*zspeed); //reverse direction
        
        Serial.print("x: ");
        Serial.print(xspeed);
        Serial.print(", y: ");
        Serial.print(yspeed);
        Serial.print(", z: ");
        Serial.print(zspeed);
        Serial.print("\r\n");
    }
    xstepper.runSpeed();
    ystepper.runSpeed();
    zstepper.runSpeed();
    
    if(digitalRead(XMIN_PIN) == 0) Serial.println("XMIN");
    //if(digitalRead(XMAX_PIN) == 0) Serial.println("XMAX");
    if(digitalRead(YMIN_PIN) == 0) Serial.println("YMIN");
    //if(digitalRead(YMAX_PIN) == 0) Serial.println("YMAX");
    if(digitalRead(ZMIN_PIN) == 0) Serial.println("ZMIN");
    //if(digitalRead(ZMAX_PIN) == 0) Serial.println("ZMAX");    
}
#endif

