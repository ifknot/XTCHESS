#ifndef MDA_WIDGETS_H
#define MDA_WIDGETS_H

#include "cp437_constants.h"
#include <stdbool.h>

static const char mda_widget_default_border[6] = {
  CP437_BOX_DOUBLE_DOWN_RIGHT,  // ╔
  CP437_BOX_DOUBLE_DOWN_LEFT,   // ╗
  CP437_BOX_DOUBLE_UP_LEFT,     // ╝
  CP437_BOX_DOUBLE_UP_RIGHT,    // ╚
  CP437_BOX_DOUBLE_HORIZONTAL,  // ═
  CP437_BOX_DOUBLE_VERTICAL     // ║
}

// progress bars, spinners, buttons etc
// TODO: a composite pattern for widgets 
// mda_widget_composite 
// mda_widget_rtti

void mda_widget_border(mda_context_t* ctx, char* border_charz, bool shrink_context); // border_charz 6 chars - 4 corners start top lhs then clockwise then horz and vert

#endif
