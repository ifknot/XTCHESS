#include "xt_bitboard.h"
#include <assert.h>

static const uint8_t TABLE_LOOKUP_BITS[256] = {
    0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
    3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,4,5,5,6,5,6,6,7,5,6,6,7,6,7,7,8
};

uint8_t xt_bit_count(xt_bitboard_t* bitboard) {
    assert(bitboard && "NULL bitboard!");
    uint8_t count;
    __asm {
        .8086
        lds     si, bitboard                ; DS:SI = bitboard pointer (Watcom-safe)
        xor     bx, bx                      ; clear BX ptr
        mov     bl, [si]                    ; BL = byte 0
        mov     cl, TABLE_LOOKUP_BITS[bx]   ; CL = count (no need to zero first)
        mov     bl, [si+1]                  ; BL = byte 1
        add     cl, TABLE_LOOKUP_BITS[bx]
        mov     bl, [si+2]                  ; BL = byte 2
        add     cl, TABLE_LOOKUP_BITS[bx]
        mov     bl, [si+3]                  ; BL = byte 3
        add     cl, TABLE_LOOKUP_BITS[bx]
        mov     bl, [si+4]                  ; BL = byte 4
        add     cl, TABLE_LOOKUP_BITS[bx]
        mov     bl, [si+5]                  ; BL = byte 5
        add     cl, TABLE_LOOKUP_BITS[bx]
        mov     bl, [si+6]                  ; BL = byte 6
        add     cl, TABLE_LOOKUP_BITS[bx]
        mov     bl, [si+7]                  ; BL = byte 7
        add     cl, TABLE_LOOKUP_BITS[bx]
        mov     count, cl
    }
    return count;
}
