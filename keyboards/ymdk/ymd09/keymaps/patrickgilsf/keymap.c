// Copyright 2022 Patrick Gilligan (@patrickgilsf)
// SPDX-License-Identifier: GPL-2.0-or-later

/*
This is my 9 key YMDK that I use to control Zoom.
*/

#include QMK_KEYBOARD_H
<<<<<<< HEAD
//#include "raw_hid.h"
=======
#include "raw_hid.h"
#include "print.h"
#include "timer.h"
>>>>>>> 548249dc0fa0c96ff4254367aadfa3e36835635f

#define _MAC 0
#define _PC 1
#define _UTIL 2

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
<<<<<<< HEAD
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
=======
    macMicMute = SAFE_RANGE,
    macVidMute,
    macShareScreen,
    macGalleryToggle,
    macGalleryLeft,
    macGalleryRight,
    macFullscreen,
    macChat,
    macMini,
    winMicMute,
    winVidMute,
    winShareScreen,
    winGalleryToggle,
    winGalleryLeft,
    winGalleryRight,
    winFullscreen,
    winChat,
    winMini,
    utilOne,
    utilTwo,
    utilThree,
    utilFour,
    utilFive,
    utilSix,
    utilSeven,
    utilEight,
    flashKeeb
>>>>>>> 548249dc0fa0c96ff4254367aadfa3e36835635f
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_MAC] = LAYOUT(macMicMute, macVidMute, macShareScreen,
               macGalleryToggle, macGalleryLeft, macGalleryRight,
               macFullscreen, macChat, macMini),

  [_PC] = LAYOUT(winMicMute, winVidMute, winShareScreen,
               winGalleryToggle, winGalleryLeft, winGalleryRight,
               winFullscreen, winChat, winMini),

<<<<<<< HEAD
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

--Layer 1 - 
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
KEY27 - If KEY25 && KEY26 are down, puts it in setup mode
*/

//initialize booleans for stacked functions:
bool kp_1 = false;
    bool kp_1a = false; //1a bounces between toggle presses
bool kp_2 = false;
bool kp_3 = false;
bool kp_4 = false;
bool kp_5 = false;
bool kp_6 = false;
bool kp_7 = false;
    bool kp_7a = false;
bool kp_8 = false;
bool kp_9 = false;

bool kp_10 = false;
    bool kp_10a = false;
bool kp_11 = false;
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

=======
  [_UTIL] = LAYOUT(utilOne, utilTwo, utilThree,
               utilFour, utilFive, utilSix,
               utilSeven, utilEight, flashKeeb)
};

/*
Legend:
--Layer 0 - [Mac OS Zoom shortcuts]
macMicMute - Mute Mic/Toggle Keyboard Light;
macVidMute - Mute Video;
macShareScreen - Raise/Lower Hand;
macGalleryToggle - Speaker/Gallery View Toggle
macGalleryLeft - Prev Page of Gallery
macGalleryRight - Next Page of Gallery
macFullscreen - Full Screen
macChat - Show/Hide Chat; // If macFullscreen is down, up to layer 1.
macMini - Minimal Window;
--Layer 1 - [PC Zoom Shortcuts]
winMicMute - Mute Mic/Toggle Keyboard Light;
winVidMute - Mute Video; // If winMicMute is down, back to layer 0
winShareScreen - Raise/Lower Hand;
winGalleryToggle - Speaker/Gallery View Toggle
winGalleryLeft - Prev Page of Gallery
winGalleryRight - Next Page of Gallery
winFullscreen - Full Screen
winChat - Show/Hide Chat; // If macFullscreen is down, down to layer 0.
winMini - Minimal Window; // If macFullscreen is down, up to layer 2
-- Layer 2 -
utilOne -
utilTwo -
utilThree -
utilFour -
utilFive -
utilSix -
utilSeven -
utilEight - If utilSeven is down, back to layer 1
flashKeeb - If utilOne && utilSeven are down, puts it in setup mode
*/

/* LEDs mapped out
2 1 0
5 4 3
8 7 6
*/

//boolean values allow me to make one key press contingent on a different keypress
//_MAC and _PC
bool mic_Muted = 1;
bool vid_Muted = 1;
bool screen_is_sharing = 0;
//_MAC
bool mac_screen_share_press = 0;
bool mac_Full_Shift = 0;
bool mac_chat_open = 0;
//_PC
bool win_screen_share_press = 0;
bool win_Full_Shift = 0;
bool win_chat_open = 0;
//_UTIL
bool flash_one = 0;
bool flash_two = 0;
bool kp_27 = 0;

