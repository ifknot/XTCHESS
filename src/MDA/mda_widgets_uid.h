#ifndef MDA_WIDGETS_UID_H
#define MDA_WIDGETS_UID_H

#include <stdint.h>

typedef uint16_t mda_widget_uid_size_t;  // upto 65535 unique IDs places a ceiling on number of objects in a quest game

typedef struct mda_widget_uid_t mda_widget_uid_t;

mda_widget_uid_size_t mda_widget_next_uid();

#endif
