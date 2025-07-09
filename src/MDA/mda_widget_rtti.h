#ifndef MDA_WIDGETS_RTTI_H
#define MDA_WIDGETS_RTTI_H

#include "mda_widget_types.h"
#include <stdbool.h>

typedef union mda_widget_rtti_t {
    mda_widget_fingerprint_t fingerprint;
    struct {
        mda_widget_size_t uid;
        mda_widget_type_t type;
    } parts;
} mda_widget_rtti_t;

mda_widget_rtti_t mda_widget_rtti_create(mda_widget_type_t type);

mda_widget_fingerprint_t mda_widget_rtti_fingerprint(mda_widget_rtti_t rtti);

mda_widget_type_t mda_widget_rtti_type(mda_widget_rtti_t rtti);

mda_widget_size_t mda_widget_rtti_uid(mda_widget_rtti_t rtti);

bool mda_widget_is_typeof(
    mda_widget_rtti_t rtti,
    mda_widget_type_t type
);

#endif
