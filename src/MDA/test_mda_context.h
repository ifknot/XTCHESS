#ifndef TEST_MDA_CONTEXT_H
#define TEST_MDA_CONTEXT_H

#include "../TDD/tdd_macros.h"
#include "mda_attributes.h"
#include "mda_context.h"
#include "mda_constants.h"
#include "mda_widget.h"
#include <stdio.h>

#define MDA_CONTEXT_TESTS &mda_context_test \

TEST(mda_context_test) {
    mda_context_t ctx;
    mda_initialize_default_context(&ctx);
        EXPECT_EQ(ctx.attributes, MDA_NORMAL);
        EXPECT_EQ(ctx.x, 0);
        EXPECT_EQ(ctx.y, 0);
        EXPECT_EQ(ctx.width, 80);
        EXPECT_EQ(ctx.height, 25);
        EXPECT_EQ(ctx.cursor.column, 0);
        EXPECT_EQ(ctx.cursor.row, 0);
    mda_set_context_frame(&ctx, 10, 11, 20, 11);
    mda_set_attributes(&ctx, MDA_REVERSE);
        EXPECT_EQ(ctx.attributes, MDA_REVERSE);
        EXPECT_EQ(ctx.x, 10);
        EXPECT_EQ(ctx.y, 11);
        EXPECT_EQ(ctx.width, 20);
        EXPECT_EQ(ctx.height, 11);
        EXPECT_EQ(ctx.cursor.column, 10);
        EXPECT_EQ(ctx.cursor.row, 11);
    mda_reset_attributes(&ctx);
        EXPECT_EQ(ctx.attributes, MDA_NORMAL);
    mda_initialize_default_context(&ctx);
    mda_cursor_to(&ctx, 1, 2);
        EXPECT_EQ(ctx.cursor.column, 1);
        EXPECT_EQ(ctx.cursor.row, 2);
    mda_write_char(&ctx, '*');
    mda_write_row(&ctx, '.', ctx.video.columns);
    mda_write_string(&ctx, "DELETEEME");
    mda_ascii_DEL(&ctx);
    mda_ascii_DEL(&ctx);
    mda_write_char(&ctx, '!');
    mda_ascii_BS(&ctx);
    mda_ascii_BS(&ctx);
    mda_write_char(&ctx, ' ');
    mda_write_CRLF(&ctx);
    mda_write_string(&ctx, "hello!");
    mda_ascii_HT(&ctx);
    mda_write_row(&ctx, CP437_RIGHT_ARROW_IBM, 20);
    mda_write_column(&ctx, CP437_DOWN_ARROW, 11);
    mda_set_context_frame(&ctx, 40, 2, 10, 11);
    mda_write_row(&ctx, CP437_RIGHT_ARROW_IBM, 20);
    mda_write_column(&ctx, CP437_DOWN_ARROW, 20);

    mda_ascii_BEL(&ctx);

    getchar();
}

TEST(mda_widgets_test) {
    mda_context_t ctx;
    //mda_widget_context_border(
}

#endif
