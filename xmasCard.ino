

//#include <Keyboard.h>
#include "Keyboard.h"
#include <CapacitiveSensor.h>

byte inbyte = 0;

CapacitiveSensor   cs_4_6 = CapacitiveSensor(6,9);        // 10 megohm resistor between pins 4 & 6, pin 6 is sensor pin, add wire, foil
CapacitiveSensor   cs_4_9 = CapacitiveSensor(15,10);        // 10 megohm resistor between pins 4 & 8, pin 8 is sensor pin, add wire, foil


boolean osDetect;
boolean startUpMac;
boolean startUpPc;
boolean gameStart;
const int osToggle = 3;

int toggleState = 0;

void setup()
{
  Serial.begin(9600);
  cs_4_9.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
  osDetect = true;
  startUpMac = false;
  startUpPc = false;
  gameStart = false;
  pinMode(osToggle, INPUT);
  Keyboard.begin();
}

void loop()
{
 
  if (osDetect == true)
  {
      long start = millis();
      long total2 =  cs_4_6.capacitiveSensor(30);
      long total3 =  cs_4_9.capacitiveSensor(30);
      
      if(total3 > 100)
     {
       if (total2 < 70)
        {
          startUpMac = true;
          osDetect = false;
        }
      
     }
    else if(total2 > 100)
    {
       if(total3 < 70)
      {
         startUpPc = true;
         osDetect = false;
      }
    }
  }      
      
    if (startUpMac == true)
    {
       openWebsiteMac(); 
    }
    
    if (startUpPc == true)
    {
       openWebsitePc();    
    } 
    
    if(gameStart == true)
    {
      long start = millis();
      long total2 =  cs_4_6.capacitiveSensor(30);
      long total3 =  cs_4_9.capacitiveSensor(30);
   
      
      Serial.println(total2);
      Serial.print("\t");
      Serial.println(total3);     
      
       if (total3 > 100)
      {
        if (total2 < 70)
        {
          Keyboard.press(KEY_RIGHT_ARROW);
          Keyboard.release(KEY_LEFT_ARROW);
          Keyboard.release(KEY_UP_ARROW);
        }
//        else if (total2 > 70)
//        {
//          Keyboard.press(KEY_UP_ARROW);
//          Keyboard.release(KEY_RIGHT_ARROW);
//          Keyboard.release(KEY_LEFT_ARROW);
//        }
      }
      
      else if (total3 <100)
     {
      Keyboard.release(KEY_RIGHT_ARROW);
     } 
      
      if (total2 > 100)
      {
        if (total3 < 70)
        {
          Keyboard.press(KEY_LEFT_ARROW);
          Keyboard.release(KEY_RIGHT_ARROW);
          Keyboard.release(KEY_UP_ARROW);
        }
//        else if (total3 > 70)
//        {
//         Keyboard.press(KEY_UP_ARROW);
//         Keyboard.release(KEY_LEFT_ARROW);
//         Keyboard.release(KEY_RIGHT_ARROW);
//        }
      }
      else if(total2 < 70)
      {
         Keyboard.release(KEY_LEFT_ARROW); 
      }
   }    
}


