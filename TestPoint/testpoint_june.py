# Demo/tkinter/matt/canvas-with-scrollbars.py
# Mouse over.
# Key holder.
# estimate time

import time
from livewires import *
import serial, struct
import random
from tdd3 import *

s=serial.Serial("Com1")
#s.open()
begin_graphics()
try:
    width = 50
    height = 30
    box_width=10
    box_height=10
    box_margin=2
    ymargin=10
    lastst=1023
    timemarker = 10

    #readbytes=[0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0]*200

    while True:
        move(10,460)
        text('TestPoint Chorded Keyboard', serifs=1, size=14)
        x=0;y=0
        while y<height:
            while x < width:
                readbytes=struct.unpack(str(timemarker)+'B', s.read(timemarker))
                output = TestPoint(readbytes)
                output.setPeriod(timemarker)

		for v,isMarker in output:
                    box_x= 10+x*box_width
                    box_y= 450- y* (box_height+ymargin)
                    x1=box_x
                    x2=box_x+box_width-box_margin
                    y1=box_y
                    y2=box_y+box_height-box_margin

                    if v==1:
                        line(x1,y2,x2,y2,Colour.black)
                    elif v==0:
                        line(x1,y1,x2,y1,Colour.black)

                    if isMarker:
                        mid=(x1 + x2)/2
                        line(mid,y1,mid,y2,Colour.red)

                    lastst=v
                    x+=1
                    if x>=width:break
            x=0;y+=1
        clear_screen()
    time.sleep(4)
finally:
    pass
if 1:
    end_graphics()
