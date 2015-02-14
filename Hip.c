#include<stdio.h>
#include<math.h>

// structure to store the positions of the tokens on the board
typedef struct
{
	int x,y;
}position;

//structure to store distances between points
typedef struct
{
	int p1,p2,distance;
}side;

typedef enum { false, true } bool;

// Declaration of Functions
bool check_SquarePresence(position [],int );
int distance(position , position );
bool isSquare(side [], position []);

// Main Function

//	1. Function that takes the state of the board as input and returns whether it contains a square or not (given there are only 4 tokens on the board) ---- DONE
//  2. Extend the Function isSquare to find squares (given many token on the board) 
//  3. Generalize the function to take two kinds of tokens which represent two kinds of tokens

int main()
{
	// 3x3 matrix to represent the board
	int board[3][3];
	position positions[9];

	// get a sample board state from the user (grid containing 0s and 1s, 1s representing the presents of a token)
	// For now, take smaple containing only 4 tokens
	printf("\n Enter the Grid elements!\n");
	int pos =0;
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			scanf("%d",&board[i][j]);
			if(board[i][j] != 0)
			{
				positions[pos].x = i;
				positions[pos].y = j; 
				pos++;
			}
		}
	}

	// pos =0;
	// for(int i=0; i<9; i++)
	// {
	// 	printf("\nx:%d\ty:%d\n",positions[pos].x, positions[pos].y);
	// 	pos++;
	// }
	
	bool result = check_SquarePresence(positions,pos);
	return 1;
}

bool check_SquarePresence(position positions[],int pos_size)
{
	side sides[100];
	int pos = 0;
	for(int i=0; i<pos_size; i++)
	{
		for(int j=0; j<pos_size; j++)
		{
			if(i != j)
			{
				sides[pos].p1 = i;
				sides[pos].p2 = j;
				sides[pos].distance = distance(positions[i], positions[j]);
				pos++;
			}
		}
	}

	bool result = isSquare(sides,positions);
	if(result == true)
		printf("\n The points form a square!");
	else
		printf("\n The points does not form a square!");

	
	return 1;
}

int distance(position point1, position point2)
{
	int dist = pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2);
	return dist;
}

// Function to check if the given four points form a square
bool isSquare(side sides[], position positions[])
{
	int equalSide1 = -1;
	int equalSide2 = -1;
	int unequalSide = -1;

	if (sides[0].distance == sides[1].distance) {
        if (sides[0].distance != sides[2].distance) {
            equalSide1 = 0;
            equalSide2 = 1;
            unequalSide = 2;
        }
    } else if (sides[1].distance == sides [2].distance) {
        if (sides[1].distance != sides[0].distance) {
            equalSide1 = 1;
            equalSide2 = 2;
            unequalSide = 0;        
        }
    } else if (sides[0].distance == sides[2].distance) {
        if (sides[0].distance != sides[1].distance) {
            equalSide1 = 0;
            equalSide2 = 2;
            unequalSide = 1;
        }
    }

    // If failed to satisfy the above condition, the points doesn't form a square
    // Otherwise check for the square distance conditions
    if (equalSide1 != -1)
    {
        int opposing = 0;
        switch (unequalSide) {
            case 0:
                opposing = distance(positions[2], positions[3]);
                break;
            case 1:
                opposing = distance(positions[1], positions[3]);
                break;
            case 2:
                opposing = distance(positions[1], positions[2]);
                break;
            default:
                break;
        }
        
        if (opposing == sides[unequalSide].distance) {       
            int diagonal = opposing;
            int adjacent = sides[equalSide1].distance;
            int is_Square= true;
            for (int a = 0; a < 4; a++) {
                int diagonalCount = 0;
                int adjacentCount = 0;                
                for (int b = 0; b < 4; b++) {
                    if (a != b) {
                        int dist = distance(positions[a], positions[b]);
                        if (dist == diagonal) {
                            diagonalCount++;
                        } else if (dist == adjacent) {
                            adjacentCount++;
                        }
                    }
                }
                // If there is one diagonal and two adjacents
                if (! (diagonalCount == 1 && adjacentCount == 2)){
                    is_Square= false;
                    break;
                }
            }
            if (is_Square) {
                // There is a square
                return true;
            }
        }
    }
    return false;
}


