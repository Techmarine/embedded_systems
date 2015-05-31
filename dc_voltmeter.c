// LCD module connections
sbit LCD_RS at RB4_bit;
sbit LCD_EN at RB5_bit;
sbit LCD_D4 at RB0_bit;
sbit LCD_D5 at RB1_bit;
sbit LCD_D6 at RB2_bit;
sbit LCD_D7 at RB3_bit;
sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7_Direction at TRISB3_bit;

unsigned char value;
unsigned int adc_output;
char *text;
long millivolts;

//Libraries used:
// - LCD
// - ADC
//for more information see http://www.mikroe.com/mikroc/pic/libraries/

void main() {
     INTCON = 0;                                //interrupts disabled
     ANSEL = 0x04;                              //RA2 is an analog input
     TRISA = 0x04;
     ANSELH = 0;                                //the other pins are digital

     Lcd_Init();                                //LCD initialization
     Lcd_Cmd(_LCD_CURSOR_OFF);                  //cursor off
     Lcd_Cmd(_LCD_CLEAR);                       //clear screen

     text = "DC Voltmeter Demo";                //first line
     Lcd_Out(1,1,text);                         //writing it to LCD
     text = "Please wait...";                   //second line
     Lcd_Out(2,1,text);                         //writing it to LCD

     ADCON1 = 0x82;                             //setting VCC as a reference for ADC
     TRISA = 0xFF;                              //all A ports are inputs
     //Delay_ms(2000);

     text = "Voltage:";                         //measured quantity

     while(1)
     {
          adc_output = ADC_Read(2);             //getting data from ADC
          Lcd_Out(2,1,text);                    //displaying measured quantity
          millivolts = (long)adc_output*5000;   //converting to millivolts
          millivolts = millivolts/1023;

          //Integer part
          value = millivolts/1000;
          Lcd_Chr(2,9,48 + value);
          Lcd_Chr_CP('.');

          //Fractional part up to 3 digits
          value = (millivolts / 100) % 10;
          Lcd_Chr_CP(48 + value);
          value = (millivolts / 10) % 10;
          Lcd_Chr_CP(48 + value);
          value = millivolts % 10;
          Lcd_Chr_CP(48 + value);

          Lcd_Chr_CP('V');                      //V for Vendetta
          Delay_ms(1);                          //LCD refresh rate
     }
}