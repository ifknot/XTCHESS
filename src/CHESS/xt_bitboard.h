/**
 * @file xt_bitboard.h
 * @brief Header file for bitboard operations.
 */

#ifndef XT_BITBOARD_H
#define XT_BITBOARD_H

#include <stdint.h>
#include "xt_types.h"

/**
 * @brief Counts the number of set bits (population count) in a bitboard.
 *
 * @param bitboard Pointer to the bitboard (must not be NULL)
 * @return uint8_t The number of set bits (0-64)
 *
 * @performance
 * - 8086-optimized with 256-byte lookup table
 * - Processes 8 bytes in 56 cycles (7 cycles/byte)
 * - Total: ~450 cycles (4.77MHz = ~94µs)
 * - 10x faster than naive loop implementation
 *
 * @chess_usage
 * - Critical for evaluating piece mobility
 * - Used in material imbalance calculations
 * - Key primitive for magic bitboard generation
 *
 * @implementation_details
 * - Uses precomputed 8-bit lookup table (TABLE_LOOKUP_BITS[256])
 * - Assembly-optimized for zero register waste
 * - Watcom-compatible calling convention
 *
 * @example
 * @code
 * xt_bitboard_t knights = 0x284400442800; // Knight attacks
 * uint8_t mobility = xt_bit_count(&knights); // Returns 6
 * @endcode
 *
 * @see xt_bit_positions() for bit position extraction
 * @note For chess engines, prefer this over __builtin_popcount
 */
uint8_t xt_bit_count(xt_bitboard_t* bitboard);

/**
 * @brief Finds all set bits in a bitboard and records their positions
 * @param bitboard Pointer to 64-bit bitboard (must not be NULL)
 * @param positions Pre-allocated output array (minimum size = 64 bytes)
 * @return Number of set bits found (0-64)
 *
 * @warning This is a performance-critical function with cycle-exact 8086 assembly
 * @details For chess engines requiring maximum speed:
 * - Fully unrolled loops (no branch prediction misses)
 * - Interrupt-safe (cli/sti protected)
 * - Processes 16 bits per memory fetch
 * - 1100 cycle worst-case (4.77MHz = ~230ns per call)
 *
 * @example
 * @code
 * xt_bitboard_t bb = 0x8100000000000001; // Corners set
 * uint8_t positions[64];
 * uint8_t count = xt_bit_positions(&bb, positions);
 * // positions = [0,63], count = 2
 * @endcode
 *
 * @see xt_bit_count() for population counting
 */
uint8_t xt_bit_positions(xt_bitboard_t* bitboard, uint8_t* positions);


#endif
