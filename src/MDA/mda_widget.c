#include "mda_widget.h"
#include "mda_widget_constants.h"
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
    assert(arena && "NULL memory arena!");

    mda_widget_component_t* comp = (mda_widget_component_t*)mem_arena_calloc(arena, sizeof(mda_widget_component_t));
    assert(comp && "NULL component - arena allocation failed!");

    mda_widget_component_init(type, comp, parent, ctx, x, y, width, height);

    return comp;
}

void mda_widget_composite_init(
    mda_widget_type_t type,
    mda_widget_composite_t* comp,
    mda_widget_component_t* parent,
    mda_context_t* ctx,
    uint8_t x,
    uint8_t y,
    uint8_t width,
    uint8_t height
) {
    assert(comp && "NULL composite!");

    mda_widget_component_init(type, &comp->base, parent, ctx, x, y, width, height);

    comp->child_count = 0;
    for (int i = 0; i < MDA_WIDGET_MAX_CHILDREN; i++) {
        comp->children[i] = NULL;
    }
}

mda_widget_composite_t* mda_widget_composite_create(
    mem_arena_t* arena,
    mda_widget_type_t type,
    mda_widget_component_t* parent,
    mda_context_t* ctx,
    uint8_t x,
    uint8_t y,
    uint8_t width,
    uint8_t height
) {
    assert(arena && "NULL memory arena!");

    mda_widget_composite_t* comp = (mda_widget_composite_t*)mem_arena_calloc(arena, sizeof(mda_widget_composite_t));
    assert(comp && "NULL component - arena allocation failed!");

    mda_widget_composite_init(type, comp, parent, ctx, x, y, width, height);

    return comp;
}

void mda_widget_composite_add(mda_widget_composite_t* parent, mda_widget_component_t* child) {
    assert(parent && "NULL parent!");
    assert(child && "NULL child!");
    assert(parent->child_count < MDA_WIDGET_MAX_CHILDREN && "FULL children array!");
    parent->children[parent->child_count++] = child;
    child->parent = (mda_widget_component_t*)parent;
}

mda_widget_component_t* mda_widget_composite_remove(mda_widget_composite_t* parent, mda_widget_component_t* child) {
    assert(parent && "NULL parent!");
    assert(child && "NULL child!");
    assert(parent->child_count > 0 && "EMPTY children array!");

    for (uint8_t i = 0; i < parent->child_count; ++i) {    // linear seach
        if (parent->children[i] == child) {
            parent->children[i] = parent->children[--parent->child_count];  // over-write with last element
            parent->children[parent->child_count] = NULL; // no hidden dangling pointers
            child->parent = NULL;
            return child;
        }
    }
    return NULL;
}
