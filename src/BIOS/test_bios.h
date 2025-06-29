#ifndef TESTS_BIOS_H
#define TESTS_BIOS_H

#include "../TDD/tdd_macros.h"
#include "../BIOS/bios_video_services.h"
#include "bios_video_services_constants.h"
#include "bios_video_services_types.h"
#include <stdio.h>

#define BIOS_VIDEO_TESTS &bios_video_services

TEST(bios_video_services) {
    bios_video_state_t video;
    bios_cursor_state_t cursor;
    bios_set_video_mode(MDA_TEXT_MONOCHROME_80X25);
    bios_get_video_state(&video);
    printf("video cols\t%i\nvideo mode\t%s\nvideo page\t%X\n", video.columns, bios_video_mode_names[video.mode], video.page);
    EXPECT_EQ(video.columns, 80);
    EXPECT_EQ(video.mode, MDA_TEXT_MONOCHROME_80X25);
    EXPECT_EQ(video.page, 0);
    bios_set_cursor_position(4, 3, 0);
    bios_get_cursor_position_size(&cursor, video.page);
    EXPECT_EQ(cursor.start_scan, 6);
    EXPECT_EQ(cursor.end_scan, 7);
    EXPECT_EQ(cursor.column, 4);
    EXPECT_EQ(cursor.row, 3);
    printf("cursor scan line %i - %i\ncursor position %i,%i\n", cursor.start_scan, cursor.end_scan, cursor.column, cursor.row);
    getchar();
}

#endif
