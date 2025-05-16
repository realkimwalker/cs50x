from cs50 import get_string

# Prompt user for text
text = get_string("Text: ")


# Use for loop and functionality to count each letter in text
letters = 0
for l in text:
    if l.isalpha():
        letters += 1

# Use functionality in python to return word count
words = len(text.split())

# Use python functionality to count sentences
sentences = text.count(".") + text.count("?") + text.count("!")

L = letters / words * 100
S = sentences / words * 100

# Compute the Coleman-Liau index
index = 0.0588 * L - 0.296 * S - 15.8

# Print the grade level
if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {round(index)}")