//https://docs.qmk.fm/#/feature_rgblight?id=defining-lighting-layers
const rgblight_segment_t PROGMEM micMuteLED[] = RGBLIGHT_LAYER_SEGMENTS(
    {2, 1, 0,255,255}
);
const rgblight_segment_t PROGMEM vidMuteLED[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 1, 0,255,255}
);
const rgblight_segment_t PROGMEM chatLED[] = RGBLIGHT_LAYER_SEGMENTS(
    {7, 1, HSV_YELLOW}
);
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    micMuteLED,
    vidMuteLED,
    chatLED
);

//these are the initialization functions
void keyboard_post_init_user(void) {
rgblight_sethsv_noeeprom(60,80,145);
rgblight_layers = my_rgb_layers;
rgblight_enable_noeeprom();
rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
layer_state_set_user(_MAC);
set_single_persistent_default_layer(_MAC);
debug_enable=1;
}

//raw HID - connects with my node script
void raw_hid_receive(uint8_t *data, uint8_t length) {
    if (data[1] == 0x01) {
        // rgblight_sethsv_at(0,255,255, 2);
        // rgblight_sethsv_at(0,255,255, 1);
        mic_Muted = 1;
        vid_Muted = 1;
        rgblight_set_layer_state(0, mic_Muted = 1);
        rgblight_set_layer_state(1, vid_Muted = 1);
        print("Mic Muted Video Stop");
    } else if (data[1] == 0x02) { //need to add a query of which layer you are on for PC
        // rgblight_sethsv_at(0,255,255, 2);
        // rgblight_sethsv_at(60,18,145, 1);
        mic_Muted = 1;
        vid_Muted = 0;
        rgblight_set_layer_state(0, mic_Muted = 1);
        rgblight_set_layer_state(1, vid_Muted = 0);
        print("Mic Muted Video Start");
    } else if (data[1] == 0x03) {
        // rgblight_sethsv_at(60,18,145, 2);
        // rgblight_sethsv_at(0,255,255, 1);
        mic_Muted = 0;
        vid_Muted = 1;
        rgblight_set_layer_state(0, mic_Muted = 0);
        rgblight_set_layer_state(1, vid_Muted = 1);
        print("Mic Unmuted Video Stop");
    } else if (data[1] == 0x04) {
        // rgblight_sethsv_at(60,18,145,2);
        // rgblight_sethsv_at(60,18,145,1);
        mic_Muted = 0;
        vid_Muted = 0;
        rgblight_set_layer_state(0, mic_Muted = 0);
        rgblight_set_layer_state(1, vid_Muted = 0);
        print("Mic Unmuted Video Start");
    }
}

//layer control
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        default:
        break;
        case _MAC:
            print("on mac layer");
            rgblight_sethsv_noeeprom(60,80,145);
            if (mic_Muted == 1) {
                rgblight_set_layer_state(0, mic_Muted = 1);
            } else if (mic_Muted == 0) {
                rgblight_set_layer_state(0, mic_Muted = 0);
            }
            if (vid_Muted == 1) {
                rgblight_set_layer_state(1, vid_Muted = 1);
            } else if (vid_Muted == 0) {
                rgblight_set_layer_state(1, vid_Muted = 0);
            }
        break;
        case _PC:
            print("on pc layer");
            rgblight_sethsv_noeeprom(144,216,237);
            if (mic_Muted == 1) {
                rgblight_set_layer_state(0, mic_Muted = 1);
            } else if (mic_Muted == 0) {
                rgblight_set_layer_state(0, mic_Muted = 0);
            }
            if (vid_Muted == 1) {
                rgblight_set_layer_state(1, vid_Muted = 1);
            } else if (vid_Muted == 0) {
                rgblight_set_layer_state(1, vid_Muted = 0);
            }
        break;
        case _UTIL:
        print("on util layer");
            rgblight_sethsv_noeeprom(85,255,127);
            if (mic_Muted == 1) {
                rgblight_set_layer_state(0, mic_Muted = 1);
            } else if (mic_Muted == 0) {
                rgblight_set_layer_state(0, mic_Muted = 0);
            }
            if (vid_Muted == 1) {
                rgblight_set_layer_state(1, vid_Muted = 1);
            } else if (vid_Muted == 0) {
                rgblight_set_layer_state(1, vid_Muted = 0);
            }
        break;
        };
