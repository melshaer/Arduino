#include <Sparki.h> // include the sparki library

boolean intersection = true;
int order = 1;

int code;

//uint8_t speed = random(0,100);

int lineLeft;   
int lineCenter;
int lineRight;
int edgeLeft;
int edgeRight;

int threshold = 700;

void setup() {
  
}

void loop() {
  code = sparki.readIR();
  if(code == 70){
    intersection = true;
    go();
    }
  else{
    if(code == 64){
      sparki.moveStop();
      }
  }
}

void which(){
   if(~intersection && order==1){
     sparki.moveForward(26);
     order = 0;
     sparki.clearLCD();
     sparki.print("Intersection: ");
     sparki.println(intersection);
     sparki.print("Order: ");
     sparki.println(order);
     sparki.updateLCD();
     intersection = true;
     go();
    }
}  
    
  
 void go() {
  sparki.servo(SERVO_CENTER);
  while(intersection){
    code = sparki.readIR();
    if(code == 64){
      sparki.moveStop();
      break;
      }

    sparki.clearLCD(); // wipe the screen
    //speed = random(0,100);
    lineLeft   = sparki.lineLeft();   // measure the left IR sensor
    lineCenter = sparki.lineCenter(); // measure the center IR sensor
    lineRight  = sparki.lineRight(); // measure the right IR sensor
    edgeLeft = sparki.edgeLeft();
    edgeRight = sparki.edgeRight();
      
        if(edgeLeft < threshold && lineLeft < threshold && lineCenter < threshold && lineRight < threshold && edgeRight < threshold)
        {
          if(order == 1){
          sparki.moveStop();
          intersection = false;
          sparki.servo(SERVO_RIGHT);
          delay(1000);
          sparki.servo(SERVO_LEFT);
          delay(1000);
          sparki.servo(SERVO_CENTER);
          delay(2000);
          sparki.print("Order: ");
          sparki.println(order);
          sparki.updateLCD();
          which();
         }
         
         if(order == 0){
          intersection = true; 
          sparki.moveForward();
          sparki.print("Order: ");
          sparki.println(order);
          sparki.updateLCD();
          }         
           
        }
         
        else {
           if ( lineCenter < threshold ) // if line is below left line sensor
          {  
            sparki.moveForward(); // move forward
            //sparki.speed(speed);
          }
            else{
              if ( lineLeft < threshold ) // if line is below left line sensor
              {  
                sparki.moveLeft(); // turn left
                //sparki.speed(speed);
              }
              if ( lineRight < threshold ) // if line is below right line sensor
              {  
                sparki.moveRight(); // turn right
                //sparki.speed(speed);
              }
            }
          }
     

  sparki.print("Intersection: ");
  sparki.println(intersection);
    
//  sparki.print("Speed: ");
//  sparki.println(speed);

  sparki.print("Edge Left: "); 
  sparki.println(edgeLeft);
  
  sparki.print("Line Left: "); // show left line sensor on screen
  sparki.println(lineLeft);
  
  sparki.print("Line Center: "); // show center line sensor on screen
  sparki.println(lineCenter);
  
  sparki.print("Line Right: "); // show right line sensor on screen
  sparki.println(lineRight);

  sparki.print("Edge Right: "); 
  sparki.println(edgeRight);
  
  sparki.updateLCD(); // display all of the information written to the screen

  delay(100); // wait 0.1 seconds  
  }
  
 
    }  

 



