import serial,sys
filename = 'i.log'
print "> entered"
s=serial.Serial("Com1", 38400)
s.flush()
print "> serial opened"
f=open(filename,'w')
event = None
value = None
i=0

def linereader(s):
    b=[]
    while True:
        b.append(s.read())
        if b[-1]=='\n':
            yield ''.join(b)
            b=[]

#lr=linereader(s)
try:
    while True:
        event = s.read()
	if event not in '012':
            print "unexpected input: %s"%repr(event)
	    continue
        e = int(event)
        if e == 0:
            event = 'NOEVT'
        elif e == 1:
            event = 'PRESSED'
        elif e == 2:
            event = 'RELEASED'
        if event=='PRESSED':
            sys.stdout.write('P')
        if event=='RELEASED':
            sys.stdout.write('R')
            sys.stdout.write('%03d\n'%i)
            i+=1
        
        sys.stdout.flush()
        f.flush()
finally:
	f.close()
	s.close()