void openWebsiteMac()
{
  
   delay(500); 
   
    //escape twice to be safe
   Keyboard.press(177); Keyboard.releaseAll();
   delay(500);
   Keyboard.press(177); Keyboard.releaseAll();
   delay(500);
   Keyboard.press(177); Keyboard.releaseAll();
   delay(1000);
   Keyboard.press(177); Keyboard.releaseAll();
   
   Keyboard.press(131); //left gui
   Keyboard.press(' '); //space
   Keyboard.release(131); //left gui
   Keyboard.release(' '); //space
   delay(1000);  
   
    ////fail safe if Windows user opens mac option (lock screen)
   Keyboard.press(131); //left gui
   Keyboard.press('l');
   Keyboard.releaseAll(); //left gui
   delay(2000);

       ////fail safe if Windows user opens mac option (lock screen)
   Keyboard.press(131); //left gui
   Keyboard.press('l');
   Keyboard.releaseAll(); //left gui
   delay(5000);
   
   //escape twice to be safe
//   Keyboard.press(58); Keyboard.releaseAll();
//   Keyboard.press(58); Keyboard.releaseAll();
   
   ////open OSX search bar
//   Keyboard.press(131); //left gui
//   Keyboard.press(' '); //space
//   Keyboard.release(131); //left gui
//   Keyboard.release(' '); //space
//   delay(500); 
//   
   // //open terminal
   Keyboard.print("Terminal.app");
   delay(3000);
   Keyboard.press(176);
   Keyboard.release(176);
   delay(1000);
   Keyboard.press(176);
   Keyboard.release(176);
   delay(1000);
   Keyboard.press(176);
   Keyboard.release(176);
   delay(2000);
   Keyboard.press(176);
   Keyboard.release(176);
   Keyboard.println("clear");
   Keyboard.press(176);
   Keyboard.release(176);
   delay(2000);
   Keyboard.println("foo(){");
   Keyboard.press(176); Keyboard.release(176);
   Keyboard.println("cat << EOF");
   Keyboard.press(176); Keyboard.release(176);
   Keyboard.println("");                                    
   Keyboard.press(176); Keyboard.release(176);                         
   Keyboard.println("hh   hh   aaa    ccccc  kk  kk yy   yy");
   Keyboard.press(176); Keyboard.release(176);
   Keyboard.println("hh   hh  aaaaa  cc    c kk kk  yy   yy");
   Keyboard.press(176); Keyboard.release(176);
   Keyboard.println("hhhhhhh aa   aa cc      kkkk    yyyyy");
   Keyboard.press(176); Keyboard.release(176);
   Keyboard.println("hh   hh aaaaaaa cc    c kk kk    yyy");
   Keyboard.press(176); Keyboard.release(176);
   Keyboard.println("hh   hh aa   aa  ccccc  kk  kk   yyy");
   Keyboard.press(176); Keyboard.release(176);
   Keyboard.println(" ");
   Keyboard.println(" ");
   Keyboard.press(176); Keyboard.release(176);
   Keyboard.press(176); Keyboard.release(176);
   Keyboard.println("xx    xx mm    mm   aaa    sssss");
   Keyboard.press(176); Keyboard.release(176);
   Keyboard.println(" xx  xx  mmm  mmm  aaaaa  ss");
   Keyboard.press(176); Keyboard.release(176);
   Keyboard.println("  xxxx   mm mm mm aa   aa  sssss");                                                              
   Keyboard.press(176); Keyboard.release(176);
   Keyboard.println(" xx  xx  mm    mm aaaaaaa      ss");                                                              
   Keyboard.press(176); Keyboard.release(176);
   Keyboard.println("xx    xx mm    mm aa   aa  sssss");
   Keyboard.press(176); Keyboard.release(176);
   Keyboard.println(" ");
   Keyboard.println(" ");            
   Keyboard.press(176); Keyboard.release(176);                                               
   Keyboard.press(176); Keyboard.release(176);
   Keyboard.println("nn   nn   aaa   vv     vv iiiii ddddd");
   Keyboard.press(176); Keyboard.release(176);
   Keyboard.println("nnn  nn  aaaaa  vv     vv  iii  dd  dd");
   Keyboard.press(176); Keyboard.release(176);
   Keyboard.println("nn n nn aa   aa  vv   vv   iii  dd   dd");
   Keyboard.press(176); Keyboard.release(176);
   Keyboard.println("nn  nnn aaaaaaa   vv vv    iii  dd   dd");
   Keyboard.press(176); Keyboard.release(176);
   Keyboard.println("nn   nn aa   aa    vvv    iiiii dddddd");
   Keyboard.press(176); Keyboard.release(176);
   Keyboard.press(176); Keyboard.release(176);
   Keyboard.println("EOF");
   Keyboard.press(176); Keyboard.release(176);
   Keyboard.println("}");
   Keyboard.press(176); Keyboard.release(176);
   delay(500);
   //talk to users
   Keyboard.println("say Hacky Christmas Navid, with love from the team at Kerve.; open http://www.hackyxmas.com/controller/dcle2cm72f; clear; killall Terminal");   
   Keyboard.press(176); Keyboard.release(176);
   delay(500);
   //open site
   Keyboard.press(176);
   Keyboard.release(176);
   delay(10000);

   startUpMac = false;
   startUpPc = false;
   gameStart = true;
}

