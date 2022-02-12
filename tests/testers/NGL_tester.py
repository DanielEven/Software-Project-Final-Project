import sys
import os

bad = False

os.system('./out > tests/testers/NGL_res.txt')

with open("tests/expected_NGL.txt", 'r') as out, open("tests/testers/NGL_res.txt", 'r') as res:
    nums_out_lines = out.read().split('\n')
    nums_res_lines = res.read().split('\n')

    for i in range(len(nums_out_lines)):
        nums_out = nums_out_lines[i].split(' ')
        nums_res = nums_res_lines[i].split(' ')

        for j in range(len(nums_out)):
            a = nums_out[j]
            b = nums_res[j]
            if a != b:
                
                val = abs(float(a)-float(b))
                if val <= 0.0011:
                    print(f"DIFF: {a}, {b}")
                else:
                    print(f"BAD DIFF: {a}, {b}")
                    bad = True

if bad:
    sys.exit(1)
