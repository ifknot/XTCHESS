#include "mda_widgets.h" 
#include "../BIOS/bios_video_service.h"

void mda_widget_border(mda_context_t* ctx, char* border_charz, bool shrink_context) {
  assert(border_charz && "NULL border characters");

  uint8_t x = ctx->x;
  uint8_t y = ctx->y;

  mda_print_char(ctx, border_charz[INDEX_TOP_LEFT]);
  mda_print_row(ctx, border_charz[INDEX_HORIZONTAL, ctx->width - 2);
  mda_print_char(ctx, border_charz[INDEX_TOP_RIGHT]);
  mda_cursor_to(ctx, x, y+1);
  mda_print_column(ctx, border_charz[INDEX_VERTICAL, ctx->height - 2);  
  mda_print_char(ctx, border_charz[INDEX_BOTTOM_LEFT]);
  mda_print_row(ctx, border_charz[INDEX_HORIZONTAL], ctx.width - 2);
  mda_print_char(ctx, border_charz[INDEX_BOTTOM_RIGHT]);
  mda_cursor_to(ctx, x + ctx->width - 1, y+ 1);
  mda_print_column(ctx, border_charz[INDEX_VERTICAL, ctx->height - 2);  

  if(shrink_context) {
    mda_set_context_frame(ctx, x + 1, y + 1, ctx->width -1, ctx->height - 1);
  }
 
}
