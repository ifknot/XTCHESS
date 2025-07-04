#ifndef MDA_CONTEXT_H
#define MDA_CONTEXT_H

#include "../BIOS/bios_video_services.h"
#include <stdbool.h>

typedef union {
    uint16_t char_attr;
    struct {
        char chr;
        char attr;
    } parts;
} mda_char_attr_t;

// having different contexts enables manage different parts of the screen in a window-esque way
typedef struct {
    char attributes;
    char x;
    char y;
    char width;
    char height;
    bios_video_state_t video;
    bios_cursor_state_t cursor;
    // TODO: mouse_state mouse; has mouse support etc
} mda_context_t;

void mda_initialize_default_context(mda_context_t* ctx);

void mda_set_context_frame(mda_context_t* ctx, uint8_t x, uint8_t y, uint8_t width, uint8_t height);

void mda_cursor_to(mda_context_t* ctx, uint8_t x, uint8_t y);

void mda_set_attributes(mda_context_t* ctx,char attr);

void mda_reset_attributes(mda_context_t* ctx);

void mda_cursor_advance(mda_context_t* ctx);

void mda_lf(mda_context_t* ctx);

void mda_crlf(mda_context_t* ctx);

void mda_backspace(mda_context_t* ctx);

void mda_delete(mda_context_t* ctx);

void mda_print_char(mda_context_t* ctx, char chr);

void mda_print_string(mda_context_t* ctx, char* stringz);

void mda_print_row(mda_context_t* ctx, char chr, uint16_t count);

void mda_print_column(mda_context_t* ctx, char chr, uint16_t count);

bool mda_context_contains(mda_context_t* ctx, uint8_t x, uint8_t y);

#endif
