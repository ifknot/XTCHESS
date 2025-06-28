#ifndef TEST_CHESS_H
#define TEST_CHESS_H

#include "../TDD/tdd_macros.h"
#include "../CHESS/xt_bitboard.h"

#define POPCNT_TEST_SUITE &test_xt_bit_count_basic, \
    &test_xt_bit_count_random_patterns, \
    &test_xt_bit_count_edge_cases
    //&test_xt_bit_count_null_ptr

TEST(test_xt_bit_count_basic) {
    // Test with 0 bits set
    xt_bitboard_t bb_zero = 0x0;
    EXPECT_EQ(xt_bit_count(&bb_zero), 0);

    // Test with 1 bit set
    xt_bitboard_t bb_one = 0x1;
    EXPECT_EQ(xt_bit_count(&bb_one), 1);

    // Test with all bits set (64 bits)
    xt_bitboard_t bb_all = ~0x0ULL;
    EXPECT_EQ(xt_bit_count(&bb_all), 64);
}

TEST(test_xt_bit_count_random_patterns) {
    // Test with alternating bits (32 bits set)
    xt_bitboard_t bb_alternating = 0xAAAAAAAAAAAAAAAAULL;
    EXPECT_EQ(xt_bit_count(&bb_alternating), 32);

    // Test with every 3rd bit set (~21 bits set)
    xt_bitboard_t bb_every_third = 0x9249249249249249ULL;
    EXPECT_EQ(xt_bit_count(&bb_every_third), 22); // 64/3 ≈ 21.33 → 22 due to rounding?

    // Test with a specific pattern (e.g., 0xF0F0F0F0F0F0F0F0 → 32 bits set)
    xt_bitboard_t bb_pattern = 0xF0F0F0F0F0F0F0F0ULL;
    EXPECT_EQ(xt_bit_count(&bb_pattern), 32);
}

TEST(test_xt_bit_count_edge_cases) {
    // Test with only MSB set
    xt_bitboard_t bb_msb = 0x8000000000000000ULL;
    EXPECT_EQ(xt_bit_count(&bb_msb), 1);

    // Test with only LSB set
    xt_bitboard_t bb_lsb = 0x1;
    EXPECT_EQ(xt_bit_count(&bb_lsb), 1);

    // Test with all bits except one set (63 bits set)
    xt_bitboard_t bb_all_but_one = ~0x1ULL;
    EXPECT_EQ(xt_bit_count(&bb_all_but_one), 63);
}

TEST(test_xt_bit_count_null_ptr) {
    // Test with NULL pointer
    EXPECT_EQ(xt_bit_count(NULL), 0); // assert fail
}

#endif
