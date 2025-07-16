#ifndef MDA_WIDGET_PANEL_H
#define MDA_WIDGET_PANEL_H

#include "mda_widget_composite.h"
#include "../mda_types.h"

typedef struct {
    mda_widget_composite_t composite_base;
    mda_char_attr_t background;
} mda_widget_panel_t;

static void mda_widget_panel_draw(mda_widget_component_t* comp);

void mda_widget_panel_init(
    mda_widget_type_t type,
    mda_widget_composite_t* comp,
    mda_widget_component_t* parent,
    mda_context_t* ctx,
    uint8_t x,
    uint8_t y,
    uint8_t width,
    uint8_t height,
    mda_char_attr_t background
);

mda_widget_panel_t* mda_widget_panel_create(
    mem_arena_t* arena,
    mda_widget_type_t type,
    mda_widget_component_t* parent,
    mda_context_t* ctx,
    uint8_t x,
    uint8_t y,
    uint8_t width,
    uint8_t height,
    mda_char_attr_t background
);

#endif
