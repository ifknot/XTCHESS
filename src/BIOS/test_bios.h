#ifndef TESTS_BIOS_H
#define TESTS_BIOS_H

#include "../TDD/tdd_macros.h"
#include "../BIOS/bios_video_services.h"
#include "bios_video_services_constants.h"
#include "bios_video_services_types.h"
#include <stdio.h>

#define BIOS_VIDEO_TESTS &bios_video_services

TEST(bios_video_services) {

     typedef union {
        uint16_t char_attr;
        struct {
            char chr;
            char attr;
        } pair;
    } char_attr_pair_t;

    bios_video_state_t video;
    bios_cursor_state_t cursor;
    char_attr_pair_t chattr;

    bios_set_video_mode(MDA_TEXT_MONOCHROME_80X25);
    bios_get_video_state(&video);
        printf("video cols\t%i\nvideo mode\t%s\nvideo page\t%X\n", video.columns, bios_video_mode_names[video.mode], video.page);
        EXPECT_EQ(video.columns, 80);
        EXPECT_EQ(video.mode, MDA_TEXT_MONOCHROME_80X25);
        EXPECT_EQ(video.page, 0);
    bios_set_cursor_position(4, 3,  video.page);
    bios_get_cursor_position_and_size(&cursor, video.page);
        EXPECT_EQ(cursor.start_scan, 6);
        EXPECT_EQ(cursor.end_scan, 7);
        EXPECT_EQ(cursor.column, 4);
        EXPECT_EQ(cursor.row, 3);
        printf("cursor scan line %i - %i\ncursor position %i,%i\n", cursor.start_scan, cursor.end_scan, cursor.column, cursor.row);
    bios_set_cursor_position(0, 0, video.page);
    bios_write_character_and_attribute_at_cursor('X', 0x07 | 0x80, 80, video.page); // top row blinking Xs
    chattr.char_attr =  bios_read_character_and_attribute_at_cursor(video.page);
        EXPECT_EQ(chattr.pair.chr, 'X');
        EXPECT_EQ(chattr.pair.attr, 0x07 | 0x80);
    bios_set_cursor_position(0, 1, video.page);
    bios_write_character_at_cursor('0', 0, 80, video.page); // 2nd row 0s
    chattr.char_attr =  bios_read_character_and_attribute_at_cursor(video.page);
        EXPECT_EQ(chattr.pair.chr, '0');
        EXPECT_EQ(chattr.pair.attr, 0x07);
    bios_set_cursor_position(0, 0, video.page);
    bios_write_character_at_cursor('!', 0, 1, video.page); //
    chattr.char_attr =  bios_read_character_and_attribute_at_cursor(video.page);
        EXPECT_EQ(chattr.pair.chr, '!');
        EXPECT_EQ(chattr.pair.attr, 0x07 | 0x80);
    bios_write_text_teletype_mode(7, 0, video.page); // "bell" does not advance cursor
    chattr.char_attr =  bios_read_character_and_attribute_at_cursor(video.page);
        EXPECT_EQ(chattr.pair.chr, '!');
        EXPECT_EQ(chattr.pair.attr, 0x07 | 0x80);
    bios_write_text_teletype_mode('?', 0, video.page); // does advance cursor
    chattr.char_attr =  bios_read_character_and_attribute_at_cursor(video.page);
        EXPECT_EQ(chattr.pair.chr, 'X');
        EXPECT_EQ(chattr.pair.attr, 0x07 | 0x80);
    getchar();
    }

#endif
