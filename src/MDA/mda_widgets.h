#ifndef MDA_WIDGETS_H
#define MDA_WIDGETS_H

#include <stdbool.h>

// progress bars, spinners, buttons etc

void mda_widget_border(mda_context_t* ctx, char* border_charz, bool shrink_context); // border_charz 6 chars - 4 corners start top lhs then clockwise then horz and vert

#endif
