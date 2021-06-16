from cs50 import get_int

# ask user for height until the user give a correct number
height = get_int("give height: ")

while height not in range(1, 9):
    height = get_int("give height again: ")

# print the half-pyramid
column = 0
row = 0

for column in range(0, height):
    column = column + 1
    print(" " * (height - column) + "#" * column + "  " + "#" * column, end="")
    print()

