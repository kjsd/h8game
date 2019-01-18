/**
 * @file h8game.h
 *
 * @brief H8�ʐM�ΐ�Q�[��
 *
 * @htmlonly
 * @version $Id: h8game.h 85 2009-02-02 05:23:14Z Administrator $
 *
 * @author MINOURA Kenji / kenji_minoura@dnet.totec.co.jp
 *
 * Copyright (c) 2008 Totec Amenity, Ltd All rights reserved.
 * @endhtmlonly
 *
 ***********************************************************************/
/**
 * @mainpage �͂��߂�
 *
 * @section abstract ���̕����ɂ���
 * ���̕����́AH8�ʐM�ΐ�Q�[���̓����\�����L�q�����ڍא݌v�d�l���ł���B@n
 * �����͑傫���f�[�^�\���̉���Z�N�V�����ƁA�t�@�C�����W���[���ʂ�
 * �C���^�t�F�[�X����Z�N�V�����ɕ�����Ă���A���ꂼ��̃Z�N�V������
 * �`���ŉ�����ڂ��T�������t���ŗ񋓂�����A���ڂ̏ڍא����������Ƃ���
 * �\���ɂȂ��Ă���B
 *
 * @section target �Ώ�
 * H8�ʐM�ΐ�Q�[���̉�͎҂�ΏۂƂ��������ł���A�V�X�e���̊�{�d�l��
 * H8-BASE2�̃v���b�g�t�H�[���𗝉����Ă��邱�Ƃ��O��ł���B@n
 * �܂��A���̃A�v���P�[�V������H8SDK���g�p���Đ݌v����Ă���B
 *
 * @see H8SDK�ڍא݌v�d�l��
 *
 ***********************************************************************/
#ifndef H8GAME_H
#define H8GAME_H

#ifdef __cplusplus
extern "C" {
#endif

#include <h8sdk.h>
#include <lcd.h>
#include <ssrp.h>

#if (SSRP_ADDR < 1) || (SSRP_ADDR > 254)
#error "Define the SSRP_ADDR (1-254)"
#endif

/**
 * @brief �ʐM����U�����̃R�}���h
 *
 * �f�[�^�y�C���[�h�͉����Ȃ��B
 *
 * @see ssrp.h
 */
#define H8GAME_CMD_ATTACK (SSRP_CMD_EX | 0x00)

/** ���e����������{�[�_�[�l */
#define H8GAME_ENEMY_LIFE_BORDER 0x4000

/** ���e�̔������x������{�[�_�[�l */
#define H8GAME_ENEMY_LIFE_WARN (H8GAME_ENEMY_LIFE_BORDER - 0x1800)

/** �Q�[���ɎQ�����Ă���m�[�h�� */
static _UBYTE h8game_total_node = 0;

/**
 * @brief ���e�o���ʒu�r�b�g�}�b�v
 *
 * 16bit�̃}�b�v�Ŕ��e�\���̃I��/�I�t��\�����߂̃t���O�B
 * LCD�̕\���ʒu�ƃr�b�g�̈ʒu�������ɂȂ�B
 */
static _UWORD h8game_enemy = 0;

/**
 * @brief ���e�^�C�v���ʃr�b�g�}�b�v
 *
 * 16bit�̃}�b�v�Ŕ��e�̃^�C�v��\�����߂̃t���O�B
 * 0���ʏ픚�e�B1���ΐ푊�肩��U�����ꂽ���e�B
 */
static _UWORD h8game_enemy_type = 0;

/**
 * @brief ���e�c�莞�ԃJ�E���^
 *
 * �e���e����������܂ł̎��Ԃ��L�^���Ă���J�E���^�B
 * �Z�b�g����Ă��锚�e�͏�ɃJ�E���g�A�b�v�����B
 * ����l�ɂȂ�ƃQ�[���I�[�o�[
 */
static _UWORD h8game_enemy_life[LCD_MAX_COLS] = { 0 };

/**
 * @brief �U���Ώۃm�[�h�A�h���X
 *
 * �U���ΏۂƂ��ăZ�b�g����Ă���m�[�h�̃A�h���X�B
 * RV3�c�}�~�ŕύX�ł���B
 */
static SSRP_Address h8game_attack_to = SSRP_ADDR_INVALID;

/**
 * @brief �U���\��
 *
 * �ʐM����ɍU���\�ȉ񐔁B�Q�[���X�R�A�ɂ���đ��傷��
 */
static _UBYTE h8game_attack_score = 0;

/**
 * @brief �Q�[���X�R�A
 */
static _UWORD h8game_score = 0;

/**
 * @brief ������
 *
 * �e�h���C�o���W���[���̏������ƋN���̌�A�^�C�g����ʂ�\�����A
 * �Q�[���X�^�[�g��҂B
 */
static void h8game_init();

/**
 * @brief �Q�[���I�[�o�[����
 *
 * �Q�[���I�[�o�[�ɂȂ������ǂ����𔻒肷��B�����̌x���\�����s���B
 * 
 * @retval TRUE �Q�[���I�[�o�[�ɂȂ���
 * @retval FALSE �Q�[���I�[�o�[�ł͂Ȃ�
 */
static BOOL h8game_gameOver();

/**
 * @brief ���e�o��
 *
 * �ΐ푊�肩��̍U���R�}���h����M�A�܂��̓����_���l�ɂ���āA���e�̏o��
 * ���X�V����B
 */
static void h8game_execEnemy();

/**
 * @brief �J�[�\���ƏƏ��̕ύX
 *
 * �c�}�~�̑����ǂݍ��݁A�J�[�\���ړ��ƍU���Ώۃm�[�h�̕\�����X�V����
 */
static void h8game_execScope();

/**
 * @brief �U������
 *
 * �{�^���̑����ǂݍ��݁A���e��ʐM����ւ̍U���������s���A�\�����X�V����B
 */
static void h8game_execAttack();

/**
 * @brief �U������
 *
 * �t���O�ϐ��ɂ���Ĕ��e�̕\����Ԃ��X�V����B
 */
static void h8game_updateEnemy();

#ifdef __cplusplus
}
#endif

#endif /* H8GAME_H */
