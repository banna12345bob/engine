#pragma once

namespace Engine {
#ifdef EG_GLFW_WINDOW
    //From glfw3.h
    #define EG_KEY_SPACE              32
    #define EG_KEY_APOSTROPHE         39  /* ' */
    #define EG_KEY_COMMA              44  /* , */
    #define EG_KEY_MINUS              45  /* - */
    #define EG_KEY_PERIOD             46  /* . */
    #define EG_KEY_SLASH              47  /* / */
    #define EG_KEY_0                  48
    #define EG_KEY_1                  49
    #define EG_KEY_2                  50
    #define EG_KEY_3                  51
    #define EG_KEY_4                  52
    #define EG_KEY_5                  53
    #define EG_KEY_6                  54
    #define EG_KEY_7                  55
    #define EG_KEY_8                  56
    #define EG_KEY_9                  57
    #define EG_KEY_SEMICOLON          59  /* ; */
    #define EG_KEY_EQUAL              61  /* = */
    #define EG_KEY_A                  65
    #define EG_KEY_B                  66
    #define EG_KEY_C                  67
    #define EG_KEY_D                  68
    #define EG_KEY_E                  69
    #define EG_KEY_F                  70
    #define EG_KEY_G                  71
    #define EG_KEY_H                  72
    #define EG_KEY_I                  73
    #define EG_KEY_J                  74
    #define EG_KEY_K                  75
    #define EG_KEY_L                  76
    #define EG_KEY_M                  77
    #define EG_KEY_N                  78
    #define EG_KEY_O                  79
    #define EG_KEY_P                  80
    #define EG_KEY_Q                  81
    #define EG_KEY_R                  82
    #define EG_KEY_S                  83
    #define EG_KEY_T                  84
    #define EG_KEY_U                  85
    #define EG_KEY_V                  86
    #define EG_KEY_W                  87
    #define EG_KEY_X                  88
    #define EG_KEY_Y                  89
    #define EG_KEY_Z                  90
    #define EG_KEY_LEFT_BRACKET       91  /* [ */
    #define EG_KEY_BACKSLASH          92  /* \ */
    #define EG_KEY_RIGHT_BRACKET      93  /* ] */
    #define EG_KEY_TILDE       96  /* ` */
    #define EG_KEY_WORLD_1            161 /* non-US #1 */
    #define EG_KEY_WORLD_2            162 /* non-US #2 */

    /* Function keys */
    #define EG_KEY_ESCAPE             256
    #define EG_KEY_ENTER              257
    #define EG_KEY_TAB                258
    #define EG_KEY_BACKSPACE          259
    #define EG_KEY_INSERT             260
    #define EG_KEY_DELETE             261
    #define EG_KEY_RIGHT              262
    #define EG_KEY_LEFT               263
    #define EG_KEY_DOWN               264
    #define EG_KEY_UP                 265
    #define EG_KEY_PAGE_UP            266
    #define EG_KEY_PAGE_DOWN          267
    #define EG_KEY_HOME               268
    #define EG_KEY_END                269
    #define EG_KEY_CAPS_LOCK          280
    #define EG_KEY_SCROLL_LOCK        281
    #define EG_KEY_NUM_LOCK           282
    #define EG_KEY_PRINT_SCREEN       283
    #define EG_KEY_PAUSE              284
    #define EG_KEY_F1                 290
    #define EG_KEY_F2                 291
    #define EG_KEY_F3                 292
    #define EG_KEY_F4                 293
    #define EG_KEY_F5                 294
    #define EG_KEY_F6                 295
    #define EG_KEY_F7                 296
    #define EG_KEY_F8                 297
    #define EG_KEY_F9                 298
    #define EG_KEY_F10                299
    #define EG_KEY_F11                300
    #define EG_KEY_F12                301
    #define EG_KEY_F13                302
    #define EG_KEY_F14                303
    #define EG_KEY_F15                304
    #define EG_KEY_F16                305
    #define EG_KEY_F17                306
    #define EG_KEY_F18                307
    #define EG_KEY_F19                308
    #define EG_KEY_F20                309
    #define EG_KEY_F21                310
    #define EG_KEY_F22                311
    #define EG_KEY_F23                312
    #define EG_KEY_F24                313
    #define EG_KEY_F25                314
    #define EG_KEY_KP_0               320
    #define EG_KEY_KP_1               321
    #define EG_KEY_KP_2               322
    #define EG_KEY_KP_3               323
    #define EG_KEY_KP_4               324
    #define EG_KEY_KP_5               325
    #define EG_KEY_KP_6               326
    #define EG_KEY_KP_7               327
    #define EG_KEY_KP_8               328
    #define EG_KEY_KP_9               329
    #define EG_KEY_KP_DECIMAL         330
    #define EG_KEY_KP_DIVIDE          331
    #define EG_KEY_KP_MULTIPLY        332
    #define EG_KEY_KP_EGBTRACT        333
    #define EG_KEY_KP_ADD             334
    #define EG_KEY_KP_ENTER           335
    #define EG_KEY_KP_EQUAL           336
    #define EG_KEY_LEFT_SHIFT         340
    #define EG_KEY_LEFT_CONTROL       341
    #define EG_KEY_LEFT_ALT           342
    #define EG_KEY_LEFT_EGPER         343
    #define EG_KEY_RIGHT_SHIFT        344
    #define EG_KEY_RIGHT_CONTROL      345
    #define EG_KEY_RIGHT_ALT          346
    #define EG_KEY_RIGHT_EGPER        347
    #define EG_KEY_MENU               348
#else
    #define EG_KEY_UNKNOWN 0
    #define EG_KEY_A 4
    #define EG_KEY_B 5
    #define EG_KEY_C 6
    #define EG_KEY_D 7
    #define EG_KEY_E 8
    #define EG_KEY_F 9
    #define EG_KEY_G 10
    #define EG_KEY_H 11
    #define EG_KEY_I 12
    #define EG_KEY_J 13
    #define EG_KEY_K 14
    #define EG_KEY_L 15
    #define EG_KEY_M 16
    #define EG_KEY_N 17
    #define EG_KEY_O 18
    #define EG_KEY_P 19
    #define EG_KEY_Q 20
    #define EG_KEY_R 21
    #define EG_KEY_S 22
    #define EG_KEY_T 23
    #define EG_KEY_U 24
    #define EG_KEY_V 25
    #define EG_KEY_W 26
    #define EG_KEY_X 27
    #define EG_KEY_Y 28
    #define EG_KEY_Z 29