return state;
}

//timer for press and hold
static uint16_t macSSTimer;
static uint16_t winSSTimer;

//custom keys
>>>>>>> 548249dc0fa0c96ff4254367aadfa3e36835635f
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
///////////mac layer/////////////////////////////////////
    case macMicMute: //Mic Mute
        if (record->event.pressed) {
<<<<<<< HEAD
            kp_1 = true;
        } else {
            kp_1 = false;
            if (kp_1a == false) {  
                kp_1a = true;       
                tap_code16(LSFT(LGUI(KC_A)));                            
                rgblight_setrgb(RGB_RED);
            }   else if (kp_1a == true) {
                    kp_1a = false;
                    tap_code16(LSFT(LGUI(KC_A)));
                    rgblight_setrgb(RGB_ORANGE);
=======
        } else {
            if (mic_Muted == 0) {
                mic_Muted = 1;
                rgblight_set_layer_state(0, mic_Muted = 1);
                tap_code16(LSFT(LGUI(KC_A)));
            }   else if (mic_Muted == 1) {
                    mic_Muted = 0;
                    rgblight_set_layer_state(0, mic_Muted = 0);
                    tap_code16(LSFT(LGUI(KC_A)));
>>>>>>> 548249dc0fa0c96ff4254367aadfa3e36835635f
                };
        };
        break;
    case macVidMute: // Video Mute
        if (record->event.pressed) {
<<<<<<< HEAD
            kp_2 = true;
        }   else {
                tap_code16(LSFT(LGUI(KC_V)));
                kp_2 = false;
        }
=======
        } else {
            if (vid_Muted == 0) {
                vid_Muted = 1;
                rgblight_set_layer_state(1, vid_Muted = 1);
                tap_code16(LSFT(LGUI(KC_V)));
            } else if (vid_Muted == 1) {
                vid_Muted = 0;
                rgblight_set_layer_state(1, vid_Muted = 0);
                tap_code16(LSFT(LGUI(KC_V)));
            };
        };
>>>>>>> 548249dc0fa0c96ff4254367aadfa3e36835635f
        break;
    case macShareScreen:
        if (record->event.pressed) {
<<<<<<< HEAD
            kp_3 = true;
        }   else {
                tap_code16(LALT(KC_Y));
                kp_3 = false;
=======
            macSSTimer = timer_read();
            mac_screen_share_press = 1; //matrix scan is listening for these events
        } else {
            mac_screen_share_press = 0;
            // if (screen_is_sharing == 1) { //deprecated idea
            //     tap_code16(LSFT(LGUI(KC_S)));
            //     screen_is_sharing = 0;
            //     rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            // }
>>>>>>> 548249dc0fa0c96ff4254367aadfa3e36835635f
        }
        return false;
    case macGalleryToggle:
        if (record->event.pressed) {
<<<<<<< HEAD
            kp_4 = true;
        }   else {
                tap_code16(LSFT(LGUI(KC_W)));
                kp_4 = false;
=======
        }   else {
                tap_code16(LSFT(LGUI(KC_W)));
>>>>>>> 548249dc0fa0c96ff4254367aadfa3e36835635f
        }
        break;
    case macGalleryLeft:
        if (record->event.pressed) {
<<<<<<< HEAD
            kp_5 = true;
        }   else {
                tap_code16(LCTL(KC_P));
                kp_5 = false;
=======
        }   else {
                tap_code16(LCTL(KC_P));
>>>>>>> 548249dc0fa0c96ff4254367aadfa3e36835635f
        }
        break;
    case macGalleryRight:
        if (record->event.pressed) {
<<<<<<< HEAD
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
=======
        }   else {
                tap_code16(LCTL(KC_N));
        }
        break;
    case macFullscreen:
        if (record->event.pressed) {
            mac_Full_Shift = 1;
        }   else {
                if (mac_Full_Shift == 1) {
                    tap_code16(LSFT(LGUI(KC_F)));
                    mac_Full_Shift = 0;
                };
                mac_Full_Shift = 0;
>>>>>>> 548249dc0fa0c96ff4254367aadfa3e36835635f
            }
        break;
    case macChat:
        if (record->event.pressed) {
<<<<<<< HEAD
            kp_8 = true;
        }   else {
                kp_8 = false;
                tap_code16(LSFT(LGUI(KC_H)));                
=======
        }   else {
                if (mac_Full_Shift == 0) {
                    if (mac_chat_open == 0) {
                        mac_chat_open = 1;
                        rgblight_set_layer_state(2, mac_chat_open = 1);
                        tap_code16(LSFT(LGUI(KC_H)));
                        // sethsv(HSV_YELLOW, (LED_TYPE *)&led[7]);
                        // rgblight_set();
                    }   else if (mac_chat_open == 1) {
                            mac_chat_open = 0;
                            rgblight_set_layer_state(2, mac_chat_open = 0);
                            tap_code16(LSFT(LGUI(KC_H)));
                            // sethsv(60,80,145, (LED_TYPE *)&led[7]);
                            // rgblight_set();
                        }
                }
                mac_Full_Shift = 0;
>>>>>>> 548249dc0fa0c96ff4254367aadfa3e36835635f
            }
        break;
    case macMini:
         if (record->event.pressed) {
            if (mac_Full_Shift == 1) {
                layer_move(_PC);
                mac_Full_Shift = 0;
            }
        }   else {
                if (layer_state_is(_MAC)) {
                    SEND_STRING(SS_LSFT(SS_LGUI("m")));
                }
            }
        break;
