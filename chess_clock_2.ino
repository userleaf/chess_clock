//   
//  Chess Clock Practice Sketches
//
//  Bob Nolan
//  3/26/2015
//

// Include LCD display library and set up pinouts
byte customChar1[8] = { //character between the remaining times of players on display
  B00001,
  B00001,
  B00001,
  B00001,
  B00001,
  B00001,
  B00001,
  B00001
};
byte customChar2[8] = { //character between the remaining times of players on display
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000
};
byte customChar3[8] = { //character that is shown on set time screen
  B00100,
  B01010,
  B10001,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);

// Declare Global Variables

int C=262;
int D=294;
int E=330;
int F=349;
int G=392;
int A=440;
int B=494;
int eu_march_n[]={E,E,F,G,G,F,E,D,C,C,D,E,D,C,C};

long long last_m;
unsigned int timeR1;
unsigned int timeR2;
unsigned long lastMilliS;
int turn,number;
int switchPin1 = 7;
int switchPin2 = 6;
boolean checkButton,switch1,switch2,last_switch1,last_switch2;
boolean flag1=0;
boolean flag2=0;
boolean begin=0;
int position=0;
int m10,m1,s10,s1,inc,mins,secs,mins1,mins2,secs1,secs2=0;

void setup() {
  timeR1 = 500;                // set initial time.  Time is in 1/10 sec
  timeR2 = 500;               
  turn=0; //to determine the who is playing
  pinMode(switchPin1,INPUT_PULLUP);  //button for P1
  pinMode(switchPin2,INPUT_PULLUP);  //button for P2
  lcd.begin(16,2);
  lcd.print("Chess Clock");
  delay(1000);
  eu_march();               //a nice opening music for the games, if not wanted the function can be deleted 
  lcd.createChar(1,customChar1);  //character between the remaining times of players on display
  lcd.createChar(2,customChar2);  //character between the remaining times of players on display
  lcd.createChar(3,customChar3);  //character to show which value the user is setting
}
void loop() {  
  if (position<5){set();} //to understand position please reed the comments on set() function
  
  if (position>4)
  {
 if (turn==0){              // dont start counting until 1st button press
    lastMilliS=millis();
 }
  if (millis()-lastMilliS >= 100) {   // every 100 msec, update time
    lastMilliS=millis();
    if((turn==1)&&(!flag1)){
      timeR1--;
    }
    if((turn==2)&&(!flag2)){
      timeR2--;
    }
    if((!flag2)&&(!flag1)){
    printTime();
    }
  }
  checkButton=digitalRead(switchPin1);   // player 1 button press
  if(!checkButton && (turn!=2)&&(!flag2)&&(!flag1)){
    turn = 2;
    timeR1=timeR1+10*inc;
    printTime();
    
  }
  checkButton=digitalRead(switchPin2);   // player 2 button press
  if(!checkButton && (turn!=1)&&(!flag2)&&(!flag1)){

    turn = 1;
    timeR2=timeR2+10*inc;
    printTime();
   
  }
  if((timeR1<=0)&&(!flag1)){            // player 1 flag
    lcd.setCursor(1,1);
    lcd.print("Flag");
    flag1=1;
  }
  if((timeR2==0)&&(!flag2)){            // player 2 flag
    lcd.setCursor(12,1);
    lcd.print("Flag");
    flag2=1;    
  }

}}
void printTime() {    
    //function to show remaining time of players
    lcd.clear(); 
    mins1=timeR1/600;
    secs1=(timeR1%600)/10;
    mins2=timeR2/600;
    secs2=(timeR2%600)/10;
    if(millis()/100!=last_m/100)
    {       
        lcd.clear();
        lcd.setCursor(7,0);
        lcd.write(1);
        lcd.setCursor(8,0);
        lcd.write(2);
        lcd.setCursor(11,0);
        //following part is needed to display time in mm:ss i.e. if the mins<9, following code prints a "0" in front to keep the digits in place
    if(mins2>9)
    {
        if(secs2>9)
        {
            lcd.print(String(mins2)+":"+String(secs2));
        }
        else if(secs2<10)
        {
            lcd.print(String(mins2)+":0"+String(secs2));    
        }
    }
    else if (mins2<10)
    {
        if(secs2>9)
        {
            lcd.print("0"+String(mins2)+":"+String(secs2));
        }
        else if(secs2<10)
        {
            lcd.print("0"+String(mins2)+":0"+String(secs2));    
        }
    }
        lcd.setCursor(0,0);
    if(mins1>9)
    {
        if(secs1>9)
        {
            lcd.print(String(mins1)+":"+String(secs1));
        }
        else if(secs1<10)
        {
            lcd.print(String(mins1)+":0"+String(secs1));    
        }
    }
    else if (mins1<10)
    {
        if(secs1>9)
        {
            lcd.print("0"+String(mins1)+":"+String(secs1));
        }
        else if(secs1<10)
        {
            lcd.print("0"+String(mins1)+":0"+String(secs1));    
        }
    }
}last_m=millis();
}
void set()
{
//the funtion to set game time and increment 99:59+60 is max which can be changed easily or an h variable can be added with the method used here
    setdisplay();
    
    
    switch1=digitalRead(switchPin1);
        if (switch1 != last_switch1) 
        {
            if (switch1 == LOW) 
            { 
                delay(200);//to debounce buttons it is not the best way to do so but there are no notable problems at this stage of application to delay
                position++; // if P1 button pressed position increases which enables to set different digits of timer, with P2 button the digits can be increased to set the timer
                number=0;
            }
        }
    
    last_switch1 = switch1;

    

   
        if(position==0)
        {
            switch2=digitalRead(switchPin2);
        if (switch2 != last_switch2) //simple code to detect putton press
        {
            if (switch2 == LOW) 
            { delay(200);
                m10++; //increase the first digit of minutes
                if(m10>9){m10=9;}
                setdisplay();
            }
        }
    last_switch2 = switch2;
        }
       if(position==1)
        {
            switch2=digitalRead(switchPin2);
        if (switch2 != last_switch2) 
        {
            if (switch2 == LOW) 
            { delay(200);//increase the second digit of minutes
                m1++;
                if(m1>9){m1=9;};
                setdisplay();
            }
        }    last_switch2 = switch2;}
       if(position==2)
        {
            switch2=digitalRead(switchPin2);
        if (switch2 != last_switch2) 
        {
            if (switch2 == LOW) 
            { delay(200);
                s10++;//increase the first digit of seconds
                if(s10>5){s10=5;};
                setdisplay();
            }
        }    last_switch2 = switch2;
        }
if(position==3)
        {

        switch2=digitalRead(switchPin2);
        if (switch2 != last_switch2) 
        {
            if (switch2 == LOW) 
            { delay(200);
                s1++;//increase the second digit of seconds
                if(s1>9){s1=9;};
                setdisplay();
            }
        }
                last_switch2 = switch2;
        }
       if(position==4)
        {
        switch2=digitalRead(switchPin2);
        if (switch2 != last_switch2) 
        {
            if (switch2 == LOW) 
            { delay(200);
                inc++;//increase the increment per move
                if(inc>60){inc=60;};
                setdisplay();
            }
        }
            last_switch2 = switch2;

    }
    if (position>4)
    {
        mins=m10*10+m1;
        secs=s10*10+s1;
        timeR1=secs*10+mins*600;//translation from minutes+seconds to seconds*10
        timeR2=secs*10+mins*600;
        //when all set and P1 button pressed again it registers the set values 
        printTime();
    }
}
void setdisplay()
{
    //funtion called in set function to display the values while setting them
mins=m10*10+m1;
    secs=s10*10+s1;
    if(millis()/100!=last_m/100)
    {
        lcd.clear();
        lcd.setCursor(0,0);
    if(mins>9)//same code in printTime()
    {
        if(secs>9)
        {
            lcd.print(String(mins)+":"+String(secs)+"+"+String(inc));
        }
        else if(secs<10)
        {
            lcd.print(String(mins)+":0"+String(secs)+"+"+String(inc));    
        }
    }
    else if (mins<10)
    {
        if(secs>9)
        {
            lcd.print("0"+String(mins)+":"+String(secs)+"+"+String(inc));
        }
        else if(secs<10)
        {
            lcd.print("0"+String(mins)+":0"+String(secs)+"+"+String(inc));    
        }
    }
}last_m=millis();
 set_cursor();
}
void eu_march()
{ // a fun way to start games
    for (int i=0;i<13;i++)
    {
    tone(10,eu_march_n[i]);
    delay(400);
        if (i==12){delay(300);}
        if (i==14){delay(300);}
    noTone(10);
    delay(30);

    }
delay(10);

    tone(10,eu_march_n[13]);
    delay(200);
    noTone(10);
    delay(10);
    tone(10,eu_march_n[14]);
    delay(200);
    
    noTone(10);
}
void set_cursor()
{//cursor to see which value you are setting
    int millis_set_last;
    if(position==0)
    {
        lcd.setCursor(0,1);
        lcd.write(3);
    }
    if(position==1)
    {
        lcd.setCursor(1,1);
        lcd.write(3);
    }

    if(position==2)
    {
        lcd.setCursor(3,1);
        lcd.write(3);
    }
    if(position==3)
    {
        lcd.setCursor(4,1);
        lcd.write(3);
    }
    if(position==4)
    {
        lcd.setCursor(6,1);
        lcd.write(3);
    }

}