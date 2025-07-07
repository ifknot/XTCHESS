#include "mda_context.h"
#include "ascii_control_codes.h"
#include "mda_attributes.h"
#include "mda_constants.h"
#include <assert.h>

void mda_initialize_default_context(mda_context_t* ctx) {
    assert(ctx && "NULL context!");
    bios_set_video_mode(MDA_TEXT_MONOCHROME_80X25);
    bios_get_video_state(&ctx->video);
    bios_get_cursor_position_and_size(&ctx->cursor, ctx->video.page);
    mda_set_context_frame(ctx, 0, 0, ctx->video.columns, MDA_SCREEN_ROWS);
    mda_reset_attributes(ctx);
    ctx->htab_size = MDA_DEFAULT_HTAB;
    ctx->vtab_size = MDA_DEFAULT_VTAB;
}

void mda_set_context_frame(mda_context_t* ctx, uint8_t x, uint8_t y, uint8_t width, uint8_t height) {
    assert(ctx && "NULL context!");
    assert(x < ctx->video.columns && "OUT OF RANGE x value!");
    assert(y < MDA_SCREEN_ROWS && "OUT OF RANGE y value!");
    ctx->x = x;
    ctx->y = y;
    ctx->width = width;
    ctx->height = height;
    mda_cursor_to(ctx, ctx->x, ctx->y);
}

void mda_cursor_to(mda_context_t* ctx, uint8_t x, uint8_t y) {
    assert(ctx && "NULL context!");
    assert(mda_context_contains(ctx, x, y) && "OUT OF BOUNDS cursor position!");
    bios_set_cursor_position(x, y, ctx->video.page);
    bios_get_cursor_position_and_size(&ctx->cursor, ctx->video.page);
}

void mda_set_attributes(mda_context_t* ctx,char attr) {
    assert(ctx && "NULL context!");
    ctx->attributes = attr;
}

void mda_reset_attributes(mda_context_t* ctx) {
    assert(ctx && "NULL context!");
    ctx->attributes = MDA_NORMAL;
}

void mda_cursor_advance(mda_context_t* ctx) {
    assert(ctx && "NULL context!");
    ctx->cursor.column++;
    if(ctx->cursor.column == (ctx->x + ctx->width)) {
        mda_write_CRLF(ctx);
        return;
    }
    bios_set_cursor_position(ctx->cursor.column, ctx->cursor.row, ctx->video.page);
}

void mda_ascii_BEL(mda_context_t* ctx) {
    assert(ctx && "NULL context!");
    bios_write_text_teletype_mode(ASCII_BEL, 0, ctx->video.page);
}

void mda_ascii_BS(mda_context_t* ctx)  {
    assert(ctx && "NULL context!");
    if(ctx->cursor.column > ctx->x) {
        ctx->cursor.column--;
        bios_set_cursor_position(ctx->cursor.column, ctx->cursor.row, ctx->video.page);
    }
}

void mda_ascii_HT(mda_context_t* ctx) {
    assert(ctx && "NULL context!");
    for(int i = 0; i < ctx->htab_size; ++i) {
        mda_cursor_advance(ctx);
    }
}

void mda_ascii_LF(mda_context_t* ctx)  {
    assert(ctx && "NULL context!");
    ctx->cursor.row++;
    if(ctx->cursor.row == (ctx->y + ctx->height)) {
        ctx->cursor.row = ctx->y;
    }
    bios_set_cursor_position(ctx->cursor.column, ctx->cursor.row, ctx->video.page);
}

void mda_ascii_VT(mda_context_t* ctx) {
    assert(ctx && "NULL context!");
    for(int i = 0; i < ctx->vtab_size; ++i){
        mda_ascii_LF(ctx);
    }
}

void mda_ascii_FF(mda_context_t* ctx) {
    assert(ctx && "NULL context!");
    //mda_scroll_up(MDA_SCREEN_ROWS);
}

void mda_ascii_CR(mda_context_t* ctx) {
    assert(ctx && "NULL context!");
    ctx->cursor.column = ctx->x;
}

void mda_ascii_ESC(mda_context_t* ctx) {
    assert(ctx && "NULL context!");
    // set esc char mode
}

void mda_ascii_DEL(mda_context_t* ctx) {
    assert(ctx && "NULL context!");
    mda_ascii_BS(ctx);
    mda_write_char(ctx, ' ');
    mda_ascii_BS(ctx);
}

void mda_write_CRLF(mda_context_t* ctx) {
    mda_ascii_CR(ctx);
    mda_ascii_LF(ctx);
}

void mda_write_char(mda_context_t* ctx, char chr) {
    assert(ctx && "NULL context!");
    bios_write_character_and_attribute_at_cursor(chr, ctx->attributes, 1, ctx->video.page);
    mda_cursor_advance(ctx);
}

void mda_write_string(mda_context_t* ctx, char* stringz) {
    assert(ctx && "NULL context!");
    assert(stringz && "NULL string!");
    int i = 0;
    while(stringz[i]) {
        mda_write_char(ctx, stringz[i++]);
    }
}

void mda_write_row(mda_context_t* ctx, char chr, uint16_t count) {
    assert(ctx && "NULL context!");
    if(!count) {
        return;
    }
    for(int i = 0; i < count; ++i) {
        mda_write_char(ctx, chr);
    }
}

void mda_write_column(mda_context_t* ctx, char chr, uint16_t count) {
    assert(ctx && "NULL context!");
    if(!count) {
        return;
    }
    for(int i = 0; i < count; ++i) {
        bios_write_character_and_attribute_at_cursor(chr, ctx->attributes, 1, ctx->video.page);
        mda_ascii_LF(ctx);

    }
}

bool mda_context_contains(mda_context_t*ctx, uint8_t x, uint8_t y) {
    assert(ctx && "NULL context!");
    assert(x < ctx->video.columns && "OUT OF RANGE x value!");
    assert(y < MDA_SCREEN_ROWS && "OUT OF RANGE y value!");
    return x >=ctx->x && x < (ctx->x + ctx->width) && y >= ctx->y && y < (ctx->y + ctx->height);
}