///////////windows layer/////////////////////////////////////
    case winMicMute:
        if (record->event.pressed) {
<<<<<<< HEAD
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
=======
        } else {
            if (mic_Muted == 0) {
                mic_Muted = 1;
                rgblight_set_layer_state(0, mic_Muted = 1);
                tap_code16(LALT(KC_A));
            }   else if (mic_Muted == 1) {
                    mic_Muted = 0;
                    rgblight_set_layer_state(0, mic_Muted = 0);
                    tap_code16(LALT(KC_A));
                };
        };
>>>>>>> 548249dc0fa0c96ff4254367aadfa3e36835635f
        break;
    case winVidMute:
        if (record->event.pressed) {
        } else {
            if (vid_Muted == 0) {
                vid_Muted = 1;
                rgblight_set_layer_state(1, vid_Muted = 1);
                tap_code16(LALT(KC_V));
            } else if (vid_Muted == 1) {
                vid_Muted = 0;
                rgblight_set_layer_state(1, vid_Muted = 0);
                tap_code16(LALT(KC_V));
            };
        };
        break;
    case winShareScreen:
        if (record->event.pressed) {
            win_screen_share_press = 1; //matrix scan is listening for these events
            winSSTimer = timer_read();
        }   else {
<<<<<<< HEAD
                kp_10 = false;
                if (kp_10a == false) {        
                    tap_code16(LALT(KC_A));          
                    rgblight_setrgb(RGB_RED);
                    kp_10a = true;     
                }   else if (kp_10a == true) {
                        tap_code16(LALT(KC_A));
                        rgblight_setrgb(RGB_YELLOW);
                        kp_10a = false;
                    };
            };         
=======

                }
>>>>>>> 548249dc0fa0c96ff4254367aadfa3e36835635f
        break;
    case winGalleryToggle:
        if (record->event.pressed) {
<<<<<<< HEAD
            kp_11 = true;       
        }   else {
                kp_11 = false;
                tap_code16(LALT(KC_V));
            }
=======
            }   else {
                    tap_code16(LALT(KC_F2));
                }
>>>>>>> 548249dc0fa0c96ff4254367aadfa3e36835635f
        break;
    case winGalleryLeft:
        if (record->event.pressed) {
<<<<<<< HEAD
            kp_12 = true;
            }   else {
                    kp_12 = false;
                    tap_code16(LALT(KC_Y));
                }
=======
            }   else {
                    tap_code(KC_PGDOWN);
                }
        break;
    case winGalleryRight:
        if (record->event.pressed) {
            }   else {
                    tap_code16(KC_PGUP);
                }
        break;
    case winFullscreen:
        if (record->event.pressed) {
            win_Full_Shift = 1;
        }   else {
                if (win_Full_Shift == 1) {
                    tap_code16(LALT(KC_F));
                    win_Full_Shift = 0;
                };
                win_Full_Shift = 0;
            };
