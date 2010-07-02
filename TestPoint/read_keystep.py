import serial

s=serial.Serial("Com1")
try:
	for i in range(1000):
	    print "%s" % s.read()
	    print "=========== %d" % i

except:
	pass
finally:
	s.close()