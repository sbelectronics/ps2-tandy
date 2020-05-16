# http://www.smbaker.com//
#
# Generates mapping of keyboard scancodes to midi notes and channels 

import sys
from ps2_scancode_list import *
from tandy_scancode_list import *


def find_ps2_code(i):
    for ps2_code in ps2_codes:
        if ps2_code[0]==i:
            return ps2_code
    return None


def find_ps2_extcode(i):
    for ps2_code in ps2_extended_codes:
        if ps2_code[0]==i:
            return ps2_code
    return None


def find_tandy_code(x):
    for tandy_code in tandy_codes:
        if tandy_code[1] == x:
            return tandy_code

    if (x == RALT):
        return find_tandy_code(LALT)

    if (x == RCTRL):
        return find_tandy_code(RALT)

    if (x == CTRLBREAK):
        return find_tandy_code(BREAK)

    if (x == BREAKRELEASE) or (x ==CTRLBREAKRELEASE):
        # Break is funny, it sends a 45/C5 or 46/C6.
        # I think the C5 and C6 are intended to be release codes.
        return find_tandy_code(BREAK) | 0x80

    return None


scancode_list = []
for i in range(0, 128):
    ps2_code = find_ps2_code(i)
    if not ps2_code:
        print >> sys.stderr, "Failed to find ps2 code for", i
        scancode_list.append(0x00)
        continue

    tandy_code = find_tandy_code(ps2_code[1])
    if not tandy_code:
        tandy_code = find_tandy_code(ps2_code[2])
    if not tandy_code:
        print >> sys.stderr, "Failed to find tandy code for", ps2_code
        scancode_list.append(0x00)
        continue

    scancode_list.append(tandy_code[2])


extcode_list = []
for i in range(0, 128):
    ps2_code = find_ps2_extcode(i)
    if not ps2_code:
        print >> sys.stderr, "Failed to find ps2 extcode for", i
        extcode_list.append(0x00)
        continue

    tandy_code = find_tandy_code(ps2_code[1])
    if not tandy_code:
        tandy_code = find_tandy_code(ps2_code[2])
    if not tandy_code:
        print >> sys.stderr, "Failed to find tandy code for", ps2_code
        extcode_list.append(0x00)
        continue

    extcode_list.append(tandy_code[2])

 
print "const char scancode_map[128] PROGMEM = {%s};" % ",".join([str(x) for x in scancode_list])
print "const char extcode_map[128] PROGMEM = {%s};" % ",".join([str(x) for x in extcode_list]) 
