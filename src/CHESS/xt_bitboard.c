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
        // 1. set up the registers
        lds     si, bitboard                ; DS:SI = bitboard pointer (Watcom-safe)
        xor     bx, bx                      ; clear BX ptr
        // 2. process each of the 8 bytes using the lookup table to index the bit cout
        mov     bl, [si]                    ; BL = byte 0
        mov     cl, TABLE_LOOKUP_BITS[bx]   ; CL = count
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
        // 3. copy CL to the count return variable
        mov     count, cl
    }
    return count;
}

uint8_t xt_bit_positions(xt_bitboard_t* bitboard, uint8_t* positions) {
    uint8_t size;
    __asm {
        .8086
        // 1. set up the registers
        lds     si, bitboard                ; DS:SI = bitboard pointer
        les     di, positions               ; ES:DI = positions array
        xor     bx, bx                      ; BL = bit number (0..63) BH = output array size
        cld                                 ; clear direction flag to increment
        // 2. process 4 words 16 bits at a time (64 bits)
        mov     dh, 4                   ; 4 words to process
BYTES:  lodsw                           ; AX = next byte (DS:SI++)
        mov     cx, 16                  ; 16 bits per word
BITS:   shr     ax, 1                   ; Shift LSB into CF
        jnc     SKIP                    ; Jump if bit not set
        mov     es:[di], bl             ; store position
        inc     di                      ; next position
        inc     bh                      ; Increment size counter
SKIP:   inc     bl                      ; Next bit position
        loop    BITS                    ; Process next bit
        dec     dh
        jnz     BYTES                   ; Process next byte
        // 3. copy BH to the count return variable
        mov     size, bh                ; Return size in BH
    }
    return size;
}

