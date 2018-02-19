s='''
000000000000000 .
010101111101101 A
110101110101110 B
011100100100011 C
110101101101110 D
111100111100111 E
111100111100100 F
011100101101011 G
101101111101101 H
111010010010111 I
001001001101111 J
101101110101101 K
100100100100111 L
101111101101101 M
110101101101101 N
111101101101111 O
111101111100100 P
111101101111001 Q
110101110101101 R
011100010001110 S
111010010010010 T
101101101101111 U
101101101101010 V
101101101111101 W
101101010101101 X
101101111010010 Y
111001010100111 Z
010101101101010 0
010110010010010 1
011101001010111 2
111001111001111 3
101101111001001 4
111100111001111 5
111100111101111 6
111001001001001 7
111101111101111 8
111101111001111 9
010010010000010 !
000010111010000 *
001010100010001 <
100010001010100 >
000000111000000 -
'''

print ('#include "font.h"')
print('')
print('unsigned char_to_index(char c) {')
print('  switch(c) {')
i = 0
for line in s.split('\n'):
    if line:
        raw, letter = line.split(' ')
        print("    case '" + letter + "': return " + str(i) + "; break;")
        i += 1
print('    default: return 0; break;\n  }\n}')

print('const bool font[][5][3] PROGMEM = {')
for line in s.split('\n'):
    if line:
        raw, letter = line.split(' ')
        print('  {' + (', '.join(list(raw))) + '}, // ' + letter)
print('};')

print('/*')
for line in s.split('\n'):
    if line:
        raw, letter = line.split(' ')
        print(letter + ':')
        for i in range(0, 15, 3):
            print(line[i:i+3].replace('1', 'X').replace('0', ' '))
        print(' ')
print('*/')
