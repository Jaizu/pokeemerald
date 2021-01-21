static const u16 sMorganasLetterPalette[] = INCBIN_U16("graphics/letters/morganas_letter.gbapal");
static const u32 sMorganasLetterTilemap[] = INCBIN_U32("graphics/letters/morganas_letter.bin.lz");
static const u32 sMorganasLetterTiles[] = INCBIN_U32("graphics/letters/morganas_letter.4bpp.lz");
static const u8 sText_MorganasLetter[] = _("Good day. You recently withdrew a\nbook from the Celanto Library.\n\nPlease bring it with you to the\nReliquia Ruins totem poles.\n\nI will wait for you there.\n\nThank you for co-operating.");

static const struct LetterData sLetters[] = {
    [LETTER_MORGANAS_LETTER] = {
        .palette = sMorganasLetterPalette,
        .tilemap = sMorganasLetterTilemap,
        .tiles = sMorganasLetterTiles,
        .string = sText_MorganasLetter,
        .textX = 8,
        .textY = 1,
    }
};
