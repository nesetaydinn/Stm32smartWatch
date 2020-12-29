#include "tos_Fonts.h"

/*******************************************************************************
 * Size: 30 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifndef DIGITAL_FONT_FOR_NUMBER_30
#define DIGITAL_FONT_FOR_NUMBER_30 1
#endif

#if DIGITAL_FONT_FOR_NUMBER_30

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t gylph_bitmap[] = {
    /* U+2E "." */
    0xf0,

    /* U+30 "0" */
    0xff, 0xaf, 0xff, 0x1, 0xe0, 0x3c, 0x7, 0x80,
    0xf0, 0x1e, 0x3, 0xc0, 0x70, 0x6, 0x0, 0xe0,
    0x3c, 0x7, 0x80, 0xf0, 0x1e, 0x3, 0xc0, 0x78,
    0xd, 0xff, 0xff, 0xd0,

    /* U+31 "1" */
    0x7f, 0xff, 0xd7, 0xff, 0xfd,

    /* U+32 "2" */
    0xff, 0xaf, 0xfc, 0x1, 0x80, 0x30, 0x6, 0x0,
    0xc0, 0x18, 0x3, 0x0, 0x6f, 0xff, 0xff, 0x60,
    0xc, 0x1, 0x80, 0x30, 0x6, 0x0, 0xc0, 0x18,
    0x1, 0xfe, 0x7f, 0xe0,

    /* U+33 "3" */
    0xff, 0xbf, 0xfc, 0x1, 0x80, 0x30, 0x6, 0x0,
    0xc0, 0x18, 0x3, 0x0, 0x6f, 0xfd, 0xff, 0x80,
    0x30, 0x6, 0x0, 0xc0, 0x18, 0x3, 0x0, 0x60,
    0xf, 0xff, 0xff, 0xd0,

    /* U+34 "4" */
    0x0, 0x10, 0xf, 0x1, 0xe0, 0x3c, 0x7, 0x80,
    0xf0, 0x1e, 0x3, 0xc0, 0x7f, 0xfd, 0xff, 0x80,
    0x30, 0x6, 0x0, 0xc0, 0x18, 0x3, 0x0, 0x60,
    0xc, 0x1, 0x80, 0x0,

    /* U+35 "5" */
    0xff, 0xcf, 0xf3, 0x0, 0x60, 0xc, 0x1, 0x80,
    0x30, 0x6, 0x0, 0xc0, 0x1f, 0xf9, 0xff, 0x80,
    0x30, 0x6, 0x0, 0xc0, 0x18, 0x3, 0x0, 0x60,
    0xd, 0xff, 0xff, 0xd0,

    /* U+36 "6" */
    0xff, 0xcf, 0xf3, 0x0, 0x60, 0xc, 0x1, 0x80,
    0x30, 0x6, 0x0, 0xc0, 0x1f, 0xfb, 0xff, 0xe0,
    0x3c, 0x7, 0x80, 0xf0, 0x1e, 0x3, 0xc0, 0x78,
    0xd, 0xff, 0xff, 0xd0,

    /* U+37 "7" */
    0xff, 0xaf, 0xff, 0x1, 0xe0, 0x3c, 0x7, 0x80,
    0xf0, 0x1e, 0x3, 0x80, 0x30, 0x4, 0x0, 0x80,
    0x30, 0x6, 0x0, 0xc0, 0x18, 0x3, 0x0, 0x60,
    0xc, 0x1, 0x80, 0x0,

    /* U+38 "8" */
    0xff, 0xaf, 0xff, 0x1, 0xe0, 0x3c, 0x7, 0x80,
    0xf0, 0x1e, 0x3, 0xc0, 0x7f, 0xff, 0xff, 0xe0,
    0x3c, 0x7, 0x80, 0xf0, 0x1e, 0x3, 0xc0, 0x78,
    0xd, 0xff, 0xff, 0xd0,

    /* U+39 "9" */
    0xff, 0xaf, 0xff, 0x1, 0xe0, 0x3c, 0x7, 0x80,
    0xf0, 0x1e, 0x3, 0xc0, 0x7f, 0xfd, 0xff, 0x80,
    0x30, 0x6, 0x0, 0xc0, 0x18, 0x3, 0x0, 0x60,
    0xd, 0xff, 0xff, 0xd0,

    /* U+3A ":" */
    0xf0, 0x0, 0x3c
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 79, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 227, .box_w = 11, .box_h = 20, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 29, .adv_w = 79, .box_w = 2, .box_h = 20, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 34, .adv_w = 227, .box_w = 11, .box_h = 20, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 62, .adv_w = 227, .box_w = 11, .box_h = 20, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 90, .adv_w = 227, .box_w = 11, .box_h = 20, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 118, .adv_w = 227, .box_w = 11, .box_h = 20, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 146, .adv_w = 227, .box_w = 11, .box_h = 20, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 174, .adv_w = 227, .box_w = 11, .box_h = 20, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 202, .adv_w = 227, .box_w = 11, .box_h = 20, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 230, .adv_w = 227, .box_w = 11, .box_h = 20, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 258, .adv_w = 79, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 4}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint8_t glyph_id_ofs_list_0[] = {
    0, 0, 1, 2, 3, 4, 5, 6,
    7, 8, 9, 10, 11
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 46, .range_length = 13, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = glyph_id_ofs_list_0, .list_length = 13, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_FULL
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

/*Store all the custom data of the font*/
static lv_font_fmt_txt_dsc_t font_dsc = {
    .glyph_bitmap = gylph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
lv_font_t digital_font_for_number_30 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 20,          /*The maximum line height required by the font*/
    .base_line = 0,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0)
    .underline_position = -3,
    .underline_thickness = 2,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if DIGITAL_FONT_FOR_NUMBER_30*/

