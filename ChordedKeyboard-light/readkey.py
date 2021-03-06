import serial,sys, ctypes

filename = 'i.log'
print "> entered"
s=serial.Serial("Com8", 38400)
s.flush()
print "> serial opened"
f=open(filename,'w')
event = None
value = None
i=0

try:
    while True:
        event = s.read()
        if ( 0 < event):
            keycode = ord(event) + ord("A") -1
            sys.stdout.write('code: %s '%chr(keycode))
            ctypes.windll.user32.keybd_event(keycode,0,0,0) #press
            ctypes.windll.user32.keybd_event(keycode,0,2,0) #release
        else:
            print "unexpected input: %s"%repr(event)
            continue
        sys.stdout.write('i: %03d\n'%i)
        i+=1
        sys.stdout.flush()
        f.flush()

finally:
	f.close()
	s.close()
