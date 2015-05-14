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


"""
	TODOS:	1. Tidy up
			2. Creation of Game Tree
				a) Implementation of minimax
				b) Implementation of alpha beta pruning
"""
from itertools import combinations
import math

class hip:
	def take_input(self):
		"""
			Function to take input from the use of the board config
		"""

		player = raw_input("Enter the player token number: 1. Blue  2. Red  :: ");

		data = []
		board = []
		player_positions = []
		print("Enter the board elements: ");
		for i in range(0,3): #We are taking input for the board. For now we use a smaller board of 3*3
			for j in range(0,3):
				data.append(raw_input())
			board.append(data)
			data = []

		print("\nThe input board is");
		print(board) #config of the board

		player_positions = self.populate_positions(board,player)
		print("\nThe Player positions are: \n");
		print(player_positions)

		self.check_square(player_positions)

	def populate_positions(self, board, player):
		""" 
			Populate the player positions on the board
		"""
		positions = []
		for i in range(0,3):
			for j in range(0,3):
				if(board[i][j] == player):
					positions.append([i,j])

		return positions

	def check_square(self, player_positions):
		"""
			Function returns a true or false depending on whether a square exists or not
		"""
		length = len(player_positions)
		sides = []

		for item in combinations(player_positions,4):
			print "\n\n", item
			"""
				populating the sides using three points of the combination
			"""
			sides = []
			sides.append(self.distance(item[0],item[1]));
			sides.append(self.distance(item[0],item[2]));
			sides.append(self.distance(item[0],item[3]));
			print("\nSides distance");
			print(sides)
			result = self.isSquare(sides,item)
			print result

	def isSquare(self, sides, player_positions):

		"""
			function to check the presence of square using the 4 points given
		"""
		equalSide1 = -1
		equalSide2 = -1
		unequalSide = -1
		if(sides[0] == sides[1]):
			if(sides[0] != sides[2]):
				equalSide1 = 0
				equalSide2 = 1
				unequalSide = 2
		elif(sides[1] == sides[2]):
			if(sides[1] != sides[0]):
				equalSide1 = 1
				equalSide2 = 2
				unequalSide = 0        
		elif(sides[0] == sides[2]):
			if(sides[0] != sides[1]):
				equalSide1 = 0
				equalSide2 = 2
				unequalSide = 1

		"""
			If failed to satisfy the above condition, the points doesn't form a square
    		Otherwise check for the square distance conditions
    	"""
		if(equalSide1 != -1):
			opposing = 0
			if(unequalSide == 0):
				opposing = self.distance(player_positions[2], player_positions[3]);
			elif(unequalSide == 1):
				opposing = self.distance(player_positions[1], player_positions[3]);
			elif(unequalSide == 2):
				opposing = self.distance(player_positions[1], player_positions[2]);

			if(opposing == sides[unequalSide]):
				diagonal = opposing
				adjacent = sides[equalSide1]
				is_Square = True
				for a in range(0,4):
					diagonalCount = 0
					adjacentCount = 0 
					for b in range(0,4):
						if(a != b):
							distance1 = self.distance(player_positions[a], player_positions[b]);
							if(distance1 == diagonal):
								diagonalCount += 1
							elif(distance1 == adjacent):
								adjacentCount += 1
					"""
						If there is one diagonal and two adjacents
					"""
					if((diagonalCount == 1 and adjacentCount == 2) != True):
						is_Square = False
						break;
				if(is_Square == True):
					"""
						There is a square
					"""
					return True
		return False

	def distance(self, point1, point2):
		"""
			Function to find the distance between any two tokens on the baord
		"""
		dist = math.pow(point1[0] - point2[0], 2) + math.pow(point1[1] - point2[1], 2);
		return dist

"""
	Calling the function
"""
hip_obj = hip()
hip_obj.take_input()
