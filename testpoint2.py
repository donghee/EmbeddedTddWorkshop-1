#Demo/tkinter/matt/canvas-with-scrollbars.py
# Mouse over.
# Key holder.
# estimate time 
import time
from livewires import *
import serial, struct
import random

s=serial.Serial("Com1")
s.open()

begin_graphics()
try:
    width = 40
    height = 55
    box_width=10
    box_height=10
    box_margin=4
    lastst=1023
    while True:
        move(10,460)
        text('TestPoint Chorded Keyboard', serifs=1, size=14)

        for y in range(width):
            for x in range(height):
                readbytes=struct.unpack('1B', s.read(1))
                v = readbytes[0]
#                v=random.randrange(0,1024)
                #if v > 300 :
                #    box_colour = Colour.red
                #else:
                #    box_colour = Colour.blue
#                c=v/1023.0
#                box_colour=Colour(c,c,c)
                if v==1: box_colour=Colour.red
                elif v==1: box_colour=Colour.blue
                else: box_colour=Colour.green
                # if v<1000:
                #     if lastst>=1000: print;print "-"*10
                #     print "%03d"%v,
                lastst=v
                # if v>=1000:
                #     continue
                box_x= 10+x*box_width
                box_y= 450- y* box_height
                box((box_x,box_y),box_x+box_width-box_margin,box_y+box_height-box_margin, colour=box_colour, filled=1)
                # move(box_x,box_y)
                # text(str(v), serifs=1, size=10)                
        
        #time.sleep(3)
        clear_screen()

    time.sleep(4)
finally:
    pass
if 1:
    end_graphics()
    s.close()
    print 'Done'



