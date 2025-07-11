#ifndef MDA_WIDGETS_H
#define MDA_WIDGETS_H

#include "mda_context.h"
#include "mda_widget_rtti.h"
#include "../MEM/mem_arena.h"
#include "mda_widget_types.h"

#define MDA_WIDGET_MAX_CHILDREN    16

typedef struct mda_widget_component_t mda_widget_component_t;

typedef struct mda_widget_component_t { // component base
    mda_widget_rtti_t rtti;
    mda_widget_component_t* parent;
    mda_context_t* ctx;
    uint8_t x;
    uint8_t y;
    uint8_t width;
    uint8_t height;
    void (*fn)(mda_widget_component_t*);
} mda_widget_component_t;

typedef struct { // composite is a component
    mda_widget_component_t base;
    mda_widget_component_t* children[MDA_WIDGET_MAX_CHILDREN];
    mda_widget_size_t child_count;
} mda_widget_composite_t;

void mda_widget_component_init(
    mda_widget_type_t type,
    mda_widget_component_t* comp,
    mda_widget_component_t* parent,
    mda_context_t* ctx,
    uint8_t x,
    uint8_t y,
    uint8_t width,
    uint8_t height
);

mda_widget_component_t* mda_widget_component_create(
    mem_arena_t* arena,
    mda_widget_type_t type,
    mda_widget_component_t* parent,
    mda_context_t* ctx,
    uint8_t x,
    uint8_t y,
    uint8_t width,
    uint8_t height
);

void mda_widget_composite_init(
    mda_widget_type_t type,
    mda_widget_composite_t* comp,
    mda_widget_component_t* parent,
    mda_context_t* ctx,
    uint8_t x,
    uint8_t y,
    uint8_t width,
    uint8_t height
);

mda_widget_composite_t* mda_widget_composite_create(
    mem_arena_t* arena,
    mda_widget_type_t type,
    mda_widget_component_t* parent,
    mda_context_t* ctx,
    uint8_t x,
    uint8_t y,
    uint8_t width,
    uint8_t height
);

void mda_widget_composite_add(mda_widget_component_t* parent, mda_widget_component_t* child);

void mda_widget_composite_remove(mda_widget_component_t* parent, mda_widget_component_t* child);





#endif
