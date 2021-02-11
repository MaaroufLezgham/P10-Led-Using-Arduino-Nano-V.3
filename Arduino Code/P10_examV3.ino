#include <FlexiTimer2.h>
#include <SPI.h>        //SPI.h must be included as DMD is written by SPI (the IDE complains otherwise)
#include <DMD.h>        //
#include <TimerOne.h>   //
#include "SystemFont5x7.h"
#include "RTClib.h"
RTC_DS1307 rtc;
String  rctsdays;
int last_minutes;
char text[]={' ',' ',' ',' ',' ' };
String shours,sminutes,sseconds,shours0,sminutes0,smonths,sdays;
int hourse,minutese, secondse,months,years,dayse;
int hours0,minutes0,seconds0;
int H0,M0;
bool ends;
int ph,pm,ps,sp;
String sph,spm,sps;
uint32_t s,pr,sref;
int buzzer=A0;
int startt =2;
int adjst=3;
int up=4;
int down=5;
String data,sdata;
float z;

#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

void ScanDMD()
{ 
  dmd.scanDisplayBySPI();
}
//-------------------------------

  
void time_inr()
{
  secondse++;
  if (secondse>59)
  {
    secondse=0;
    minutese++;
  }
  if (minutese>59)
  {
   minutese=0;
   hourse++;
  }
  if (hourse>23)
  
  {
     hourse=0;
  }
if (hourse<10 )
{
shours='0' + String(hourse);
}
else 
{
shours=String(hourse);
}
//---
if ( minutese <10 )
{
sminutes='0'+ String( minutese);
}
else 
{
sminutes=String( minutese);
}
//-----

    
}
//-----
void  rtc_time ()
{
   DateTime now = rtc.now();
    hourse= now.hour();
   minutese=now.minute();
   secondse=now.second();
   dayse=now.day();
   months=now.month();
   shours=String(hourse);
   sminutes=String(minutese);
   sdays=String(dayse);
   smonths=String(months);
  if (hourse<10 )
{
shours='0' + String(hourse);
}
else 
{
shours=String(hourse);
}
//---
if ( minutese <10 )
{
sminutes='0'+ String( minutese);
}
else 
{
sminutes=String( minutese);
}
//-----
if (secondse <10 )
{
sseconds='0' + String(secondse);
}
else 
{
  sseconds= String(secondse);
}

//--
if (dayse <10 )
{
sdays='0' + String(dayse);
}
else 
{
  sdays =String(dayse);
}
//------
if (months <10 )
{
smonths='0' + String(months);
}
else 
{
  smonths =String(months);
}

 
    
}
void setup()
{
  Serial.begin(9600);
  Serial.println("fffzzYPUPUPPfzf");
 
  Timer1.initialize( 5000 );  
  Timer1.attachInterrupt( ScanDMD );
   rtc.begin();    
   dmd.clearScreen( true );  
   dmd.selectFont(SystemFont5x7); 
   pinMode(startt,INPUT_PULLUP);
    pinMode(adjst,INPUT_PULLUP);
     pinMode(up,INPUT_PULLUP);
      pinMode(down,INPUT_PULLUP);
   pinMode(buzzer,OUTPUT);
     digitalWrite(buzzer,HIGH);
     hours0=1;
    minutes0=30;
     shours0="01";
    sminutes0="30";
     sp=0;
   last_minutes=0;
  H0=0;
  M0=0;
  ends=false;
delay(2000);
   digitalWrite(buzzer,LOW);
//---
}

//---------------------------
//--------------------------------------------
void aff_text( String str)
{
   dmd.clearScreen( true );
  dmd.drawChar(0,0, str[0], GRAPHICS_NORMAL );
   dmd.drawChar(6,0, str[1], GRAPHICS_NORMAL );
    dmd.drawChar(12,0, str[2], GRAPHICS_NORMAL );
     dmd.drawChar(18,0, str[3], GRAPHICS_NORMAL );
      dmd.drawChar(24,0, str[4], GRAPHICS_NORMAL );
      //-----------------------------------
   dmd.drawChar(0,9, str[5], GRAPHICS_NORMAL );
   dmd.drawChar(6,9,str[6], GRAPHICS_NORMAL );
    dmd.drawChar(12,9,str[7], GRAPHICS_NORMAL );
     dmd.drawChar(18,9,str[8], GRAPHICS_NORMAL );
      dmd.drawChar(24,9, str[9], GRAPHICS_NORMAL );
     
      }
   
