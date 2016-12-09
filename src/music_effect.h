/**
 * @file music_effect.h
 *
 * @brief Sound effects
 *
 * いろんなサウンドエフェクトの楽譜データ定義。
 * データ形式は snd.h に準拠。
 *
 * @htmlonly
 * @version $Id: music_effect.h 85 2009-02-02 05:23:14Z Administrator $
 *
 * @author MINOURA Kenji / kenji_minoura@dnet.totec.co.jp
 *
 * Copyright (c) 2008 Totec Amenity, Ltd All rights reserved.
 * @endhtmlonly
 *
 ***********************************************************************/
#ifndef MUSIC_EFFECT_H
#define MUSIC_EFFECT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <snd.h>

/** ゲームスタート時の効果音 */
extern const SND_Music MUSIC_EftStart;

/** 爆弾撃破時の効果音 */
extern const SND_Music MUSIC_EftCoin;

/** 通信相手に攻撃する時の効果音 */
extern const SND_Music MUSIC_EftAttack;

/** 通信相手から攻撃された時の効果音 */
extern const SND_Music MUSIC_EftDamage;

/** ゲームオーバー時の効果音 */
extern const SND_Music MUSIC_EftEnd;
        
#ifdef __cplusplus
}
#endif

#endif /* MUSIC_EFFECT_H */
