#ifndef GUARD_LETTER_H
#define GUARD_LETTER_H

struct LetterData {
    const u16 *palette;
    const u32 *tilemap;
    const u32 *tiles;
    const u8 *string;
    u8 textX;
    u8 textY;
};

#endif // GUARD_LETTER_H
