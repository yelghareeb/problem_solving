""" UVA 10106
	Author: Youssef ElGhareeb
	
	Multiplication of large numbers in Python
"""

while True:
	try:
		x = int(input())
	except EOFError:
		break
	y = int(input())
	print (x * y)