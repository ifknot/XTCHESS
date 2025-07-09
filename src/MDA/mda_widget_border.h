#ifndef MDA_WIDGETS_BORDER_H
#define MDA_WIDGETS_BORDER_H

#include "mda_widget.h"
#include <stdbool.h>

typedef struct mda_widget_border_t mda_widget_border_t;

static void mda_widget_border_draw(mda_widget_border_t* widget);

typedef struct mda_widget_border_t {
    mda_widget_component_t base;
    char* border_chars;
} mda_widget_border_t;

void mda_widget_border_init(
    mda_widget_border_t* widget,
    mda_widget_component_t* parent,
    uint8_t x,
    uint8_t y,
    uint8_t width,
    uint8_t height,
    char* border_chars,
    bool shrink_context
);

#endif
