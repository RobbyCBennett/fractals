#pragma once


#include <stdint.h>


namespace frac {


// The code of a key, button, or something similar
//
// https://raw.githubusercontent.com/torvalds/linux/master/include/uapi/linux/input-event-codes.h
using Key = uint16_t;


// Some specific codes of a key, button, or something similar
//
// https://raw.githubusercontent.com/torvalds/linux/master/include/uapi/linux/input-event-codes.h
enum Keys: Key
{
	KEY_RESERVED = 0,
	// Keyboard: escape
	KEY_ESC = 1,
	// Keyboard: 1 from number row
	KEY_1 = 2,
	// Keyboard: 2 from number row
	KEY_2 = 3,
	// Keyboard: 3 from number row
	KEY_3 = 4,
	// Keyboard: 4 from number row
	KEY_4 = 5,
	// Keyboard: 5 from number row
	KEY_5 = 6,
	// Keyboard: 6 from number row
	KEY_6 = 7,
	// Keyboard: 7 from number row
	KEY_7 = 8,
	// Keyboard: 8 from number row
	KEY_8 = 9,
	// Keyboard: 9 from number row
	KEY_9 = 10,
	// Keyboard: 0 from number row
	KEY_0 = 11,
	// Keyboard: minus, subtract, or dash -
	KEY_MINUS = 12,
	// Keyboard: equal =
	KEY_EQUAL = 13,
	// Keyboard: backspace
	KEY_BACKSPACE = 14,
	// Keyboard: tab
	KEY_TAB = 15,
	// Keyboard: letter q
	KEY_Q = 16,
	// Keyboard: letter w
	KEY_W = 17,
	// Keyboard: letter e
	KEY_E = 18,
	// Keyboard: letter r
	KEY_R = 19,
	// Keyboard: letter t
	KEY_T = 20,
	// Keyboard: letter y
	KEY_Y = 21,
	// Keyboard: letter u
	KEY_U = 22,
	// Keyboard: letter i
	KEY_I = 23,
	// Keyboard: letter o
	KEY_O = 24,
	// Keyboard: letter p
	KEY_P = 25,
	// Keyboard: left square bracket [
	KEY_LEFTBRACE = 26,
	// Keyboard: right square bracket ]
	KEY_RIGHTBRACE = 27,
	// Keyboard: enter
	KEY_ENTER = 28,
	// Keyboard: left control
	KEY_LEFTCTRL = 29,
	// Keyboard: letter a
	KEY_A = 30,
	// Keyboard: letter s
	KEY_S = 31,
	// Keyboard: letter d
	KEY_D = 32,
	// Keyboard: letter f
	KEY_F = 33,
	// Keyboard: letter g
	KEY_G = 34,
	// Keyboard: letter h
	KEY_H = 35,
	// Keyboard: letter j
	KEY_J = 36,
	// Keyboard: letter k
	KEY_K = 37,
	// Keyboard: letter l
	KEY_L = 38,
	// Keyboard: semicolon ;
	KEY_SEMICOLON = 39,
	// Keyboard: apostrophe or single-quote '
	KEY_APOSTROPHE = 40,
	// Keyboard: backtick or grave `
	KEY_GRAVE = 41,
	// Keyboard: left shift
	KEY_LEFTSHIFT = 42,
	// Keyboard: backslash `\`
	KEY_BACKSLASH = 43,
	// Keyboard: letter z
	KEY_Z = 44,
	// Keyboard: letter x
	KEY_X = 45,
	// Keyboard: letter c
	KEY_C = 46,
	// Keyboard: letter v
	KEY_V = 47,
	// Keyboard: letter b
	KEY_B = 48,
	// Keyboard: letter n
	KEY_N = 49,
	// Keyboard: letter m
	KEY_M = 50,
	// Keyboard: comma ,
	KEY_COMMA = 51,
	// Keyboard: dot, period, or decimal point .
	KEY_DOT = 52,
	// Keyboard: forward slash /
	KEY_SLASH = 53,
	// Keyboard: right shift
	KEY_RIGHTSHIFT = 54,
	// Keyboard: asterisk, multiply, or times *
	KEY_KPASTERISK = 55,
	// Keyboard: left alt
	KEY_LEFTALT = 56,
	// Keyboard: spacebar
	KEY_SPACE = 57,
	// Keyboard: caps lock
	KEY_CAPSLOCK = 58,
	// Keyboard: function 1
	KEY_F1 = 59,
	// Keyboard: function 2
	KEY_F2 = 60,
	// Keyboard: function 3
	KEY_F3 = 61,
	// Keyboard: function 4
	KEY_F4 = 62,
	// Keyboard: function 5
	KEY_F5 = 63,
	// Keyboard: function 6
	KEY_F6 = 64,
	// Keyboard: function 7
	KEY_F7 = 65,
	// Keyboard: function 8
	KEY_F8 = 66,
	// Keyboard: function 9
	KEY_F9 = 67,
	// Keyboard: function 10
	KEY_F10 = 68,
	// Keyboard: num lock
	KEY_NUMLOCK = 69,
	// Keyboard: scroll lock
	KEY_SCROLLLOCK = 70,
	// Keyboard: keypad/numpad 7
	KEY_KP7 = 71,
	// Keyboard: keypad/numpad 8
	KEY_KP8 = 72,
	// Keyboard: keypad/numpad 9
	KEY_KP9 = 73,
	// Keyboard: keypad/numpad minus, subtract, or dash -
	KEY_KPMINUS = 74,
	// Keyboard: keypad/numpad 4
	KEY_KP4 = 75,
	// Keyboard: keypad/numpad 5
	KEY_KP5 = 76,
	// Keyboard: keypad/numpad 6
	KEY_KP6 = 77,
	// Keyboard: keypad/numpad plus or add +
	KEY_KPPLUS = 78,
	// Keyboard: keypad/numpad 1
	KEY_KP1 = 79,
	// Keyboard: keypad/numpad 2
	KEY_KP2 = 80,
	// Keyboard: keypad/numpad 3
	KEY_KP3 = 81,
	// Keyboard: keypad/numpad 0
	KEY_KP0 = 82,
	// Keyboard: keypad/numpad dot, period, or decimal point .
	KEY_KPDOT = 83,

