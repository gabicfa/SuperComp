import os

books = [
    'http://www.gutenberg.org/files/57846/57846-0.txt',
    'https://www.gutenberg.org/files/1342/1342-0.txt',
    'https://www.gutenberg.org/ebooks/16328.txt.utf-8',
    'https://www.gutenberg.org/ebooks/6130.txt.utf-8',
    'https://www.gutenberg.org/files/84/84-0.txt',
    'https://www.gutenberg.org/files/219/219-0.txt',
    'https://www.gutenberg.org/files/11/11-0.txt',
    'https://www.gutenberg.org/files/2701/2701-0.txt', 
    'https://www.gutenberg.org/ebooks/1661.txt.utf-8',
    'https://www.gutenberg.org/ebooks/1232.txt.utf-8',
    'https://www.gutenberg.org/files/74/74-0.txt',
    'https://www.gutenberg.org/ebooks/345.txt.utf-8',
    'https://www.gutenberg.org/ebooks/851.txt.utf-8',
    'https://www.gutenberg.org/files/98/98-0.txt',
    'https://www.gutenberg.org/ebooks/23.txt.utf-8',
    'https://www.gutenberg.org/ebooks/1497.txt.utf-8',
    'https://www.gutenberg.org/ebooks/1080.txt.utf-8',
    'https://www.gutenberg.org/ebooks/408.txt.utf-8',
    'https://www.gutenberg.org/files/76/76-0.txt',
    'https://www.gutenberg.org/ebooks/844.txt.utf-8',
    'https://www.gutenberg.org/ebooks/5200.txt.utf-8', 
    'https://www.gutenberg.org/files/30254/30254-0.txt', 
    'https://www.gutenberg.org/ebooks/2542.txt.utf-8', 
    'https://www.gutenberg.org/ebooks/3207.txt.utf-8',
    'https://www.gutenberg.org/files/1952/1952-0.txt'
]

for b in books:
    os.system('wget {}'.format(b))
