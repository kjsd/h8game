/**
 * @file h8game.c
 *
 * @version $Id: h8game.c 85 2009-02-02 05:23:14Z Administrator $
 * @version $Name:$
 *
 * @brief This file contains the implementation of modules which are
 * responsibility of management of H8-BASE Game.
 *
 * @component H8GAME
 *
 * @author MINOURA Kenji / kenji_minoura@dnet.totec.co.jp
 *
 * Copyright (c) 2009 Totec Amenity, Ltd All rights reserved.
 *
 * @see <related_items>
 ***********************************************************************/
#ifdef __cplusplus
extern "C" {
void abort(void);
#endif
void main(void);
#ifdef __cplusplus
}
#endif

#include <util.h>
#include <led.h>
#include <adc.h>
#include <push_switch.h>
#include "music_effect.h"
#include "h8game.h"

#define H8GAME_LCDWRITE_ENTER(ox, oy, tx, ty)       \
    {                                               \
        LCD_setVisual(TRUE, FALSE, FALSE);          \
        LCD_getCursor(&(ox), &(oy));                \
        LCD_setCursor((tx), (ty));                  \
    }

#define H8GAME_LCDWRITE_LEAVE(ox, oy)               \
    {                                               \
        LCD_setCursor((ox), (oy));                  \
        LCD_setVisual(TRUE, TRUE, FALSE);           \
    }

#define H8GAME_UPDATE_STATUS(front, total)                      \
    {                                                           \
        _SINT x, y;                                             \
        _SBYTE str[3] = { '\0' };                               \
        H8GAME_LCDWRITE_ENTER(x, y, 3, 0);                      \
        UTIL_itoa((front), 16, str, 2);                         \
        LCD_puts(str);                                          \
        LCD_puts("/");                                          \
        UTIL_itoa((total), 16, str, 2);                         \
        LCD_puts(str);                                          \
        H8GAME_LCDWRITE_LEAVE(x, y);                            \
    }

void h8game_update_enemy(_UBYTE type)
{
    _SINT x, y;
    _UBYTE enemy = UTIL_rand() % 16;
    _SINT i = LCD_MAX_COLS;

    while (h8game_enemy & (1U << enemy))
    {
        if (i-- == 0) return;
        enemy = UTIL_NEXT_RING(enemy, LCD_MAX_COLS - 1);
    }
    h8game_enemy |= (1U << enemy);

    H8GAME_LCDWRITE_ENTER(x, y, enemy, 1);
    if (type == 0)
    {
        h8game_enemy_type &= ~(1U << enemy);
        LCD_puts("#");
    }
    else
    {
        h8game_enemy_type |= (1U << enemy);
        LCD_puts("@");
    }
    H8GAME_LCDWRITE_LEAVE(x, y);
}

static void h8game_init()
{
    _UWORD counter = 1U << 8;
    _SBYTE str[3] = { '\0' };

    LED_INIT;
    LCD_init();
    PSW_init(FALSE);
    ADC_init(ADC_SCAN, FALSE);
    ADC_enable(ADC_AN1);
    ADC_start();

    SSRP_init(SSRP_ADDR);
    SND_init();
    SND_setVolume(3);
    UTIL_srand(SSRP_ADDR ^ ADC_get(ADC_AN1, TRUE));

    SSRP_start();

    LCD_cls();
    LCD_puts(SSRP_AddrStr);
    LCD_puts(":");
    UTIL_itoa(SSRP_getPear(SSRP_CON_FRONT), 16, str, 2);
    LCD_puts(str);
    LCD_puts("-");
    UTIL_itoa(SSRP_getPear(SSRP_CON_BACK), 16, str, 2);
    LCD_puts(str);
    LCD_puts("/");
    UTIL_itoa(SSRP_getTotalPear(), 16, str, 2);
    LCD_puts(str);
    LCD_puts("\nPush S1 to start");

    while (!PSW_snapShot(PSW_SW1))
    {
        SSRP_exec();

        LCD_setCursor(3, 0);
        UTIL_itoa(SSRP_getPear(SSRP_CON_FRONT), 16, str, 2);
        LCD_puts(str);
        LCD_setCursor(6, 0);
        UTIL_itoa(SSRP_getPear(SSRP_CON_BACK), 16, str, 2);
        LCD_puts(str);
        LCD_setCursor(9, 0);
        UTIL_itoa(SSRP_getTotalPear(), 16, str, 2);
        LCD_puts(str);
    }

    SND_setMusic(&MUSIC_EftStart, 0, NULL);
    SND_play();

    LCD_cls();
    LCD_setCursor(0, 0);
    LCD_puts("       Go       ");
    UTIL_WAIT(3000);
    LCD_setCursor(0, 0);

    LCD_puts(SSRP_AddrStr);
    LCD_puts(":");
    UTIL_itoa(SSRP_getPear(SSRP_CON_FRONT), 16, str, 2);
    LCD_puts(str);
    LCD_puts("/");
    UTIL_itoa(SSRP_getTotalPear(), 16, str, 2);
    LCD_puts(str);

    LCD_puts(" 00 0000");

    LCD_setVisual(TRUE, TRUE, FALSE);
}