	KEY_ZENKAKUHANKAKU = 85,
	KEY_102ND = 86,
	// Keyboard: function 11
	KEY_F11 = 87,
	// Keyboard: function 12
	KEY_F12 = 88,
	KEY_RO = 89,
	KEY_KATAKANA = 90,
	KEY_HIRAGANA = 91,
	KEY_HENKAN = 92,
	KEY_KATAKANAHIRAGANA = 93,
	KEY_MUHENKAN = 94,
	KEY_KPJPCOMMA = 95,
	// Keyboard: keypad/numpad enter
	KEY_KPENTER = 96,
	// Keyboard: right control
	KEY_RIGHTCTRL = 97,
	// Keyboard: forward slash or divide /
	KEY_KPSLASH = 98,
	KEY_SYSRQ = 99,
	// Keyboard: right alt
	KEY_RIGHTALT = 100,
	KEY_LINEFEED = 101,
	// Keyboard: home
	KEY_HOME = 102,
	// Keyboard: up arrow
	KEY_UP = 103,
	// Keyboard: page up
	KEY_PAGEUP = 104,
	// Keyboard: left arrow
	KEY_LEFT = 105,
	// Keyboard: right arrow
	KEY_RIGHT = 106,
	// Keyboard: end
	KEY_END = 107,
	// Keyboard: down arrow
	KEY_DOWN = 108,
	// Keyboard: page down
	KEY_PAGEDOWN = 109,
	// Keyboard: insert
	KEY_INSERT = 110,
	// Keyboard: delete
	KEY_DELETE = 111,
	KEY_MACRO = 112,
	// Media control: mute (same as `KEY_MIN_INTERESTING`)
	KEY_MUTE = 113,
	// Media control: mute (same as `KEY_MUTE`)
	KEY_MIN_INTERESTING = 113,
	// Media control: volume down
	KEY_VOLUMEDOWN = 114,
	// Media control: volume up
	KEY_VOLUMEUP = 115,
	// System control: power down
	KEY_POWER = 116,
	// Keyboard: keypad/numpad equals =
	KEY_KPEQUAL = 117,
	KEY_KPPLUSMINUS = 118,
	// Keyboard: pause
	KEY_PAUSE = 119,
	// Application launch: Compiz: scale: expose
	KEY_SCALE = 120,

	KEY_KPCOMMA = 121,
	// (Same as `KEY_HANGUEL`)
	KEY_HANGEUL = 122,
	// (Same as `KEY_HANGEUL`)
	KEY_HANGUEL = 122,
	KEY_HANJA = 123,
	KEY_YEN = 124,
	// Keyboard: left Windows, left command, or left super
	KEY_LEFTMETA = 125,
	// Keyboard: right Windows, right command, or right super
	KEY_RIGHTMETA = 126,
	KEY_COMPOSE = 127,

