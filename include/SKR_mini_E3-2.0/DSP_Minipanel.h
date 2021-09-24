/**
 * SMuFF Firmware
 * Copyright (C) 2019 Technik Gegg
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
/*
 * Pins configuration file for FYSETC Mini12864 Panel V2.0 and 2.1
 */
#pragma once
#pragma message "Compiling for FYSETC Mini12864 Panel V2.0 and 2.1"

#define DSP_DATA_PIN        -1      // USE MOSI ON SPI1 HEADER
#define DSP_CS_PIN          PB9     // EXP1.5 (DOGLCD_CS)
#define DSP_DC_PIN          PA15    // EXP1.9 (DOGLCD_A0)
#define DSP_RESET_PIN       PA13    // SWDIO --- IMPORTANT: This display needs a RESET signal!

#define ENCODER1_PIN        PA9
#define ENCODER2_PIN        PA10
#define ENCODER_BUTTON_PIN  PB8

#define BEEPER_PIN          PB5     // EXP1.10

#if defined(USE_MINI12864_PANEL_V21)
#define NEOPIXEL_PIN        PA14    // for display backlight (SWCLK)
#define NUM_LEDS            3       // number of Neopixel LEDS
#define BRIGHTNESS          127
#define LED_TYPE            WS2812B
#endif
