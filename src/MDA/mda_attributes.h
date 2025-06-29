/**
 * MDA/Hercules Text Attribute Constants
 * For IBM PC/XT, AT, and compatibles.
 */
#ifndef MDA_ATTRIBUTES_H
#define MDA_ATTRIBUTES_H

typedef enum {
    MDA_NORMAL      = 0x07, // White on black
    MDA_UNDERLINE   = 0x01, // Underlined text
    MDA_BOLD        = 0x08, // Bright white (OR with NORMAL)
    MDA_BLINK       = 0x80, // Blinking text (OR with other attrs)
    MDA_REVERSE     = 0x70, // Black on white (inverse)
    MDA_INVISIBLE   = 0x00  // Hidden text (foreground = background)
} mda_attribute_t;

#endif
