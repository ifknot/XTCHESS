#include "mda_context.h"
#include "mda_attributes.h"
#include "mda_constants.h"
#include <assert.h>

void mda_initialize_default_context(mda_context_t* ctx) {
    bios_set_video_mode(MDA_TEXT_MONOCHROME_80X25);
    bios_get_video_state(&ctx->video);
    bios_get_cursor_position_and_size(&ctx->cursor, ctx->video.page);
    mda_set_context_frame(ctx, 0, 0, ctx->video.columns, MDA_SCREEN_ROWS);
    mda_reset_attributes(ctx);
}

void mda_set_context_frame(mda_context_t*ctx, uint8_t x, uint8_t y, uint8_t width, uint8_t height) {
    assert(x <= ctx->video.columns && "OUT OF RANGE x value!");
    assert(y <= MDA_SCREEN_ROWS && "OUT OF RANGE y value!");
    ctx->x = x;
    ctx->y = y;
    ctx->width = width;
    ctx->height = height;
}

void mda_cursor_to(mda_context_t*ctx, uint8_t x, uint8_t y) {
    assert(mda_context_contains(ctx, x, y) && "OUT OF BOUNDS cursor position!");
    bios_set_cursor_position(x, y, ctx->video.page);
}

void mda_set_attributes(mda_context_t*ctx,char attr) {
    ctx->attributes = attr;
}

void mda_reset_attributes(mda_context_t*ctx) {
    ctx->attributes = MDA_NORMAL;
}

void mda_print(mda_context_t*ctx, char* stringz) {

}

bool mda_context_contains(mda_context_t*ctx, uint8_t x, uint8_t y) {
    return x >=ctx->x && x <= ctx->width && y >= ctx->y && y<= ctx->height;
}