	// Application control: stop
	KEY_STOP = 128,
	KEY_AGAIN = 129,
	// Application control: properties
	KEY_PROPS = 130,
	// Application control: undo
	KEY_UNDO = 131,
	KEY_FRONT = 132,
	// Application control: copy
	KEY_COPY = 133,
	// Application control: open
	KEY_OPEN = 134,
	// Application control: paste
	KEY_PASTE = 135,
	// Application control: search
	KEY_FIND = 136,
	// Application control: cut
	KEY_CUT = 137,
	// Application launch: integrated help center
	KEY_HELP = 138,
	// Menu (show menu)
	KEY_MENU = 139,
	// Application launch: calculator
	KEY_CALC = 140,
	KEY_SETUP = 141,
	// System control: sleep
	KEY_SLEEP = 142,
	// System control: wake up
	KEY_WAKEUP = 143,
	// Application launch: file browser
	KEY_FILE = 144,
	KEY_SENDFILE = 145,
	KEY_DELETEFILE = 146,
	KEY_XFER = 147,
	KEY_PROG1 = 148,
	KEY_PROG2 = 149,
	// Application launch: internet browser
	KEY_WWW = 150,
	KEY_MSDOS = 151,
	// Application launch: lock or screensaver (same as `KEY_COFFEE`)
	KEY_SCREENLOCK = 152,
	// Application launch: lock or screensaver (same as `KEY_SCREENLOCK`)
	KEY_COFFEE = 152,
	// Rotate the display orientation (same as `KEY_DIRECTION`)
	KEY_ROTATE_DISPLAY = 153,
	// Rotate the display orientation (same as `KEY_ROTATE_DISPLAY`)
	KEY_DIRECTION = 153,
	KEY_CYCLEWINDOWS = 154,
	KEY_MAIL = 155,
	// Application control: bookmarks
	KEY_BOOKMARKS = 156,
	KEY_COMPUTER = 157,
	// Application control: back
	KEY_BACK = 158,
	// Application control: forward
	KEY_FORWARD = 159,
	KEY_CLOSECD = 160,
	KEY_EJECTCD = 161,
	KEY_EJECTCLOSECD = 162,
	// Media control: next song
	KEY_NEXTSONG = 163,
	// Media control: play or pause song
	KEY_PLAYPAUSE = 164,
	// Media control: previous song
	KEY_PREVIOUSSONG = 165,
	KEY_STOPCD = 166,
	KEY_RECORD = 167,
	KEY_REWIND = 168,
	// Media select: telephone
	KEY_PHONE = 169,
	KEY_ISO = 170,
	// Application launch: consumer control configuration
	KEY_CONFIG = 171,
	// Application control: home
	KEY_HOMEPAGE = 172,
	// Application control: refresh
	KEY_REFRESH = 173,
	// Application control: exit
	KEY_EXIT = 174,
	KEY_MOVE = 175,
	KEY_EDIT = 176,
	KEY_SCROLLUP = 177,
	KEY_SCROLLDOWN = 178,
	// Keyboard: left parenthesis (
	KEY_KPLEFTPAREN = 179,
	// Keyboard: right parenthesis )
	KEY_KPRIGHTPAREN = 180,
	// Application control: new
	KEY_NEW = 181,
	// Application control: redo or repeat
	KEY_REDO = 182,

	KEY_F13 = 183,
	KEY_F14 = 184,
	KEY_F15 = 185,
	KEY_F16 = 186,
	KEY_F17 = 187,
	KEY_F18 = 188,
	KEY_F19 = 189,
	KEY_F20 = 190,
	KEY_F21 = 191,
	KEY_F22 = 192,
	KEY_F23 = 193,
	KEY_F24 = 194,

	KEY_PLAYCD = 200,
	KEY_PAUSECD = 201,
	KEY_PROG3 = 202,
	KEY_PROG4 = 203,
	// Application control: desktop show all applications (same as
	// `KEY_DASHBOARD`)
	KEY_ALL_APPLICATIONS = 204,
	// Application control: desktop show all applications (same as
	// `KEY_ALL_APPLICATIONS`)
	KEY_DASHBOARD = 204,

	KEY_SUSPEND = 205,
	// Application control: close
	KEY_CLOSE = 206,
	KEY_PLAY = 207,
	KEY_FASTFORWARD = 208,
	KEY_BASSBOOST = 209,
	// Application control: print
	KEY_PRINT = 210,
	KEY_HP = 211,
	KEY_CAMERA = 212,
	KEY_SOUND = 213,
	KEY_QUESTION = 214,
	KEY_EMAIL = 215,
	KEY_CHAT = 216,
	KEY_SEARCH = 217,
	KEY_CONNECT = 218,
	// Application launch: checkbook or finance
	KEY_FINANCE = 219,
	KEY_SPORT = 220,
	KEY_SHOP = 221,
	KEY_ALTERASE = 222,
	// Application control: cancel
	KEY_CANCEL = 223,
	KEY_BRIGHTNESSDOWN = 224,
	KEY_BRIGHTNESSUP = 225,
	KEY_MEDIA = 226,

	// Cycle between available video outputs
	KEY_SWITCHVIDEOMODE = 227,
	KEY_KBDILLUMTOGGLE = 228,
	KEY_KBDILLUMDOWN = 229,
	KEY_KBDILLUMUP = 230,

	// Application control: send
	KEY_SEND = 231,
	// Application control: reply
	KEY_REPLY = 232,
	// Application control: forward message
	KEY_FORWARDMAIL = 233,
	// Application control: save
	KEY_SAVE = 234,
	KEY_DOCUMENTS = 235,

	KEY_BATTERY = 236,

	KEY_BLUETOOTH = 237,
	KEY_WLAN = 238,
	KEY_UWB = 239,

	KEY_UNKNOWN = 240,

	// Drive next video source
	KEY_VIDEO_NEXT = 241,
	// Drive previous video source
	KEY_VIDEO_PREV = 242,
	// Brightness up, after max is min
	KEY_BRIGHTNESS_CYCLE = 243,
	// Set auto-brightness on instead of manual-brightness, relying on ambient
	// light (same as `KEY_BRIGHTNESS_ZERO`)
	KEY_BRIGHTNESS_AUTO = 244,
	// Set auto-brightness on instead of manual-brightness, relying on ambient
	// light (same as `KEY_BRIGHTNESS_AUTO`)
	KEY_BRIGHTNESS_ZERO = 244,
	// Display device to off state
	KEY_DISPLAY_OFF = 245,

	// Wireless WAN: LTE, UMTS, GSM, etc. (same as `KEY_WIMAX`)
	KEY_WWAN = 246,
	// Wireless WAN: LTE, UMTS, GSM, etc. (same as `KEY_WWAN`)
	KEY_WIMAX = 246,
	// Key that controls all radios
	KEY_RFKILL = 247,

