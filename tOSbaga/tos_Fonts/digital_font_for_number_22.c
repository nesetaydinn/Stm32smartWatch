#include "tos_Fonts.h"

/*******************************************************************************
 * Size: 22 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifndef DIGITAL_FONT_FOR_NUMBER_22
#define DIGITAL_FONT_FOR_NUMBER_22 1
#endif

#if DIGITAL_FONT_FOR_NUMBER_22

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t gylph_bitmap[] = {
    /* U+2E "." */
    0xc0,

    /* U+30 "0" */
    0xff, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xe, 0x2,
    0x0, 0x80, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf,
    0xfe,

    /* U+31 "1" */
    0x7f, 0xf4, 0x7f, 0xf4,

    /* U+32 "2" */
    0xff, 0x80, 0xc0, 0x60, 0x30, 0x18, 0xc, 0x6,
    0xfe, 0xc0, 0x60, 0x30, 0x18, 0xc, 0x6, 0x3,
    0xfc,

    /* U+33 "3" */
    0xff, 0x80, 0xc0, 0x60, 0x30, 0x18, 0xc, 0x6,
    0xff, 0x1, 0x80, 0xc0, 0x60, 0x30, 0x18, 0xf,
    0xfe,

    /* U+34 "4" */
    0x0, 0x40, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x6,
    0xff, 0x1, 0x80, 0xc0, 0x60, 0x30, 0x18, 0xc,
    0x0,

    /* U+35 "5" */
    0xff, 0x60, 0x30, 0x18, 0xc, 0x6, 0x3, 0x0,
    0xff, 0x1, 0x80, 0xc0, 0x60, 0x30, 0x18, 0xf,
    0xfe,

    /* U+36 "6" */
    0xff, 0x60, 0x30, 0x18, 0xc, 0x6, 0x3, 0x0,
    0xff, 0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf,
    0xfe,

    /* U+37 "7" */
    0xff, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xe, 0x2,
    0x1, 0x1, 0x80, 0xc0, 0x60, 0x30, 0x18, 0xc,

    /* U+38 "8" */
    0xff, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x6,
    0xff, 0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf,
    0xfe,

    /* U+39 "9" */
    0xff, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x6,
    0xff, 0x1, 0x80, 0xc0, 0x60, 0x30, 0x18, 0xf,
    0xfe,

    /* U+3A ":" */
    0xc0, 0x3
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 58, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 166, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 18, .adv_w = 58, .box_w = 2, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 22, .adv_w = 166, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 39, .adv_w = 166, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 56, .adv_w = 166, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 73, .adv_w = 166, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 90, .adv_w = 166, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 107, .adv_w = 166, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 123, .adv_w = 166, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 140, .adv_w = 166, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 157, .adv_w = 58, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 4}
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
lv_font_t digital_font_for_number_22 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 15,          /*The maximum line height required by the font*/
    .base_line = 0,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0)
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if DIGITAL_FONT_FOR_NUMBER_22*/

