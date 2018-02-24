a = """{"SHIT", "FUCK", "CUNT", "CUCK", "NIGGER", "NIGGA", "ASS", "DICK", 
  "NUDES", "NUDE", "NOODS", "NOOD", "NOODES", "COCK", "BITCH", "FAGGOT", "GIL", "SEX", 
  "BOOB", "PENIS", "VAGINA", "PUSSY", "PU$$Y", "N00D", "N00DS", "WHORE", "SLUT", "DYKE", "NIBBA"
  "SHREK", "SHREKT", "SHREKED", "BASTARD", "PISS", "SUCK", "SUCC", "SUC", "DAMN", "TWAT"
  "ARSE", "ASSHOLE", "JERRY", "JESUS", "HELL", "BBC", "MILF", "GODDAMN", "BALLS", "BUTT", 
  "SHITTY", "KKK", "NUTS", "FUCKING", "GAY", "TRIGGERED", "STRIP", "STRIPPER", "PROSTITUTE",
  "PORN"}"""
b = a.replace("{","").replace("}","").translate(None, '\n').split(',')
c=[]
for i in range(0, len(b)):
	b[i].replace(',','')
	print ("const char s" + str(i) + "[] PROGMEM = " + b[i] + ";")
	c.append("s" + str(i) + ",")

print("const char* const black_list[] PROGMEM = {" + "".join(c)
 + "'\\0'};") 
