/*
	Copyright 2019 @foostan
	Copyright 2020 Drashna Jaelre <@drashna>

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.	If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <stdio.h>
#include <keymap_spanish.h>

// Magic for alt_t(/) starts
// From: https://docs.qmk.fm/#/feature_tap_dance?id=example-5-using-tap-dance-for-advanced-mod-tap-and-layer-tap-keys
enum td_keycodes {
		ALT_S7
};

typedef enum {
		TD_NONE,
		TD_UNKNOWN,
		TD_SINGLE_TAP,
		TD_SINGLE_HOLD,
		TD_DOUBLE_SINGLE_TAP
} td_state_t;

static td_state_t td_state;

td_state_t cur_dance(qk_tap_dance_state_t *state);

void alts7_finished(qk_tap_dance_state_t *state, void *user_data);
void alts7_reset(qk_tap_dance_state_t *state, void *user_data);
// Magic for alt_t(/) ends
// More after layout

// List of keycodes: https://docs.qmk.fm/#/keycodes

// TODO: Workspaces on top row lol
// TODO: left-right arrow somewhere that can be holded
// TODO: Make sure that I can do mod + enter
// TODO: Make sure that I can do mod + enter
// TODO: VOLUME
// TODO: Brightness and backlight control

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_split_3x6_3(
	//,-----------------------------------------------------.										 ,-----------------------------------------------------.
			 XXXXXXX,		KC_Q,		 KC_W,		KC_E,		 KC_R,		KC_T,													KC_Y,		 KC_U,		KC_I,		 KC_O,	 KC_P,	KC_BSPC,
	//|--------+--------+--------+--------+--------+--------|										 |--------+--------+--------+--------+--------+--------| TODO: +
	 LT(0, KC_ESC),	KC_A,		 KC_S,		KC_D,		 KC_F,		KC_G,													KC_H,		 KC_J,		KC_K,		 KC_L, KC_SCLN, KC_QUOT,
	//|--------+--------+--------+--------+--------+--------|										 |--------+--------+--------+--------+--------+--------|
			XXXXXXX,		KC_Z,		 KC_X,		KC_C,		 KC_V,		KC_B,													KC_N,		 KC_M, KC_COMM,	 KC_DOT, KC_SLSH,	 XXXXXXX,
	//|--------+--------+--------+--------+--------+--------+--------|	|--------+--------+--------+--------+--------+--------+--------|
										TD(ALT_S7),	LCTL_T(KC_TAB),	LGUI_T(XXXXXXX),						 LT(1, KC_ENTER),	SFT_T(KC_SPC) , LT(2, XXXXXXX)
			 //`--------------------------'	`--------------------------'

                           ),

	[1] = LAYOUT_split_3x6_3( // Symbols
	//,---------------------------------------------------------------|						 |------------------------------------------------------------------------------------.
		KC_BSLS,		XXXXXXX,		S(KC_5),		S(KC_EQL), S(KC_MINS), RALT(KC_BSLS),			RALT(KC_3),	RALT(KC_LBRACKET), RALT(KC_RBRACKET),	KC_MINS,			S(KC_LBRC), S(KC_RBRC),
	//|--------+--------+--------+--------+--------+-------------------------|		 |--------+--------+--------+--------+--------+------------------------------------|
		RALT(KC_E), XXXXXXX,		S(KC_6),		KC_EQL,		 S(KC_1),		 RALT(KC_QUOT),			S(KC_2),		S(KC_8),					 S(KC_9),						RALT(KC_GRV), S(KC_0),		KC_LBRC, 
	//|--------+--------+--------+--------+--------+--------|										 |--------+--------+--------+--------+--------+--------------------------------------|
		RALT(KC_6), RALT(KC_4), RALT(KC_1), KC_NUBS,	 S(KC_NUBS), RALT(KC_2),				S(KC_4),		S(KC_SLSH),				 S(KC_COMM),				S(KC_DOT),		S(KC_3),		RESET,
	//|--------+--------+--------+--------+--------+--------+--------|	|--------+--------+--------+--------+--------+--------+--------|
																						S(KC_MINS), _______,	 _______,							 _______,	_______ , _______
																			//`--------------------------'	`--------------------------'
	),

	[2] = LAYOUT_split_3x6_3( // Numbers
	//,-----------------------------------------------------.										 ,-----------------------------------------------------.
			XXXXXXX, XXXXXXX,	XXXXXXX, XXXXXXX,	 XXXXXXX, XXXXXXX,											XXXXXXX,	KC_7,		 KC_8,		KC_9,	 XXXXXXX, XXXXXXX,
	//|--------+--------+--------+--------+--------+--------|										 |--------+--------+--------+--------+--------+--------|
			 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,											 KC_0,		KC_4,		 KC_5,		KC_6,	 XXXXXXX, XXXXXXX,
	//|--------+--------+--------+--------+--------+--------|										 |--------+--------+--------+--------+--------+--------|
			XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,											 XXXXXXX,		KC_1,		 KC_2,		KC_3,	 XXXXXXX, XXXXXXX,
	//|--------+--------+--------+--------+--------+--------+--------|	|--------+--------+--------+--------+--------+--------+--------|
																				_______,	 _______,	 _______,		 _______, _______, _______
																			//`--------------------------'	`--------------------------'
	),

	[3] = LAYOUT_split_3x6_3( // Movement
		//,-----------------------------------------------------.										 ,-----------------------------------------------------.
				XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,	 XXXXXXX, XXXXXXX,										 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		//|--------+--------+--------+--------+--------+--------|										 |--------+--------+--------+--------+--------+--------|
				 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,										 KC_LEFT, KC_DOWN, KC_UP,		KC_RIGHT, XXXXXXX, XXXXXXX,
		//|--------+--------+--------+--------+--------+--------|										 |--------+--------+--------+--------+--------+--------|
				XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,											 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		//|--------+--------+--------+--------+--------+--------+--------|	|--------+--------+--------+--------+--------+--------+--------|
																			_______,	 _______,	 _______,		 _______, _______, _______
																		//`--------------------------'	`--------------------------'
	)
};

// Empty layer template
//		//,-----------------------------------------------------.										 ,-----------------------------------------------------.
//				XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,	 XXXXXXX, XXXXXXX,										 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
//		//|--------+--------+--------+--------+--------+--------|										 |--------+--------+--------+--------+--------+--------|
//				 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,										 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
//		//|--------+--------+--------+--------+--------+--------|										 |--------+--------+--------+--------+--------+--------|
//				XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,											 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
//		//|--------+--------+--------+--------+--------+--------+--------|	|--------+--------+--------+--------+--------+--------+--------|
//																			_______,	 _______,	 _______,		 _______, _______, _______,
																		//`--------------------------'	`--------------------------'

// Magic for alt_t(/) starts
td_state_t cur_dance(qk_tap_dance_state_t *state) {
		if (state->count == 1) {
				if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
				else return TD_SINGLE_HOLD;
		}

		if (state->count == 2) return TD_DOUBLE_SINGLE_TAP;
		else return TD_UNKNOWN; // Any number higher than the maximum state value you return above
}

void alts7_finished(qk_tap_dance_state_t *state, void *user_data) {
		td_state = cur_dance(state);
		switch (td_state) {
				case TD_SINGLE_TAP:
					register_code16(S(KC_7));
						break;
				case TD_SINGLE_HOLD:
						register_mods(MOD_BIT(KC_LALT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
						break;
				case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
						tap_code16(S(KC_7));
						register_code16(S(KC_7));
    default:
      break;
    }
}

void alts7_reset(qk_tap_dance_state_t *state, void *user_data) {
		switch (td_state) {
				case TD_SINGLE_TAP:
						unregister_code16(S(KC_7));
						break;
				case TD_SINGLE_HOLD:
						unregister_mods(MOD_BIT(KC_LALT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
						break;
				case TD_DOUBLE_SINGLE_TAP:
						unregister_code16(S(KC_7));
     default:
       break;
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
		[ALT_S7] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, alts7_finished, alts7_reset)
};

// Magic for alt_t(/) ends

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	if (!is_keyboard_master()) {
		return OLED_ROTATION_180;	 // flips the display 180 degrees if offhand
	}
	return rotation;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

void oled_render_layer_state(void) {
		oled_write_P(PSTR("Layer: "), false);
		switch (layer_state) {
				case L_BASE:
						oled_write_ln_P(PSTR("Default"), false);
						break;
				case L_LOWER:
						oled_write_ln_P(PSTR("Lower"), false);
						break;
				case L_RAISE:
						oled_write_ln_P(PSTR("Raise"), false);
						break;
				case L_ADJUST:
				case L_ADJUST|L_LOWER:
				case L_ADJUST|L_RAISE:
				case L_ADJUST|L_LOWER|L_RAISE:
						oled_write_ln_P(PSTR("Adjust"), false);
						break;
		}
}


char keylog_str[24] = {};

const char code_to_name[60] = {
		' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
		'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
		'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
		'1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
		'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
		'#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
	char name = ' ';
		if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
				(keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
	if (keycode < 60) {
		name = code_to_name[keycode];
	}

	// update keylog
	snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
					 record->event.key.row, record->event.key.col,
					 keycode, name);
}

void oled_render_keylog(void) {
		oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
		/* Show Ctrl-Gui Swap options */
		static const char PROGMEM logo[][2][3] = {
				{{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
				{{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
		};
		if (status) {
				oled_write_ln_P(logo[0][0], false);
				oled_write_ln_P(logo[0][1], false);
		} else {
				oled_write_ln_P(logo[1][0], false);
				oled_write_ln_P(logo[1][1], false);
		}
}

void oled_render_logo(void) {
		static const char PROGMEM crkbd_logo[] = {
				0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
				0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
				0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
				0};
		oled_write_P(crkbd_logo, false);
}

void oled_task_user(void) {
		if (is_keyboard_master()) {
				oled_render_layer_state();
				oled_render_keylog();
		} else {
				oled_render_logo();
		}
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	if (record->event.pressed) {
		set_keylog(keycode, record);
	}
	return true;
	return true;
	if (record->event.pressed) {
		set_keylog(keycode, record);
	}
	return true;
}
#endif // OLED_ENABLE