	// Mute or unmute the microphone
	KEY_MICMUTE = 248,

	// Miscellaneous button 0 (same as `BTN_0`)
	BTN_MISC = 256,
	// Miscellaneous button 0 (same as `BTN_MISC`)
	BTN_0 = 256,
	// Miscellaneous button 1
	BTN_1 = 257,
	// Miscellaneous button 2
	BTN_2 = 258,
	// Miscellaneous button 3
	BTN_3 = 259,
	// Miscellaneous button 4
	BTN_4 = 260,
	// Miscellaneous button 5
	BTN_5 = 261,
	// Miscellaneous button 6
	BTN_6 = 262,
	// Miscellaneous button 7
	BTN_7 = 263,
	// Miscellaneous button 8
	BTN_8 = 264,
	// Miscellaneous button 9
	BTN_9 = 265,

	// Mouse button: left (same as `BTN_LEFT`)
	BTN_MOUSE = 272,
	// Mouse click button: left (same as `BTN_MOUSE`)
	BTN_LEFT = 272,
	// Mouse click button: right
	BTN_RIGHT = 273,
	// Mouse click button: middle
	BTN_MIDDLE = 274,
	// Mouse click button: side
	BTN_SIDE = 275,
	// Mouse click button: extra
	BTN_EXTRA = 276,
	// Mouse click button: forward
	BTN_FORWARD = 277,
	// Mouse click button: back
	BTN_BACK = 278,
	// Mouse click button: task
	BTN_TASK = 279,

	// (Same as `BTN_TRIGGER`)
	BTN_JOYSTICK = 288,
	// (Same as `BTN_JOYSTICK`)
	BTN_TRIGGER = 288,
	BTN_THUMB = 289,
	BTN_THUMB2 = 290,
	BTN_TOP = 291,
	BTN_TOP2 = 292,
	BTN_PINKIE = 293,
	BTN_BASE = 294,
	BTN_BASE2 = 295,
	BTN_BASE3 = 296,
	BTN_BASE4 = 297,
	BTN_BASE5 = 298,
	BTN_BASE6 = 299,
	BTN_DEAD = 303,

	// Gamepad button: A or south (same as `BTN_A` and `BTN_SOUTH`)
	BTN_GAMEPAD = 304,
	// Gamepad button: A or south (same as `BTN_A` and `BTN_GAMEPAD`)
	BTN_SOUTH = 304,
	// Gamepad button: A or south (same as `BTN_SOUTH` and `BTN_GAMEPAD`)
	BTN_A = 304,
	// Gamepad button: B or east (same as `BTN_B`)
	BTN_EAST = 305,
	// Gamepad button: B or east (same as `BTN_EAST`)
	BTN_B = 305,
	// Gamepad button: C
	BTN_C = 306,
	// Gamepad button: X or north (same as `BTN_X`)
	BTN_NORTH = 307,
	// Gamepad button: X or north (same as `BTN_NORTH`)
	BTN_X = 307,
	// Gamepad button: Y or west (same as `BTN_Y`)
	BTN_WEST = 308,
	// Gamepad button: Y or west (same as `BTN_WEST`)
	BTN_Y = 308,
	// Gamepad button: Z
	BTN_Z = 309,
	// Gamepad button: left trigger
	BTN_TL = 310,
	// Gamepad button: right trigger
	BTN_TR = 311,
	// Gamepad button: left bumper or left trigger 2
	BTN_TL2 = 312,
	// Gamepad button: right bumper or right trigger 2
	BTN_TR2 = 313,
	// Gamepad button: select
	BTN_SELECT = 314,
	// Gamepad button: start
	BTN_START = 315,
	// Gamepad button: mode
	BTN_MODE = 316,
	// Gamepad button: left thumbstick
	BTN_THUMBL = 317,
	// Gamepad button: right thumbstick
	BTN_THUMBR = 318,

	// Trackpad tool: pen (same as `BTN_TOOL_PEN`)
	BTN_DIGI = 320,
	// Trackpad tool: pen (same as `BTN_DIGI`)
	BTN_TOOL_PEN = 320,
	// Trackpad tool: rubber
	BTN_TOOL_RUBBER = 321,
	// Trackpad tool: brush
	BTN_TOOL_BRUSH = 322,
	// Trackpad tool: pencil
	BTN_TOOL_PENCIL = 323,
	// Trackpad tool: airbrush
	BTN_TOOL_AIRBRUSH = 324,
	// Trackpad tool: finger
	BTN_TOOL_FINGER = 325,
	// Trackpad tool: mouse
	BTN_TOOL_MOUSE = 326,
	// Trackpad tool: lens
	BTN_TOOL_LENS = 327,
	// Trackpack: five fingers
	BTN_TOOL_QUINTTAP = 328,
	// Trackpad: stylus 3
	BTN_STYLUS3 = 329,
	// Trackpad: touch
	BTN_TOUCH = 330,
	// Trackpad: stylus 1
	BTN_STYLUS = 331,
	// Trackpad: stylus 2
	BTN_STYLUS2 = 332,
	// Trackpack: two fingers
	BTN_TOOL_DOUBLETAP = 333,
	// Trackpack: three fingers
	BTN_TOOL_TRIPLETAP = 334,
	// Trackpack: four fingers
	BTN_TOOL_QUADTAP = 335,

