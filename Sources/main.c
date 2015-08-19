#include <hidef.h>      /* common defines and macros */
#include <mc9s12c128.h>     /* derivative information */
#pragma LINK_INFO DERIVATIVE "mc9s12c128"



void main(void) {
  /* put your own code here */
    int b1on =0;
    int b2on =0;
    int led=0;
    int inc=0;
    int paused =0;
  
  //Setting Ports B0-B3 to imputs
  DDRB_BIT0 = 0x1;
  DDRB_BIT1 = 0x1;
  DDRB_BIT2 = 0x1;
  DDRB_BIT3 = 0x1;

  //Setting Ports A0-A2 to be inputs
  
  DDRA_BIT0 = 0x0;
  DDRA_BIT1 = 0x0;
  DDRA_BIT2 = 0x0;


	
	EnableInterrupts;

 

  for(;;) {
    _FEED_COP(); /* feeds the dog */
    
     // step on LED to light forwards
     if (b1on && !paused){
        PORTB =0x1<<(led%4);
        if (inc > 5000){
          inc = 0;
          led++;
          led = led % 4;
        }
        inc++;
     }
     //step on LED to light backwards 
     if (b2on && !paused){
        PORTB =0x1<<(led%4);
        if (inc > 5000){
          inc = 0;
          led--;
          led = led % 4;
        }
        inc++;
     } 
     if (led < 0) {
        led =3;
     }
     
     //switch roles of buttons when b2 is on
     if ((PORTA_BIT0 == 0x0) && (b2on)){
         b1on = !b1on;
         b2on = !b2on;
         while(PORTA_BIT0 == 0x0){}
     //reset button 1 back to be on
     }else if((PORTA_BIT0 == 0x0) && (!b2on)){
         b1on = 1;

     }else if ((PORTA_BIT1 == 0x0) && (b1on)){
         b2on = !b2on;
         b1on = !b1on;
         while(PORTA_BIT1 == 0x0){}
     }else if ((PORTA_BIT0 == 0x0) && (!b1on)){
         b2on = 1;
     }
     if (PORTA_BIT2 == 0){
         paused = !paused;
         while(PORTA_BIT2 == 0x0){}         
     }

  } /* loop forever */
  /* please make sure that you never leave main */
}
