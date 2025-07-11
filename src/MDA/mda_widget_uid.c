#include "mda_widget_uid.h"
#include "mda_widget_types.h"
#include <assert.h>

struct mda_widget_uid_t {
    mda_widget_size_t i;
};

static struct mda_widget_uid_t uid = { 0 };

mda_widget_uid_size_t mda_widget_next_uid(void) {
    uid.i++;
    assert(uid.i != 0); // if zero counter has wrapped around!
    return uid.i;
}
