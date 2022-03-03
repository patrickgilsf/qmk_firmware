// Copyright 2022 Patrick Gilligan (@patrickgilsf)
// SPDX-License-Identifier: GPL-2.0-or-later

/* This is my 9 key YMDK that I use to control Zoom. I have some future goals with the project as well:
    - Leverage Zoom SDK and node-hid to sync true mute status with kb rgb backlight
    - added rgb coloration for when the video is muted
*/


#include QMK_KEYBOARD_H
#include "raw_hid.h"
#include "print.h"

/*
HSV Values
RGB_RED == (0,255,255);
RGB_ORANGE == (28,255,255);
RGB_YELLOW == (43,255,255);
RGB_GREEN == (85,255,127);
Gunmetal Grey = (60,18,145);
Windows Blue = (144,216,237);
Light Red = (0,127,255);
White = (0,0,255)
Purple = (245,84,204)
*/

enum custom_keycodes {
    KEY1 = SAFE_RANGE,
    KEY2,
    KEY3,
    KEY4,
    KEY5,
    KEY6,
    KEY7,
    KEY8,
    KEY9,
    KEY10,
    KEY11,
    KEY12,
    KEY13,
    KEY14,
    KEY15,
    KEY16,
    KEY17,
    KEY18,
    KEY19,
    KEY20,
    KEY21,
    KEY22,
    KEY23,
    KEY24,
    KEY25,
    KEY26,
    KEY27
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT(KEY1, KEY2, KEY3,
               KEY4, KEY5, KEY6,
               KEY7, KEY8, KEY9),

  [1] = LAYOUT(KEY10, KEY11, KEY12,
               KEY13, KEY14, KEY15,
               KEY16, KEY17, KEY18),

  [2] = LAYOUT(KEY19, KEY20, KEY21,
               KEY22, KEY23, KEY24,
               KEY25, KEY26, KEY27)

};

//this is the timer for flash mode sequence
//static uint32_t key_timer = 0;




/*
Legend:
--Layer 0 - [Mac OS Zoom shortcuts]
KEY1 - Mute Mic/Toggle Keyboard Light;
KEY2 - Mute Video;
KEY3 - Raise/Lower Hand;
KEY4 - Speaker/Gallery View Toggle
KEY5 - Prev Page of Gallery
KEY6 - Next Page of Gallery
KEY7 - Full Screen
KEY8 - Show/Hide Chat; // If KEY7 is down, up to layer 1.
KEY9 - Minimal Window;
--Layer 1 - [PC Zoom Shortcuts]
KEY10 - Mute Mic/Toggle Keyboard Light;
KEY11 - Mute Video; // If KEY10 is down, back to layer 0
KEY12 - Raise/Lower Hand;
KEY13 - Speaker/Gallery View Toggle
KEY14 - Prev Page of Gallery
KEY15 - Next Page of Gallery
KEY16 - Full Screen
KEY17 - Show/Hide Chat; // If KEY7 is down, down to layer 0.
KEY18 - Minimal Window; // If KEY7 is down, up to layer 2
-- Layer 2 -
KEY19 -
KEY20 -
KEY21 -
KEY22 -
KEY23 -
KEY24 -
KEY25 -
KEY26 - If KEY25 is down, back to layer 1
KEY27 - If KEY19 && KEY25 are down, puts it in setup mode
*/

/* Here is the LED map, from various testing
2 1 0
5 4 3
8 7 6
*/

//initialize booleans for stacked functions:
bool kp_1 = false;
    bool micMute = true; //1a bounces between toggle presses
bool kp_2 = false;
    bool vidMute = true;
bool kp_3 = false;
bool kp_4 = false;
bool kp_5 = false;
bool kp_6 = false;
bool kp_7 = false;
    bool kp_7a = false;
bool kp_8 = false;
bool kp_9 = false;

bool kp_10 = false;
    bool winMicMute = true;
bool kp_11 = false;
    bool winVidMute = true;
bool kp_12 = false;
bool kp_13 = false;
bool kp_14 = false;
bool kp_15 = false;
bool kp_16 = false;
    bool kp_16a = false;
bool kp_17 = false;
bool kp_18 = false;

bool kp_19 = false;
    bool kp_19a = false;
