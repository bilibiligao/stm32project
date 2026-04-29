#include "app_ui.h"
#include "rgblcd.h"
#include "led.h"
#include "key.h"
#include <stdio.h>

static uint8_t  ui_screen = 0;
static uint32_t ui_tick = 0;
static uint16_t ui_bg_color = WHITE;
static uint16_t ui_fg_color = BLACK;

void ui_init(void)
{
    rgblcd_clear(ui_bg_color);

    rgblcd_show_string(10, 5, 400, 32, 32, "Elderly Care System", BLUE);
    rgblcd_show_string(10, 40, 400, 16, 16, "STM32N647 AI Device", GRAY);

    rgblcd_draw_hline(5, 60, rgblcddev.width - 10, RED);
}

void ui_update(void)
{
    char buf[40];
    uint8_t lcd_id_str[16];
    uint16_t y = 70;

    ui_tick++;

    if (ui_tick % 2 == 0)
    {
        rgblcd_fill(5, y, rgblcddev.width - 5, y + 20, ui_bg_color);
    }

    sprintf((char *)lcd_id_str, "LCD ID: %04X", rgblcddev.id);
    rgblcd_show_string(10, y, 300, 24, 24, (char *)lcd_id_str, ui_fg_color);
    y += 30;

    sprintf(buf, "Screen: %d  Tick: %lu", ui_screen, (unsigned long)ui_tick);
    rgblcd_fill(5, y, rgblcddev.width - 5, y + 20, ui_bg_color);
    rgblcd_show_string(10, y, 300, 16, 16, buf, ui_fg_color);
    y += 22;

    sprintf(buf, "LED0: %s  LED1: %s",
            (HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_10) == GPIO_PIN_RESET) ? "ON " : "OFF",
            (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_10) == GPIO_PIN_RESET) ? "ON " : "OFF");
    rgblcd_fill(5, y, rgblcddev.width - 5, y + 20, ui_bg_color);
    rgblcd_show_string(10, y, 300, 16, 16, buf, ui_fg_color);
    y += 30;

    rgblcd_draw_hline(5, y, rgblcddev.width - 10, GRAY);
    y += 5;

    rgblcd_show_string(10, y, 300, 16, 16, "KEY0: Toggle LED0", DARKBLUE);
    y += 18;
    rgblcd_show_string(10, y, 300, 16, 16, "KEY1: Toggle LED1", DARKBLUE);
    y += 18;
    rgblcd_show_string(10, y, 300, 16, 16, "KEY2: Change Theme", DARKBLUE);
    y += 18;
    rgblcd_show_string(10, y, 300, 16, 16, "WKUP: Toggle Screen", DARKBLUE);
}

void ui_handle_key(uint8_t key_val)
{
    switch (key_val)
    {
    case KEY0_PRES:
        HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_10);
        ui_tick = 0;
        break;
    case KEY1_PRES:
        HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_10);
        ui_tick = 0;
        break;
    case KEY2_PRES:
        ui_screen++;
        switch (ui_screen % 4)
        {
        case 0:
            ui_bg_color = WHITE;
            ui_fg_color = BLACK;
            break;
        case 1:
            ui_bg_color = BLACK;
            ui_fg_color = WHITE;
            break;
        case 2:
            ui_bg_color = DARKBLUE;
            ui_fg_color = YELLOW;
            break;
        case 3:
            ui_bg_color = LIGHTBLUE;
            ui_fg_color = BLACK;
            break;
        }
        rgblcd_clear(ui_bg_color);
        ui_init();
        break;
    case WKUP_PRES:
        ui_screen = (ui_screen + 1) % 2;
        rgblcd_clear(ui_bg_color);
        ui_init();
        break;
    default:
        break;
    }
}