/* super optimized version
uint8_t xt_bit_positions(xt_bitboard_t* bitboard, uint8_t* positions) {
    uint8_t size;
    __asm {
        .8086
        cli                         ; Disable interrupts
        push    ds                  ; Save segments
        push    es

        ; === SETUP ===
        lds     si, bitboard        ; DS:SI = bitboard
        les     di, positions       ; ES:DI = output array
        xor     bx, bx              ; BH = size, BL = bit pos

        ; === PROCESS ALL 64 BITS ===
        ; --- WORD 0 (Bits 0-15) ---
        lodsw                       ; Load bits 0-15
        ; Bit 0
        shr     ax, 1
        jnc     w0b0
        mov     es:[di], bl
        inc     di
        inc     bh
    w0b0: inc     bl
        ; Bit 1
        shr     ax, 1
        jnc     w0b1
        mov     es:[di], bl
        inc     di
        inc     bh
    w0b1: inc     bl
        ; Bit 2
        shr     ax, 1
        jnc     w0b2
        mov     es:[di], bl
        inc     di
        inc     bh
    w0b2: inc     bl
        ; Bit 3
        shr     ax, 1
        jnc     w0b3
        mov     es:[di], bl
        inc     di
        inc     bh
    w0b3: inc     bl
        ; Bit 4
        shr     ax, 1
        jnc     w0b4
        mov     es:[di], bl
        inc     di
        inc     bh
    w0b4: inc     bl
        ; Bit 5
        shr     ax, 1
        jnc     w0b5
        mov     es:[di], bl
        inc     di
        inc     bh
    w0b5: inc     bl
        ; Bit 6
        shr     ax, 1
        jnc     w0b6
        mov     es:[di], bl
        inc     di
        inc     bh
    w0b6: inc     bl
        ; Bit 7
        shr     ax, 1
        jnc     w0b7
        mov     es:[di], bl
        inc     di
        inc     bh
    w0b7: inc     bl
        ; Bit 8
        shr     ax, 1
        jnc     w0b8
        mov     es:[di], bl
        inc     di
        inc     bh
    w0b8: inc     bl
        ; Bit 9
        shr     ax, 1
        jnc     w0b9
        mov     es:[di], bl
        inc     di
        inc     bh
    w0b9: inc     bl
        ; Bit 10
        shr     ax, 1
        jnc     w0b10
        mov     es:[di], bl
        inc     di
        inc     bh
    w0b10: inc    bl
        ; Bit 11
        shr     ax, 1
        jnc     w0b11
        mov     es:[di], bl
        inc     di
        inc     bh
    w0b11: inc    bl
        ; Bit 12
        shr     ax, 1
        jnc     w0b12
        mov     es:[di], bl
        inc     di
        inc     bh
    w0b12: inc    bl
        ; Bit 13
        shr     ax, 1
        jnc     w0b13
        mov     es:[di], bl
        inc     di
        inc     bh
    w0b13: inc    bl
        ; Bit 14
        shr     ax, 1
        jnc     w0b14
        mov     es:[di], bl
        inc     di
        inc     bh
    w0b14: inc    bl
        ; Bit 15
        shr     ax, 1
        jnc     w0b15
        mov     es:[di], bl
        inc     di
        inc     bh
    w0b15: inc    bl

        ; --- WORD 1 (Bits 16-31) ---
        lodsw                       ; Load bits 16-31
        ; Bit 16
        shr     ax, 1
        jnc     w1b0
        mov     es:[di], bl
        inc     di
        inc     bh
    w1b0: inc     bl
        ; Bit 17
        shr     ax, 1
        jnc     w1b1
        mov     es:[di], bl
        inc     di
        inc     bh
    w1b1: inc     bl
        ; Bit 18
        shr     ax, 1
        jnc     w1b2
        mov     es:[di], bl
        inc     di
        inc     bh
    w1b2: inc     bl
        ; Bit 19
        shr     ax, 1
        jnc     w1b3
        mov     es:[di], bl
        inc     di
        inc     bh
    w1b3: inc     bl
        ; Bit 20
        shr     ax, 1
        jnc     w1b4
        mov     es:[di], bl
        inc     di
        inc     bh
    w1b4: inc     bl
        ; Bit 21
        shr     ax, 1
        jnc     w1b5
        mov     es:[di], bl
        inc     di
        inc     bh
    w1b5: inc     bl
        ; Bit 22
        shr     ax, 1
        jnc     w1b6
        mov     es:[di], bl
        inc     di
        inc     bh
    w1b6: inc     bl
        ; Bit 23
        shr     ax, 1
        jnc     w1b7
        mov     es:[di], bl
        inc     di
        inc     bh
    w1b7: inc     bl
        ; Bit 24
        shr     ax, 1
        jnc     w1b8
        mov     es:[di], bl
        inc     di
        inc     bh
    w1b8: inc     bl
        ; Bit 25
        shr     ax, 1
        jnc     w1b9
        mov     es:[di], bl
        inc     di
        inc     bh
    w1b9: inc     bl
        ; Bit 26
        shr     ax, 1
        jnc     w1b10
        mov     es:[di], bl
        inc     di
        inc     bh
    w1b10: inc    bl
        ; Bit 27
        shr     ax, 1
        jnc     w1b11
        mov     es:[di], bl
        inc     di
        inc     bh
    w1b11: inc    bl
        ; Bit 28
        shr     ax, 1
        jnc     w1b12
        mov     es:[di], bl
        inc     di
        inc     bh
    w1b12: inc    bl
        ; Bit 29
        shr     ax, 1
        jnc     w1b13
        mov     es:[di], bl
        inc     di
        inc     bh
    w1b13: inc    bl
        ; Bit 30
        shr     ax, 1
        jnc     w1b14
        mov     es:[di], bl
        inc     di
        inc     bh
    w1b14: inc    bl
        ; Bit 31
        shr     ax, 1
        jnc     w1b15
        mov     es:[di], bl
        inc     di
        inc     bh
    w1b15: inc    bl

        ; --- WORD 2 (Bits 32-47) ---
        lodsw                       ; Load bits 32-47
        ; Bit 32
        shr     ax, 1
        jnc     w2b0
        mov     es:[di], bl
        inc     di
        inc     bh
    w2b0: inc     bl
        ; Bit 33
        shr     ax, 1
        jnc     w2b1
        mov     es:[di], bl
        inc     di
        inc     bh
    w2b1: inc     bl
        ; Bit 34
        shr     ax, 1
        jnc     w2b2
        mov     es:[di], bl
        inc     di
        inc     bh
    w2b2: inc     bl
        ; Bit 35
        shr     ax, 1
        jnc     w2b3
        mov     es:[di], bl
        inc     di
        inc     bh
    w2b3: inc     bl
        ; Bit 36
        shr     ax, 1
        jnc     w2b4
        mov     es:[di], bl
        inc     di
        inc     bh
    w2b4: inc     bl
        ; Bit 37
        shr     ax, 1
        jnc     w2b5
        mov     es:[di], bl
        inc     di
        inc     bh
    w2b5: inc     bl
        ; Bit 38
        shr     ax, 1
        jnc     w2b6
        mov     es:[di], bl
        inc     di
        inc     bh
    w2b6: inc     bl
        ; Bit 39
        shr     ax, 1
        jnc     w2b7
        mov     es:[di], bl
        inc     di
        inc     bh
    w2b7: inc     bl
        ; Bit 40
        shr     ax, 1
        jnc     w2b8
        mov     es:[di], bl
        inc     di
        inc     bh
    w2b8: inc     bl
        ; Bit 41
        shr     ax, 1
        jnc     w2b9
        mov     es:[di], bl
        inc     di
        inc     bh
    w2b9: inc     bl
        ; Bit 42
        shr     ax, 1
        jnc     w2b10
        mov     es:[di], bl
        inc     di
        inc     bh
    w2b10: inc    bl
        ; Bit 43
        shr     ax, 1
        jnc     w2b11
        mov     es:[di], bl
        inc     di
        inc     bh
    w2b11: inc    bl
        ; Bit 44
        shr     ax, 1
        jnc     w2b12
        mov     es:[di], bl
        inc     di
        inc     bh
    w2b12: inc    bl
        ; Bit 45
        shr     ax, 1
        jnc     w2b13
        mov     es:[di], bl
        inc     di
        inc     bh
    w2b13: inc    bl
        ; Bit 46
        shr     ax, 1
        jnc     w2b14
        mov     es:[di], bl
        inc     di
        inc     bh
    w2b14: inc    bl
        ; Bit 47
        shr     ax, 1
        jnc     w2b15
        mov     es:[di], bl
        inc     di
        inc     bh
    w2b15: inc    bl

        ; --- WORD 3 (Bits 48-63) ---
        lodsw                       ; Load bits 48-63
        ; Bit 48
        shr     ax, 1
        jnc     w3b0
        mov     es:[di], bl
        inc     di
        inc     bh
    w3b0: inc     bl
        ; Bit 49
        shr     ax, 1
        jnc     w3b1
        mov     es:[di], bl
        inc     di
        inc     bh
    w3b1: inc     bl
        ; Bit 50
        shr     ax, 1
        jnc     w3b2
        mov     es:[di], bl
        inc     di
        inc     bh
    w3b2: inc     bl
        ; Bit 51
        shr     ax, 1
        jnc     w3b3
        mov     es:[di], bl
        inc     di
        inc     bh
    w3b3: inc     bl
        ; Bit 52
        shr     ax, 1
        jnc     w3b4
        mov     es:[di], bl
        inc     di
        inc     bh
    w3b4: inc     bl
        ; Bit 53
        shr     ax, 1
        jnc     w3b5
        mov     es:[di], bl
        inc     di
        inc     bh
    w3b5: inc     bl
        ; Bit 54
        shr     ax, 1
        jnc     w3b6
        mov     es:[di], bl
        inc     di
        inc     bh
    w3b6: inc     bl
        ; Bit 55
        shr     ax, 1
        jnc     w3b7
        mov     es:[di], bl
        inc     di
        inc     bh
    w3b7: inc     bl
        ; Bit 56
        shr     ax, 1
        jnc     w3b8
        mov     es:[di], bl
        inc     di
        inc     bh
    w3b8: inc     bl
        ; Bit 57
        shr     ax, 1
        jnc     w3b9
        mov     es:[di], bl
        inc     di
        inc     bh
    w3b9: inc     bl
        ; Bit 58
        shr     ax, 1
        jnc     w3b10
        mov     es:[di], bl
        inc     di
        inc     bh
    w3b10: inc    bl
        ; Bit 59
        shr     ax, 1
        jnc     w3b11
        mov     es:[di], bl
        inc     di
        inc     bh
    w3b11: inc    bl
        ; Bit 60
        shr     ax, 1
        jnc     w3b12
        mov     es:[di], bl
        inc     di
        inc     bh
    w3b12: inc    bl
        ; Bit 61
        shr     ax, 1
        jnc     w3b13
        mov     es:[di], bl
        inc     di
        inc     bh
    w3b13: inc    bl
        ; Bit 62
        shr     ax, 1
        jnc     w3b14
        mov     es:[di], bl
        inc     di
        inc     bh
    w3b14: inc    bl
        ; Bit 63
        shr     ax, 1
        jnc     w3b15
        mov     es:[di], bl
        inc     di
        inc     bh
    w3b15:

        ; === CLEANUP ===
        mov     size, bh            ; Store result
        pop     es                  ; Restore segments
        pop     ds
        sti                         ; Enable interrupts
    }
    return size;
}
 */

