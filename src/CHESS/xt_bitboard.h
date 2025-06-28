/**
 * @file xt_bitboard.h
 * @brief Header file for bitboard operations.
 */

#ifndef XT_BITBOARD_H
#define XT_BITBOARD_H

#include <stdint.h>

/**
 * @typedef xt_bitboard_t
 * @brief A bitboard type represented as a 64-bit unsigned integer.
 */
typedef uint64_t xt_bitboard_t;

/**
 * @brief Counts the number of set bits (population count) in a bitboard.
 *
 * @param bitboard Pointer to the bitboard to count bits in.
 * @return uint8_t The number of set bits in the bitboard.
 */
uint8_t xt_bit_count(xt_bitboard_t* bitboard);

#endif
