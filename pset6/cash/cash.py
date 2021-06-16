from cs50 import get_float

# define arguments
q = 0  # q - number of 0,25$ coins
d = 0  # q - number of 0,10$ coins
n = 0  # q - number of 0,05$ coins
p = 0  # q - number of 0,01$ coins


# ask the user for change (a non-negative number)
change = get_float("How much change is owed?\n")

while change < 0:
    change = get_float("Please give a non-negative number:\n")

cents = int(change * 100)


# check how many 0,25$ coins are needed
while cents - q * 25 >= 25:
    q += 1

# check how many 0,10$ coins is needed
while cents - q * 25 - d * 10 >= 10:
    d += 1
    
# check how many 0,05$ coins is needed
while cents - q * 25 - d * 10 - n * 5 >= 5:
    n += 1
    
# check how many 0,01$ coins is needed
while cents - q * 25 - d * 10 - n * 5 - p * 1 >= 1:
    p += 1
    
# s - summarize the amount of the needed coins
s = q + d + n + p
print(s)