bool kp_20 = false;
bool kp_21 = false;
bool kp_22 = false;
bool kp_23 = false;
bool kp_24 = false;
bool kp_25 = false;
    bool kp_25a = false;
bool kp_26 = false;
bool kp_27 = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case KEY1: //Mic Mute
        if (record->event.pressed) {
            kp_1 = true;
        } else {
            kp_1 = false;
            if (micMute == false) {
                micMute = true;
                tap_code16(LSFT(LGUI(KC_A)));
                //rgblight_setrgb(RGB_RED);
                //rgblight_setrgb_at(RGB_RED,2);
                rgblight_sethsv_at(0,255,255, 2);
            }   else if (micMute == true) {
                    micMute = false;
                    tap_code16(LSFT(LGUI(KC_A)));
                    //rgblight_setrgb_at(RGB_ORANGE,2);
                    rgblight_sethsv_at(60,18,145, 2);
                };
        };
        break;
    case KEY2: // Video Mute
        if (record->event.pressed) {
            kp_2 = true;
        } else {
            kp_2 = false;
            if (vidMute == false) {
                vidMute = true;
                tap_code16(LSFT(LGUI(KC_V)));
                //rgblight_setrgb_at(RGB_RED, 1);
                rgblight_sethsv_at(0,255,255, 1);
            } else if (vidMute == true) {
                vidMute = false;
                tap_code16(LSFT(LGUI(KC_V)));
                //rgblight_setrgb_at(RGB_ORANGE,1);
                rgblight_sethsv_at(60,18,145, 1);
            }
        }
        break;
    case KEY3:
        if (record->event.pressed) {
            kp_3 = true;
        }   else {
                tap_code16(LALT(KC_Y));
                kp_3 = false;
        }
        break;
    case KEY4:
        if (record->event.pressed) {
            kp_4 = true;
        }   else {
                tap_code16(LSFT(LGUI(KC_W)));
                kp_4 = false;
        }
        break;
    case KEY5:
        if (record->event.pressed) {
            kp_5 = true;
        }   else {
                tap_code16(LCTL(KC_P));
                kp_5 = false;
        }
        break;
    case KEY6:
        if (record->event.pressed) {
            kp_6 = true;
        }   else {
                tap_code16(LCTL(KC_N));
                kp_6 = false;
        }
        break;
    case KEY7:
        if (record->event.pressed) {
            kp_7 = true;
        }   else {
                kp_7 = false;
                if (kp_7a == false) {
                    tap_code16(LSFT(LGUI(KC_F)));
                }
            }
        break;
    case KEY8:
        if (record->event.pressed) {
            kp_8 = true;
        }   else {
                kp_8 = false;
                tap_code16(LSFT(LGUI(KC_H)));
            }
        break;
    case KEY9:
        if (record->event.pressed) {
            kp_9 = true;
            if (kp_7) {
                layer_move(1);
                kp_7a = true;
            }
        }   else {
                kp_9 = false;
                kp_7a = false;
                SEND_STRING(SS_LSFT(SS_LGUI("m")));
            }
        break;
    case KEY10:
        if (record->event.pressed) {
            kp_10 = true;
        }   else {
                kp_10 = false;
                if (winMicMute == false) {
                    winMicMute = true;
                    tap_code16(LALT(KC_A));
                    // rgblight_setrgb_at(RGB_RED,2);
                    rgblight_sethsv_at(0,255,255, 2);
                }   else if (winMicMute == true) {
                        winMicMute = false;
                        tap_code16(LALT(KC_A));
                        //rgblight_setrgb_at(RGB_YELLOW,2);
                        rgblight_sethsv_at(144,216,237, 2);
                    };
            };
        break;
    case KEY11:
        if (record->event.pressed) {
            kp_11 = true;
        } else {
            kp_11 = false;
            if (winVidMute == false) {
                winVidMute = true;
                tap_code16(LALT(KC_V));
                // rgblight_setrgb_at(RGB_RED, 1);
                rgblight_sethsv_at(245,84,204, 1); //purple
            } else if (winVidMute == true) {
                winVidMute = false;
                tap_code16(LALT(KC_V));
                // rgblight_setrgb_at(RGB_YELLOW, 1);
                rgblight_sethsv_at(144,216,237, 1);
            }
        }
        break;
    case KEY12:
        if (record->event.pressed) {
            kp_12 = true;
            }   else {
                    kp_12 = false;
                    tap_code16(LALT(KC_Y));
                }
        break;
    case KEY13:
        if (record->event.pressed) {
            kp_13 = true;
            }   else {
                    kp_13 = false;
                    tap_code16(LALT(KC_F2));
                }
        break;
    case KEY14:
        if (record->event.pressed) {
            kp_14 = true;
            }   else {
                    kp_14 = false;
                    tap_code(KC_PGUP);
                }
        break;
    case KEY15:
        if (record->event.pressed) {
            kp_15 = true;
            }   else {
                    kp_15 = false;
                    tap_code16(KC_PGDOWN);
                }
        break;
    case KEY16:
        if (record->event.pressed) {
            kp_16 = true;
        }   else {
                kp_16 = false;
                if (kp_16a == false) {
                  tap_code16(LALT(KC_F));
                }
            };
        break;
    case KEY17:
        if (record->event.pressed) {
            kp_17 = true;
            if (kp_16) {
                layer_move(0);
                kp_16a = true;
            }
        }   else {
                kp_17 = false;
                kp_16a = false;
                tap_code16(LALT(KC_H));
            }
        break;
    case KEY18:
        if (record->event.pressed) {
            kp_18 = true;
            if (kp_16) {
                layer_move(2);
                kp_16a = true;
            }
        }   else {
                kp_18 = false;
                kp_16a = false;
            }
        break;
    case KEY19:
        if (record->event.pressed) {
            kp_19 = true;
        }   else {
            kp_19 = false;
        }
        break;
    case KEY20:
        if (record->event.pressed) {
            kp_20 = true;
        } else {
            kp_20 = false;
        }
        break;
    case KEY21:
        if (record->event.pressed) {
            kp_21 = true;
        }   else {
                kp_21 = false;
            }
        break;
    case KEY22:
        if (record->event.pressed) {
            kp_22 = true;
        }   else {
                kp_22 = false;
            }
        break;
    case KEY23:
        if (record->event.pressed) {
            kp_23 = true;
        }   else {
                kp_23 = false;
            }
        break;
    case KEY24:
        if (record->event.pressed) {
            kp_24 = true;
        }   else {
            kp_24 = false;
        }
        break;
    case KEY25:
        if (record->event.pressed) {
            kp_25 = true;
        }   else {
            kp_25 = false;
            /*if (kp_25a == false) {
                //put command here if you think of one
            }*/
        }
        break;
    case KEY26:
        if (record->event.pressed) {
            kp_26 = true;
            if (kp_25) {
                layer_move(1);
                kp_25a = true;
            }
        }   else {
            kp_26 = false;
            kp_25a = false;
            }
        break;
    case KEY27:
        if (record->event.pressed) {
            kp_27 = true;
            if (kp_19 && kp_25) {
                //rgblight_setrgb(RGB_WHITE);
                rgblight_sethsv_noeeprom(0,0,255);
                reset_keyboard();
            }
       }   else {
            kp_27 = false;
        }
        break;
    }
    return true;
};


