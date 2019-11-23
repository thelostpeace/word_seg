#!/usr/bin/env python
# -*- coding: utf-8 -*-

total = 0
right = 0
with open('log') as f:
    for line in f:
        v = line.strip().split('\t')
        if len(v) < 3:
            continue
        total += 1
        if v[1] == v[2]:
            right += 1

print "total: ", total
print "right: ", right
print "acc: ", float(right) / total