static BOOL h8game_gameOver()
{
    static _UWORD blink_counter = 0;
    _SINT x = 0;
    _SINT y = 0;
    _SINT i;

    for (i = 0; i < UTIL_ARRAY_SIZE_OF(h8game_enemy_life); i++)
    {
        if (h8game_enemy & (1U << i))
        {
            if (++h8game_enemy_life[i] > H8GAME_ENEMY_LIFE_BORDER)
            {
                return TRUE;
            }

            if (h8game_enemy_life[i] > H8GAME_ENEMY_LIFE_WARN)
            {
                H8GAME_LCDWRITE_ENTER(x, y, i, 1);
                if (blink_counter++ & (1U << 8))
                {
                    if (h8game_enemy_type & (1U << i))
                    {
                        LCD_puts("@");
                    }
                    else
                    {
                        LCD_puts("#");
                    }
                    
                }
                else
                {
                    LCD_puts(" ");
                }
                H8GAME_LCDWRITE_LEAVE(x, y);
            }
        }
    }

    return FALSE;
}

static void h8game_execEnemy()
{
    static _UWORD counter = 0;
    static _UWORD enemy_counter = 0x800;
    SSRP_Header* header = NULL;
    _UBYTE* data = NULL;
    _SINT rsize = 0;

    rsize = SSRP_recvfrom(&header, &data);
    if (rsize == 1)
    {
        if (SSRP_COMMAND_EQ(header, H8GAME_CMD_ATTACK, SSRP_FLG_EVT))
        {
            SND_setMusic(&MUSIC_EftDamage, 0, NULL);
            SND_play();
            h8game_update_enemy(1);
        }
    }

    if (counter++ >= enemy_counter)
    {
        h8game_update_enemy(0);

        counter = 0;
        enemy_counter = UTIL_rand() >> 2;
    }
}

static void h8game_execScope()
{
    static _UBYTE an0_prev = 0;
    static _UBYTE an1_prev = 0;
    SSRP_Address to;
    _SDWORD adcdata = -1;
    _UBYTE idx = 0;

    adcdata = ADC_get(ADC_AN0, FALSE);
    if (adcdata >= 0)
    {
        adcdata >>= 2;
        if (adcdata != an0_prev)
        {
            h8game_attack_to = adcdata;
            H8GAME_UPDATE_STATUS(h8game_attack_to, h8game_total_node);
        }
        an0_prev = adcdata;
    }

    adcdata = ADC_get(ADC_AN1, TRUE);
    if (adcdata >= 0)
    {
        adcdata >>= 6;
        if (adcdata != an1_prev)
        {
            LCD_setCursor(adcdata, 1);
            an1_prev = adcdata;
        }
    }
}

static void h8game_execAttack()
{
    _SBYTE str[5] = { '\0' };
    _SINT x;
    _SINT y;
    _UBYTE buf = 0;

    LCD_getCursor(&x, &y);
    if (PSW_oneShot(PSW_SW2) && (h8game_enemy & (1U << x)))
    {
        SND_setMusic(&MUSIC_EftCoin, 0, NULL);
        SND_play();

        h8game_enemy &= ~(1U << x);
        h8game_enemy_life[x] = 0;
        if (h8game_score & (1U << 0))
        {
            h8game_attack_score++;
        }
        h8game_score++;

        LCD_setVisual(TRUE, FALSE, FALSE);
        LCD_puts(" ");

        LCD_setCursor(9, 0);
        str[2] = '\0';
        UTIL_itoa(h8game_attack_score, 16, str, 2);
        LCD_puts(str);

        LCD_setCursor(12, 0);
        str[4] = '\0';
        UTIL_itoa(h8game_score, 16, str, 4);
        LCD_puts(str);

        H8GAME_LCDWRITE_LEAVE(x, y);
    }
    if ((h8game_attack_score > 0) && (h8game_attack_to != SSRP_ADDR_INVALID) &&
        PSW_oneShot(PSW_SW1))
    {
        SND_setMusic(&MUSIC_EftAttack, 0, NULL);
        SND_play();

        SSRP_sendto(h8game_attack_to, H8GAME_CMD_ATTACK, SSRP_FLG_EVT,
                    &buf, sizeof(buf), NULL, TRUE);

        --h8game_attack_score;

        H8GAME_LCDWRITE_ENTER(x, y, 9, 0);
        str[2] = '\0';
        UTIL_itoa(h8game_attack_score, 16, str, 2);
        LCD_puts(str);
        H8GAME_LCDWRITE_LEAVE(x, y);
    }
}

void main(void)
{
    _UBYTE total_prev = 0;

    h8game_init();
    h8game_attack_to = SSRP_getPear(SSRP_CON_FRONT);

    while (!h8game_gameOver())
    {
        SSRP_exec();

        h8game_total_node = SSRP_getTotalPear();
        if (h8game_total_node != total_prev)
        {
            H8GAME_UPDATE_STATUS(h8game_attack_to, h8game_total_node);
            total_prev = h8game_total_node;
        }

        h8game_execEnemy();
        h8game_execScope();
        h8game_execAttack();
    }

    SSRP_end();

    SND_setMusic(&MUSIC_EftEnd, 0, NULL);
    SND_play();

    LCD_cls();
    LCD_setCursor(0, 0);
    LCD_puts("G A M E O V E R ");

    while (TRUE)
    {
        SSRP_exec();
    }
}

#ifdef __cplusplus
void abort(void)
{
	
}
#endif
