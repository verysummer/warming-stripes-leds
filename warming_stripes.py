# -*- coding: utf-8 -*-
"""
Created on Wed Nov 10 22:46:25 2021

@author: verena
"""

## Warming Stripes 
# adjusted from 
# https://matplotlib.org/matplotblog/posts/warming-stripes/

import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle
from matplotlib.collections import PatchCollection
from matplotlib.colors import ListedColormap
import pandas as pd
import numpy as np

# save image / colors
SAVE = False

FIRST = 1850
LAST = 2018  # inclusive
STEP = 3 # 1 = all dates, 3 = reduced


# Reference period for the center of the color scale

FIRST_REFERENCE = 1971
LAST_REFERENCE = 2000
LIM = 0.7 # degrees

# data from
# https://www.metoffice.gov.uk/hadobs/hadcrut4/data/current/time_series/HadCRUT.4.6.0.0.annual_ns_avg.txt

df = pd.read_fwf(
    'HadCRUT.4.6.0.0.annual_ns_avg.txt',
    index_col=0,
    usecols=(0, 1),
    names=['year', 'anomaly'],
    header=None,
)

anomaly = df.loc[FIRST:LAST, 'anomaly'].dropna()

if STEP == 3:
    # reduce data to 1/3
    new_data = pd.Series([])
    for y in range(1850,2018,3):
        mean_year = np.mean([anomaly[y], anomaly[y+1], anomaly[y+2]])
        new_data[y] = mean_year
        
    # add last 3 years    
    new_data[2018] = np.mean([df.anomaly[2019], df.anomaly[2020], df.anomaly[2021]])
        
    anomaly = new_data

#reference = anomaly.loc[FIRST_REFERENCE:LAST_REFERENCE].mean() # 0.10810000000000002
reference = 0.1081 # hard coded for reduced version

# the colors in this colormap come from http://colorbrewer2.org

# the 8 more saturated colors from the 9 blues / 9 reds

cmap = ListedColormap([
    '#08306b', '#08519c', '#2171b5', '#4292c6',
    '#6baed6', '#9ecae1', '#c6dbef', '#deebf7',
    '#fee0d2', '#fcbba1', '#fc9272', '#fb6a4a',
    '#ef3b2c', '#cb181d', '#a50f15', '#67000d',
])

fig = plt.figure(figsize=(10, 1))

ax = fig.add_axes([0, 0, 1, 1])
ax.set_axis_off()


# create a collection with a rectangle for each year

col = PatchCollection([
    Rectangle((y, 0), STEP, 1)
#    for y in range(FIRST, LAST + 1)
for y in range(FIRST, LAST + 1, STEP)
])

# set data, colormap and color limits

col.set_array(anomaly)
col.set_cmap(cmap)
col.set_clim(reference - LIM, reference + LIM)
ax.add_collection(col)

ax.set_ylim(0, 1)
#ax.set_xlim(FIRST, LAST + 1)
ax.set_xlim(FIRST, LAST + 1, STEP)

if SAVE:
    fig.savefig('warming-stripes_reduced.png')



## get rgb colors

colors = getattr(col,'_facecolors')
rgb = np.zeros((len(colors),3))
for c in range(len(colors)):
    my_c = colors[c]
    my_c = np.delete(my_c,-1)
    rgb[c] = my_c
    
rgb = rgb * 255
rgb = rgb.astype(int)

if SAVE:
    np.savetxt('rgb.csv', rgb, delimiter=',')

r = rgb[:,0]
g = rgb[:,1]
b = rgb[:,2]










