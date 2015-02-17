"""
We use a [9][9] matrix to indicate the board of the Hip game.
0 - it is empty
1 - Blue
2 - Red
There are 2 approaches to this
1. Is either all the given boxes are predefined and stored.
No matter which inclination and position.
2. Else we have function which takes the current input of the board and
predicts whether a square is possible or not
At any point of time as soon as a square is formed by either R or B, that person loses and the game terminates.
"""

"""
First attempt to solve the problem 
All the input will be given by the human itself.
There will no human vs computer. 
"""

"""
In this program we are taking input states of different board configuration.
Step 1: Human driven board configurations
Step 2: Given this config return if there is possible square and then true or false accordingly.
"""

def take_input():
	"""
		Function to take input from the use of the board config
	"""

	data = []
	for i in range(0,100): #We are taking input for the board. For now we use a smaller board of 3*3
		data.append(raw_input())

	print data #config of the board


def check_square(data):
	"""
		Function returns a true or false depending on whether a square exists or not
	"""

	for i in range(0,9):
		for j in range(0,9):
			"""
				check across the row, col, across both diagnols
			"""

def getallsquareconfig():
	hipsquares = []
	"""
		[0 1 2 3 4
	 	5 6 7 8 9
	 	10 11 12 13 14
	 	15 16 17 18 19
	 	20 21 22 23 24]
	 	To make a square - all the 4 sides of the square will add up uniquely. Take a queue from that
	 	to check if the square exists
	 """
