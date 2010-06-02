# -*- coding: utf-8 -*-
import unittest

class TestPoint:
    def __init__(self,input):
        self.input = iter(input)
        self._pos = 0
        self._pv =None
        self._period = None
        
    def _next(self):
        v = self.input.next()
        self._pos += 1

        if v != self._pv or self.isTimemaker():
            self._pv = v
            return v, self._pos
        else:
            self._pv = v            
            return self._next()
    def next(self):
        v,p=self._next()
        isMarker=self.isTimemaker()
        return (v,isMarker)
    def isTimemaker(self):
        return (self._pos-1) % self._period == 0

    def setPeriod(self, period):
        self._period = period

class Test(unittest.TestCase):
    def assertIter(self,it_method,l):
        for each in l:
            self.assertEqual(each, it_method())

    # input: 1,0,1,1,0
    # output(value,pos): (1,1),(0,2),(1,3),(0,5)
    
    def testDiff(self):
        input = [1,0,1,1,0]
        output = TestPoint(input)

        output.setPeriod(1000)
        self.assertIter(output._next, [
            (1,1),(0,2),(1,3),(0,5)
            ])

    def testDiff2(self):
        input = [1,1,1,1,1,1,0,1,1,0]
        output = TestPoint(input)
        output.setPeriod(1000)        
        self.assertIter(output._next, [
            (1,1),(0,7),(1,8),(0,10)
            ])

    def testTimemaker(self):
        input = [1, 1,1,1, 1,1,0, 1, 1,0]
        inputt="1111110110"
        expect="^  ^  ^^ ^"
        output = TestPoint(input)
        output.setPeriod(3)

        self.assertIter(output._next, [
            (1,1),(1,4),(0,7),(1,8), (0,10)
            ])

        # self.assertEqual((1,1),output._next())
        # self.assertEqual((1,4),output._next())
        # self.assertEqual((0,7),output._next())                
        # self.assertEqual((1,8),output._next())                
        # self.assertEqual((0,10),output._next())
        self.assertRaises(StopIteration, output._next)
    def testNextPoint(self):
        input=[1,1,1,1,1,0,1]
        output=TestPoint(input)
        output.setPeriod(3)
        self.assertIter(output.next,[
            (1,True),(1,True),(0,False),(1,True)
            ])
        
if __name__ == '__main__':
    unittest.main()