	// (Same as `BTN_GEAR_DOWN`)
	BTN_WHEEL = 336,
	// (Same as `BTN_WHEEL`)
	BTN_GEAR_DOWN = 336,
	BTN_GEAR_UP = 337,

	KEY_OK = 352,
	KEY_SELECT = 353,
	KEY_GOTO = 354,
	KEY_CLEAR = 355,
	KEY_POWER2 = 356,
	KEY_OPTION = 357,
	// Application launch: OEM features, tips, or tutorial
	KEY_INFO = 358,
	KEY_TIME = 359,
	KEY_VENDOR = 360,
	KEY_ARCHIVE = 361,
	// Media select: program guide
	KEY_PROGRAM = 362,
	KEY_CHANNEL = 363,
	KEY_FAVORITES = 364,
	KEY_EPG = 365,
	// Media select: home
	KEY_PVR = 366,
	KEY_MHP = 367,
	KEY_LANGUAGE = 368,
	KEY_TITLE = 369,
	KEY_SUBTITLE = 370,
	KEY_ANGLE = 371,
	// Application control: view toggle (same as `KEY_ZOOM`)
	KEY_FULL_SCREEN = 372,
	// Application control: view toggle (same as `KEY_FULL_SCREEN`)
	KEY_ZOOM = 372,
	KEY_MODE = 373,
	KEY_KEYBOARD = 374,
	// (Same as `KEY_SCREEN`)
	KEY_ASPECT_RATIO = 375,
	// (Same as `KEY_ASPECT_RATIO`)
	KEY_SCREEN = 375,
	// Media select: computer
	KEY_PC = 376,
	// Media select: TV
	KEY_TV = 377,
	// Media select: cable
	KEY_TV2 = 378,
	// Media select: VCR
	KEY_VCR = 379,
	// VCR Plus
	KEY_VCR2 = 380,
	// Media select: Satellite
	KEY_SAT = 381,
	KEY_SAT2 = 382,
	// Media select: CD
	KEY_CD = 383,
	// Media select: tape
	KEY_TAPE = 384,
	KEY_RADIO = 385,
	// Media select: tuner
	KEY_TUNER = 386,
	KEY_PLAYER = 387,
	KEY_TEXT = 388,
	// Media select: DVD
	KEY_DVD = 389,
	KEY_AUX = 390,
	KEY_MP3 = 391,
	// Application launch: audio browser
	KEY_AUDIO = 392,
	// Application launch: movie browser
	KEY_VIDEO = 393,
	KEY_DIRECTORY = 394,
	KEY_LIST = 395,
	// Media select: messages
	KEY_MEMO = 396,
	KEY_CALENDAR = 397,
	KEY_RED = 398,
	KEY_GREEN = 399,
	KEY_YELLOW = 400,
	KEY_BLUE = 401,
	// Channel increment
	KEY_CHANNELUP = 402,
	// Channel decrement
	KEY_CHANNELDOWN = 403,
	KEY_FIRST = 404,
	// Recall last
	KEY_LAST = 405,
	KEY_AB = 406,
	KEY_NEXT = 407,
	KEY_RESTART = 408,
	KEY_SLOW = 409,
	KEY_SHUFFLE = 410,
	KEY_BREAK = 411,
	KEY_PREVIOUS = 412,
	KEY_DIGITS = 413,
	KEY_TEEN = 414,
	KEY_TWEN = 415,
	// Media select: Video Phone
	KEY_VIDEOPHONE = 416,
	// Media select: Games
	KEY_GAMES = 417,
	// Application control: Zoom In
	KEY_ZOOMIN = 418,
	// Application control: Zoom Out
	KEY_ZOOMOUT = 419,
	// Application control: Zoom
	KEY_ZOOMRESET = 420,
	// Application launch: word processor
	KEY_WORDPROCESSOR = 421,
	// Application launch: text editor
	KEY_EDITOR = 422,
	// Application launch: spreadsheet
	KEY_SPREADSHEET = 423,
	// Application launch: graphics editor
	KEY_GRAPHICSEDITOR = 424,
	// Application launch: presentation app
	KEY_PRESENTATION = 425,
	// Application launch: database app
	KEY_DATABASE = 426,
	// Application launch: newsreader
	KEY_NEWS = 427,
	// Application launch: voicemail
	KEY_VOICEMAIL = 428,
	// Application launch: contacts or address book
	KEY_ADDRESSBOOK = 429,
	// Application launch: instant messaging
	KEY_MESSENGER = 430,
	// Turn display on and off (same as `KEY_BRIGHTNESS_TOGGLE`)
	KEY_DISPLAYTOGGLE = 431,
	// Turn display on and off (same as `KEY_DISPLAYTOGGLE`)
	KEY_BRIGHTNESS_TOGGLE = 431,
	// Application launch: spell check
	KEY_SPELLCHECK = 432,
	// Application launch: log off
	KEY_LOGOFF = 433,

	// Currency: dollar
	KEY_DOLLAR = 434,
	// Currency: euro
	KEY_EURO = 435,

