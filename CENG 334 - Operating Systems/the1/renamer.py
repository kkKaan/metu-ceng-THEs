import os
import sys


def add_file_name(name, *args):
    for f in args[0]:
        os.rename(f, name+f)


if __name__ == "__main__":
    name = sys.argv[1]
    args = sys.argv[2:]
    add_file_name(name, args)
