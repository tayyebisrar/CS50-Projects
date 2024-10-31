import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py [csvfile].csv [txtfile].txt")

    # Read database file into a variable
    rows = []
    with open(sys.argv[1]) as databasefile:
        reader = csv.DictReader(databasefile)
        for row in reader:  # for each person
            rows.append(row)  # create a new dictionary
        header = reader.fieldnames  # or rows[0].keys()

    # Read DNA sequence file into a variable
    dnastring = open(sys.argv[2]).read()

    # Find longest match of each STR in DNA sequence
    matches = {}
    for i in range(1, len(header)):  # exclude 'name' from the dictionary
        matches[header[i]] = longest_match(dnastring, header[i])

    # Check database for matching profiles
    matched_index = -1
    for person in range(len(rows)):  # for each person in dict
        for dnastr in matches:  # for each of their substrings
            if int(rows[person][dnastr]) != int(matches[dnastr]):  # if one doesn't match
                break  # can't be the correct person
        else:
            matched_index = person  # if all matched then it's the right person

    if matched_index == -1:
        print("No match")
    else:
        print(rows[matched_index]['name'])


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
