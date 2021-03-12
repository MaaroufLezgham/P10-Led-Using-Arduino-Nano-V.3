#include <FlexiTimer2.h>
#include <SPI.h>        //SPI.h must be included as DMD is written by SPI (the IDE complains otherwise)
#include <DMD.h>        //
#include <TimerOne.h>   //
#include "SystemFont5x7.h"
#include "RTClib.h"
String data0="IHE ESPITA";
RTC_DS1307 rtc;
String  rctsdays;
int last_minutes;
char text[]={' ',' ',' ',' ',' ' };
String shours,sminutes,sseconds,shours0,sminutes0,smonths,sdays;
int hours,minutes, seconds,months,years,days;
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
int k;
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
  Timer1.initialize( 6000 );  
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
   ends=false;
  k=0;
  

}
//---


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
 
switch(sp)
{
  case 0: 
rtc_time ();
data=shours+ ':' + sminutes + sdays +'/'+ smonths;  
aff_text(data);

if (digitalRead(startt)==LOW)
{
   digitalWrite(buzzer,HIGH);

while (digitalRead(startt)==LOW)
{
  }
 digitalWrite(buzzer,LOW); 

 sp=2;
 goto st1;
}

//--------------------------------------------
 else if (digitalRead(adjst)==LOW)
{
 digitalWrite(buzzer,HIGH);
while (digitalRead(adjst)==LOW)
{
 }
 digitalWrite(buzzer,LOW);
 sp=5;
 goto st2;
}
delay(1000);
 break;
 //*************************************************************************
st1:
case 2:
Serial.println("sp2");
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
    Serial.println("sp3");
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
    FlexiTimer2::stop(); 
    ends=false;
    sp=0;
    }
   delay(200);  
break;
//*************************************************************************
st2:
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
if (hours>23)
{
hours=0;
}
else
{
hours++;
}
 rtc.adjust(DateTime(2021, months, days, hours, minutes, seconds));
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
if (hours<0)
{
hours=23;
}
else
{
hours--;
}
 rtc.adjust(DateTime(2021, months, days, hours, minutes, seconds));
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
shours=String(hours);
delay(200);
break;
//*************************************************************************
case 6: 
data="MUNT: " + sminutes;
aff_text(data);
if (digitalRead(up)==LOW)
    {        digitalWrite(buzzer,HIGH);
       while (digitalRead(up)==LOW)
       {
        }
digitalWrite(buzzer,LOW);
if (minutes>59)
{
minutes=0;
}
else
{
minutes++;
}
  rtc.adjust(DateTime(2021, months, days, hours, minutes, seconds));
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
if( minutes<0)
{
minutes=59;
}
else 
{
minutes--;
}
 rtc.adjust(DateTime(2021, months, days, hours, minutes, seconds));
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
    sminutes=String(minutes);
    delay(200);
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
   delay(200);
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
if (minutes0==0)
{
minutes0=0;
}
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
sp=9;
 dmd.clearScreen( true ); 
    }
        sminutes0=String(minutes0);
        delay(200);
break;
//--------------------------

case 9:
data="DAYS:  " + sdays;
aff_text(data);
if (digitalRead(up)==LOW )
    {
     
      digitalWrite(buzzer,HIGH);
       while (digitalRead(up)==LOW)
       {
        }
digitalWrite(buzzer,LOW);
if(days>31)
{
days=1;
}
else
{
  days++;
}
 rtc.adjust(DateTime(2021, months, days, hours, minutes, seconds));
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
if(days<1)
{
days=31;
}
else
{
  days--;
}
 dmd.clearScreen( true ); 
 rtc.adjust(DateTime(2021, months, days, hours, minutes, seconds));
 
    }
//-----------------------------------
else if (digitalRead(adjst)==LOW )
    {
       digitalWrite(buzzer,HIGH);
       while (digitalRead(adjst)==LOW)
       {
        }
digitalWrite(buzzer,LOW);
sp=10;
 dmd.clearScreen( true ); 
    }
     sdays=String(days);
        delay(200);
break;
//-------------------------------------------

case 10:
data="MNTH:  " + smonths;
aff_text(data);
if (digitalRead(up)==LOW )
    {
     
      digitalWrite(buzzer,HIGH);
       while (digitalRead(up)==LOW)
       {
        }
digitalWrite(buzzer,LOW);
if(months>12)
{
months=1;
}
else
{
  months++;
}
 rtc.adjust(DateTime(2021, months, days, hours, minutes, seconds));
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
if(months<1)
{
days=31;
}
else
{
  months--;
}
 rtc.adjust(DateTime(2021, months, days, hours, minutes, seconds));
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
       smonths=String(months);
        delay(200);
break;
}
}
//--------------------------------------------------------------

void aff_time()
{
 s=sref- (hours*3600+minutes*60+seconds);

 //-----


 
  if ((s>0 && s<2)  || digitalRead(startt)==LOW  )
{
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
else if (s<3600 && s>3598)
 {
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
 }
 else if (s<1800 && s>1798)
 {
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
 }
 else if (s<900 && s>898)
 {
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
 }
else if (s<10 && s>8)

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

 if(pm<10)
 {
   spm='0' + String(pm);
 }
 else 
 {
  spm= String(pm);
 }

 

  dmd.clearScreen( true );
    dmd.drawChar(0,5, '0', GRAPHICS_NORMAL );
   dmd.drawChar(6,5, sph[0], GRAPHICS_NORMAL );
    dmd.drawChar(12,5, ':', GRAPHICS_NORMAL );
     dmd.drawChar(18,5, spm[0], GRAPHICS_NORMAL );
      dmd.drawChar(24,5, spm[1], GRAPHICS_NORMAL );
      delay(200);
      //-----------------------------------
        
 //----
 
}
