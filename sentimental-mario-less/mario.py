# Import get_int from cs50 lib per spec
from cs50 import get_int


# Function prints right-alligned half triangle base * height n
def get_height():
    while True:
        try:
            n = get_int("Height: ")
            if (n > 0) and (n < 9):
                return n
        except ValueError:
            print("Not an integer")

# Def Main is placed after the core of the program


def main():
    n = get_height()
    for i in range(n):
        print(" " * (n - (i + 1)), end="")
        print("#" * (i + 1), end="")
        print("")


# Main is called at the end
main()
