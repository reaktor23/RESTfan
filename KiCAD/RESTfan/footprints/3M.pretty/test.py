a = 15.24
b = 13.97
for i in range(28,51,2):
    a = a - 2.54
    b = b - 2.54
    print(f'(pad "{i}" thru_hole circle (at {a:.2f} 0.96) (size 1.2 1.2) (drill 0.8) (layers *.Cu *.Mask) (tstamp 59004b2d-c835-4f90-bdd9-54c5799141cd))')
    print(f'(pad "{i+1}" thru_hole circle (at {b:.2f} 2.86) (size 1.2 1.2) (drill 0.8) (layers *.Cu *.Mask) (tstamp 82ebd3c9-b9e8-4f65-b4d9-5d059c37fb48))')

