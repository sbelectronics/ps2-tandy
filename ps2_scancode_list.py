F1=chr(201)
F2=chr(202)
F3=chr(203)
F4=chr(204)
F5=chr(205)
F6=chr(206)
F7=chr(207)
F8=chr(208)
F9=chr(209)
F10=chr(210)
F11=chr(211)
F12=chr(212)

CAPSLOCK=chr(213)
LCTRL=chr(214)
RCTRL=chr(215)
LALT=chr(216)
RALT=chr(217)
LSHIFT=chr(218)
RSHIFT=chr(219)
SCROLL=chr(220)
NUM=chr(221)
INS=chr(222)
DEL=chr(223)
UARR=chr(224)
DARR=chr(225)
LARR=chr(226)
RARR=chr(227)
HOME=chr(228)
PGUP=chr(229)
PGDN=chr(230)
END=chr(231)
LGUI=chr(232)
RGUI=chr(233)
APPS=chr(234)
BREAK=chr(235)
BREAKRELEASE=chr(236)
CTRLBREAK=chr(237)
CTRLBREAKRELEASE=chr(238)
PRINTSCR=chr(239)

KP0=chr(240)
KP1=chr(241)
KP2=chr(242)
KP3=chr(243)
KP4=chr(244)
KP5=chr(245)
KP6=chr(246)
KP7=chr(247)
KP8=chr(248)
KP9=chr(249)
KPDOT=chr(250)
KPENTER=chr(251)
HOLD=chr(252)


BS=chr(8)
TAB=chr(9)
ENTER=chr(13)
ESC=chr(27)
SQUOTE="'"
BACKSLASH="\\"
BACKQUOTE='`'
SPACE=' '

ps2_codes=[
  (0x16, '1', '!'),
  (0x1e, '2', '@'),
  (0x26, '3', '#'),
  (0x25, '4', '$'),
  (0x2e, '5', '%'),
  (0x29, ' ', ' '),
  (0x36, '6', '^'),
  (0x3d, '7', '&'),
  (0x3e, '8', '*'),
  (0x46, '9', '('),
  (0x45, '0', ')'),
  (0x4e, '-', '_'),
  (0x55, '=', '+'),
  (0x66, BS, BS),
  (0xd, TAB, TAB),
  (0x15, 'q', 'Q'),
  (0x1d, 'w', 'W'),
  (0x24, 'e', 'E'),
  (0x2d, 'r', 'R'),
  (0x2c, 't', 'T'),
  (0x35, 'y', 'Y'),
  (0x3c, 'u', 'U'),
  (0x43, 'i', 'I'),
  (0x44, 'o', 'O'),
  (0x4d, 'p', 'P'),
  (0x54, '[', '{'),
  (0x5b, ']', '}'),
  (0x5a, ENTER, ENTER),
  (0x1c, 'a', 'A'),
  (0x1b, 's', 'S'),
  (0x23, 'd', 'D'),
  (0x2b, 'f', 'F'),
  (0x34, 'g', 'G'),
  (0x33, 'h', 'H'),
  (0x3b, 'j', 'J'),
  (0x42, 'k', 'K'),
  (0x4b, 'l', 'L'),
  (0x4c, ';', ':'),
  (0x52, SQUOTE, '"'),
  (0xe, '`', '~'),
  (0x5d, BACKSLASH, '|'),
  (0x1a, 'z', 'Z'),
  (0x22, 'x', 'X'),
  (0x21, 'c', 'C'),
  (0x2a, 'v', 'V'),
  (0x32, 'b', 'B'),
  (0x31, 'n', 'N'),
  (0x3a, 'm', 'M'),
  (0x41, ',', '<'),
  (0x49, '.', '>'),
  (0x4a, '/', '?'),

  (0x45, BREAK, BREAK),  # break when ctrl not held down
  (0xC5, BREAKRELEASE, BREAKRELEASE),  # break when ctrl not held down

  (0x76, ESC, ESC),
  (0x14, LCTRL, LCTRL),
  (0x11, LALT, LALT),
  (0x12, LSHIFT, LSHIFT),
  (0x59, RSHIFT, RSHIFT),
  (0x77, NUM, NUM),
  (0x7E, SCROLL, SCROLL),
  (0x58, CAPSLOCK, CAPSLOCK),

  (0x05, F1, F1),
  (0x06, F2, F2),
  (0x04, F3, F3),
  (0x0C, F4, F4),
  (0x03, F5, F5),
  (0x0B, F6, F6),
  (0x83, F7, F7),
  (0x0A, F8, F8),
  (0x01, F9, F9),
  (0x09, F10, F10),
  (0x78, F11, F11),
  (0x07, F12, F12),

  (0x69, KP1, KP1),
  (0x6B, KP4, KP4),
  (0x6C, KP7, KP7),
  (0x70, KP0, KP0),
  (0x71, KPDOT, KPDOT),
  (0x72, KP2, KP2),
  (0x73, KP5, KP5),
  (0x74, KP6, KP6),
  (0x75, KP8, KP8),
  (0x79, '+', '+'),
  (0x7A, KP3, KP3),
  (0x7B, '-', '-'),
  (0x7C, '*', '*'),
  (0x7D, KP9, KP9),  

#  (0x69, '1', '1'),
#  (0x6B, '4', '4'),
#  (0x6C, '7', '7'),
#  (0x70, '0', '0'),
#  (0x71, '.', '.'),
#  (0x72, '2', '2'),
#  (0x73, '5', '5'),
#  (0x74, '6', '6'),
#  (0x75, '8', '8'),
#  (0x79, '+', '+'),
#  (0x7A, '3', '3'),
#  (0x7B, '-', '-'),
#  (0x7C, '*', '*'),
#  (0x7D, '9', '9'),
]

ps2_extended_codes=[
  (0x11, RALT, RALT),   # EXTENDED
  (0x14, RCTRL, RCTRL), # EXTENDED
  (0x1F, LGUI, LGUI),   # EXTENDED
  (0x27, RGUI, RGUI),   # EXTENDED
  (0x2F, APPS, APPS),   # EXTENDED 
  (0x4A, '/', '/'),     # EXTENDED - keypad
  (0x55, PGUP, PGUP),   # EXTENDED
  (0x5A, KPENTER, KPENTER), # EXTENDED - keypad
  (0x69, END, END),     # EXTENDED
  (0x6B, LARR, LARR),   # EXTENDED
  (0x6C, HOME, HOME),   # EXTENDED
  (0x70, INS, INS),     # EXTENDED
  (0x71, DEL, DEL),     # EXTENDED
  (0x72, DARR, DARR),   # EXTENDED
  (0x74, RARR, RARR),   # EXTENDED
  (0x75, UARR, UARR),   # EXTENDED
  (0x7A, PGDN, PGDN),   # EXTENDED  
  (0x7D, PGUP, PGUP),   # EXTENDED  
  (0x7E, CTRLBREAK, CTRLBREAK),  # EXTENDED 
]
