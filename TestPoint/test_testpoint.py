# ctrl -j new line and indent
# ctrl-c ctrl-j
# longlines-mode

import unittest


class Serial:
    def __init__(self, values):
        self.values= values
        self._index=0
    def read(self,num):
        v=self.values[self._index:self._index+num]
        self._index+=num
        return v

class TestPoint:
    def __init__(self, serial, pace):
        self.serial= serial
        self.pace = pace
        self.bind=0
        self._total_index=05

    def next1(self):
        self.buffer=self.serial.read(self.pace)
        v=self.buffer[0]
        self._total_index=0
        return self._next(v)
    

    def next2(self):
        self.bind=0
        self.buffer=self.serial.read(self.pace)
        self._total_index+=self.pace
        v=self.buffer[self.bind]
        return self._next(v)

    def _next(self,v):
        isMarker=(self.bind%5)==0
        return (v,isMarker)
    
class Test(unittest.TestCase):
    def test1(self):
        self.assertEquals(1,1)

    def test_same(self):
                     #!0 1 2 3 4!5 6 7
        serial=Serial([1,1,1,1,1,1,1,1])
        tp=TestPoint(serial,pace=5)
        self.assertEquals((1,True),tp.next1())

        self.assertEquals((1,True),tp.next2())
        self.assertEquals(5, tp._total_index)
        
        

if __name__=='__main__':
    unittest.main()
