#include "mda_widget_border.h"
#include <assert.h>

static void mda_widget_border_draw(mda_widget_border_t* widget) {
    assert(widget->border_chars && "NULL border characters");

    uint8_t x = widget->base.x;
    uint8_t y = widget->base.y;

    mda_write_char(widget->base.ctx, widget->border_chars[INDEX_TOP_LEFT]);
    mda_write_row(widget->base.ctx, widget->border_chars[INDEX_HORIZONTAL], widget->base.width - 2);
    mda_write_char(widget->base.ctx, widget->border_chars[INDEX_TOP_RIGHT]);
    mda_cursor_to(widget->base.ctx, x, y + 1);
    mda_write_column(widget->base.ctx, widget->border_chars[INDEX_VERTICAL], widget->base.height - 2);
    mda_write_char(widget->base.ctx, widget->border_chars[INDEX_BOTTOM_LEFT]);
    mda_write_row(widget->base.ctx, widget->border_chars[INDEX_HORIZONTAL], widget->base.width - 2);
    mda_write_char(widget->base.ctx, widget->border_chars[INDEX_BOTTOM_RIGHT]);
    mda_cursor_to(widget->base.ctx, x + widget->base.width - 1, y+ 1);
    mda_write_column(widget->base.ctx, widget->border_chars[INDEX_VERTICAL], widget->base.height - 2);

}
