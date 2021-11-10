#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Apr 29 13:02:02 2020

@author: titouanlermite
"""

import utm ## convert lat, lon to x, y
import json
filename = "metros_raw.json"

with open(filename, 'r') as read_file :
    data = json.load(read_file)

geo_point_2d, res_com = [], []
for d in data :
    geo_point_2d.append(d["geo_point_2d"]) ## list of coords
    res_com.append(d["res_com"].strip('M')) ## list of metros

min_lat, min_lon = 0, 0
first = True
for coords in geo_point_2d :
    coord = 100 * coords #utm.from_latlon(coords[0], coords[1])
    coords[0], coords[1] = int(coord[0]), int(coord[1]) ## convert to x, y (int, int)
    if first :
        min_lat, min_lon = coords[0], coords[1]
        first = False
    else :
        if coords[0] < min_lat :
            min_lat = coords[0]
        if coords[1] < min_lon :
            min_lon = coords[1]
            
for coords in geo_point_2d :
    coords[0] -= min_lat ## left bound is 0
    coords[1] -= min_lon ## left bound is 0

metros = dict()
for met in res_com :
    metros[met] = list() ## creates the dict

for i in range(len(res_com)) :
    metros[res_com[i]].append([geo_point_2d[i][0], geo_point_2d[i][1]]) ## fills the dict

alphabet = { ## used for nodes
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

def generate_id(i) : ## works fine (don't need to read that ^^))
    res = ""
    while i // 26 != 0 :
        res += alphabet[i // 26 - 1]
        i %= 26
    res += alphabet[i]
    return res

i = 0
saved_nodes = list()
with open("metros_graph.txt", 'w') as f :
    f.write("1\n")
    temp = ""
    for key, value in metros.items() :#ligne : string, stations : list
        for coords in value :
            if coords not in saved_nodes : ## dont write in the file a node that has already been written
                saved_nodes.append(coords)
                temp += str(i) + " "
                temp += generate_id(i) + " "
                temp += str(coords[0]) + " "
                temp += str(coords[1]) + " "
                temp += "\n"
                i += 1
    f.write(str(i) + "\n")
    f.write(temp)
    i = 0
    k = 0
    temp = ""
    for value in metros.values() :# each list stations
        for j, coords in enumerate(value) :
            # i is the index of the node
            if j != 0:
                temp += str(k) + " "
                temp += str(j) + " " ## numero of origin node
                temp += str(j + 1) + " " ## numero of target node
                temp += "\n"
                k += 1
            if j != len(value) - 1:
                temp += str(k) + " "
                temp += str(j + 1) + " " ## numero of origin node
                temp += str(j) + " " ## numero of target node
                temp += "\n"
                k += 1
    f.write(str(k) + "\n")
    f.write(temp)