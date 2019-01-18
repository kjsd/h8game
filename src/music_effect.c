/**
 * @file music_effect.c
 *
 * @brief This header file declares the definitions that are music score some
 * sound effects.
 *
 * @htmlonly
 * @version $Id: music_effect.c 85 2009-02-02 05:23:14Z Administrator $
 *
 * @author MINOURA Kenji / kenji_minoura@dnet.totec.co.jp
 *
 * Copyright (c) 2008 Totec Amenity, Ltd All rights reserved.
 * @endhtmlonly
 *
 ***********************************************************************/
#include <h8sdk.h>
#include <util.h>
#include <envelope.h>
#include <snddata.h>
#include "music_effect.h"


static const SND_Tone sta_melody0[] = {
    { &SND_MONO_NA, SND_L16, &ENVELOPE_NA },
    { &SND_MONO_C1, SND_L16, &ENVELOPE_L16 },
    { &SND_MONO_E1, SND_L16, &ENVELOPE_L16 },
    { &SND_MONO_G1, SND_L16, &ENVELOPE_L16 },
    { &SND_MONO_C2, SND_L4, &ENVELOPE_L4 },
    { &SND_MONO_NA, SND_L2, &ENVELOPE_NA },
};
static const SND_Tone sta_melody1[] = {
    { &SND_MONO_NA, SND_L16, &ENVELOPE_NA },
    { &SND_MONO_G0, SND_L16, &ENVELOPE_L16 },
    { &SND_MONO_C1, SND_L16, &ENVELOPE_L16 },
    { &SND_MONO_E1, SND_L16, &ENVELOPE_L16 },
    { &SND_MONO_G1, SND_L4, &ENVELOPE_L4 },
    { &SND_MONO_NA, SND_L2, &ENVELOPE_NA },
};
static const SND_Melody sta_part0[] = {
    { sta_melody0, UTIL_ARRAY_SIZE_OF(sta_melody0) }
};
static const SND_Melody sta_part1[] = {
    { sta_melody1, UTIL_ARRAY_SIZE_OF(sta_melody1) }
};
static const SND_Part sta_score[] = {
    { sta_part0, UTIL_ARRAY_SIZE_OF(sta_part0) },
    { sta_part1, UTIL_ARRAY_SIZE_OF(sta_part1) },
};
const SND_Music MUSIC_EftStart = {
    sta_score, UTIL_ARRAY_SIZE_OF(sta_score)
};

static const SND_Tone coi_melody[] = {
    { &SND_MONO_A1, SND_L16, &ENVELOPE_L16 },
    { &SND_MONO_E2, SND_L2, &ENVELOPE_L2 },
};
static const SND_Melody coi_part[] = {
    { coi_melody, UTIL_ARRAY_SIZE_OF(coi_melody) }
};
static const SND_Part coi_score[] = {
    { coi_part, UTIL_ARRAY_SIZE_OF(coi_part) },
};
const SND_Music MUSIC_EftCoin = {
    coi_score, UTIL_ARRAY_SIZE_OF(coi_score)
};

static const SND_Tone ata_melody[] = {
    { &SND_MONO_C2, SND_L32, &ENVELOPE_L32 },
    { &SND_MONO_Cb2, SND_L32, &ENVELOPE_L32 },
    { &SND_MONO_D2, SND_L32, &ENVELOPE_L32 },
    { &SND_MONO_Db2, SND_L32, &ENVELOPE_L32 },
    { &SND_MONO_E2, SND_L32, &ENVELOPE_L32 },
    { &SND_MONO_F2, SND_L32, &ENVELOPE_L32 },
    { &SND_MONO_E2, SND_L32, &ENVELOPE_L32 },
    { &SND_MONO_Db2, SND_L32, &ENVELOPE_L32 },

    { &SND_MONO_D2, SND_L32, &ENVELOPE_L32 },
    { &SND_MONO_Cb2, SND_L32, &ENVELOPE_L32 },
    { &SND_MONO_C2, SND_L32, &ENVELOPE_L32 },
    { &SND_MONO_H1, SND_L32, &ENVELOPE_L32 },
    { &SND_MONO_Ab1, SND_L32, &ENVELOPE_L32 },
    { &SND_MONO_A1, SND_L32, &ENVELOPE_L32 },
    { &SND_MONO_Gb1, SND_L32, &ENVELOPE_L32 },
    { &SND_MONO_G1, SND_L32, &ENVELOPE_L32 },

    { &SND_MONO_Fb1, SND_L32, &ENVELOPE_L32 },
    { &SND_MONO_F1, SND_L32, &ENVELOPE_L32 },
    { &SND_MONO_E1, SND_L32, &ENVELOPE_L32 },
    { &SND_MONO_Db1, SND_L32, &ENVELOPE_L32 },
    { &SND_MONO_D1, SND_L32, &ENVELOPE_L32 },
    { &SND_MONO_Cb1, SND_L32, &ENVELOPE_L32 },
    { &SND_MONO_C1, SND_L32, &ENVELOPE_L32 },
    { &SND_MONO_H0, SND_L32, &ENVELOPE_L32 },

    { &SND_MONO_Ab0, SND_L32, &ENVELOPE_L32 },
    { &SND_MONO_A0, SND_L32, &ENVELOPE_L32 },
    { &SND_MONO_Gb0, SND_L32, &ENVELOPE_L32 },
    { &SND_MONO_G0, SND_L32, &ENVELOPE_L32 },
    { &SND_MONO_Fb0, SND_L32, &ENVELOPE_L32 },
    { &SND_MONO_F0, SND_L32, &ENVELOPE_L32 },
    { &SND_MONO_E0, SND_L32, &ENVELOPE_L32 },
    { &SND_MONO_Db0, SND_L32, &ENVELOPE_L32 },
};
static const SND_Melody ata_part[] = {
    { ata_melody, UTIL_ARRAY_SIZE_OF(ata_melody) }
};
static const SND_Part ata_score[] = {
    { ata_part, UTIL_ARRAY_SIZE_OF(ata_part) },
};
const SND_Music MUSIC_EftAttack = {
    ata_score, UTIL_ARRAY_SIZE_OF(ata_score)
};

