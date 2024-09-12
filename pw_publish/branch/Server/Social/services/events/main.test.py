import unittest
import main

class Test_Counter(unittest.TestCase):

    def test_Simple(self):
        c = main.Counter([5, 10], 0)
        self.assertEquals(0, c.Get()[5])
        self.assertEquals(0, c.Get()[10])

        c.Add(1)
        self.assertEquals(1, c.Get()[5])
        self.assertEquals(1, c.Get()[10])
    
        c.Add(4.99)
        self.assertEquals(2, c.Get()[5])
        self.assertEquals(2, c.Get()[10])

        c.Add(5.01)
        self.assertEquals(1, c.Get()[5])
        self.assertEquals(3, c.Get()[10])
        
        c.Add(9.99)
        self.assertEquals(2, c.Get()[5])
        self.assertEquals(4, c.Get()[10])

        c.Add(10.01)
        self.assertEquals(1, c.Get()[5])
        self.assertEquals(1, c.Get()[10])

    def test_Update(self):
        c = main.Counter([5, 10], 0)
        self.assertEquals(0, c.Get()[5])
        self.assertEquals(0, c.Get()[10])

        c.Add(1)
        self.assertEquals(1, c.Get()[5])
        self.assertEquals(1, c.Get()[10])

        c.Update(4.99)
        self.assertEquals(1, c.Get()[5])
        self.assertEquals(1, c.Get()[10])

        c.Update(5.01)
        self.assertEquals(0, c.Get()[5])
        self.assertEquals(1, c.Get()[10])

unittest.main()