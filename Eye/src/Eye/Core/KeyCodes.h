#pragma once

// ref: https://github.com/glfw/glfw/blob/master/include/GLFW/glfw3.h#L391-L511
/* Printable keys */
#define EYE_KEY_SPACE              32
#define EYE_KEY_APOSTROPHE         39  /* ' */
#define EYE_KEY_COMMA              44  /* , */
#define EYE_KEY_MINUS              45  /* - */
#define EYE_KEY_PERIOD             46  /* . */
#define EYE_KEY_SLASH              47  /* / */
#define EYE_KEY_0                  48
#define EYE_KEY_1                  49
#define EYE_KEY_2                  50
#define EYE_KEY_3                  51
#define EYE_KEY_4                  52
#define EYE_KEY_5                  53
#define EYE_KEY_6                  54
#define EYE_KEY_7                  55
#define EYE_KEY_8                  56
#define EYE_KEY_9                  57
#define EYE_KEY_SEMICOLON          59  /* ; */
#define EYE_KEY_EQUAL              61  /* = */
#define EYE_KEY_A                  65
#define EYE_KEY_B                  66
#define EYE_KEY_C                  67
#define EYE_KEY_D                  68
#define EYE_KEY_E                  69
#define EYE_KEY_F                  70
#define EYE_KEY_G                  71
#define EYE_KEY_H                  72
#define EYE_KEY_I                  73
#define EYE_KEY_J                  74
#define EYE_KEY_K                  75
#define EYE_KEY_L                  76
#define EYE_KEY_M                  77
#define EYE_KEY_N                  78
#define EYE_KEY_O                  79
#define EYE_KEY_P                  80
#define EYE_KEY_Q                  81
#define EYE_KEY_R                  82
#define EYE_KEY_S                  83
#define EYE_KEY_T                  84
#define EYE_KEY_U                  85
#define EYE_KEY_V                  86
#define EYE_KEY_W                  87
#define EYE_KEY_X                  88
#define EYE_KEY_Y                  89
#define EYE_KEY_Z                  90
#define EYE_KEY_LEFT_BRACKET       91  /* [ */
#define EYE_KEY_BACKSLASH          92  /* \ */
#define EYE_KEY_RIGHT_BRACKET      93  /* ] */
#define EYE_KEY_GRAVE_ACCENT       96  /* ` */
#define EYE_KEY_WORLD_1            161 /* non-US #1 */
#define EYE_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define EYE_KEY_ESCAPE             256
#define EYE_KEY_ENTER              257
#define EYE_KEY_TAB                258
#define EYE_KEY_BACKSPACE          259
#define EYE_KEY_INSERT             260
#define EYE_KEY_DELETE             261
#define EYE_KEY_RIGHT              262
#define EYE_KEY_LEFT               263
#define EYE_KEY_DOWN               264
#define EYE_KEY_UP                 265
#define EYE_KEY_PAGE_UP            266
#define EYE_KEY_PAGE_DOWN          267
#define EYE_KEY_HOME               268
#define EYE_KEY_END                269
#define EYE_KEY_CAPS_LOCK          280
#define EYE_KEY_SCROLL_LOCK        281
#define EYE_KEY_NUM_LOCK           282
#define EYE_KEY_PRINT_SCREEN       283
#define EYE_KEY_PAUSE              284
#define EYE_KEY_F1                 290
#define EYE_KEY_F2                 291
#define EYE_KEY_F3                 292
#define EYE_KEY_F4                 293
#define EYE_KEY_F5                 294
#define EYE_KEY_F6                 295
#define EYE_KEY_F7                 296
#define EYE_KEY_F8                 297
#define EYE_KEY_F9                 298
#define EYE_KEY_F10                299
#define EYE_KEY_F11                300
#define EYE_KEY_F12                301
#define EYE_KEY_F13                302
#define EYE_KEY_F14                303
#define EYE_KEY_F15                304
#define EYE_KEY_F16                305
#define EYE_KEY_F17                306
#define EYE_KEY_F18                307
#define EYE_KEY_F19                308
#define EYE_KEY_F20                309
#define EYE_KEY_F21                310
#define EYE_KEY_F22                311
#define EYE_KEY_F23                312
#define EYE_KEY_F24                313
#define EYE_KEY_F25                314
#define EYE_KEY_KP_0               320
#define EYE_KEY_KP_1               321
#define EYE_KEY_KP_2               322
#define EYE_KEY_KP_3               323
#define EYE_KEY_KP_4               324
#define EYE_KEY_KP_5               325
#define EYE_KEY_KP_6               326
#define EYE_KEY_KP_7               327
#define EYE_KEY_KP_8               328
#define EYE_KEY_KP_9               329
#define EYE_KEY_KP_DECIMAL         330
#define EYE_KEY_KP_DIVIDE          331
#define EYE_KEY_KP_MULTIPLY        332
#define EYE_KEY_KP_SUBTRACT        333
#define EYE_KEY_KP_ADD             334
#define EYE_KEY_KP_ENTER           335
#define EYE_KEY_KP_EQUAL           336
#define EYE_KEY_LEFT_SHIFT         340
#define EYE_KEY_LEFT_CONTROL       341
#define EYE_KEY_LEFT_ALT           342
#define EYE_KEY_LEFT_SUPER         343
#define EYE_KEY_RIGHT_SHIFT        344
#define EYE_KEY_RIGHT_CONTROL      345
#define EYE_KEY_RIGHT_ALT          346
#define EYE_KEY_RIGHT_SUPER        347
#define EYE_KEY_MENU               348

#define EYE_KEY_LAST               EYE_KEY_MENU