//for when I use rawHID to add feedback:
void raw_hid_receive(uint8_t *data, uint8_t length) {
    if (data[1] == 0x01) {
        rgblight_sethsv_at(0,255,255, 2);
        micMute = true;
        print("Mic Muted");
    } else if (data[1] == 0x02) { //need to add a query of which layer you are on
        rgblight_sethsv_at(60,18,145, 2);
        micMute = false;
        print("Mic Unmuted");
    } else if (data[1] == 0x03) {
        rgblight_sethsv_at(0,255,255, 1);
        vidMute = true;
        print("Vid Muted");
    } else if (data[1] == 0x04) {
        rgblight_sethsv_at(60,18,145,2);
        vidMute = false;
        print("Vid Unmuted");
    }
}



// messing with lighting layers
const rgblight_segment_t PROGMEM startup[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 1, HSV_RED},
    {2, 1, HSV_RED}
);
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    startup
);

//these are the initialization functions
void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom(); //
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
  set_single_persistent_default_layer(0);
  rgblight_sethsv_noeeprom(60,80,145); //worked
  rgblight_sethsv_at(0,255,255, 2);
  rgblight_sethsv_at(0,255,255, 1);
  debug_enable=true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_sethsv_at(0,255,255, 2);
    rgblight_sethsv_at(0,255,255, 1);
    return state;
}






