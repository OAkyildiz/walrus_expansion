class CloudIterator:
    def __init__(self, iterator, width):
        self.iterator = iterator
        self.width = width
        self.index = 0
    
    def getPoint(self):
        if self.index >= self.width:
            return None
        self.index += 1
        return next(self.iterator)
