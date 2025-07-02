#include "mda_widgets.h" 
#include "../BIOS/bios_video_service.h"

void mda_widget_border(mda_context_t* ctx, char* border_charz, bool shrink_context) {
  assert(border_charz && "NULL border characters");
  mda_print_char(ctx, border_charz[INDEX_TOP_LEFT]);
  mda_print_row(ctx, border_charz[INDEX_HORIZONTAL, ctx.width - 2);
  mda_print_char(ctx, border_charz[INDEX_TOP_RIGHT]);
  mda_cursor_to(ctx, ctx.x, ctx.height - 1);  
  mda_print_char(ctx, border_charz[INDEX_BOTTOM_LEFT]);
  mda_print_row(ctx, border_charz[INDEX_HORIZONTAL], ctx.width - 2);
  mda_print_char(ctx, border_charz[INDEX_BOTTOM_RIGHT]);
  // move 
  // column
  // move 
  // column
}
