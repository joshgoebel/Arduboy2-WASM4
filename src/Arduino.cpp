#include "Arduino.h"

void randomSeed(int a) { }
int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }
int random(int max) {return 0; }
int random(int min, int max) { return 0; }
int abs(int n) { return n < 0 ? -n : n; }

unsigned long frameTicks = 0;

// return applox number of ms since boot
unsigned long millis() {
    return frameTicks * 17;
}

void reverse(char s[])
 {
     int i, j;
     char c;

     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
}

/* itoa:  convert n to characters in s */
 void itoa(int n, char s[], int base)
 {
     int i, sign;

     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % base + '0';   /* get next digit */
     } while ((n /= base) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
}

void ltoa(long n, char s[], int base)
 {
     int i, sign;

     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % base + '0';   /* get next digit */
     } while ((n /= base) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
}

// struct EEPROMClass{
//     uint8_t read( int idx )              { return 0; };
//     void write( int idx, uint8_t val )   { };
//     void update( int idx, uint8_t val )  { };
//     template< typename T > const T &put( int idx, const T &t ){

//     }
//      template< typename T > T &get( int idx, T &t ){
//      }
// // };

// EEPROMClass EEPROM __attribute__ ((unused));
