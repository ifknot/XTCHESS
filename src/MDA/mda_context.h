#ifndef MDA_CONTEXT_H
#define MDA_CONTEXT_H

#include "../BIOS/bios_video_services.h"
#include "mda_types.h"
#include <stdbool.h>

// having different contexts enables manage different parts of the screen in a window-esque way
typedef struct {
    char attributes;
    char x;
    char y;
    char width;
    char height;
    uint8_t htab_size;
    uint8_t vtab_size;
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

void mda_ascii_BEL(mda_context_t* ctx);

void mda_ascii_BS(mda_context_t* ctx);

void mda_ascii_HT(mda_context_t* ctx);

void mda_ascii_LF(mda_context_t* ctx);

void mda_ascii_VT(mda_context_t* ctx);

void mda_ascii_FF(mda_context_t* ctx);

void mda_ascii_CR(mda_context_t* ctx);

void mda_ascii_ESC(mda_context_t* ctx);

void mda_ascii_DEL(mda_context_t* ctx);

void mda_write_CRLF(mda_context_t* ctx);

void mda_write_char(mda_context_t* ctx, char chr);

// void mda_read_char(mda_context_t* ctx, char* chr);

void mda_write_string(mda_context_t* ctx, char* stringz);

// void mda_read_string(mda_context_t* ctx, char* stringz, mda_size_t size);

// void mda_input_string(mda_context_t* ctx, char* stringz, mda_size_t size);

void mda_write_row(mda_context_t* ctx, char chr, uint16_t count);

void mda_write_column(mda_context_t* ctx, char chr, uint16_t count);

bool mda_context_contains(mda_context_t* ctx, uint8_t x, uint8_t y);

#endif