    #define EG_KEY_1 30
    #define EG_KEY_2 31
    #define EG_KEY_3 32
    #define EG_KEY_4 33
    #define EG_KEY_5 34
    #define EG_KEY_6 35
    #define EG_KEY_7 36
    #define EG_KEY_8 37
    #define EG_KEY_9 38
    #define EG_KEY_0 39

    #define EG_KEY_RETURN 40
    #define EG_KEY_ESCAPE 41
    #define EG_KEY_BACKSPACE 42
    #define EG_KEY_TAB 43
    #define EG_KEY_SPACE 44

    #define EG_KEY_MINUS 45
    #define EG_KEY_EQUALS 46
    #define EG_KEY_LEFTBRACKET 47
    #define EG_KEY_RIGHTBRACKET 48
    #define EG_KEY_BACKSLASH 49
    #define EG_KEY_NONUSHASH 50
    #define EG_KEY_SEMICOLON 51
    #define EG_KEY_APOSTROPHE 52
    #define EG_KEY_GRAVE 53
    #define EG_KEY_COMMA 54
    #define EG_KEY_PERIOD 55
    #define EG_KEY_SLASH 56

    #define EG_KEY_CAPSLOCK 57

    #define EG_KEY_F1 58
    #define EG_KEY_F2 59
    #define EG_KEY_F3 60
    #define EG_KEY_F4 61
    #define EG_KEY_F5 62
    #define EG_KEY_F6 63
    #define EG_KEY_F7 64
    #define EG_KEY_F8 65
    #define EG_KEY_F9 66
    #define EG_KEY_F10 67
    #define EG_KEY_F11 68
    #define EG_KEY_F12 69

    #define EG_KEY_PRINTSCREEN 70
    #define EG_KEY_SCROLLLOCK 71
    #define EG_KEY_PAUSE 72
    #define EG_KEY_INSERT 73
    #define EG_KEY_HOME 74
    #define EG_KEY_PAGEUP 75
    #define EG_KEY_DELETE 76
    #define EG_KEY_END 77
    #define EG_KEY_PAGEDOWN 78
    #define EG_KEY_RIGHT 79
    #define EG_KEY_LEFT 80
    #define EG_KEY_DOWN 81
    #define EG_KEY_UP 82

