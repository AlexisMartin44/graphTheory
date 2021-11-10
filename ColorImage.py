#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri May  1 20:36:40 2020

@author: titouanlermite
"""

from PIL import Image, ImageDraw
import numpy as np
step = 0.000001
repartition = np.arange(0, 1, step)
number = 1 / step
i = 0
w, h = 500, 300
image = Image.new("RGB", (w, h), (0, 0, 0))
draw = ImageDraw.Draw(image)
for r in repartition :
    normalized = int(r * 256 * 4)
    temp = normalized % 256
    normalized //= 256
    if normalized == 0 :
        r = 0
        g = temp
        b = 255
    elif normalized == 1 :
        r = 0
        g = 255
        b = 255 - temp
    elif normalized == 2 :
        r = temp
        g = 255
        b = 0
    elif normalized == 3 :
        r = 255
        g = 255 - temp
        b = 0
    draw.rectangle((i * w / number, 0, (i + 1) * w / number, h), 
                   fill = (int(r), int(g), int(b)))
    i += 1
image.save("colors_guide.jpg", quality = 100)