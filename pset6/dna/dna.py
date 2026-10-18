import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print(" ")
        return

    # TODO: Read database file into a variable
    persons = []
    with open(sys.argv[1], newline="") as database:
        reader = csv.DictReader(database)
        subsequences = reader.fieldnames[1:]
        persons = list(reader)
        count_sub = int(len(subsequences))

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], newline="") as dna:
        sequence = dna.read().strip()

    # TODO: Find longest match of each STR in DNA sequence
    length_sub = [0] * count_sub
    for i in range(0, count_sub):
        length_sub[i] = longest_match(sequence, subsequences[i])

    # TODO: Check database for matching profiles
    for i in range(0, len(persons)):
        all_match = True
        for j in range(0, count_sub):
            if (int(persons[i][subsequences[j]]) != length_sub[j]):
                all_match = False
        if all_match:
            print(persons[i]["name"])
            return
    print("No match")
    return


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

    # After checking for runs at each character in sequence, return longest run found
    return longest_run


main()
