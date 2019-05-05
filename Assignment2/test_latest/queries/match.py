import argparse

parser = argparse.ArgumentParser()
parser.add_argument('-a', '--actual', type=str, help='Actual output file for testing')
parser.add_argument('-p', '--provided', type=str, help='Student generated output file for testing')
args = parser.parse_args()

try:
    with open(args.actual, 'r') as f:
        try:
            actual = [int(row.strip()) for row in f.readlines()]
        except ValueError:
            print "Incorrect format of actual file"
            exit()
except IOError:
    print "Actual File not found"
    exit()

try:
    with open(args.provided, 'r') as f:
        try:
            provided = [int(row.strip()) for row in f.readlines()]
        except ValueError:
            print "Incorrect format of provided file"
            exit()
except IOError:
    print "Provided File not found"
    exit()

if actual == provided:
    print "Files Match Completely!"
else:
    print "File do not Match. Sorry!"
