#include "mda_widget.h"
#include <assert.h>

void mda_widget_component_init(
    mda_widget_type_t type,
    mda_widget_component_t* comp,
    mda_widget_component_t* parent,
    mda_context_t* ctx,
    uint8_t x,
    uint8_t y,
    uint8_t width,
    uint8_t height
) {
    assert(comp && "NULL component!");
    assert(ctx && "NULL context!");
    comp->rtti = mda_widget_rtti_create(type);
    comp->parent = parent;
    comp->ctx =ctx;
    comp->x = x;
    comp->y = y;
    comp->width = width;
    comp->height = height;
}

mda_widget_component_t* mda_widget_component_create(
    mem_arena_t* arena,
    mda_widget_type_t type,
    mda_widget_component_t* parent,
    mda_context_t* ctx,
    uint8_t x,
    uint8_t y,
    uint8_t width,
    uint8_t height
) {

}
