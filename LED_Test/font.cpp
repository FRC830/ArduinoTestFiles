#include "font.h"

unsigned char_to_index(char c) {
  switch(c) {
    case '.': return 0; break;
    case 'A': return 1; break;
    case 'B': return 2; break;
    case 'C': return 3; break;
    case 'D': return 4; break;
    case 'E': return 5; break;
    case 'F': return 6; break;
    case 'G': return 7; break;
    case 'H': return 8; break;
    case 'I': return 9; break;
    case 'J': return 10; break;
    case 'K': return 11; break;
    case 'L': return 12; break;
    case 'M': return 13; break;
    case 'N': return 14; break;
    case 'O': return 15; break;
    case 'P': return 16; break;
    case 'Q': return 17; break;
    case 'R': return 18; break;
    case 'S': return 19; break;
    case 'T': return 20; break;
    case 'U': return 21; break;
    case 'V': return 22; break;
    case 'W': return 23; break;
    case 'X': return 24; break;
    case 'Y': return 25; break;
    case 'Z': return 26; break;
    case '0': return 27; break;
    case '1': return 28; break;
    case '2': return 29; break;
    case '3': return 30; break;
    case '4': return 31; break;
    case '5': return 32; break;
    case '6': return 33; break;
    case '7': return 34; break;
    case '8': return 35; break;
    case '9': return 36; break;
    case '!': return 37; break;
    default: return 0; break;
  }
}
const bool font[][5][3] PROGMEM = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // .
  {0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1}, // A
  {1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0}, // B
  {0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1}, // C
  {1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0}, // D
  {1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1}, // E
  {1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0}, // F
  {0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1}, // G
  {1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1}, // H
  {1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1}, // I
  {0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1}, // J
  {1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1}, // K
  {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1}, // L
  {1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1}, // M
  {1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1}, // N
  {1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1}, // O
  {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0}, // P
  {1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1}, // Q
  {1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1}, // R
  {0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0}, // S
  {1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0}, // T
  {1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1}, // U
  {1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0}, // V
  {1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1}, // W
  {1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1}, // X
  {1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0}, // Y
  {1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1}, // Z
  {0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0}, // 0
  {0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0}, // 1
  {0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1}, // 2
  {1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1}, // 3
  {1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1}, // 4
  {1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1}, // 5
  {1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1}, // 7
  {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1}, // 9
  {0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0}, // !
};
/*
.:
   
   
   
   
   
 
A:
 X 
X X
XXX
X X
X X
 
B:
XX 
X X
XX 
X X
XX 
 
C:
 XX
X  
X  
X  
 XX
 
D:
XX 
X X
X X
X X
XX 
 
E:
XXX
X  
XXX
X  
XXX
 
F:
XXX
X  
XXX
X  
X  
 
G:
 XX
X  
X X
X X
 XX
 
H:
X X
X X
XXX
X X
X X
 
I:
XXX
 X 
 X 
 X 
XXX
 
J:
  X
  X
  X
X X
XXX
 
K:
X X
X X
XX 
X X
X X
 
L:
X  
X  
X  
X  
XXX
 
M:
X X
XXX
X X
X X
X X
 
N:
XX 
X X
X X
X X
X X
 
O:
XXX
X X
X X
X X
XXX
 
P:
XXX
X X
XXX
X  
X  
 
Q:
XXX
X X
X X
XXX
  X
 
R:
XX 
X X
XX 
X X
X X
 
S:
 XX
X  
 X 
  X
XX 
 
T:
XXX
 X 
 X 
 X 
 X 
 
U:
X X
X X
X X
X X
XXX
 
V:
X X
X X
X X
X X
 X 
 
W:
X X
X X
X X
XXX
X X
 
X:
X X
X X
 X 
X X
X X
 
Y:
X X
X X
XXX
 X 
 X 
 
Z:
XXX
  X
 X 
X  
XXX
 
0:
 X 
X X
X X
X X
 X 
 
1:
 X 
XX 
 X 
 X 
 X 
 
2:
 XX
X X
  X
 X 
XXX
 
3:
XXX
  X
XXX
  X
XXX
 
4:
X X
X X
XXX
  X
  X
 
5:
XXX
X  
XXX
  X
XXX
 
6:
XXX
X  
XXX
X X
XXX
 
7:
XXX
  X
  X
  X
  X
 
8:
XXX
X X
XXX
X X
XXX
 
9:
XXX
X X
XXX
  X
XXX
 
!:
 X 
 X 
 X 
   
 X 
 
*/
 