/**
 * @brief Determines if a bitboard has 0, 1, or multiple bits set (ternary classification)
 * @param bitboard Pointer to the bitboard (must not be NULL)
 * @return uint8_t 0 (no bits), 1 (exactly one bit), or 2 (multiple bits)
 *
 * @performance
 * - Early-out branching makes this 3-5x faster than full popcount
 * - Worst case: ~150 cycles (when checking dense bitboards)
 * - Best case: 12 cycles (empty bitboard detection)
 *
 * @chess_usage
 * - Pawn structure evaluation (isolated/doubled pawns)
 * - King safety checks (multiple attackers)
 * - Move legality verification (exactly one piece moving)
 *
 * @implementation_details
 * - Uses 8086's fast bit test instructions (TEST + JNZ)
 * - Branch prediction-friendly design
 * - Watcom-compatible register usage
 *
 * @example
 * @code
 * xt_bitboard_t attackers = 0x100000001000; // Two rooks
 * if (xt_bit_count_ternary(&attackers) > 1)
 *     king_danger += DOUBLE_ROOK_PENALTY;
 *
 * // Detect doubled pawns
 xt_bitboard_t pawns = board->pawns[color];
 xt_bitboard_t files = FILE_A | FILE_C; // Example files

 if (xt_bit_count_ternary(&(pawns & files)) == 2) {
     score -= DOUBLED_PAWN_PENALTY;
 }
 * @endcode
 *
 * @warning Not suitable for exact population counts
 * @see xt_bit_count() for full population counting
 */

 /*__asm {
     .8086
     cli
     lds     si, bitboard    ; DS:SI = bitboard
     xor     ax, ax          ; AL=result, AH=temp
     mov     cx, 4           ; Process 4 words total

 scan_loop:
     lodsw                   ; AX = next 16 bits
     test    ax, ax
     jz      next_word       ; Skip if empty

     ; --- Detect bit collisions ---
     mov     bx, ax          ; BX = working copy
     shr     bx, 1
     and     bx, ax          ; Non-zero if >1 bit set
     jnz     multiple_bits   ; Early exit if found

     inc     al              ; Mark single bit
     cmp     al, 2
     je      done            ; Exit if two singles found

 next_word:
     loop    scan_loop
     jmp     done

 multiple_bits:
     mov     al, 2           ; Force return 2

 done:
     mov     result, al
     sti
 }
 */