void openWebsitePc()
{  

  
   Keyboard.releaseAll();
   Keyboard.releaseAll();
 
   //escape twice to be safe
   delay(500);
   Keyboard.press(177); Keyboard.releaseAll();
   delay(500);
   Keyboard.press(177); Keyboard.releaseAll();
   delay(500);
   Keyboard.press(177); Keyboard.releaseAll();
   delay(1000);
   Keyboard.press(177); Keyboard.releaseAll();
  
   delay(2000);
   Keyboard.releaseAll();
   Keyboard.releaseAll();
//   ////fail safe if mac user opens windows option
   Keyboard.press(131); //left gui
   Keyboard.press(' '); //space
   Keyboard.release(131); //left gui
   Keyboard.release(' '); //space

   delay(1000); 

   Keyboard.print("TextEdit.app");
   delay(1000); 
   Keyboard.press(176);
   Keyboard.release(176);
   Keyboard.press(176);
   Keyboard.release(176);
   delay(500);
   Keyboard.press(131); //left gui
   Keyboard.press('n'); //left gui
   delay(500);
   Keyboard.release(131); //left gui
   Keyboard.release('n'); //left gui
   delay(500);
   Keyboard.press(176);
   Keyboard.release(176);
   Keyboard.press(176);
   Keyboard.release(176);
   delay(2000);
   
   //escape twice to be safe
   Keyboard.press(177); Keyboard.releaseAll();
   Keyboard.press(177); Keyboard.releaseAll();
   delay(500);
   //open windows search bar
   Keyboard.press(131); //left gui
   Keyboard.release(131); //left gui
   delay(5000);
    
       // //open terminal
   Keyboard.print("Command Prompt");
   delay(3000);
   Keyboard.press(176);
   Keyboard.release(176);
  
   delay(1500);
   Keyboard.press(176);
   Keyboard.release(176);
   delay(1500);
   Keyboard.press(176);
   Keyboard.release(176);
   delay(5000);  

   delay(500);
   Keyboard.press(177); Keyboard.releaseAll();
   delay(1000);
   Keyboard.press(177); Keyboard.releaseAll();
   delay(5000);
   
    //open windows search bar
   Keyboard.press(131); //left gui
   Keyboard.release(131); //left gui
   delay(5000);
    
       // //open terminal a second time to be safe
   Keyboard.print("Command Prompt");
   delay(1500);
   Keyboard.press(176);
   Keyboard.release(176);
  
   delay(1500);
   Keyboard.press(176);
   Keyboard.release(176);
   delay(1500);
   Keyboard.press(176);
   Keyboard.release(176);
   delay(7000);  
   

   //:
   Keyboard.press(129); Keyboard.press(58); Keyboard.release(58);

   //:
   Keyboard.press(129); Keyboard.press(58); Keyboard.release(58);
   
   //:
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
 

   Keyboard.println("hh   hh   aaa    ccccc  kk  kk yy   yy");
   delay(500); 
   Keyboard.press(176); Keyboard.release(176);
   Keyboard.press(129); Keyboard.press(58); Keyboard.release(58); 

   //:
   Keyboard.press(129); Keyboard.press(58); Keyboard.release(58); 

   //:
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();

   
   Keyboard.println("hh   hh  aaaaa  cc    c kk kk  yy   yy");
   delay(500); 
   Keyboard.press(176); Keyboard.release(176);
   
   Keyboard.press(129); Keyboard.press(58); Keyboard.release(58); 

   //:
   Keyboard.press(129); Keyboard.press(58); Keyboard.release(58); 
    
   //:
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
 
   
   Keyboard.println("hhhhhhh aa   aa cc      kkkk    yyyyy");
   delay(500); 
   Keyboard.press(176); Keyboard.release(176);
   
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   
   Keyboard.println("hh   hh aaaaaaa cc    c kk kk    yyy");
   delay(500); 
   Keyboard.press(176); Keyboard.release(176);

   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   
   Keyboard.println("hh   hh aa   aa  ccccc  kk  kk   yyy");
   delay(500); 
   Keyboard.press(176); Keyboard.release(176);

   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();

   Keyboard.println("xx    xx mm    mm   aaa    sssss");
   delay(500); 
   Keyboard.press(176); Keyboard.release(176);
   
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();

   Keyboard.println(" xx  xx  mmm  mmm  aaaaa  ss");
   delay(500); 
   Keyboard.press(176); Keyboard.release(176);
 
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();

   Keyboard.println("  xxxx   mm mm mm aa   aa  sssss");
   delay(500); 
   Keyboard.press(176); Keyboard.release(176);
 
 
    Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();

   Keyboard.println(" xx  xx  mm    mm aaaaaaa      ss");
   delay(500); 
   Keyboard.press(176); Keyboard.release(176);
 
 
    Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();

   Keyboard.println("xx    xx mm    mm aa   aa  sssss");
   delay(500); 
   Keyboard.press(176); Keyboard.release(176);
 
    Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();

   Keyboard.println("nn   nn   aaa   vv     vv iiiii ddddd");
   delay(500); 
   Keyboard.press(176); Keyboard.release(176);
   
       Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();

   Keyboard.println("nnn  nn  aaaaa  vv     vv  iii  dd  dd");
   delay(500); 
   Keyboard.press(176); Keyboard.release(176);
   
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();

   Keyboard.println("nn n nn aa   aa  vv   vv   iii  dd   dd");
   delay(500); 
   Keyboard.press(176); Keyboard.release(176);

   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();

   Keyboard.println("nn  nnn aaaaaaa   vv vv    iii  dd   dd");
   delay(500); 
   Keyboard.press(176); Keyboard.release(176);

   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();

   Keyboard.println("nn   nn aa   aa    vvv    iiiii dddddd");
   delay(500); 
   Keyboard.press(176); Keyboard.release(176);
   Keyboard.press(176); Keyboard.release(176);
   delay(4000);
   Keyboard.releaseAll();
   //open site
   delay(500);
   Keyboard.print("start http");

   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   delay(500);
   Keyboard.print("//www.hackyxmas.com/controller/dcle2cm72f");
   Keyboard.press(129); Keyboard.press(55); Keyboard.releaseAll();
   delay(1000);
   Keyboard.press(129); Keyboard.press(55); Keyboard.releaseAll();
   delay(1000);
   Keyboard.println(" exit");
   delay(500);
   Keyboard.press(176);
   Keyboard.release(176);
   Keyboard.press(176);
   Keyboard.release(176);
   delay(1500);
   
   //message to mac user who accidentally pressed windows:
   Keyboard.println("You pressed the Windows button! Close the Notes application, replug in the usb and tap the Mac button on the controller.");
   
   startUpPc = false;
   startUpMac = false; 
   gameStart = true;
}
