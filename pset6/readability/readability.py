from cs50 import get_string

# define arguments
L = 0               # L - average number of letters per 100 words in the text
S = 0               # S - average number of sentences per 100 words in the tex
total_words = 0
dots = 0
exclamation_mark = 0
question_mark = 0
total_sentences = 0
commas = 0
apostrophes = 0
grade = 0

# prompt the user for a string of text
text = get_string("Text: ")
    
# total number of words
total_words = len(text.split())
print("Total nb of words: " + str(total_words))

# total number of sentences
dots = text.count(".")
exclamation_mark = text.count("!")
question_mark = text.count("?")
total_sentences = dots + exclamation_mark + question_mark
print("Total nb of sentences: " + str(total_sentences))

S = total_sentences * 100 / total_words
print("S: " + str(S))

spaces = text.count(" ")
# print("spaces: " + str(spaces))
commas = text.count(",")
# print("commas: " + str(commas))
apostrophes = text.count("'")
# print("apostrophes: " + str(apostrophes))

total_letters = len(text) - spaces - commas - apostrophes - total_sentences
print("Total nb of letters: " + str(total_letters))

L = total_letters * 100 / total_words
print("L: " + str(L))

grade_notround = 0.0588 * L - 0.296 * S - 15.8
print("grade: " + str(grade_notround))

grade = round(0.0588 * L - 0.296 * S - 15.8)
print("grade: " + str(grade))

# output result
if grade >= 1 and grade < 16:
    print("Grade: " + str(grade))

elif grade >= 16:
    print("Grade 16+\n")

elif grade < 1:
    print("Before Grade 1\n")
    
    
  # for dna 
print("row[i] : " + row[i])
        print("wordposition " + str(data[0][i]) + " :" + str(wordposition(DNA_sequence, data[0][i])) ) 
        
            print(row['name'] + str(AGATC) + "," + str(TTTTTTCT) + "," + str(AATG)+ "," + str(TCTAG)+ "," + str(GATA)+ "," + str(TATC)+ "," + str(GAAA)+ "," + str(TCTG))
            
            
            print(str(row[0]) +" " + str(data[0][i]) + " "  +str(wordposition(DNA_sequence, data[0][i])))
            
            taieb thing:
                if (string[n: (n+first_end)] == 'TCTG'):
                    print('GAAA!!!!!!!!!!!!!!!!!!!' )
                else
                  print(string[n: (n+first_end)] )