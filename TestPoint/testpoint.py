# Demo/tkinter/matt/canvas-with-scrollbars.py
# Mouse over.
# Key holder.
# estimate time 

import time
from livewires import *
import serial, struct
import random
from tdd3 import *

#s=serial.Serial("Com3")
#s.open()
math.
begin_graphics()
try:
    width = 50
    height = 40
    box_width=10
    box_height=10
    box_margin=4
    lastst=1023
    while True:
        move(10,460)
        text('TestPoint Chorded Keyboard', serifs=1, size=14)
        x=0;y=0
        while y<height:
            while x < width:
                timemarker = 10
#                readbytes=struct.unpack(str(timemarker)+'B', s.read(timemarker))
                readbytes=[1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0]
                output = TestPoint(readbytes)
                output.setPeriod(timemarker)
                for v,isMarker in output:
                    if v==1: box_colour=Colour.red
                    elif v==0: box_colour=Colour.blue
                    else: box_colour=Colour.green
                    if isMarker:
                        box_colour = [Colour.grey,Colour.yellow][v]
                    lastst=v
                    
                    box_x= 10+x*box_width
                    box_y= 450- y* box_height
                    box((box_x,box_y),box_x+box_width-box_margin,box_y+box_height-box_margin, colour=box_colour, filled=1)
                    x+=1
                    if x>=width:break
                    # move(box_x,box_y)
                    # text(str(v), serifs=1, size=10)                
            x=0;y+=1
#        time.sleep(3)
        clear_screen()

    time.sleep(4)
finally:
    pass
if 1:
    end_graphics()
    s.close()
    print 'Done'
