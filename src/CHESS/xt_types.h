#ifndef XT_TYPES_H
#define XT_TYPES_H

#include <stdint.h>

/**
 * @typedef xt_bitboard_t
 * @brief 64-bit bitboard representation for chess positions 8 bytes 4 words
 * @note Uses little-endian word ordering (bits 0-15 in first word)
 */
typedef uint64_t xt_bitboard_t;

#endif