	// Consumer - transport controls
	KEY_FRAMEBACK = 436,
	KEY_FRAMEFORWARD = 437,
	// GenDesc - system context menu
	KEY_CONTEXT_MENU = 438,
	// Consumer - transport control
	KEY_MEDIA_REPEAT = 439,
	// 10 channels up
	KEY_10CHANNELSUP = 440,
	// 10 channels down
	KEY_10CHANNELSDOWN = 441,
	// Application launch: image browser
	KEY_IMAGES = 442,
	// Show or hide the notification center
	KEY_NOTIFICATION_CENTER = 444,
	// Answer incoming call
	KEY_PICKUP_PHONE = 445,
	// Decline incoming call
	KEY_HANGUP_PHONE = 446,

	KEY_DEL_EOL = 448,
	KEY_DEL_EOS = 449,
	KEY_INS_LINE = 450,
	KEY_DEL_LINE = 451,

	KEY_FN = 464,
	KEY_FN_ESC = 465,
	KEY_FN_F1 = 466,
	KEY_FN_F2 = 467,
	KEY_FN_F3 = 468,
	KEY_FN_F4 = 469,
	KEY_FN_F5 = 470,
	KEY_FN_F6 = 471,
	KEY_FN_F7 = 472,
	KEY_FN_F8 = 473,
	KEY_FN_F9 = 474,
	KEY_FN_F10 = 475,
	KEY_FN_F11 = 476,
	KEY_FN_F12 = 477,
	KEY_FN_1 = 478,
	KEY_FN_2 = 479,
	KEY_FN_D = 480,
	KEY_FN_E = 481,
	KEY_FN_F = 482,
	KEY_FN_S = 483,
	KEY_FN_B = 484,
	KEY_FN_RIGHT_SHIFT = 485,

	KEY_BRL_DOT1 = 497,
	KEY_BRL_DOT2 = 498,
	KEY_BRL_DOT3 = 499,
	KEY_BRL_DOT4 = 500,
	KEY_BRL_DOT5 = 501,
	KEY_BRL_DOT6 = 502,
	KEY_BRL_DOT7 = 503,
	KEY_BRL_DOT8 = 504,
	KEY_BRL_DOT9 = 505,
	KEY_BRL_DOT10 = 506,

	// Keypad 0, used by phones and remote controls
	KEY_NUMERIC_0 = 512,
	// Keypad 1, used by phones and remote controls
	KEY_NUMERIC_1 = 513,
	// Keypad 2, used by phones and remote controls
	KEY_NUMERIC_2 = 514,
	// Keypad 3, used by phones and remote controls
	KEY_NUMERIC_3 = 515,
	// Keypad 4, used by phones and remote controls
	KEY_NUMERIC_4 = 516,
	// Keypad 5, used by phones and remote controls
	KEY_NUMERIC_5 = 517,
	// Keypad 6, used by phones and remote controls
	KEY_NUMERIC_6 = 518,
	// Keypad 7, used by phones and remote controls
	KEY_NUMERIC_7 = 519,
	// Keypad 8, used by phones and remote controls
	KEY_NUMERIC_8 = 520,
	// Keypad 9, used by phones and remote controls
	KEY_NUMERIC_9 = 521,
	// Keypad star, used by phones and remote controls
	KEY_NUMERIC_STAR = 522,
	// Keypad pound, used by phones and remote controls
	KEY_NUMERIC_POUND = 523,
	// Keypad A, used by phones and remote controls
	KEY_NUMERIC_A = 524,
	// Keypad B, used by phones and remote controls
	KEY_NUMERIC_B = 525,
	// Keypad C, used by phones and remote controls
	KEY_NUMERIC_C = 526,
	// Keypad D, used by phones and remote controls
	KEY_NUMERIC_D = 527,

	KEY_CAMERA_FOCUS = 528,
	// Wi-Fi protected setup
	KEY_WPS_BUTTON = 529,

	// Request switch touchpad on or off
	KEY_TOUCHPAD_TOGGLE = 530,
	KEY_TOUCHPAD_ON = 531,
	KEY_TOUCHPAD_OFF = 532,

	KEY_CAMERA_ZOOMIN = 533,
	KEY_CAMERA_ZOOMOUT = 534,
	KEY_CAMERA_UP = 535,
	KEY_CAMERA_DOWN = 536,
	KEY_CAMERA_LEFT = 537,
	KEY_CAMERA_RIGHT = 538,

	// Attendant call on
	KEY_ATTENDANT_ON = 539,
	// Attendant call off
	KEY_ATTENDANT_OFF = 540,
	// Attendant call on or off
	KEY_ATTENDANT_TOGGLE = 541,
	// Reading light on or off
	KEY_LIGHTS_TOGGLE = 542,

	BTN_DPAD_UP = 544,
	BTN_DPAD_DOWN = 545,
	BTN_DPAD_LEFT = 546,
	BTN_DPAD_RIGHT = 547,

	// Ambient light sensor
	KEY_ALS_TOGGLE = 560,
	// Display rotation lock
	KEY_ROTATE_LOCK_TOGGLE = 561,
	// Display refresh rate toggle
	KEY_REFRESH_RATE_TOGGLE = 562,

