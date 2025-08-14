

/* Start of automatically generated font definition for Iconfont24. */

#ifndef MF_RLEFONT_INTERNALS
#define MF_RLEFONT_INTERNALS
#endif
#include "../mcufont/mf_rlefont.h"

#ifndef MF_RLEFONT_VERSION_4_SUPPORTED
#error The font file is not compatible with this version of mcufont.
#endif

static const uint8_t mf_rlefont_Iconfont24_dictionary_data[78] PROGMEM = {
    0x05, 0xc1, 0xc5, 0xd8, 0xc6, 0xc1, 0x09, 0xc3, 0xcd, 0x83, 0xcd, 0xc3, 0x07, 0xc2, 0xce, 0x80,
    0xcc, 0xd7, 0xcc, 0x80, 0xce, 0xc2, 0x06, 0xc9, 0x80, 0xcb, 0x04, 0xcb, 0x80, 0xc9, 0x06, 0xcd,
    0x80, 0xc3, 0x04, 0xc3, 0x80, 0xce, 0x06, 0x81, 0x06, 0x81, 0x06, 0x81, 0x06, 0x81, 0x03, 0xe9,
    0x81, 0xf9, 0xd9, 0x81, 0xe9, 0xbf, 0x85, 0xce, 0xd8, 0xce, 0x8b, 0xc4, 0x02, 0xc4, 0x8b, 0xc1,
    0x02, 0xc1, 0x8b, 0xc6, 0x02, 0xc6, 0x8c, 0xdb, 0xbf, 0x86, 0xf6, 0xf6, 0xf6, 0xf6,
};

static const uint16_t mf_rlefont_Iconfont24_dictionary_offsets[2] PROGMEM = {
    0x0000, 0x004e,
};

static const uint8_t mf_rlefont_Iconfont24_glyph_data_0[2] PROGMEM = {
    0x18, 0x18,
};

static const uint16_t mf_rlefont_Iconfont24_glyph_offsets_0[1] PROGMEM = {
    0x0000,
};

static const struct mf_rlefont_char_range_s mf_rlefont_Iconfont24_char_ranges[] = {
    {69, 1, mf_rlefont_Iconfont24_glyph_offsets_0, mf_rlefont_Iconfont24_glyph_data_0},
};

const struct mf_rlefont_s mf_rlefont_Iconfont24 = {
    {
    "Untitled1 Regular 24",
    "Iconfont24",
    16, /* width */
    22, /* height */
    24, /* min x advance */
    24, /* max x advance */
    -4, /* baseline x */
    19, /* baseline y */
    26, /* line height */
    1, /* flags */
    32, /* fallback character */
    &mf_rlefont_character_width,
    &mf_rlefont_render_character,
    },
    4, /* version */
    mf_rlefont_Iconfont24_dictionary_data,
    mf_rlefont_Iconfont24_dictionary_offsets,
    1, /* rle dict count */
    1, /* total dict count */
    1, /* char range count */
    mf_rlefont_Iconfont24_char_ranges,
};

#ifdef MF_INCLUDED_FONTS
/* List entry for searching fonts by name. */
static const struct mf_font_list_s mf_rlefont_Iconfont24_listentry = {
    MF_INCLUDED_FONTS,
    (struct mf_font_s*)&mf_rlefont_Iconfont24
};
#undef MF_INCLUDED_FONTS
#define MF_INCLUDED_FONTS (&mf_rlefont_Iconfont24_listentry)
#endif


/* End of automatically generated font definition for Iconfont24. */

