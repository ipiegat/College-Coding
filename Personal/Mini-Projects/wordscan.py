"""
find most used words in current directory
print words and amount of times used

to execute: 'python wordscan.py'
"""

import os
import argparse

if __name__ == "__main__":
    # parse the arguments
    parser = argparse.ArgumentParser()
    parser.add_argument("--dir", default=".")
    args = parser.parse_args()
    print(args.dir)

    # get all files in the target directory, including folders
    filenames = os.listdir(args.dir)

    # remove the folders, only retain _real_ files
    actual_files = [f for f in filenames if os.path.isfile(f)]
    print(f"Found {len(actual_files)} files in directory '{args.dir}'")

    word_counts = {}

    for filename in actual_files:
        with open(filename, "r") as file:

            # get the contents and split them into words
            contents = file.read()
            word_list = contents.split()

            word_set = set(word_list) # this is the set of unique words
            for word in word_set:
                if word not in word_counts:
                    word_counts[word] = 0

                # add the number of words into the count
                word_counts[word] += word_list.count(word)

print(f"Found {len(list(word_counts.values()))} unique words across {len(list(word_counts.values()))} total")

# convert the dict to a list of tuples
word_count_tuples = list(word_counts.items())

#sort from the most frequent to least
word_count_tuples.sort(key=lambda x: x[1], reverse=True)
print(word_count_tuples[:5])