// Copyright 2022 Patrick Gilligan (@patrickgilsf)
// SPDX-License-Identifier: GPL-2.0-or-later

/* This is my 9 key YMDK that I use to control Zoom. I have some future goals with the project as well:
    - Leverage Zoom SDK and node-hid to sync 1 mute status with kb rgb backlight
    - added rgb coloration for when the video is muted
*/

#include QMK_KEYBOARD_H
#include "raw_hid.h"
#include "print.h"

#define _MAC 0
#define _PC 1
#define _UTIL 2


// typedef union {
//   uint32_t raw;
//   struct {
//     bool     rgb_layer_change :1;
//   };
// } user_config_t;
// user_config_t user_config;

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

  [_MAC] = LAYOUT(KEY1, KEY2, KEY3,
               KEY4, KEY5, KEY6,
               KEY7, KEY8, KEY9),

  [_PC] = LAYOUT(KEY10, KEY11, KEY12,
               KEY13, KEY14, KEY15,
               KEY16, KEY17, KEY18),

  [_UTIL] = LAYOUT(KEY19, KEY20, KEY21,
               KEY22, KEY23, KEY24,
               KEY25, KEY26, KEY27)

};

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

/* LEDs mapped out
2 1 0
5 4 3
8 7 6
*/

//this is something I'm doing custom...not sure if there is a better way
bool kp_1 = 0;
    bool micMute = 1;
bool kp_2 = 0;
    bool vidMute = 1;
bool kp_3 = 0;
bool kp_4 = 0;
bool kp_5 = 0;
bool kp_6 = 0;
bool kp_7 = 0;
    bool kp_7a = 0;
bool kp_8 = 0;
bool kp_9 = 0;
bool kp_10 = 0;
    // bool winMicMute = 1;
bool kp_11 = 0;
    // bool winVidMute = 1;
bool kp_12 = 0;
bool kp_13 = 0;
bool kp_14 = 0;
bool kp_15 = 0;
bool kp_16 = 0;
    bool kp_16a = 0;
bool kp_17 = 0;
bool kp_18 = 0;

bool kp_19 = 0;
    bool kp_19a = 0;
bool kp_20 = 0;
bool kp_21 = 0;
bool kp_22 = 0;
bool kp_23 = 0;
bool kp_24 = 0;
bool kp_25 = 0;
    bool kp_25a = 0;
bool kp_26 = 0;
bool kp_27 = 0;

//https://docs.qmk.fm/#/feature_rgblight?id=defining-lighting-layers
const rgblight_segment_t PROGMEM micMuteLED[] = RGBLIGHT_LAYER_SEGMENTS(
    {2, 1, 0,255,255}
);
const rgblight_segment_t PROGMEM vidMuteLED[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 1, 0,255,255}
);
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    micMuteLED,
    vidMuteLED
);

//these are the initialization functions
void keyboard_post_init_user(void) {
rgblight_sethsv_noeeprom(60,80,145);
rgblight_layers = my_rgb_layers;
//   rgblight_enable_noeeprom();
//   rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
  layer_state_set_user(_MAC);
//   set_single_persistent_default_layer(0);
  debug_enable=1;
}

//raw HID - connects with my node script
void raw_hid_receive(uint8_t *data, uint8_t length) {
    if (data[1] == 0x01) {
        rgblight_sethsv_at(0,255,255, 2);
        micMute = 1;
        print("Mic Muted");
    } else if (data[1] == 0x02) { //need to add a query of which layer you are on
        rgblight_sethsv_at(60,18,145, 2);
        micMute = 0;
        print("Mic Unmuted");
    } else if (data[1] == 0x03) {
        rgblight_sethsv_at(0,255,255, 1);
        vidMute = 1;
        print("Vid Muted");
    } else if (data[1] == 0x04) {
        rgblight_sethsv_at(60,18,145,2);
        vidMute = 0;
        print("Vid Unmuted");
    }
}