//---------------------------------------------------------------------
  
    
void loop()
{

Serial.println(sp);
switch(sp)
{
  case 0: 
//rtc_time ();
data="helooheloo";//shours+ ':' + sminutes + sdays +'/'+ smonths;  
aff_text(data);
while(1)
{
  
}
if (digitalRead(startt)==LOW)
{
  
   digitalWrite(buzzer,HIGH);
 
while (digitalRead(startt)==LOW)
{
  
}
 digitalWrite(buzzer,LOW); 

 sp=2;
}


//--------------------------------------------
 if (digitalRead(adjst)==LOW )
{
 
  digitalWrite(buzzer,HIGH);
while (digitalRead(adjst)==LOW)
{
 }
 digitalWrite(buzzer,LOW);
 sp=5;
}
delay(1000);
 break;
 //*************************************************************************
case 2:
    H0= hours0+hourse;
    M0=minutes0+minutese;
    sref=  H0*3600+M0*60+secondse;
   if (hours0<10)
{
  shours0='0' + String(hours0);
}
else 
{
  shours0=String(hours0);
}
if (minutes0<10)
{
  sminutes0='0' + String(minutes0);
}
else 
{
  sminutes0=String(minutes0);
}
 
    dmd.clearScreen( true ); 
        sp=3;
    break;
//******************************************************************************************************************
    case 3:
    data="EXAM:" +shours0 +':' + sminutes0;
   aff_text(data);
   delay(2000);
   FlexiTimer2::set(1000, time_inr); 
  FlexiTimer2::start();   
 sp=4;
   break;

//******************************************************************

case 4:
  aff_time();
   if  (ends==true)

  {
    ends=false;
    sp=0;
    }
    delay(500);
break;
//*************************************************************************
case 5: 
data="HEUR: " + shours;
aff_text(data);
if (digitalRead(up)==LOW )
    {
     
      digitalWrite(buzzer,HIGH);
       while (digitalRead(up)==LOW)
       {
        }
digitalWrite(buzzer,LOW);
hourse++;
 rtc.adjust(DateTime(2021, 01, 9, hourse, minutese, secondse));
 dmd.clearScreen( true ); 
 
    }
//---------------------------------------------------------------------------------------------------------------------
else if (digitalRead(down)==LOW)
    {
      digitalWrite(buzzer,HIGH);
       while (digitalRead(down)==LOW)
       {
        }
digitalWrite(buzzer,LOW);
hourse--;
 rtc.adjust(DateTime(2021, 01, 9, hourse, minutese, secondse));
 dmd.clearScreen( true ); 
    }
//-----------------------------------------------------------------------------------------
else if (digitalRead(adjst)==LOW )
    {
     
      digitalWrite(buzzer,HIGH);
       while (digitalRead(adjst)==LOW)
       {
        }
digitalWrite(buzzer,LOW);
sp=6;
 dmd.clearScreen( true ); 
    }
shours=String(hourse);
delay(1000);
break;
//*************************************************************************
case 6: 
data="MUNT: " + sminutes;
aff_text(data);
if (digitalRead(up)==LOW )
    {
      digitalWrite(buzzer,HIGH);
       while (digitalRead(up)==LOW)
       {
        }
digitalWrite(buzzer,LOW);
minutese++;
 rtc.adjust(DateTime(2021, 01, 9, hourse, minutese, secondse));
 dmd.clearScreen( true ); 
    }
//------------------------------------------------------
else if (digitalRead(down)==LOW)
    {
  
      digitalWrite(buzzer,HIGH);
       while (digitalRead(down)==LOW)
       {
        }
digitalWrite(buzzer,LOW);
minutese--;
 rtc.adjust(DateTime(2021, 01, 9, hourse, minutese, secondse));
 dmd.clearScreen( true ); 
    }
//------------------------------------------------------------------------------------------
else if (digitalRead(adjst)==LOW )
    {
      
      digitalWrite(buzzer,HIGH);
       while (digitalRead(adjst)==LOW)
       {
        }
digitalWrite(buzzer,LOW);
sp=7;
 dmd.clearScreen( true ); 
    }
    sminutes=String(minutese);
    delay(1000);
break;
 //*************************************************************************
case 7:
data="HEXM  :" + shours0;
aff_text(data);
if (digitalRead(up)==LOW )
   
      {
     
            digitalWrite(buzzer,HIGH);
       while (digitalRead(up)==LOW)
       {
        }
digitalWrite(buzzer,LOW);
hours0++;
  dmd.clearScreen( true ); 
    }
//----------------------------------------------------------------------------
else if (digitalRead(down)==LOW)
    {
     
      digitalWrite(buzzer,HIGH);
       while (digitalRead(down)==LOW)
       {
        }
digitalWrite(buzzer,LOW);
hours0--;
 dmd.clearScreen( true ); 
    }
//---------------------------------------------------------------------------------
else if (digitalRead(adjst)==LOW )
    {
  
      digitalWrite(buzzer,HIGH);
       while (digitalRead(adjst)==LOW)
       {
        }
digitalWrite(buzzer,LOW);
sp=8;
 dmd.clearScreen( true ); 
    }
   shours0=String(hours0);
   delay(1000);
break;
//*************************************************************************
case 8:
data="MEXM:  " + sminutes0;
aff_text(data);
if (digitalRead(up)==LOW )
    {
       digitalWrite(buzzer,HIGH);
       while (digitalRead(up)==LOW)
       {
        }
digitalWrite(buzzer,LOW);
minutes0=minutes0+15;
  dmd.clearScreen( true ); 
    }
//------------------------------------------------------
else if (digitalRead(down)==LOW)
    {
      digitalWrite(buzzer,HIGH);
       while (digitalRead(down)==LOW)
       {
        }
digitalWrite(buzzer,LOW);
minutes0=minutes0-15;
 dmd.clearScreen( true ); 
    }
//-----------------------------------
else if (digitalRead(adjst)==LOW )
    {
      digitalWrite(buzzer,HIGH);
       while (digitalRead(adjst)==LOW)
       {
        }
digitalWrite(buzzer,LOW);
sp=0;
 dmd.clearScreen( true ); 
    }
        sminutes0=String(minutes0);
        delay(1000);
break;

}
}
//--------------------------------------------------------------
void aff_time()
{
 s=sref- (hourse*3600+minutese*60+secondse);
 if (s==1 || digitalRead(startt)==LOW )
{
  digitalWrite(buzzer,HIGH);
while (digitalRead(startt)==LOW)
{
 }
     digitalWrite(buzzer,LOW);
     ends=true;
   data="ENDS!ENDS!";
   aff_text(data);
   delay(3000); 
           }
  else if (s==5400)
 {
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
 }
     
else if (s==3600)
 {
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
 }
 else if (s==1800)
 {
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
 }
 else if (s==900)
 {
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
 }
 else if (s==60)
 {
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
 }
else if (s<10)

  {
  digitalWrite(buzzer,!digitalRead(buzzer));
    }
  //----------------------------------------------
   z=s/3600.0;
    z=z-0.5;
  ph=round(z);
   //------------------------------------------
 pr=s-ph*3600;
    z=pr/60.0;
  z=z-0.5;
  pm=round(z);
 //-----------------------------------------------
ps=s-((ph*3600)+(pm*60));
 sph=String(ph);
 spm=String(pm);
 sps=String(ps);
  dmd.clearScreen( true );
   dmd.drawChar(0,0, '0', GRAPHICS_NORMAL );
   dmd.drawChar(6,0, sph[0], GRAPHICS_NORMAL );
    dmd.drawChar(12,0, ':', GRAPHICS_NORMAL );
     dmd.drawChar(18,0, spm[0], GRAPHICS_NORMAL );
      dmd.drawChar(24,0, spm[1], GRAPHICS_NORMAL );
      //-----------------------------------
    dmd.drawChar(9,9,sps[0], GRAPHICS_NORMAL );
 dmd.drawChar(14,9,sps[1], GRAPHICS_NORMAL );
    dmd.drawChar(20,9,' ', GRAPHICS_NORMAL );
     dmd.drawChar(26,9,' ', GRAPHICS_NORMAL );
      dmd.drawChar(32,9, ' ', GRAPHICS_NORMAL );
     
 //----
 
}
