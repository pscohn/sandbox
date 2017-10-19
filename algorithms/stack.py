#!/usr/local/bin/python3

class StackStrict:
    def __init__(self):
        self.stack = [0, 0, 0, 0]
        self.top = -1

    def push(self, item):
        self.top += 1
        self.stack[self.top] = item

    def pop(self):
        popped = self.stack[self.top]
        self.top -= 1
        return popped


def main():
    s = StackStrict()
    s.push(5)
    s.push(3)
    print(s.stack, s.top)

if __name__ == "__main__": main()
