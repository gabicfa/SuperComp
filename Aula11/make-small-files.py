import random
import string
import sys

def small_file(name):
    lw = string.ascii_letters + ' ' * 7
    with open(name, 'w') as f:
        f.write(''.join([random.choice(lw) for i in range(100)]))
        
if __name__ == '__main__':
    num_files = int(sys.argv[1])
    output_dir = sys.argv[2]
    for i in range(num_files):
        small_file('{}/small-{}.txt'.format(output_dir, i))
