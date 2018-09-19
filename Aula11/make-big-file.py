import random
import string
import sys

def random_big_file(num_lines, name):
    lw = string.ascii_letters + ' ' * 7
    content = ''
    with open(name, 'w') as f:
        for i in range(num_lines):
            content += ''.join([random.choice(lw) for i in range(100)])
        f.write(content)
        
if __name__ == '__main__':
    num_lines = int(sys.argv[1])
    num_files = int(sys.argv[2])
    output_dir = sys.argv[3]
    for i in range(num_files):
        random_big_file(num_lines, '{}/{}.txt'.format(output_dir, i))