    #define EG_KEY_NUMLOCKCLEAR 83
    #define EG_KEY_KP_DIVIDE 84
    #define EG_KEY_KP_MULTIPLY 85
    #define EG_KEY_KP_MINUS 86
    #define EG_KEY_KP_PLUS 87
    #define EG_KEY_KP_ENTER 88
    #define EG_KEY_KP_1 89
    #define EG_KEY_KP_2 90
    #define EG_KEY_KP_3 91
    #define EG_KEY_KP_4 92
    #define EG_KEY_KP_5 93
    #define EG_KEY_KP_6 94
    #define EG_KEY_KP_7 95
    #define EG_KEY_KP_8 96
    #define EG_KEY_KP_9 97
    #define EG_KEY_KP_0 98
    #define EG_KEY_KP_PERIOD 99

    #define EG_KEY_NONUSBACKSLASH 100
    #define EG_KEY_APPLICATION 101
    #define EG_KEY_POWER 102
    #define EG_KEY_KP_EQUALS 103
    #define EG_KEY_F13 104
    #define EG_KEY_F14 105
    #define EG_KEY_F15 106
    #define EG_KEY_F16 107
    #define EG_KEY_F17 108
    #define EG_KEY_F18 109
    #define EG_KEY_F19 110
    #define EG_KEY_F20 111
    #define EG_KEY_F21 112
    #define EG_KEY_F22 113
    #define EG_KEY_F23 114
    #define EG_KEY_F24 115
    #define EG_KEY_EXECUTE 116
    #define EG_KEY_HELP 117 
    #define EG_KEY_MENU 118 
    #define EG_KEY_SELECT 119
    #define EG_KEY_STOP 120  
    #define EG_KEY_AGAIN 121  
    #define EG_KEY_UNDO 122 
    #define EG_KEY_CUT 123  
    #define EG_KEY_COPY 124 
    #define EG_KEY_PASTE 125 
    #define EG_KEY_FIND 126 
    #define EG_KEY_MUTE 127
    #define EG_KEY_VOLUMEUP 128
    #define EG_KEY_VOLUMEDOWN 129
    #define EG_KEY_KP_COMMA 133
    #define EG_KEY_KP_EQUALSAS400 134

    #define EG_KEY_INTERNATIONAL1 135 
    #define EG_KEY_INTERNATIONAL2 136
    #define EG_KEY_INTERNATIONAL3 137 
    #define EG_KEY_INTERNATIONAL4 138
    #define EG_KEY_INTERNATIONAL5 139
    #define EG_KEY_INTERNATIONAL6 140
    #define EG_KEY_INTERNATIONAL7 141
    #define EG_KEY_INTERNATIONAL8 142
    #define EG_KEY_INTERNATIONAL9 143
    #define EG_KEY_LANG1 144 /**< Hangul/English toggle */
    #define EG_KEY_LANG2 145 /**< Hanja conversion */
    #define EG_KEY_LANG3 146 /**< Katakana */
    #define EG_KEY_LANG4 147 /**< Hiragana */
    #define EG_KEY_LANG5 148 /**< Zenkaku/Hankaku */
    #define EG_KEY_LANG6 149 /**< reserved */
    #define EG_KEY_LANG7 150 /**< reserved */
    #define EG_KEY_LANG8 151 /**< reserved */
    #define EG_KEY_LANG9 152 /**< reserved */

    #define EG_KEY_ALTERASE 153  /**< Erase-Eaze */
    #define EG_KEY_SYSREQ 154
    #define EG_KEY_CANCEL 155   /**< AC Cancel */
    #define EG_KEY_CLEAR 156
    #define EG_KEY_PRIOR 157
    #define EG_KEY_RETURN2 158
    #define EG_KEY_SEPARATOR 159
    #define EG_KEY_OUT 160
    #define EG_KEY_OPER 161
    #define EG_KEY_CLEARAGAIN 162
    #define EG_KEY_CRSEL 163
    #define EG_KEY_EXSEL 164