>>>>>>> 548249dc0fa0c96ff4254367aadfa3e36835635f
        break;
    case winChat:
        if (record->event.pressed) {
<<<<<<< HEAD
            kp_13 = true;
            }   else {
                    kp_13 = false;
                    tap_code16(LALT(KC_F2));
                }
=======
            if (win_Full_Shift == 1) {
                layer_move(_MAC);
                mac_Full_Shift = 1;
            }
        }   else {
                if (win_Full_Shift == 0) {
                    if (win_chat_open == 0) {
                        win_chat_open = 1;
                        rgblight_set_layer_state(2, mac_chat_open = 1);
                        tap_code16(LALT(KC_H));
                        // sethsv(HSV_YELLOW, (LED_TYPE *)&led[7]);
                        // rgblight_set();
                    } else if (win_chat_open == 1) {
                        win_chat_open = 0;
                        rgblight_set_layer_state(2, mac_chat_open = 0);
                        tap_code16(LALT(KC_H));
                        // sethsv(144,216,237, (LED_TYPE *)&led[7]);
                        // rgblight_set();
                    }
                }
                win_Full_Shift = 0;
            }
>>>>>>> 548249dc0fa0c96ff4254367aadfa3e36835635f
        break;
    case winMini:
        if (record->event.pressed) {
<<<<<<< HEAD
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
=======
            if (win_Full_Shift) {
                layer_move(_UTIL);
            }
        }   else {
            }
        break;
///////////utility layer/////////////////////////////////////
    case utilOne:
        if (record->event.pressed) {
            flash_one = 1;
        }   else {
            flash_one = 0;
        }
        break;
    case utilTwo:
    case utilThree:
    case utilFour:
    case utilFive:
    case utilSix:
    case utilSeven:
        if (record->event.pressed) {
            flash_two = 1;
            win_Full_Shift = 1;
        }   else {
            flash_two = 0;
        }
>>>>>>> 548249dc0fa0c96ff4254367aadfa3e36835635f
        break;
    case utilEight:
        if (record->event.pressed) {
<<<<<<< HEAD
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
            if (kp_25 && kp_26) {
                rgblight_setrgb(RGB_WHITE);
                reset_keyboard();
            }
       }   else {
            kp_27 = false;
=======
            if (flash_two) {
                layer_move(_PC);
                win_Full_Shift = 1;
            }
        }   else {
            }
        break;
    case flashKeeb:
        if (record->event.pressed) {
            kp_27 = 1;
            if (flash_one && flash_two) {
                rgblight_sethsv_noeeprom(0,0,255);
                rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
                reset_keyboard();
            }
       }   else {
            kp_27 = 0;
>>>>>>> 548249dc0fa0c96ff4254367aadfa3e36835635f
        }
        break;
    }
    return true;
};

<<<<<<< HEAD

//for when I use rawHID to add feedback:
void raw_hid_receive(uint8_t *data, uint8_t length) {
}


//these are the initialization functions
void keyboard_post_init_user(void) {
  // Call the post init code.
  rgblight_enable_noeeprom(); // enables Rgb, without saving settings
  rgblight_setrgb(RGB_ORANGE);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT); 
  set_single_persistent_default_layer(0); 
}

//RGB control for layers
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        default:
            if (kp_1a) {
                rgblight_setrgb(RGB_RED);
            }   else {
                rgblight_setrgb(RGB_ORANGE);
            };
        break;
        case 1:
            if (kp_10a) {
                rgblight_setrgb(RGB_RED); 
            }   else {
                rgblight_setrgb(RGB_YELLOW);
            }
        break;
    case 2:
        rgblight_setrgb(RGB_GREEN);
        break;
    }
return state;    
}

=======
//scans for my press and hold (screen share)...wish there was a better way, but alas
void matrix_scan_user(void) {
    if (mac_screen_share_press == 1 && timer_elapsed(macSSTimer) > 1500) {
        print("mac sharing");
        tap_code16(LSFT(LGUI(KC_S)));
        screen_is_sharing = 1;
        // rgblight_mode(RGBLIGHT_MODE_BREATHING);
        mac_screen_share_press = 0;
    };
    if (win_screen_share_press == 1 && timer_elapsed(winSSTimer) > 1500) {
        print("win sharing");
        tap_code16(LALT(LSFT(KC_S)));
        win_screen_share_press = 0;
    }
};
>>>>>>> 548249dc0fa0c96ff4254367aadfa3e36835635f
