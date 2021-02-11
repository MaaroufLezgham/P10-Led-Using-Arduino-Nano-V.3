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
int hours,minutes, seconds,months,years,days;
int hours0,minutes0,seconds0;
int H0,M0;
bool exam,ends;
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
bool adjt,uppt,downn,st;
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
  seconds++;
  if (seconds>59)
  {
    seconds=0;
    minutes++;
  }
  if (minutes>59)
  {
   minutes=0;
   hours++;
  }
  if (hours>23)
  {
     hours=0;
  }
if (hours<10 )
{
shours='0' + String(hours);
}
else 
{
shours=String(hours);
}
//---
if ( minutes <10 )
{
sminutes='0'+ String( minutes);
}
else 
{
sminutes=String( minutes);
}
//-----

    
}
//-----
void  rtc_time ()
{
       DateTime now = rtc.now();
    hours= now.hour();
   minutes=now.minute();
   seconds=now.second();
   days=now.day();
   months=now.month();
   shours=String(hours);
   sminutes=String(minutes);
   sdays=String(days);
   smonths=String(months);
  if (hours<10 )
{
shours='0' + String(hours);
}
else 
{
shours=String(hours);
}
//---
if ( minutes <10 )
{
sminutes='0'+ String( minutes);
}
else 
{
sminutes=String( minutes);
}
//-----
if (seconds <10 )
{
sseconds='0' + String(seconds);
}
else 
{
  sseconds= String(seconds);
}

//--
if (days <10 )
{
sdays='0' + String(days);
}
else 
{
  sdays =String(days);
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
    digitalWrite(buzzer,LOW);
    hours0=1;
    minutes0=30;
     shours0="01";
    sminutes0="30";
     sp=0;
   last_minutes=0;
  exam=false;
  ends=false;
  adjt=false;
  uppt=false;
  downn=false;
//rtc.adjust(DateTime(2021, 01, 26, 12, 22, 0));
}
//---

void read_serial()
 {
if ( Serial.available())
{

  data= Serial.readString();
if(data.indexOf("start")!=-1)
{
exam=true;
    }
  else if(data.indexOf("adjst")!=-1)
{
adjt=true;
    }
   else if(data.indexOf("up")!=-1)
{
uppt=true;
    }
   else if(data.indexOf("down")!=-1)
{
downn=true;
    }

else if (data[0]=='H')
{
  data.remove(0,1); 
  hours=data.toInt();
  Serial.print("hours =");
   Serial.println(hours);
}

else if (data[0]=='M')
{
  data.remove(0,1); 
minutes=data.toInt();
 Serial.print("minutes =");
   Serial.println(minutes);
}
else if (data[0]=='h')
{
  data.remove(0,1); 
 hours0=data.toInt();
 Serial.print("hours0 =");
   Serial.println(hours0);
}
else if (data[0]=='m')
{
  data.remove(0,1); 
 minutes0=data.toInt();
 Serial.print("minutes0 =");
   Serial.println(minutes0);
}
}
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
read_serial();
switch(sp)
{
  case 0: 
rtc_time ();
data=shours+ ':' + sminutes + sdays +'/'+ smonths;  
aff_text(data);

if (digitalRead(startt)==LOW|| exam==true)
{
  
  exam=false;
   digitalWrite(buzzer,HIGH);
 
while (digitalRead(startt)==LOW|| exam==true)
{
  
}
 digitalWrite(buzzer,LOW); 

 sp=2;
}

//----


//--------------------------------------------
 if (digitalRead(adjst)==LOW || adjt==true)
{
  adjt=false;
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
    H0= hours0+hours;
    M0=minutes0+minutes;
    sref=  H0*3600+M0*60+seconds;
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
  Serial.println("exmaends");
    }
    delay(500);
break;
//*************************************************************************
case 5: 
data="HEUR: " + shours;
aff_text(data);
if (digitalRead(up)==LOW || uppt==true)
    {
       uppt=false;
      digitalWrite(buzzer,HIGH);
       while (digitalRead(up)==LOW)
       {
        }
digitalWrite(buzzer,LOW);
hours++;
 rtc.adjust(DateTime(2021, 01, 9, hours, minutes, seconds));
 dmd.clearScreen( true ); 
 
    }
//---------------------------------------------------------------------------------------------------------------------
else if (digitalRead(down)==LOW|| downn== true)
    {
      downn=false;
      digitalWrite(buzzer,HIGH);
       while (digitalRead(down)==LOW)
       {
        }
digitalWrite(buzzer,LOW);
hours--;
 rtc.adjust(DateTime(2021, 01, 9, hours, minutes, seconds));
 dmd.clearScreen( true ); 
    }
//-----------------------------------------------------------------------------------------
else if (digitalRead(adjst)==LOW || adjt== true)
    {
      adjt= false;
      digitalWrite(buzzer,HIGH);
       while (digitalRead(adjst)==LOW)
       {
        }
digitalWrite(buzzer,LOW);
sp=6;
 dmd.clearScreen( true ); 
    }
shours=String(hours);
delay(1000);
break;
//*************************************************************************
case 6: 
data="MUNT: " + sminutes;
aff_text(data);
if (digitalRead(up)==LOW || uppt==true)
    {
       uppt=false;
        digitalWrite(buzzer,HIGH);
       while (digitalRead(up)==LOW)
       {
        }
digitalWrite(buzzer,LOW);
minutes++;
 rtc.adjust(DateTime(2021, 01, 9, hours, minutes, seconds));
 dmd.clearScreen( true ); 
    }
//------------------------------------------------------
else if (digitalRead(down)==LOW|| downn== true)
    {
      downn=false;
      digitalWrite(buzzer,HIGH);
       while (digitalRead(down)==LOW)
       {
        }
digitalWrite(buzzer,LOW);
minutes--;
 rtc.adjust(DateTime(2021, 01, 9, hours, minutes, seconds));
 dmd.clearScreen( true ); 
    }
//------------------------------------------------------------------------------------------
else if (digitalRead(adjst)==LOW || adjt== true)
    {
      adjt= false;
      digitalWrite(buzzer,HIGH);
       while (digitalRead(adjst)==LOW)
       {
        }
digitalWrite(buzzer,LOW);
sp=7;
 dmd.clearScreen( true ); 
    }
    sminutes=String(minutes);
    delay(1000);
break;
 //*************************************************************************
case 7:
data="HEXM  :" + shours0;
aff_text(data);
if (digitalRead(up)==LOW || uppt==true)
   
      {
        uppt=false;
            digitalWrite(buzzer,HIGH);
       while (digitalRead(up)==LOW)
       {
        }
digitalWrite(buzzer,LOW);
hours0++;
  dmd.clearScreen( true ); 
    }
//----------------------------------------------------------------------------
else if (digitalRead(down)==LOW|| downn== true)
    {
      downn=false;
      digitalWrite(buzzer,HIGH);
       while (digitalRead(down)==LOW)
       {
        }
digitalWrite(buzzer,LOW);
hours0--;
 dmd.clearScreen( true ); 
    }
//---------------------------------------------------------------------------------
else if (digitalRead(adjst)==LOW || adjt== true)
    {
      adjt= false;
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
if (digitalRead(up)==LOW || uppt==true)
    {
       uppt=false;
   
      digitalWrite(buzzer,HIGH);
       while (digitalRead(up)==LOW)
       {
        }
digitalWrite(buzzer,LOW);
minutes0=minutes0+15;
  dmd.clearScreen( true ); 
    }
//------------------------------------------------------
else if (digitalRead(down)==LOW|| downn== true)
    {
      downn=false;
      digitalWrite(buzzer,HIGH);
       while (digitalRead(down)==LOW)
       {
        }
digitalWrite(buzzer,LOW);
minutes0=minutes0-15;
 dmd.clearScreen( true ); 
    }
//-----------------------------------
else if (digitalRead(adjst)==LOW || adjt== true)
    {
      adjt= false;
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
 s=sref- (hours*3600+minutes*60+seconds);

 //-----
  if (s==1  || digitalRead(startt)==LOW || exam==true)
{
  exam=false;
  digitalWrite(buzzer,HIGH);
while (digitalRead(startt)==LOW)
{
 }
     digitalWrite(buzzer,LOW);
    Serial.println("ends!!");
    ends=true;
   data="ENDS!!!!";
   aff_text(data);
   delay(3000); 
       
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
 //-------------
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
