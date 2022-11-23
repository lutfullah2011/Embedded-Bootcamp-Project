#include <16f877.h>

#device adc=10
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD
#use delay(clock=4000000)

#define use_portb_lcd TRUE //
#include <LCD.C>

#define adc_step 0.0048828125//( 5V /2^10 ) We use this macro to calculate VOLTAGE level.


int16 i;
#INT_AD
void AD_int()
{     
   for (i=0;i<=10000;i++)//Producing Some delay
   output_high(pin_c0);
    
   for (i=0;i<=10000;i++)//Producing Some delay
   output_low(pin_c0);


}

   
unsigned long int adcValue;

float voltage;

void main()
{

   set_tris_a(0x0F);
   set_tris_c(0x00);   
   output_c(0x00);

   setup_adc_ports(AN0_AN1_AN3);
   setup_adc(ADC_CLOCK_INTERNAL);
  
   enable_interrupts(INT_AD);
   enable_interrupts(GLOBAL);   
   
   
   lcd_init();   
   printf(lcd_putc,"\f ADC APPLICATION ");
   delay_ms(500);
   
   while(1)
   {
      set_adc_channel(0);     
      delay_us(20);      
      adcValue = read_adc();
      voltage=adc_step*adcValue; 
      
      printf(lcd_putc,"\f--Channel AN0--");
      delay_ms(1500);
      printf(lcd_putc,"\f Digital=%lu",adcValue);
      printf(lcd_putc,"\n Voltage=%0.2fV",voltage);
      delay_ms(2000);
      
      
      set_adc_channel(1);      
      delay_us(20);     
      adcValue=read_adc();      
      voltage=adc_step*adcValue;  
      
      printf(lcd_putc,"\f--Channel AN1--");
      delay_ms(1500);
      printf(lcd_putc,"\fDigital=%lu",adcValue);
      printf(lcd_putc,"\nVoltage=%0.2fV",voltage);     
      delay_ms(2000);
 
   }
   
}

