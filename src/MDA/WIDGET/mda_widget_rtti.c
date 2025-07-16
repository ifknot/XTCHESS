#include "mda_widget_rtti.h"
#include "mda_widget_types.h"
#include "mda_widget_uid.h"

mda_widget_rtti_t mda_widget_rtti_create(mda_widget_type_t type) {
    mda_widget_rtti_t rtti;
    rtti.parts.type = type;
    rtti.parts.uid = mda_widget_next_uid();
    return rtti;
}

mda_widget_fingerprint_t mda_widget_rtti_fingerprint(mda_widget_rtti_t rtti) {
    return rtti.fingerprint;
}

mda_widget_type_t mda_widget_rtti_type(mda_widget_rtti_t rtti) {
    return rtti.parts.type;
}

mda_widget_size_t mda_widget_rtti_uid(mda_widget_rtti_t rtti) {
    return rtti.parts.uid;
}

bool mda_widget_is_typeof(mda_widget_rtti_t rtti, mda_widget_type_t type) {
    return  type == rtti.parts.type;
}