	// Application launch: button configuration
	KEY_BUTTONCONFIG = 576,
	// Application launch: task or project manager
	KEY_TASKMANAGER = 577,
	// Application launch: log, journal, or timecard
	KEY_JOURNAL = 578,
	// Application launch: control panel
	KEY_CONTROLPANEL = 579,
	// Application launch: select task or application
	KEY_APPSELECT = 580,
	// Application launch: screen saver
	KEY_SCREENSAVER = 581,
	// Listening voice command
	KEY_VOICECOMMAND = 582,
	// Application launch: context-aware desktop assistant
	KEY_ASSISTANT = 583,
	// Application control: next keyboard layout select
	KEY_KBD_LAYOUT_NEXT = 584,
	// Show or hide the emoji picker
	KEY_EMOJI_PICKER = 585,
	// Start or stop voice dictation session
	KEY_DICTATE = 586,
	// Enable programmatic access to camera devices
	KEY_CAMERA_ACCESS_ENABLE = 587,
	// Disable programmatic access to camera devices
	KEY_CAMERA_ACCESS_DISABLE = 588,
	// Toggle the current state of the camera access control
	KEY_CAMERA_ACCESS_TOGGLE = 589,
	// Toggle the system accessibility UI or command
	KEY_ACCESSIBILITY = 590,
	// Toggle the system-wide "Do Not Disturb" control
	KEY_DO_NOT_DISTURB = 591,

	// Set brightness to minimum
	KEY_BRIGHTNESS_MIN = 592,
	// Set brightness to maximum
	KEY_BRIGHTNESS_MAX = 593,

	// Keyboard input assist: prev
	KEY_KBDINPUTASSIST_PREV = 608,
	// Keyboard input assist: next
	KEY_KBDINPUTASSIST_NEXT = 609,
	// Keyboard input assist: previous group
	KEY_KBDINPUTASSIST_PREVGROUP = 610,
	// Keyboard input assist: next group
	KEY_KBDINPUTASSIST_NEXTGROUP = 611,
	// Keyboard input assist: accept
	KEY_KBDINPUTASSIST_ACCEPT = 612,
	// Keyboard input assist: cancel
	KEY_KBDINPUTASSIST_CANCEL = 613,

	// Diagonal movement key: right up
	KEY_RIGHT_UP = 614,
	// Diagonal movement key: right down
	KEY_RIGHT_DOWN = 615,
	// Diagonal movement key: left up
	KEY_LEFT_UP = 616,
	// Diagonal movement key: left down
	KEY_LEFT_DOWN = 617,

	// Show device's root menu
	KEY_ROOT_MENU = 618,

	// Show top menu of the media (for example, a DVD menu)
	KEY_MEDIA_TOP_MENU = 619,
	// Keypad 11, used by phones and remote controls
	KEY_NUMERIC_11 = 620,
	// Keypad 12, used by phones and remote controls
	KEY_NUMERIC_12 = 621,

	// Toggle audio description, which is used to describe actions in a program
	// for the visually impaired
	KEY_AUDIO_DESC = 622,
	KEY_3D_MODE = 623,
	KEY_NEXT_FAVORITE = 624,
	KEY_STOP_RECORD = 625,
	KEY_PAUSE_RECORD = 626,
	// Video on demand
	KEY_VOD = 627,
	KEY_UNMUTE = 628,
	KEY_FASTREVERSE = 629,
	KEY_SLOWREVERSE = 630,

	// Control a data application associated with the currently viewed channel
	// (for example, a teletext or data broadcast application (MHEG, MHP,
	// HbbTV, etc.))
	KEY_DATA = 631,

	// Toggle on-screen keyboard
	KEY_ONSCREEN_KEYBOARD = 632,

	// Electronic privacy screen control
	KEY_PRIVACY_SCREEN_TOGGLE = 633,

	// Select an area of the screen to be copied
	KEY_SELECTIVE_SCREENSHOT = 634,

	// Move the focus to the next user-controllable element within a UI
	// container
	KEY_NEXT_ELEMENT = 635,
	// Move the focus to the previous user-controllable element within a UI
	// container
	KEY_PREVIOUS_ELEMENT = 636,

	// Toggle autopilot engagement
	KEY_AUTOPILOT_ENGAGE_TOGGLE = 637,

	// Shortcut key: mark waypoint
	KEY_MARK_WAYPOINT = 638,
	// Shortcut key: SOS
	KEY_SOS = 639,
	// Shortcut key: navigation chart
	KEY_NAV_CHART = 640,
	// Shortcut key: fishing chart
	KEY_FISHING_CHART = 641,
	// Shortcut key: single range radar
	KEY_SINGLE_RANGE_RADAR = 642,
	// Shortcut key: dual range radar
	KEY_DUAL_RANGE_RADAR = 643,
	// Shortcut key: radar overlay
	KEY_RADAR_OVERLAY = 644,
	// Shortcut key: traditional sonar
	KEY_TRADITIONAL_SONAR = 645,
	// Shortcut key: ClearVü sonar
	KEY_CLEARVU_SONAR = 646,
	// Shortcut key: SideVü sonar
	KEY_SIDEVU_SONAR = 647,
	// Shortcut key: navigation info
	KEY_NAV_INFO = 648,
	// Shortcut key: brightness menu
	KEY_BRIGHTNESS_MENU = 649,

