# Addition with int [using get_float]
from cs50 import get_float
import math


def get_cents():
    while True:
        try:
            c = get_float("Change: ")
            if (c > 0.00):
                return c
        except ValueError:
            print("Not an integer")


# Using counters for each type of coin
def main():
    t = 0
    p = 0
    d = 0
    n = 0
    q = 0
    f = 0
    c = get_cents()

    c = int((round(c, 2)) * 100)
    # Calculating quarters
    if ((c / 25) >= 1):
        q = int(c / 25)
        c = (c - int(q * 25))

    # Calculating dimes
    if ((c / 10) >= 1) and (c < 25):
        d = int(c / 10)
        c = (c - int(d * 10))

    # Calculating nickels
    if ((c / 5) >= 1) and (c < 10):
        n = int(c / 5)
        c = (c - int(n * 5))

    # Calculating pennies
    if ((c / 1) >= 1) and (c < 5):
        p = int(c)

    # Add all coins and print
    t = (f + q + d + n + p)
    print(t)


main()
