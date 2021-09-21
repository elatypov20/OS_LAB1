# this script gets output of ex3 (from pipe)
# and checks when it prints incorrect data
# (all output should be in alphabetical order, otherwise we caught race condition)
from sys import stdin

alp = 'abcdefghijklmnopqrstuvwxyz'
p = 0

while (True):
	c = stdin.read(1)

	if c != alp[p]:
		print(f"expected: '{alp[p]}', got: '{c}'")
	
	p = (p + 1) % len(alp)