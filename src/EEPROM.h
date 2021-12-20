#ifndef EEPROM_h
#define EEPROM_h

#if defined(__has_include) && __has_include(<type_traits>)
#include <type_traits>
#endif

struct EEPROMClass{
    uint8_t read( int idx ) { return 0 ;}
    void write( int idx, uint8_t val ) {}
    void update( int idx, uint8_t val ) {}
    template< typename T > const T &put( int idx, const T &t ) {
        #if defined(__has_include) && __has_include(<type_traits>)
        static_assert(std::is_trivially_copyable<T>::value, "You can not use this type with EEPROM.get"); // the code below only makes sense if you can "memcpy" T
        #endif
        return t;
    }
    template< typename T > T &get( int idx, T &t ) {
        #if defined(__has_include) && __has_include(<type_traits>)
        static_assert(std::is_trivially_copyable<T>::value, "You can not use this type with EEPROM.get"); // the code below only makes sense if you can "memcpy" T
        #endif
        return t;
    }
};

static EEPROMClass EEPROM __attribute__ ((unused));

#endif