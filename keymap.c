/* Copyright 2021 @ Keychron (https://www.keychron.com)
 * Copyright 2024 @ Jean Olivier Simoneau (modifications)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "keychron_common.h"
#include "action_layer.h"

// TODO: THOSE ARE IDEAS:
// TODO:
// TODO: - Proper support for "GUI+TAB" application switching, with the GUI holding and shift, etc.
// TODO:     - Maybe implement a process_record instead of a tap-dance, or complex tap dance?
// TODO: - Media keys on Fn1 layer, *hjklm,.* or arrow cluster?
// TODO: - What more than NumPad + LED on the Fn3 toggled layer?
// TODO: - Add an in-keymap way to toggle LGUI/F(0) key, HELD_ESC_IS_SHIFT and BSPC_BLOCKS_DEL.
// TODO:
// TODO: THOSE ARE BUGS TO FIX:
// TODO: - None (found so far)

// Adjusting process_record_user functionnalities, comment to disable.
#define ISOLIKE_ALT_ENTER
#define TWO_SFT_CAPS
//#define APP_IS_RALT_RCTRL  // Keeping this here in case I change my mind
#define HELD_ESC_IS_SHIFT
//#define BSPC_BLOCKS_DEL    // Should not be needed on the K6_pro with the big backspace
#define ALT_MINSEQL_IS_ALT_78

// Cases where the GUI key will actually do what the GUI key normally does.
#define AC_G_W    LGUI(KC_W)   // Ubuntu: Shows windows on current desktop
#define AC_G_S    LGUI(KC_S)   // Ubuntu: Overview of all desktops
#define AC_G_D    LGUI(KC_D)   // Windows: Show/Toggle desktop
#define AC_G_L    LGUI(KC_L)   // Ubuntu/Windows: Lock session
#define AC_G_T    LGUI(KC_T)   // Ubuntu: Shows Trash // elementary: Opens terminal
#define AC_G_E    LGUI(KC_E)   // Windows: Opens file explorer
#define AC_G_H    LGUI(KC_H)   // Windows: Show/Hide hidden files
#define AC_G_SPC  LGUI(KC_SPC) // elementary: Shows application launcher
#define AC_G_TB  LGUI(KC_TAB) // elementary: Shows application launcher


// For leader key macros
#define AROBASE "@"         // To avoid crawlers that match email addresses
#define CANADA ".ca"       // Idem
#define COMMERCIAL ".com"  // Idem
#define SLASH "`"  // To get "/" using the Canadian Multilingual layout
#define NAME "Jean Olivier Simoneau"
#define NAMEDOT "jean.olivier.simoneau"
#define SCHOOL_EMAIL NAMEDOT AROBASE "usherbrooke" CANADA
#define WORK_EMAIL "jos" AROBASE "nordquantique" CANADA
#define PERSONAL_EMAIL NAMEDOT AROBASE "gmail" COMMERCIAL
#define GITHUB "www.github" COMMERCIAL SLASH "jeanolivier\n"


// clang-format off
enum layers{
  MAC,      // Now, MAC is for MACRO, aka the Windows key is the combo GUI/Fn key
  WIN,      // Now Win is for WINDOWS, aka the Windows key is normal
  FN,       // Regular function layer
  FN_LED,   // Layer to adjust the LED/Backlight
  GUILAY,   // Layer for the custom GUI/Fn key aka Windows key
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[MAC] = LAYOUT_ansi_68(
     KC_GRAVE, KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,      KC_MINS,   KC_EQL,   KC_BSPC, KC_DEL,
     KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,      KC_LBRC,   KC_RBRC,  KC_BSLS, MO(FN_LED),
     KC_ESC,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,   KC_QUOT,             KC_ENT,  QK_LEAD,
     KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,   KC_RSFT,             KC_UP,   MO(FN),
     KC_LCTL,  TD(0),    KC_LALT,                                KC_SPC,                       KC_RALT,  KC_APP,    KC_RCTL,   KC_LEFT,  KC_DOWN, KC_RGHT),

[WIN] = LAYOUT_ansi_68(
     KC_GRAVE, KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,      KC_MINS,   KC_EQL,   KC_BSPC, KC_DEL,
     KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,      KC_LBRC,   KC_RBRC,  KC_BSLS, MO(FN_LED),
     KC_ESC,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,   KC_QUOT,             KC_ENT,  QK_LEAD,
     KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,   KC_RSFT,             KC_UP,   MO(FN),
     KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                       KC_RALT,  KC_APP,    KC_RCTL,   KC_LEFT,  KC_DOWN, KC_RGHT),

[FN] = LAYOUT_ansi_68(
     QK_BOOT,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11,    KC_F12,   KC_PAUS,  KC_PSCR,
     _______,  KC_BTN1,  KC_MS_U,  KC_BTN2,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,   _______,  _______,  _______,
     _______,  KC_MS_L,  KC_MS_D,  KC_MS_R,  _______,  _______,  _______,  KC_MPLY,  KC_MPRV,  KC_MNXT,  KC_MSTP,   _______,             _______,  _______,
     _______,  _______,  _______,  _______,  _______,  _______,  NK_TOGG,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,   _______,             KC_PGUP,  _______,
     _______,  _______,  _______,                                _______,                      _______,  _______,   _______,   KC_HOME,  KC_PGDN,  KC_END),

[FN_LED] = LAYOUT_ansi_68(
     KC_GRV,   KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  BL_DOWN,  BL_UP,    KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,   KC_VOLD,   KC_VOLU,  _______,  BL_TOGG,
     _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  _______,  _______,  _______,   _______,   _______,  _______,  _______,
     BL_TOGG,  BL_STEP,  BL_UP,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,             _______,  _______,
     _______,  _______,  BL_DOWN,  _______,  _______,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,   _______,             _______,  _______,
     _______,  _______,  _______,                                _______,                      _______,  _______,   _______,   _______,  _______,  _______),

[GUILAY] = LAYOUT_ansi_68(
     KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   KC_PAUS,  KC_PSCR,
     AC_G_TB,  _______,  AC_G_W,   AC_G_E,   _______,  AC_G_T,   _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,
     _______,  _______,  AC_G_S,   AC_G_D,   _______,  _______,  AC_G_H,   _______,bb _______,  AC_G_L,   _______,  _______,              _______,  _______,
     _______,  _______,  _______,  _______,  _______,  BAT_LVL,  _______,  _______,  _______,  _______,  _______,  _______,              KC_PGUP,  _______,
     _______,  _______,  _______,                                AC_G_SPC,                     _______,  _______,  _______,    KC_HOME,  KC_PGDN,  KC_END),
};

// LGUI acts as F(1) if held or as a tapped LGUI if tapped. Adapted from https://goo.gl/WnqGNS
// Commented lines are for the "sticky" layer on two presses. Left it here for reference.
//static const int GUILAY = 2; // GUI Layer is layer #2  // Removing this for the keychron in favor of the use of an enum


typedef struct {
  bool layer_toggle;
  bool sticky;
} td_ta_state_t;

static void ang_tap_dance_ta_finished (tap_dance_state_t *state, void *user_data) {
  td_ta_state_t *td_ta = (td_ta_state_t *) user_data;

//  if (td_ta->sticky) {
//    td_ta->sticky = false;
//    td_ta->layer_toggle = false;
//    layer_off (GUILAY);
//    return;
//  }
//
  if (state->count == 1 && !state->pressed) {
    register_code (KC_LGUI);
//    td_ta->sticky = false;
    td_ta->layer_toggle = false;
  } else {
    td_ta->layer_toggle = true;
    layer_on(GUILAY);
//    td_ta->sticky = (state->count == 2);
  }
}

// Added this one to make it more reactive on keyup
static void ang_tap_dance_ta_each (tap_dance_state_t *state, void *user_data) {
  td_ta_state_t *td_ta = (td_ta_state_t *) user_data;

  if (!td_ta->layer_toggle) {   // Braces added for clarity
    unregister_code (KC_LGUI);
  }
}


static void ang_tap_dance_ta_reset (tap_dance_state_t *state, void *user_data) {
  td_ta_state_t *td_ta = (td_ta_state_t *) user_data;

  if (!td_ta->layer_toggle) {   // Braces added for clarity
    unregister_code (KC_LGUI);
  }
//  if (!td_ta->sticky)
    layer_off (GUILAY); // We don't verify it was swithed on, switching off regardless
}


tap_dance_action_t tap_dance_actions[] = {
   [0]  = {
     .fn = { ang_tap_dance_ta_each, ang_tap_dance_ta_finished, ang_tap_dance_ta_reset },
     .user_data = (void *)&((td_ta_state_t) { false, false })
   }
};

#if defined ISOLIKE_ALT_ENTER  || defined TWO_SFT_CAPS  || defined APP_IS_RALT_RCTRL || defined ALT_MINSEQL_IS_ALT_78
// Function for the special modifiers actions below, makes it cleaner and yields smaller firmware.
static bool special_mods(uint16_t keycode, keyrecord_t *record, uint16_t modifier) {
  if (record->event.pressed && (keyboard_report->mods & MOD_BIT(modifier))) {
    register_code(keycode);
    return false;
  } else {
    unregister_code(keycode);
    return true;
  }
}
#endif

#ifdef BSPC_BLOCKS_DEL
static bool del_blocked = false; // Static as to not be defined elsewhere
#endif

// This function is processed before the key events on each key press/release.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode){
    #ifdef ISOLIKE_ALT_ENTER
    // RALT + ENT is the same as RALT+BSLS. 
    // For logical placement of *{* and *}* (the former being RALT+BSLS) with ANSI enter on 
    // ISO-based Canadian Multilingual layout (or any other ISO layout on ANSI keyboards).
    case KC_ENT:    return special_mods(KC_BSLS, record, KC_RALT);  // RALT + ENT -> RALT + BSLS            // See comment above
    #endif
    #ifdef TWO_SFT_CAPS
    case KC_LSFT:   return special_mods(KC_CAPS, record, KC_RSFT);  // Both shifts together -> Caps Lock    // RSFT  pressed first case
    case KC_RSFT:   return special_mods(KC_CAPS, record, KC_LSFT);  // Both shifts together -> Caps Lock    // LSFT  pressed first case
    #endif
    #ifdef APP_IS_RALT_RCTRL
    case KC_RCTL:   return special_mods(KC_APP,  record, KC_RALT);  // RALT + RCTRL -> APP                  // RCTRL pressed first case
    case KC_RALT:   return special_mods(KC_APP,  record, KC_RCTL);  // RALT + RCTRL -> APP                  // RALT  pressed first case
    #endif
    #ifdef ALT_MINSEQL_IS_ALT_78
    case KC_MINS:  return special_mods(KC_7,  record, KC_RALT); // RALT + MINS -> RALT+7                  // {} in CAN Mult. softawre layout
    case KC_EQL:   return special_mods(KC_8,  record, KC_RALT); // RALT + EQL  -> RALT+8                  // ½¬ normally... Less finger stretch.
    #endif
    #ifdef HELD_ESC_IS_SHIFT
    case KC_ESC:    // Physically *ESC* is *CAPS*                   // Holding ESC -> SHIFT  (0 delay)      // Less awkward *<ESC>:wq* in vim
      if (record->event.pressed) {
        register_code(KC_ESC);      // Tapping ESC
        unregister_code(KC_ESC);
        register_code(KC_LSFT);     // Holding LSFT
        return false;
      } else {
        unregister_code(KC_LSFT);   // Releasing LSFT
        return false;
      }
    #endif
    #ifdef BSPC_BLOCKS_DEL
    // If BSPC is held, we flag DEL as disabled. To avoids acidental presses of DEL with split backspace key.
    case KC_BSPC:
      del_blocked = record->event.pressed;
      return true;
    // We don't handle DEL if it is pressed and flagged as disabled
    case KC_DEL:
      if (del_blocked && record->event.pressed) {
        return false;
      } else {
        return true;
      }
    #endif
    default: return true;   // Let QMK handle the rest as usual
  }
}


// Leader key macros

void leader_start_user(void) {
    // Do something when the leader key is pressed, kept as an example
}

void leader_end_user(void) {
    if (leader_sequence_one_key(KC_N)) {  // Name
        SEND_STRING(NAME);
    } else if (leader_sequence_two_keys(KC_N, KC_D)){  // Name with dots
        SEND_STRING(NAMEDOT);
    } else if (leader_sequence_two_keys(KC_S, KC_E)){  // School email
        SEND_STRING(SCHOOL_EMAIL);
    } else if (leader_sequence_two_keys(KC_W, KC_E)){  // Work email
        SEND_STRING(WORK_EMAIL);
    } else if (leader_sequence_two_keys(KC_P, KC_E)){  // Personal email
        SEND_STRING(PERSONAL_EMAIL);
    } else if (leader_sequence_one_key(KC_G)){
        SEND_STRING(GITHUB);
    }
}

