#ifndef MDA_WIDGETS_H
#define MDA_WIDGETS_H

#include "mda_widgets_rtti.h"

#define MDA_WIDGET_MAX_CHILDREN    16

typedef struct mda_widget_component_t mda_widget_component_t;

typedef struct mda_widget_component_t { // component base
    mda_widget_rtti_t rtti;
    mda_widget_component_t* parent;
} mda_widget_component_t;

typedef struct { // composite is a component
    mda_widget_component_t base;
    mda_widget_component_t* children[MDA_WIDGET_MAX_CHILDREN];
    mda_widget_size_t child_count;
} mda_widget_t;

#endif
