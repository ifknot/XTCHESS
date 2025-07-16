#ifndef MDA_TYPES_H
#define MDA_TYPES_H

#include <stdint.h>

typedef union {
    uint16_t char_attr;
    struct {
        char chr;
        char attr;
    } parts;
} mda_char_attr_t;

#endif
