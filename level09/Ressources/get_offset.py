#!/usr/bin/env python3

import sys

string = "aaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssssttttuuuuvvvvwwwwxxxxyyyyzzzzAAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUUVVVVWWWWXXXXYYYYZZZZ"

i = 0
star = -1
stop = 0
while i < len(string):
    if string[i] == sys.argv[1][0]:
        star = i
        stop = 1
    if stop == 1:
        break
    i += 1

print("offset -> ", star)
