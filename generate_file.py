#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Apr 27 17:34:28 2020
@author: titouanlermite
"""

import random
import time
random.seed(int(round(time.time())) % 1000)

alphabet = {
    0 : "A",
    1 : "B",
    2 : "C",
    3 : "D",
    4 : "E",
    5 : "F",
    6 : "G",
    7 : "H",
    8 : "I",
    9 : "J",
    10 : "K",
    11 : "L",
    12 : "M",
    13 : "N",
    14 : "O",
    15 : "P",
    16 : "Q",
    17 : "R",
    18 : "S",
    19 : "T",
    20 : "U",
    21 : "V",
    22 : "W",
    23 : "X",
    24 : "Y",
    25 : "Z"
    }

w, h = 1000, 800 ## width/height of the screen
<<<<<<< HEAD
max_nodes, max_edges_node = 10, 2 ## width/height of the screen
=======
max_nodes, max_edges_node = 25, 2 ## width/height of the screen
>>>>>>> nodes_color
oriented, weighted = False, False
max_weight = 100

def generate_file(file_name) :
    ## file_name : dont forget to add .txt at the end
    file = open(file_name, "w")
    if oriented :
        file.write("1\n")
    else :
        file.write("0\n")
    file.write(str(max_nodes) + "\n")
    for i in range(max_nodes) :
        file.write(str(i) + " ")
        file.write(generate_id(i) + " ")
        file.write(str(random.randint(0, w) - 1) + " ")
        file.write(str(random.randint(0, h - 1)) + " ")
        file.write("\n")
    visited_nodes = [[0 for i in range(max_nodes)] for j in range(max_nodes)]
    next_node = {random.randint(0, max_nodes - 1)}
    temp = ""
    i = 0
    first = True
    while visited(visited_nodes) != 0 :
        if first : ## add at least one edge
            temp += str(i) + " "
            origin = list(next_node)[-1]
            next_node.discard(origin)
            temp += str(origin) + " "
            target = random.randint(0, max_nodes - 1)
            while target == origin or visited_nodes[origin][target] != 0 :
                target = random.randint(0, max_nodes - 1)
            next_node.add(target)
            temp += str(target) + " "
            if weighted :
                temp += str(random.randint(0, max_weight)) + "\n"
            temp += "\n"
            visited_nodes[origin][target] += 1
            i += 1
            first = False
        if edges(visited_nodes, origin, target) >= max_edges_node :
            first = True
            continue
        rand = random.randint(0, 1)
        if rand == 0 : ## add edge
            temp += str(i) + " "
            temp += str(origin) + " "
            target = random.randint(0, max_nodes - 1)
            while target == origin or visited_nodes[origin][target] != 0 :
                target = random.randint(0, max_nodes - 1)
            next_node.add(target)
            temp += str(target) + " "
            if weighted :
                temp += str(random.randint(0, max_weight)) + "\n"
            temp += "\n"
            visited_nodes[origin][target] += 1
            i += 1
        else : ## go to next node
            first = True
            continue
        if edges(visited_nodes, origin, target) >= max_edges_node :
            first = True
            continue
    file.write(str(i) + "\n")     
    file.write(temp)
    file.close()

def generate_id(i) :
    res = ""
    while i // 26 != 0 :
        res += alphabet[i // 26 - 1]
        i %= 26
    res += alphabet[i]
    return res
        
def visited(visited_list) :
    s = 0
    for n1 in visited_list :
        if sum(n1) == 0 :
            s += 1
    return s

def edges(visited_list, origin, target) :
    s = 0
    for n in visited_list[origin] :
        s += n
    for n in visited_list :
        s += n[origin]
    return s