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

The second approach is used in this code
"""

"""
This script is designed according to the human vs computer strategy. 
The player starts with an empty board and takes the turn first the follwed by the computer's turn.
This continues till the board is filled
"""

"""
	TODOS:	1. Tidy up ----DONE
			2. Implementation of the human vs computer game plan ----DONE
			3. Creation of Game Tree
				a) Implementation of minimax ----DONE
				b) Implementation of alpha beta pruning ----DONE
"""
from itertools import combinations
import math
import copy
import sys

class hip:
	def take_input(self):
		"""
			Function to take input from the use of the board config
		"""

		data = []
		board = []
		player_positions = []
		for i in range(0,3): #We are defining the initial empty board For now we use a smaller board of 3*3
			for j in range(0,3):
				data.append('0')
			board.append(data)
			data = []

		print("\nThe initial board is");
		print(board) #Empty board

		self.AlphaBetaMinimax(board)

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
			"""
				populating the sides using three points of the combination
			"""
			sides = []
			sides.append(self.distance(item[0],item[1]));
			sides.append(self.distance(item[0],item[2]));
			sides.append(self.distance(item[0],item[3]));
			result = self.isSquare(sides,item)
			if(result == True):
				return result
		return False

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
	
					if((diagonalCount == 1 and adjacentCount == 2) != True): #If there is one diagonal and two adjacents
						is_Square = False
						break;
				if(is_Square == True): #There is a square
					return True
		return False

	def distance(self, point1, point2):
		"""
			Function to find the distance between any two tokens on the baord
		"""
		dist = math.pow(point1[0] - point2[0], 2) + math.pow(point1[1] - point2[1], 2);
		return dist


	"""
		Functions for the Implementation of Minimax Algorithm
	"""
	def AlphaBetaMinimax(self, board):
		player = True
		free_positions = self.populate_positions(board, '0')
		result = 0
		while(result == 0 and len(free_positions) != 0):
			if(player == True):
				flag = 0
				print "\nIts your turn! \nEnter the position where the token is to be placed: \n"
				while(flag == 0):
					x = raw_input("Enter the x position: ")
					y = raw_input("Enter the y position: ")
					if(board[int(x)][int(y)] == '0'):
						board[int(x)][int(y)] = '1'
						flag = 1
					else:
						print "\nThe position is already filled! Enter some other position!"
				print "\nUpdated board", board
				player = False
			else:
				print "\n\nComputer's turn"
				board = self.firstBestMove(board, 0)
				print "\nUpdated board", board
				player = True

			free_positions = self.populate_positions(board, '0')
			result = self.evaluate_game(board)
			if(result == 1):
				print "\nYou lose!"
			elif(result == 2):
				print "\nYou won!"

	def firstBestMove(self, board, depth):

		free_positions = self.populate_positions(board, '0')
		previous = -sys.maxint - 1
		depth += 1

		for position in free_positions:
			child = copy.deepcopy(board)
			child[int(position[0])][int(position[1])] = '2'
			current = self.min(child, depth, -sys.maxint - 1, sys.maxint)
			if(current > previous):
				bestChild = child
				previous = current
		return bestChild

	def max(self, board, depth, alpha, beta):

		free_positions = self.populate_positions(board, '0')
		result = self.evaluate_game(board)

		if(result == 1):
			return 10000-depth
		elif(result == 2):
			return depth-10000
		elif(result == 0 and len(free_positions) == 0):
			return 0

		depth += 1
		for position in free_positions:
			new_board = copy.deepcopy(board)
			new_board[int(position[0])][int(position[1])] = '2'
			move = self.min(new_board, depth, alpha, beta)
			if(move > alpha): #Find max and store in alpha
				alpha = move
			if(alpha >= beta): #Beta cut-off
				break
		return alpha

	def min(self, board, depth, alpha, beta):

		free_positions = self.populate_positions(board, '0')
		result = self.evaluate_game(board)

		if(result == 1):
			return 10000-depth
		elif(result == 2):
			return depth-10000
		elif(result == 0 and len(free_positions) == 0):
			return 0

		depth += 1
		for position in free_positions:
			new_board = copy.deepcopy(board)
			new_board[int(position[0])][int(position[1])] = '1'
			move = self.max(new_board, depth, alpha, beta)
			if(move < beta): #Find min and store in beta
				beta = move
			if(alpha >= beta): #alpha cut-off
				break
		return beta

	def evaluate_game(self, board):
		player_positions = self.populate_positions(board, '1')
		player_result = self.check_square(player_positions)
		computer_positions = self.populate_positions(board, '2')
		computer_result = self.check_square(computer_positions)
		if(player_result == True):
			return 1
		elif(computer_result == True):
			return 2
		else:
			return 0

"""
	Calling the function
"""
hip_obj = hip()
hip_obj.take_input()