static const SND_Tone dam_melody[] = {
    { &SND_MONO_Cb1, SND_L16, &ENVELOPE_L16 },
    { &SND_MONO_Db1, SND_L16, &ENVELOPE_L16 },
    { &SND_MONO_D1, SND_L16, &ENVELOPE_L16 },
    { &SND_MONO_F1, SND_L16, &ENVELOPE_L16 },
    { &SND_MONO_A1, SND_L16, &ENVELOPE_L16 },
    { &SND_MONO_C2, SND_L16, &ENVELOPE_L16 },

    { &SND_MONO_NA, (SND_L8 + SND_L2), &ENVELOPE_NA },
};
static const SND_Melody dam_part[] = {
    { dam_melody, UTIL_ARRAY_SIZE_OF(dam_melody) }
};
static const SND_Part dam_score[] = {
    { dam_part, UTIL_ARRAY_SIZE_OF(dam_part) },
};
const SND_Music MUSIC_EftDamage = {
    dam_score, UTIL_ARRAY_SIZE_OF(dam_score)
};

static const SND_Tone end_melody0[] = {
    { &SND_MONO_C1, SND_L8, &ENVELOPE_L8 },
    { &SND_MONO_E1, SND_L8, &ENVELOPE_L8 },
    { &SND_MONO_G1, SND_L8, &ENVELOPE_L8 },
    { &SND_MONO_C2, SND_L8, &ENVELOPE_L8 },

    { &SND_MONO_D1, SND_L8, &ENVELOPE_L8 },
    { &SND_MONO_Fb1, SND_L8, &ENVELOPE_L8 },
    { &SND_MONO_A1, SND_L8, &ENVELOPE_L8 },
    { &SND_MONO_D2, SND_L8, &ENVELOPE_L8 },

    { &SND_MONO_E2, SND_L8, &ENVELOPE_L8 },
    { &SND_MONO_H1, SND_L8, &ENVELOPE_L8 },
    { &SND_MONO_A1, SND_L8, &ENVELOPE_L8 },
    { &SND_MONO_Fb1, SND_L8, &ENVELOPE_L8 },

    { &SND_MONO_Gb1, SND_L2, &ENVELOPE_L2 },
};
static const SND_Tone end_melody1[] = {
    { &SND_MONO_A1, SND_L4, &ENVELOPE_L4 },
    { &SND_MONO_E1, SND_L4, &ENVELOPE_L4 },
    { &SND_MONO_H1, SND_L4, &ENVELOPE_L4 },
    { &SND_MONO_F1, SND_L4, &ENVELOPE_L4 },

    { &SND_MONO_C2, SND_L0, &ENVELOPE_L0 },
};
static const SND_Melody end_part0[] = {
    { end_melody0, UTIL_ARRAY_SIZE_OF(end_melody0) }
};
static const SND_Melody end_part1[] = {
    { end_melody1, UTIL_ARRAY_SIZE_OF(end_melody1) }
};
static const SND_Part end_score[] = {
    { end_part0, UTIL_ARRAY_SIZE_OF(end_part0) },
    { end_part1, UTIL_ARRAY_SIZE_OF(end_part1) },
};
const SND_Music MUSIC_EftEnd = {
    end_score, UTIL_ARRAY_SIZE_OF(end_score)
};

