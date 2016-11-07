//adc.c
#include "adc.h"
//#include "ioat91sam7x256.h"
#include <AT91SAM7X256.H>                        /* AT91SAMT7X256 definitions */

AT91PS_ADC a_pADC = AT91C_BASE_ADC;
AT91PS_PMC a_pPMC = AT91C_BASE_PMC;

void InitADC(void)   //konfiguracja ADC
{ 
  // Enable clock for interface
  a_pPMC->PMC_PCER = 1 << AT91C_ID_ADC;

  // Reset
  a_pADC->ADC_CR = 0x1;
  a_pADC->ADC_CR = 0x0;

  // Set maximum startup time and hold time
  a_pADC->ADC_MR = 0x0F1F0F00;
}


unsigned int GetAdcChanel(unsigned char chanel) {
    unsigned int result;
  
  a_pADC->ADC_CHER = chanel; // Enable desired chanel
  
  a_pADC->ADC_CR = 0x2; // Start conversion

  while(!(a_pADC->ADC_SR&chanel)); // wait for end of convertion

  switch (chanel) {
    case ADC_CHN_1: result = a_pADC->ADC_CDR0; break;
    case ADC_CHN_2: result = a_pADC->ADC_CDR1; break;
    case ADC_CHN_3: result = a_pADC->ADC_CDR2; break;
    case ADC_CHN_4: result = a_pADC->ADC_CDR3; break;
    case ADC_CHN_5: result = a_pADC->ADC_CDR4; break;
    case ADC_CHN_6: result = a_pADC->ADC_CDR5; break;
    case ADC_CHN_7: result = a_pADC->ADC_CDR6; break;
    case ADC_CHN_8: result = a_pADC->ADC_CDR7; break;
  }

  return result;
}

unsigned int GetAdcChanel_wersja2(unsigned char chanel_number_0_7) //ta wersja jest bardziej czytelna 
{
    unsigned int result;
  
  a_pADC->ADC_CHER = (1<<chanel_number_0_7); // Wybranie pojedynczego kanału do przetwarzania
  
  a_pADC->ADC_CR = 0x2; // Rozpoczecie przetwarzania

  while(!(a_pADC->ADC_SR&AT91C_ADC_DRDY)); // czekanie na koniec konwersji przetwarzania, który rozpoznany bedzie ustawieniem bity DataReady == AT91C_ADC_DRDY == (1<<16)

  result = a_pADC->ADC_LCDR; //odczyt wyniku
  return result;
}
