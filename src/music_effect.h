/**
 * @file music_effect.h
 *
 * @brief Sound effects
 *
 * �����ȃT�E���h�G�t�F�N�g�̊y���f�[�^��`�B
 * �f�[�^�`���� snd.h �ɏ����B
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

/** �Q�[���X�^�[�g���̌��ʉ� */
extern const SND_Music MUSIC_EftStart;

/** ���e���j���̌��ʉ� */
extern const SND_Music MUSIC_EftCoin;

/** �ʐM����ɍU�����鎞�̌��ʉ� */
extern const SND_Music MUSIC_EftAttack;

/** �ʐM���肩��U�����ꂽ���̌��ʉ� */
extern const SND_Music MUSIC_EftDamage;

/** �Q�[���I�[�o�[���̌��ʉ� */
extern const SND_Music MUSIC_EftEnd;
        
#ifdef __cplusplus
}
#endif

#endif /* MUSIC_EFFECT_H */
