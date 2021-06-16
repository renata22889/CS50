from sys import argv
import csv
import re
import sys
from re import search


def wordposition(string, word):

    first_end = len(word) - 1  # end of first word
    second_start = len(word)  # start of second word
    second_end = len(word) + len(word) - 1  # end of second word
    longest_chain = 0
    chain = 1

    for n in range(len(string)):
        if string[n: (n + first_end + 1)] == word[0: (first_end + 1)]:
            if string[n: (n + first_end + 1)] == string[(n + second_start): (n + second_end + 1)]:
                chain += 1
            if string[n: (n + first_end + 1)] != string[(n + second_start): (n + second_end + 1)]:
                if longest_chain < chain:
                    longest_chain = chain
                    chain = 1
                else:
                    chain = 1
    return longest_chain


# require correct number of command-line arguments
if len(argv) != 3:
    print("missing command-line argument")
    exit(1)


# open the CSV file and the DNA sequence and read its contents into memory
DNA_opened = open(argv[2], 'r')
DNA_sequence = DNA_opened.read()

with open(argv[1], newline='') as csvfile:
    data = list(csv.reader(open(argv[1])))


# compute the run of consecutive repeats
# if the STR counts match, print out the name

DNA_types = len(data[0]) - 1  # number of dna types
match = 0

for row in data:
    for i in range(1, DNA_types+1):
        if (row[i] == str(wordposition(DNA_sequence, data[0][i]))):
            match += 1
            if match == DNA_types:
                print(row[0])
                sys.exit(0)
        if (row[i] != str(wordposition(DNA_sequence, data[0][i]))):
            match = 0
print("No match")
sys.exit(1)

