#ifndef EEPROM_h
#define EEPROM_h

#include "wasm4.h"

#if defined(__has_include) && __has_include(<type_traits>)
#include <type_traits>
#endif

static uint8_t* eeprom = NULL;

struct EEPROMClass{
    uint8_t read( int idx ) {
        return *(eeprom + idx);
    }
    void write( int idx, uint8_t val ) {
        update(idx, val);
    }
    void update( int idx, uint8_t val ) {
        uint8_t old_val = read(idx);
        if (old_val == val) return;

        *(eeprom + idx) = val;
        saveAll();
    }
    void boot() {
        uint8_t* ptr;
        tracef("ptr is %d", (int)ptr);
        // tracef("heap_base is %d", __heap_base);
        ptr = (uint8_t *)malloc(1024);
        tracef("ptr is %d", (int)ptr);
        eeprom = ptr;
        diskr(eeprom, 1024);
    }
    void saveAll() {
        diskw(eeprom,1024);
    }
    template< typename T > const T &put( int idx, const T &t ) {
        #if defined(__has_include) && __has_include(<type_traits>)
        static_assert(std::is_trivially_copyable<T>::value, "You can not use this type with EEPROM.get"); // the code below only makes sense if you can "memcpy" T
        #endif

        int count = sizeof(T);
        uint8_t *ptr = (uint8_t*) &t;
        for (int i = 0; i < count; i++) {
            *(eeprom + idx + i) = *ptr++;
        }
        saveAll();

        return t;
    }
    template< typename T > T &get( int idx, T &t ) {
        #if defined(__has_include) && __has_include(<type_traits>)
        static_assert(std::is_trivially_copyable<T>::value, "You can not use this type with EEPROM.get"); // the code below only makes sense if you can "memcpy" T
        #endif

        int count = sizeof(T);
        uint8_t *ptr = (uint8_t*) &t;
        for (int i = 0; i < count; i++) {
            *ptr++ = *(eeprom + idx + i);
        }

        return t;
    }
};

static EEPROMClass EEPROM __attribute__ ((unused));

#endif