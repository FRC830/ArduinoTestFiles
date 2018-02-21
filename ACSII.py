#dec oct hex bin symbol html-number html-name description
from __future__ import print_function

s = """
0	000	00	00000000	NUL	&#000;	 	Null char
32	040	20	00100000	 	&#32;	 	Space
33	041	21	00100001	!	&#33;	 	Exclamation mark
34	042	22	00100010	"	&#34;	&quot;	Double quotes (or speech marks)
35	043	23	00100011	#	&#35;	 	Number
36	044	24	00100100	$	&#36;	 	Dollar
37	045	25	00100101	%	&#37;	 	Procenttecken
38	046	26	00100110	&	&#38;	&amp;	Ampersand
39	047	27	00100111	'	&#39;	 	Single quote
40	050	28	00101000	(	&#40;	 	Open parenthesis (or open bracket)
41	051	29	00101001	)	&#41;	 	Close parenthesis (or close bracket)
42	052	2A	00101010	*	&#42;	 	Asterisk
43	053	2B	00101011	+	&#43;	 	Plus
44	054	2C	00101100	,	&#44;	 	Comma
45	055	2D	00101101	-	&#45;	 	Hyphen
46	056	2E	00101110	.	&#46;	 	Period, dot or full stop
47	057	2F	00101111	/	&#47;	 	Slash or divide
48	060	30	00110000	0	&#48;	 	Zero
49	061	31	00110001	1	&#49;	 	One
50	062	32	00110010	2	&#50;	 	Two
51	063	33	00110011	3	&#51;	 	Three
52	064	34	00110100	4	&#52;	 	Four
53	065	35	00110101	5	&#53;	 	Five
54	066	36	00110110	6	&#54;	 	Six
55	067	37	00110111	7	&#55;	 	Seven
56	070	38	00111000	8	&#56;	 	Eight
57	071	39	00111001	9	&#57;	 	Nine
58	072	3A	00111010	:	&#58;	 	Colon
59	073	3B	00111011	;	&#59;	 	Semicolon
60	074	3C	00111100	<	&#60;	&lt;	Less than (or open angled bracket)
61	075	3D	00111101	=	&#61;	 	Equals
62	076	3E	00111110	>	&#62;	&gt;	Greater than (or close angled bracket)
63	077	3F	00111111	?	&#63;	 	Question mark
64	100	40	01000000	@	&#64;	 	At symbol
65	101	41	01000001	A	&#65;	 	Uppercase A
66	102	42	01000010	B	&#66;	 	Uppercase B
67	103	43	01000011	C	&#67;	 	Uppercase C
68	104	44	01000100	D	&#68;	 	Uppercase D
69	105	45	01000101	E	&#69;	 	Uppercase E
70	106	46	01000110	F	&#70;	 	Uppercase F
71	107	47	01000111	G	&#71;	 	Uppercase G
72	110	48	01001000	H	&#72;	 	Uppercase H
73	111	49	01001001	I	&#73;	 	Uppercase I
74	112	4A	01001010	J	&#74;	 	Uppercase J
75	113	4B	01001011	K	&#75;	 	Uppercase K
76	114	4C	01001100	L	&#76;	 	Uppercase L
77	115	4D	01001101	M	&#77;	 	Uppercase M
78	116	4E	01001110	N	&#78;	 	Uppercase N
79	117	4F	01001111	O	&#79;	 	Uppercase O
80	120	50	01010000	P	&#80;	 	Uppercase P
81	121	51	01010001	Q	&#81;	 	Uppercase Q
82	122	52	01010010	R	&#82;	 	Uppercase R
83	123	53	01010011	S	&#83;	 	Uppercase S
84	124	54	01010100	T	&#84;	 	Uppercase T
85	125	55	01010101	U	&#85;	 	Uppercase U
86	126	56	01010110	V	&#86;	 	Uppercase V
87	127	57	01010111	W	&#87;	 	Uppercase W
88	130	58	01011000	X	&#88;	 	Uppercase X
89	131	59	01011001	Y	&#89;	 	Uppercase Y
90	132	5A	01011010	Z	&#90;	 	
"""

cpp_array = """
{"SHIT", "FUCK", "CUNT", "CUCK", "NIGGER", "NIGGA", "ASS", "DICK", 
  "NUDES", "NUDE", "NOODS", "NOOD", "NOODES", "COCK", "BITCH", "FAGGOT", "GIL", "SEX", 
  "BOOB", "PENIS", "VAGINA", "PUSSY", "PU$$Y", "N00D", "N00DS", "WHORE", "SLUT", "DYKE", "NIBBA"
  "SHREK", "SHREKT", "SHREKED", "BASTARD", "PISS", "SUCK", "SUCC", "SUC", "DAMN", "TWAT"
  "ARSE", "ASSHOLE", "JERRY", "JESUS", "HELL", "BBC", "MILF", "GODDAMN", "BALLS", "BUTT", 
  "SHITTY", "KKK", "NUTS", "FUCKING", "GAY", "TRIGGERED", "STRIP", "STRIPPER", "PROSTITUTE"
  "PORN",   '\0'};
 """
#test_list = ["YIKES", "BAD", "LOSE", "SOMETHING"]
test_list = []
for i in range(0,len(cpp_array)):
	test_list = cpp_array.replace("{", "").replace("}","").replace(",","").replace('"',"")
	test_list = test_list.split(' ')
print (test_list, end="")	

print ("black_list = {")
for i in range (0,len(test_list)):
	print ('"',end="")
 	for j in range(0, len(test_list[i])):
		for line in s.split('\n'):
			if line:
				raw = line.split('\t')
				#print raw[4]
				#print test_list[i][j]
				if (test_list[i][j] == raw[4]):
					str_new = []
					str_new += test_list[i][j].replace(test_list[i][j], raw[2],1)
					print ("\\x" +(('').join(str_new)) , end="")
	print ('" ,')			

						#print str(test_list[i])