	// Macro key 1
	KEY_MACRO1 = 656,
	// Macro key 2
	KEY_MACRO2 = 657,
	// Macro key 3
	KEY_MACRO3 = 658,
	// Macro key 4
	KEY_MACRO4 = 659,
	// Macro key 5
	KEY_MACRO5 = 660,
	// Macro key 6
	KEY_MACRO6 = 661,
	// Macro key 7
	KEY_MACRO7 = 662,
	// Macro key 8
	KEY_MACRO8 = 663,
	// Macro key 9
	KEY_MACRO9 = 664,
	// Macro key 10
	KEY_MACRO10 = 665,
	// Macro key 11
	KEY_MACRO11 = 666,
	// Macro key 12
	KEY_MACRO12 = 667,
	// Macro key 13
	KEY_MACRO13 = 668,
	// Macro key 14
	KEY_MACRO14 = 669,
	// Macro key 15
	KEY_MACRO15 = 670,
	// Macro key 16
	KEY_MACRO16 = 671,
	// Macro key 17
	KEY_MACRO17 = 672,
	// Macro key 18
	KEY_MACRO18 = 673,
	// Macro key 19
	KEY_MACRO19 = 674,
	// Macro key 20
	KEY_MACRO20 = 675,
	// Macro key 21
	KEY_MACRO21 = 676,
	// Macro key 22
	KEY_MACRO22 = 677,
	// Macro key 23
	KEY_MACRO23 = 678,
	// Macro key 24
	KEY_MACRO24 = 679,
	// Macro key 25
	KEY_MACRO25 = 680,
	// Macro key 26
	KEY_MACRO26 = 681,
	// Macro key 27
	KEY_MACRO27 = 682,
	// Macro key 28
	KEY_MACRO28 = 683,
	// Macro key 29
	KEY_MACRO29 = 684,
	// Macro key 30
	KEY_MACRO30 = 685,

	// Start recording a macro (it will also occur at the end if
	// `KEY_MACRO_RECORD_STOP` is not advertised)
	KEY_MACRO_RECORD_START = 688,
	// Stop recording a macro (it will only occur at the end if it is
	// advertised, otherwise `KEY_MACRO_RECORD_START` will occur)
	KEY_MACRO_RECORD_STOP = 689,
	// Cylce through configured macro presets
	KEY_MACRO_PRESET_CYCLE = 690,
	// Directly select macro preset 1
	KEY_MACRO_PRESET1 = 691,
	// Directly select macro preset 2
	KEY_MACRO_PRESET2 = 692,
	// Directly select macro preset 3
	KEY_MACRO_PRESET3 = 693,

	// LCD menu control: button 1
	KEY_KBD_LCD_MENU1 = 696,
	// LCD menu control: button 2
	KEY_KBD_LCD_MENU2 = 697,
	// LCD menu control: button 3
	KEY_KBD_LCD_MENU3 = 698,
	// LCD menu control: button 4
	KEY_KBD_LCD_MENU4 = 699,
	// LCD menu control: button 5
	KEY_KBD_LCD_MENU5 = 700,

	// (Same as `BTN_TRIGGER_HAPPY1`)
	BTN_TRIGGER_HAPPY = 704,
	// (Same as `BTN_TRIGGER_HAPPY`)
	BTN_TRIGGER_HAPPY1 = 704,
	BTN_TRIGGER_HAPPY2 = 705,
	BTN_TRIGGER_HAPPY3 = 706,
	BTN_TRIGGER_HAPPY4 = 707,
	BTN_TRIGGER_HAPPY5 = 708,
	BTN_TRIGGER_HAPPY6 = 709,
	BTN_TRIGGER_HAPPY7 = 710,
	BTN_TRIGGER_HAPPY8 = 711,
	BTN_TRIGGER_HAPPY9 = 712,
	BTN_TRIGGER_HAPPY10 = 713,
	BTN_TRIGGER_HAPPY11 = 714,
	BTN_TRIGGER_HAPPY12 = 715,
	BTN_TRIGGER_HAPPY13 = 716,
	BTN_TRIGGER_HAPPY14 = 717,
	BTN_TRIGGER_HAPPY15 = 718,
	BTN_TRIGGER_HAPPY16 = 719,
	BTN_TRIGGER_HAPPY17 = 720,
	BTN_TRIGGER_HAPPY18 = 721,
	BTN_TRIGGER_HAPPY19 = 722,
	BTN_TRIGGER_HAPPY20 = 723,
	BTN_TRIGGER_HAPPY21 = 724,
	BTN_TRIGGER_HAPPY22 = 725,
	BTN_TRIGGER_HAPPY23 = 726,
	BTN_TRIGGER_HAPPY24 = 727,
	BTN_TRIGGER_HAPPY25 = 728,
	BTN_TRIGGER_HAPPY26 = 729,
	BTN_TRIGGER_HAPPY27 = 730,
	BTN_TRIGGER_HAPPY28 = 731,
	BTN_TRIGGER_HAPPY29 = 732,
	BTN_TRIGGER_HAPPY30 = 733,
	BTN_TRIGGER_HAPPY31 = 734,
	BTN_TRIGGER_HAPPY32 = 735,
	BTN_TRIGGER_HAPPY33 = 736,
	BTN_TRIGGER_HAPPY34 = 737,
	BTN_TRIGGER_HAPPY35 = 738,
	BTN_TRIGGER_HAPPY36 = 739,
	BTN_TRIGGER_HAPPY37 = 740,
	BTN_TRIGGER_HAPPY38 = 741,
	BTN_TRIGGER_HAPPY39 = 742,
	BTN_TRIGGER_HAPPY40 = 743,

	KEY_MAX = 767,
	KEY_CNT = 768,
};


const char *to_string(Key key);


} // namespace frac