//layer control
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        default:
            // rgblight_set_layer_state(0, layer_state_cmp(state, micMute == 1));
            // rgblight_set_layer_state(1, layer_state_cmp(state, vidMute == 1));
        break;
        case _MAC:
            print("on mac layer");
            rgblight_sethsv_noeeprom(60,80,145);
            if (micMute == 1) {
                rgblight_set_layer_state(0, micMute = 1);
            } else if (micMute == 0) {
                rgblight_set_layer_state(0, micMute = 0);
            }
            if (vidMute == 1) {
                rgblight_set_layer_state(1, vidMute = 1);
            } else if (vidMute == 0) {
                rgblight_set_layer_state(1, vidMute = 0);
            }
        break;
        case _PC:
            print("on pc layer");
            rgblight_sethsv_noeeprom(144,216,237);
            if (micMute == 1) {
                rgblight_set_layer_state(0, micMute = 1);
            } else if (micMute == 0) {
                rgblight_set_layer_state(0, micMute = 0);
            }
            if (vidMute == 1) {
                rgblight_set_layer_state(1, vidMute = 1);
            } else if (vidMute == 0) {
                rgblight_set_layer_state(1, vidMute = 0);
            }
        break;
        case _UTIL:
        print("on util layer");
            rgblight_sethsv_noeeprom(85,255,127);
            if (micMute == 1) {
                rgblight_set_layer_state(0, micMute = 1);
            } else if (micMute == 0) {
                rgblight_set_layer_state(0, micMute = 0);
            }
            if (vidMute == 1) {
                rgblight_set_layer_state(1, vidMute = 1);
            } else if (vidMute == 0) {
                rgblight_set_layer_state(1, vidMute = 0);
            }
        break;
        };
return state;
}

