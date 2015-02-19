/** 

	Hip Game
	Author:
	LICENSE: MIT License

 */


/** Function_name = what it does */


#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#define N 3

// structure to store the positions of the tokens on the board
typedef struct
{
	int x,y;
}position;

//structure to store distances between points
typedef struct
{
	position p1,p2;
    int distance;
}side;

// structure to define the state of the board in the game tree

typedef struct {

    int board_state[3][3];
    int heuristic_value;

}graph_node;

typedef struct vertexTag {

    graph_node element;
    struct edgeTag *edges;
    struct vertexTag *next;

} vertexT;

typedef struct edgeTag {
    struct vertexTag *connectsTo;
    struct edgeTag *next;
} edgeT;

typedef struct gameTree {
    vertexT *vertices;
} gameTree;

// TODOS: use linked list representation of directed graphs to construct game tree 

typedef enum { false, true } bool;

// TODOS: use linked list representation of directed graphs to construct game tree 
// node of the graph = data+list(pointers) representing the children

// Declaration of Functions
void check_SquarePresence(position [],int );
void combinations_AllPositions(position arr[],int n,int r,int index,position data[],int i);
int distance(position , position );
bool isSquare(side [], position []);
void create_GameTree();
void recursion_game(int element[N][N], int row, int col);

// Main Function

// TODOS:
//	1. Function that takes the state of the board as input and returns whether it contains a square or not (given there are only 4 tokens on the board) ---- DONE
//  2. Extend the Function isSquare to find squares (given many token on the board) ---- DONE
//  3. Refine the code ---- DONE
//  4. Generalize the function to take two kinds of tokens ---- DONE
//  5. Formulate a game tree
//     * Function to generate all the children of a particular game state ---- DONE
//     * Construct a directed graph using linked list (structure for vertex and edge ---- DONE)

int main()
{
	// 3x3 matrix to represent the board
	int board[3][3];
	position positions1[9];
	position positions2[9];

	// get a sample board state from the user (grid containing 0s and 1s, 1s representing the presents of a token)
	// For now, take sample containing only tokens of only one kind
	printf("\n Enter the Grid elements!\n\n 1--> To represent red tokens\n\n 2--> To represent blue tokens\n\n 3---> To represent blank position\n\n");
	int pos1 =0;
    	int pos2 =0;

	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
            		printf("\n Position (%d,%d):", i,j);
			scanf("%d",&board[i][j]);
			if(board[i][j] == 1)
			{
				positions1[pos1].x = i;
				positions1[pos1].y = j; 
				pos1++;
			}
            		else if(board[i][j] == 2)
            		{
                		positions2[pos2].x = i;
                		positions2[pos2].y = j; 
                		pos2++;
            		}
		}	
    	}
	
    printf("\n ------------------------- Red tokens -------------------------");
	check_SquarePresence(positions1,pos1);
    printf("\n ------------------------ Blue  tokens ------------------------");
    check_SquarePresence(positions2,pos2);
    create_GameTree();
	return 1;
}

void check_SquarePresence(position positions[],int pos_size)
{
    // A temporary array to store all combination one by one
    position data[pos_size];
    
	// taking all combinations of the positions of size 4
	combinations_AllPositions(positions, pos_size, 4, 0, data, 0);
	return;
}

/*** 
   arr[]  ---> Input Array
   n      ---> Size of input array
   r      ---> Size of a combination to be printed
   index  ---> Current index in data[]
   data[] ---> Temporary array to store current combination
   i      ---> index of current element in arr[]     
*/


void combinations_AllPositions(position arr[], int n, int r, int index, position data[], int i)
{
    // Current combination is ready ---> call distance function and store the distance
    if (index == r)
    {
        side sides[100];
        int pos = 0;
        int curr = 0;
        for(int j=0; j<r; j++)
        {
            if(curr != j)
            {
                sides[pos].p1 = data[curr];
                sides[pos].p2 = data[j];
                sides[pos].distance = distance(data[curr], data[j]);
                pos++;
            }
        }
        bool result = isSquare(sides,data);
        if(result == true)
        {
            for (int j=0; j<r; j++)
            printf("\n(%d,%d) ",data[j].x, data[j].y);
            printf("\n");
            printf("\n The points form a square!\n");
        }
        return;
    }
 
    // When no more elements are there to put in data[]
    if (i >= n)
        return;
 
    // current is included, put next at next location
    data[index] = arr[i];
    combinations_AllPositions(arr, n, r, index+1, data, i+1);
 
    // current is excluded, replace it with next (Note that
    // i+1 is passed, but index is not changed)
    combinations_AllPositions(arr, n, r, index, data, i+1);
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

//Construction of Game Tree
void create_GameTree()
{
    vertexT *game_tree;
    vertexT *start;
    vertexT *temp;
    int game_state[3][3] = {0,0,0,0,0,0,0,0,0};
    start = (vertexT *)malloc(sizeof(vertexT));
    game_tree = start;
    memcpy(start->element.board_state, game_state, N * N * sizeof(int));
    // for(int i=0; i<3; i++)
    //     for(int j=0; j<3; j++)
    //         printf("%d",start->element.board_state[i][j]);
    start->edges = NULL;
    start->next = NULL;

}


// This function on giving a matrix, will produce all its children
void recursion_game(int element[N][N], int row, int col)
{
    if(row == 2 && col >2)
    {
        return;
    }
    int temp [N][N];
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            temp[i][j] = element[i][j];
        }
    }

    if(element[row][col] == 0)
    {
        temp[row][col] = 3;
    }
    printf("------------\n");
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            printf("%d", temp[i][j]);
        }
    }
    if(col > 2)
    {
        col = 0;
        row = row+1;
    }
    col = col+1;
    recursion_game(element,row,col);
    //printf("++++++++ row = %d, col = %d\n", row,col);
}