    #define EG_KEY_KP_00 176
    #define EG_KEY_KP_000 177
    #define EG_KEY_THOUSANDSSEPARATOR 178
    #define EG_KEY_DECIMALSEPARATOR 179
    #define EG_KEY_CURRENCYUNIT 180
    #define EG_KEY_CURRENCYEGBUNIT 181
    #define EG_KEY_KP_LEFTPAREN 182
    #define EG_KEY_KP_RIGHTPAREN 183
    #define EG_KEY_KP_LEFTBRACE 184
    #define EG_KEY_KP_RIGHTBRACE 185
    #define EG_KEY_KP_TAB 186
    #define EG_KEY_KP_BACKSPACE 187
    #define EG_KEY_KP_A 188
    #define EG_KEY_KP_B 189
    #define EG_KEY_KP_C 190
    #define EG_KEY_KP_D 191
    #define EG_KEY_KP_E 192
    #define EG_KEY_KP_F 193
    #define EG_KEY_KP_XOR 194
    #define EG_KEY_KP_POWER 195
    #define EG_KEY_KP_PERCENT 196
    #define EG_KEY_KP_LESS 197
    #define EG_KEY_KP_GREATER 198
    #define EG_KEY_KP_AMPERSAND 199
    #define EG_KEY_KP_DBLAMPERSAND 200
    #define EG_KEY_KP_VERTICALBAR 201
    #define EG_KEY_KP_DBLVERTICALBAR 202
    #define EG_KEY_KP_COLON 203
    #define EG_KEY_KP_HASH 204
    #define EG_KEY_KP_SPACE 205
    #define EG_KEY_KP_AT 206
    #define EG_KEY_KP_EXCLAM 207
    #define EG_KEY_KP_MEMSTORE 208
    #define EG_KEY_KP_MEMRECALL 209
    #define EG_KEY_KP_MEMCLEAR 210
    #define EG_KEY_KP_MEMADD 211
    #define EG_KEY_KP_MEMEGBTRACT 212
    #define EG_KEY_KP_MEMMULTIPLY 213
    #define EG_KEY_KP_MEMDIVIDE 214
    #define EG_KEY_KP_PLUSMINUS 215
    #define EG_KEY_KP_CLEAR 216
    #define EG_KEY_KP_CLEARENTRY 217
    #define EG_KEY_KP_BINARY 218
    #define EG_KEY_KP_OCTAL 219
    #define EG_KEY_KP_DECIMAL 220
    #define EG_KEY_KP_HEXADECIMAL 221

    #define EG_KEY_LCTRL 224
    #define EG_KEY_LSHIFT 225
    #define EG_KEY_LALT 226 /**< alt option */
    #define EG_KEY_LGUI 227 /**< windows command (apple) meta */
    #define EG_KEY_RCTRL 228
    #define EG_KEY_RSHIFT 229
    #define EG_KEY_RALT 230 /**< alt gr option */
    #define EG_KEY_RGUI 231 /**< windows command (apple) meta */

    #define EG_KEY_MODE 257

    #define EG_KEY_SLEEP 258          /**< Sleep */
    #define EG_KEY_WAKE 259          /**< Wake */

    #define EG_KEY_CHANNEL_INCREMENT 260    /**< Channel Increment */
    #define EG_KEY_CHANNEL_DECREMENT 261    /**< Channel Decrement */

    #define EG_KEY_MEDIA_PLAY 262     /**< Play */
    #define EG_KEY_MEDIA_PAUSE 263     /**< Pause */
    #define EG_KEY_MEDIA_RECORD 264    /**< Record */
    #define EG_KEY_MEDIA_FAST_FORWARD 265 /**< Fast Forward */
    #define EG_KEY_MEDIA_REWIND 266    /**< Rewind */
    #define EG_KEY_MEDIA_NEXT_TRACK 267  /**< Next Track */
    #define EG_KEY_MEDIA_PREVIOUS_TRACK 268 /**< Previous Track */
    #define EG_KEY_MEDIA_STOP 269     /**< Stop */
    #define EG_KEY_MEDIA_EJECT 270     /**< Eject */
    #define EG_KEY_MEDIA_PLAY_PAUSE 271  /**< Play / Pause */
    #define EG_KEY_MEDIA_SELECT 272    /* Media Select */

    #define EG_KEY_AC_NEW 273       /**< AC New */
    #define EG_KEY_AC_OPEN 274       /**< AC Open */
    #define EG_KEY_AC_CLOSE 275      /**< AC Close */
    #define EG_KEY_AC_EXIT 276       /**< AC Exit */
    #define EG_KEY_AC_SAVE 277       /**< AC Save */
    #define EG_KEY_AC_PRINT 278
    #define EG_KEY_AC_PROPERTIES 279

    #define EG_KEY_AC_SEARCH 280
    #define EG_KEY_AC_HOME 281
    #define EG_KEY_AC_BACK 282     
    #define EG_KEY_AC_FORWARD 283
    #define EG_KEY_AC_STOP 284
    #define EG_KEY_AC_REFRESH 285
    #define EG_KEY_AC_BOOKMARKS 286


    #define EG_KEY_SOFTLEFT 287
    #define EG_KEY_SOFTRIGHT 288
    #define EG_KEY_CALL 289
    #define EG_KEY_ENDCALL 290
    #define EG_KEY_RESERVED 400
    #define EG_KEY_COUNT 512 
#endif
}