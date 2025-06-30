#ifndef MDA_CONTEXT_H
#define MDA_CONTEXT_H

#include "../BIOS/bios_video_services.h"

typedef union {
    uint16_t char_attr;
    struct {
        char chr;     
        char attr;    
    } parts;
} mda_char_attr_t;

// having different contexts enables manage different parts of the screen in a window-esque way
// TODO: add mouse support 
typedef struct {
    char attribute;
    char x, y, width, height;
    bios_video_state_t video;
    bios_cursor_state_t cursor;
} mda_context_t;

void mda_initialize_context(mda_context_t* context);

void mda_cursor_to(mda_context_t* context, uint8_t x, uint8_t y);

void mda_set_attributes(mda_context_t* context,char attr);

void mda_reset_attributes(mda_context_t* context);

void mda_print(mda_context_t* context, char* stringz); // teletype print 

#endif
