
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
   
   Keyboard.press(KEY_LEFT_GUI); //left gui
   Keyboard.press(' '); //space
   Keyboard.release(KEY_LEFT_GUI); //left gui
   Keyboard.release(' '); //space
   delay(1000);  
   
    ////fail safe if Windows user opens mac option (lock screen)
   Keyboard.press(KEY_LEFT_GUI); //left gui
   Keyboard.press('l');
   Keyboard.releaseAll(); //left gui
   delay(1000);
   
   //escape twice to be safe
//   Keyboard.press(58); Keyboard.releaseAll();
//   Keyboard.press(58); Keyboard.releaseAll();
   
   ////open OSX search bar
//   Keyboard.press(KEY_LEFT_GUI); //left gui
//   Keyboard.press(' '); //space
//   Keyboard.release(KEY_LEFT_GUI); //left gui
//   Keyboard.release(' '); //space
//   delay(500); 
//   
   // //open terminal
   Keyboard.print("Terminal.app");
   delay(2000);
   Keyboard.press(KEY_RETURN);
   Keyboard.release(KEY_RETURN);
   delay(1000);
   Keyboard.press(KEY_RETURN);
   Keyboard.release(KEY_RETURN);
   delay(1000);
   Keyboard.press(KEY_RETURN);
   Keyboard.release(KEY_RETURN);
   delay(2000);
   Keyboard.press(KEY_RETURN);
   Keyboard.release(KEY_RETURN);
   Keyboard.println("clear");
   Keyboard.press(KEY_RETURN);
   Keyboard.release(KEY_RETURN);
   delay(2000);
   Keyboard.println("foo(){");
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);
   Keyboard.println("cat << EOF");
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);
   Keyboard.println("");                                    
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);                         
   Keyboard.println("hh   hh   aaa    ccccc  kk  kk yy   yy");
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);
   Keyboard.println("hh   hh  aaaaa  cc    c kk kk  yy   yy");
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);
   Keyboard.println("hhhhhhh aa   aa cc      kkkk    yyyyy");
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);
   Keyboard.println("hh   hh aaaaaaa cc    c kk kk    yyy");
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);
   Keyboard.println("hh   hh aa   aa  ccccc  kk  kk   yyy");
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);
   Keyboard.println(" ");
   Keyboard.println(" ");
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);
   Keyboard.println("xx    xx mm    mm   aaa    sssss");
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);
   Keyboard.println(" xx  xx  mmm  mmm  aaaaa  ss");
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);
   Keyboard.println("  xxxx   mm mm mm aa   aa  sssss");                                                              
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);
   Keyboard.println(" xx  xx  mm    mm aaaaaaa      ss");                                                              
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);
   Keyboard.println("xx    xx mm    mm aa   aa  sssss");
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);
   Keyboard.println(" ");
   Keyboard.println(" ");            
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);                                               
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);
   Keyboard.println("ttttttt  ooooo  mm    mm");
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);
   Keyboard.println("  ttt   oo   oo mmm  mmm");
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);
   Keyboard.println("  ttt   oo   oo mm mm mm");
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);
   Keyboard.println("  ttt   oo   oo mm    mm");
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);
   Keyboard.println("  ttt    oooo0  mm    mm");
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);
   Keyboard.println("EOF");
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);
   Keyboard.println("}");
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);
   delay(500);
   //talk to users
   Keyboard.println("say Hacky Xmas Tom, with love from the team at Kerve.; open http://www.hackyxmas.com/controller/a3gjj65t4a; clear; killall Terminal");   
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);
   delay(500);
   //open site
   Keyboard.press(KEY_RETURN);
   Keyboard.release(KEY_RETURN);
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
   Keyboard.press(KEY_LEFT_GUI); //left gui
   Keyboard.press(' '); //space
   Keyboard.release(KEY_LEFT_GUI); //left gui
   Keyboard.release(' '); //space

   delay(1000); 

   Keyboard.print("TextEdit.app");
   delay(1000); 
   Keyboard.press(KEY_RETURN);
   Keyboard.release(KEY_RETURN);
   Keyboard.press(KEY_RETURN);
   Keyboard.release(KEY_RETURN);
   delay(500);
   Keyboard.press(KEY_LEFT_GUI); //left gui
   Keyboard.press('n'); //left gui
   delay(500);
   Keyboard.release(KEY_LEFT_GUI); //left gui
   Keyboard.release('n'); //left gui
   delay(500);
   Keyboard.press(KEY_RETURN);
   Keyboard.release(KEY_RETURN);
   Keyboard.press(KEY_RETURN);
   Keyboard.release(KEY_RETURN);
   delay(2000);
   
   //escape twice to be safe
   Keyboard.press(177); Keyboard.releaseAll();
   Keyboard.press(177); Keyboard.releaseAll();
   delay(500);
   //open windows search bar
   Keyboard.press(KEY_LEFT_GUI); //left gui
   Keyboard.release(KEY_LEFT_GUI); //left gui
   delay(3000);
    
       // //open terminal
   Keyboard.print("Command Prompt");
   delay(1500);
   Keyboard.press(KEY_RETURN);
   Keyboard.release(KEY_RETURN);
  
   delay(1500);
   Keyboard.press(KEY_RETURN);
   Keyboard.release(KEY_RETURN);
   delay(1500);
   Keyboard.press(KEY_RETURN);
   Keyboard.release(KEY_RETURN);
   delay(2500);  
   

   //:
   Keyboard.press(129); Keyboard.press(58); Keyboard.release(58);

   //:
   Keyboard.press(129); Keyboard.press(58); Keyboard.release(58);
   
   //:
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
 

   Keyboard.println("hh   hh   aaa    ccccc  kk  kk yy   yy");
   delay(500); 
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);
   Keyboard.press(129); Keyboard.press(58); Keyboard.release(58); 

   //:
   Keyboard.press(129); Keyboard.press(58); Keyboard.release(58); 

   //:
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();

   
   Keyboard.println("hh   hh  aaaaa  cc    c kk kk  yy   yy");
   delay(500); 
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);
   
   Keyboard.press(129); Keyboard.press(58); Keyboard.release(58); 

   //:
   Keyboard.press(129); Keyboard.press(58); Keyboard.release(58); 
    
   //:
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
 
   
   Keyboard.println("hhhhhhh aa   aa cc      kkkk    yyyyy");
   delay(500); 
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);
   
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   
   Keyboard.println("hh   hh aaaaaaa cc    c kk kk    yyy");
   delay(500); 
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);

   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   
   Keyboard.println("hh   hh aa   aa  ccccc  kk  kk   yyy");
   delay(500); 
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);

   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();

   Keyboard.println("xx    xx mm    mm   aaa    sssss");
   delay(500); 
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);
   
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();

   Keyboard.println(" xx  xx  mmm  mmm  aaaaa  ss");
   delay(500); 
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);
 
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();

   Keyboard.println("  xxxx   mm mm mm aa   aa  sssss");
   delay(500); 
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);
 
 
    Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();

   Keyboard.println(" xx  xx  mm    mm aaaaaaa      ss");
   delay(500); 
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);
 
 
    Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();

   Keyboard.println("xx    xx mm    mm aa   aa  sssss");
   delay(500); 
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);
 
    Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();

   Keyboard.println("ttttttt  ooooo  mm    mm");
   delay(500); 
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);
   
       Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();

   Keyboard.println("  ttt   oo   oo mmm  mmm");
   delay(500); 
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);
   
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();

   Keyboard.println("  ttt   oo   oo mm mm mm");
   delay(500); 
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);

   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();

   Keyboard.println("  ttt   oo   oo mm    mm");
   delay(500); 
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);

   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();

   Keyboard.println("  ttt    oooo0  mm    mm");
   delay(500); 
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);
   Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);
   delay(4000);
   Keyboard.releaseAll();
   //open site
   delay(500);
   Keyboard.print("start http");

   Keyboard.press(129); Keyboard.press(58); Keyboard.releaseAll();
   delay(500);
   Keyboard.print("//www.hackyxmas.com/controller/a3gjj65t4a");
   Keyboard.press(129); Keyboard.press(55); Keyboard.releaseAll();
   delay(1000);
   Keyboard.press(129); Keyboard.press(55); Keyboard.releaseAll();
   delay(1000);
   Keyboard.println(" exit");
   delay(500);
   Keyboard.press(KEY_RETURN);
   Keyboard.release(KEY_RETURN);
   Keyboard.press(KEY_RETURN);
   Keyboard.release(KEY_RETURN);
   delay(1500);
   
   //message to mac user who accidentally pressed windows:
   Keyboard.println("You pressed the Windows button! Close the Notes application, replug in the usb and tap the Mac button on the controller.");
   
   startUpPc = false;
   startUpMac = false; 
   gameStart = true;
}
