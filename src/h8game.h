/**
 * @file h8game.h
 *
 * @brief H8通信対戦ゲーム
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
 * @mainpage はじめに
 *
 * @section abstract この文書について
 * この文書は、H8通信対戦ゲームの内部構造を記述した詳細設計仕様書である。@n
 * 文書は大きくデータ構造の解説セクションと、ファイルモジュール別の
 * インタフェース解説セクションに分かれており、それぞれのセクションは
 * 冒頭で解説項目を概略説明付きで列挙した後、項目の詳細説明が続くという
 * 構成になっている。
 *
 * @section target 対象
 * H8通信対戦ゲームの解析者を対象とした文書であり、システムの基本仕様と
 * H8-BASE2のプラットフォームを理解していることが前提である。@n
 * また、このアプリケーションはH8SDKを使用して設計されている。
 *
 * @see H8SDK詳細設計仕様書
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
 * @brief 通信相手攻撃時のコマンド
 *
 * データペイロードは何もなし。
 *
 * @see ssrp.h
 */
#define H8GAME_CMD_ATTACK (SSRP_CMD_EX | 0x00)

/** 爆弾が爆発するボーダー値 */
#define H8GAME_ENEMY_LIFE_BORDER 0x4000

/** 爆弾の爆発を警告するボーダー値 */
#define H8GAME_ENEMY_LIFE_WARN (H8GAME_ENEMY_LIFE_BORDER - 0x1800)

/** ゲームに参加しているノード数 */
static _UBYTE h8game_total_node = 0;

/**
 * @brief 爆弾出現位置ビットマップ
 *
 * 16bitのマップで爆弾表示のオン/オフを表すためのフラグ。
 * LCDの表示位置とビットの位置が同じになる。
 */
static _UWORD h8game_enemy = 0;

/**
 * @brief 爆弾タイプ識別ビットマップ
 *
 * 16bitのマップで爆弾のタイプを表すためのフラグ。
 * 0が通常爆弾。1が対戦相手から攻撃された爆弾。
 */
static _UWORD h8game_enemy_type = 0;

/**
 * @brief 爆弾残り時間カウンタ
 *
 * 各爆弾が爆発するまでの時間を記録してあるカウンタ。
 * セットされている爆弾は常にカウントアップされる。
 * 既定値になるとゲームオーバー
 */
static _UWORD h8game_enemy_life[LCD_MAX_COLS] = { 0 };

/**
 * @brief 攻撃対象ノードアドレス
 *
 * 攻撃対象としてセットされているノードのアドレス。
 * RV3ツマミで変更できる。
 */
static SSRP_Address h8game_attack_to = SSRP_ADDR_INVALID;

/**
 * @brief 攻撃可能数
 *
 * 通信相手に攻撃可能な回数。ゲームスコアによって増大する
 */
static _UBYTE h8game_attack_score = 0;

/**
 * @brief ゲームスコア
 */
static _UWORD h8game_score = 0;

/**
 * @brief 初期化
 *
 * 各ドライバモジュールの初期化と起動の後、タイトル画面を表示し、
 * ゲームスタートを待つ。
 */
static void h8game_init();

/**
 * @brief ゲームオーバー判定
 *
 * ゲームオーバーになったかどうかを判定する。爆発の警告表示も行う。
 * 
 * @retval TRUE ゲームオーバーになった
 * @retval FALSE ゲームオーバーではない
 */
static BOOL h8game_gameOver();

/**
 * @brief 爆弾出現
 *
 * 対戦相手からの攻撃コマンドを受信、またはランダム値によって、爆弾の出現
 * を更新する。
 */
static void h8game_execEnemy();

/**
 * @brief カーソルと照準の変更
 *
 * ツマミの操作を読み込み、カーソル移動と攻撃対象ノードの表示を更新する
 */
static void h8game_execScope();

/**
 * @brief 攻撃処理
 *
 * ボタンの操作を読み込み、爆弾や通信相手への攻撃処理を行い、表示を更新する。
 */
static void h8game_execAttack();

/**
 * @brief 攻撃処理
 *
 * フラグ変数によって爆弾の表示状態を更新する。
 */
static void h8game_updateEnemy();

#ifdef __cplusplus
}
#endif

#endif /* H8GAME_H */