//custom keys
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case KEY1: //Mic Mute
        if (record->event.pressed) {
            kp_1 = 1;
        } else {
            kp_1 = 0;
            if (micMute == 0) {
                micMute = 1;
                rgblight_set_layer_state(0, micMute = 1);
                tap_code16(LSFT(LGUI(KC_A)));
                print("mic muted");
            }   else if (micMute == 1) {
                    // rgblight_set_layer_state(1, micMute = 1);
                    // rgblight_set_layer_state(0, micMute = 0);
                    micMute = 0;
                    rgblight_set_layer_state(0, micMute = 0);
                    tap_code16(LSFT(LGUI(KC_A)));
                    print("mic unmuted");
                };
        };
        break;
    case KEY2: // Video Mute
        if (record->event.pressed) {
            kp_2 = 1;
        } else {
            kp_2 = 0;
            if (vidMute == 0) {
                vidMute = 1;
                rgblight_set_layer_state(1, vidMute = 1);
                tap_code16(LSFT(LGUI(KC_V)));
                print("vid muted");
            } else if (vidMute == 1) {
                vidMute = 0;
                rgblight_set_layer_state(1, vidMute = 0);
                tap_code16(LSFT(LGUI(KC_V)));
                print("vid unmuted");
            };
        };
        break;
    case KEY3:
        if (record->event.pressed) {
            kp_3 = 1;
        }   else {
                tap_code16(LALT(KC_Y));
                kp_3 = 0;
        }
        break;
    case KEY4:
        if (record->event.pressed) {
            kp_4 = 1;
        }   else {
                tap_code16(LSFT(LGUI(KC_W)));
                kp_4 = 0;
        }
        break;
    case KEY5:
        if (record->event.pressed) {
            kp_5 = 1;
        }   else {
                tap_code16(LCTL(KC_P));
                kp_5 = 0;
        }
        break;
    case KEY6:
        if (record->event.pressed) {
            kp_6 = 1;
        }   else {
                tap_code16(LCTL(KC_N));
                kp_6 = 0;
        }
        break;
    case KEY7:
        if (record->event.pressed) {
            kp_7 = 1;
        }   else {
                kp_7 = 0;
                if (kp_7a == 0) {
                    tap_code16(LSFT(LGUI(KC_F)));
                }
            }
        break;
    case KEY8:
        if (record->event.pressed) {
            kp_8 = 1;
        }   else {
                kp_8 = 0;
                tap_code16(LSFT(LGUI(KC_H)));
            }
        break;
    case KEY9:
        if (record->event.pressed) {
            kp_9 = 1;
            if (kp_7) {
                layer_move(_PC);
                kp_7a = 1;
            }
        }   else {
                kp_9 = 0;
                kp_7a = 0;
                SEND_STRING(SS_LSFT(SS_LGUI("m")));
            }
        break;
    case KEY10:
        if (record->event.pressed) {
            kp_10 = 1;
        } else {
            kp_10 = 0;
            if (micMute == 0) {
                micMute = 1;
                rgblight_set_layer_state(0, micMute = 1);
                tap_code16(LSFT(LGUI(KC_A)));
                print("win mic muted");
            }   else if (micMute == 1) {
                    // rgblight_set_layer_state(1, micMute = 1);
                    // rgblight_set_layer_state(0, micMute = 0);
                    micMute = 0;
                    rgblight_set_layer_state(0, micMute = 0);
                    tap_code16(LSFT(LGUI(KC_A)));
                    print("win mic unmuted");
                };
        };
        break;
    case KEY11:
        if (record->event.pressed) {
            kp_11 = 1;
        } else {
            kp_11 = 0;
            if (vidMute == 0) {
                vidMute = 1;
                rgblight_set_layer_state(1, vidMute = 1);
                tap_code16(LSFT(LGUI(KC_V)));
                print("win vid muted");
            } else if (vidMute == 1) {
                vidMute = 0;
                rgblight_set_layer_state(1, vidMute = 0);
                tap_code16(LSFT(LGUI(KC_V)));
                print("win vid unmuted");
            };
        };
        break;
    case KEY12:
        if (record->event.pressed) {
            kp_12 = 1;
            }   else {
                    kp_12 = 0;
                    tap_code16(LALT(KC_Y));
                }
        break;
    case KEY13:
        if (record->event.pressed) {
            kp_13 = 1;
            }   else {
                    kp_13 = 0;
                    tap_code16(LALT(KC_F2));
                }
        break;
    case KEY14:
        if (record->event.pressed) {
            kp_14 = 1;
            }   else {
                    kp_14 = 0;
                    tap_code(KC_PGUP);
                }
        break;
    case KEY15:
        if (record->event.pressed) {
            kp_15 = 1;
            }   else {
                    kp_15 = 0;
                    tap_code16(KC_PGDOWN);
                }
        break;
    case KEY16:
        if (record->event.pressed) {
            kp_16 = 1;
        }   else {
                kp_16 = 0;
                if (kp_16a == 0) {
                  tap_code16(LALT(KC_F));
                }
            };
        break;
    case KEY17:
        if (record->event.pressed) {
            kp_17 = 1;
            if (kp_16) {
                layer_move(_MAC);
                kp_16a = 1;
            }
        }   else {
                kp_17 = 0;
                kp_16a = 0;
                tap_code16(LALT(KC_H));
            }
        break;
    case KEY18:
        if (record->event.pressed) {
            kp_18 = 1;
            if (kp_16) {
                layer_move(_UTIL);
                kp_16a = 1;
            }
        }   else {
                kp_18 = 0;
                kp_16a = 0;
            }
        break;
    case KEY19:
        if (record->event.pressed) {
            kp_19 = 1;
        }   else {
            kp_19 = 0;
        }
        break;
    case KEY20:
        if (record->event.pressed) {
            kp_20 = 1;
        } else {
            kp_20 = 0;
        }
        break;
    case KEY21:
        if (record->event.pressed) {
            kp_21 = 1;
        }   else {
                kp_21 = 0;
            }
        break;
    case KEY22:
        if (record->event.pressed) {
            kp_22 = 1;
        }   else {
                kp_22 = 0;
            }
        break;
    case KEY23:
        if (record->event.pressed) {
            kp_23 = 1;
        }   else {
                kp_23 = 0;
            }
        break;
    case KEY24:
        if (record->event.pressed) {
            kp_24 = 1;
        }   else {
            kp_24 = 0;
        }
        break;
    case KEY25:
        if (record->event.pressed) {
            kp_25 = 1;
        }   else {
            kp_25 = 0;
            /*if (kp_25a == 0) {
                //put command here if you think of one
            }*/
        }
        break;
    case KEY26:
        if (record->event.pressed) {
            kp_26 = 1;
            if (kp_25) {
                layer_move(_PC);
                kp_25a = 1;
            }
        }   else {
            kp_26 = 0;
            kp_25a = 0;
            }
        break;
    case KEY27:
        if (record->event.pressed) {
            kp_27 = 1;
            if (kp_19 && kp_25) {
                //rgblight_setrgb(RGB_WHITE);
                rgblight_sethsv_noeeprom(0,0,255);
                reset_keyboard();
            }
       }   else {
            kp_27 = 0;
        }
        break;
    }
    return 1;
};
