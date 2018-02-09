from PIL import Image
import sys

im = Image.open(sys.argv[1])
px = im.load()


width, height = im.size
print ('#include <Arduino.h>')
print ('#include "image-gen.h"')

print ("const byte pxl[][13][3] PROGMEM = { ")
for x in range(0,23):
	print ('{ ')
	for y in range(0,13):
		if (x < width and y < height):
			color = px[x,y][:3]
		else:
			color = (0,0,0)
		print (str(color).replace('(', '{').replace(')', '}') + ',')
	print ('},')

print ("};")

