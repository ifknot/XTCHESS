#ifndef MDA_WIDGETS_TYPES_H
#define MDA_WIDGETS_TYPES_H

#include "cp437_constants.h"
#include <stdint.h>

typedef uint16_t mda_widget_size_t;

typedef uint32_t mda_widget_fingerprint_t;

typedef uint16_t mda_widget_type_t;

static const unsigned char mda_widget_default_border[6] = {
  CP437_BOX_DOUBLE_DOWN_RIGHT,  // ╔
  CP437_BOX_DOUBLE_DOWN_LEFT,   // ╗
  CP437_BOX_DOUBLE_UP_LEFT,     // ╝
  CP437_BOX_DOUBLE_UP_RIGHT,    // ╚
  CP437_BOX_DOUBLE_HORIZONTAL,  // ═
  CP437_BOX_DOUBLE_VERTICAL     // ║
};

typedef enum {
  INDEX_TOP_LEFT,
  INDEX_TOP_RIGHT,
  INDEX_BOTTOM_LEFT,
  INDEX_BOTTOM_RIGHT,
  INDEX_HORIZONTAL,
  INDEX_VERTICAL
} widget_index_t;

#endif
