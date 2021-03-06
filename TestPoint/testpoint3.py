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
                readbytes=struct.unpack('10B', s.read(10))
                v = readbytes[0]
                print "%02x"%v,
                if v==1: box_colour=Colour.red
                elif v==0: box_colour=Colour.blue
                else: box_colour=Colour.green
                lastst=v
                box_x= 10+x*box_width
                box_y= 450- y* box_height
                box((box_x,box_y),box_x+box_width-box_margin,box_y+box_height-box_margin, colour=box_colour, filled=1)
        clear_screen()

    time.sleep(4)
finally:
    pass
if 1:
    end_graphics()
    s.close()
    print 'Done'
