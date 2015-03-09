#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#define N 3

typedef struct
{
	int x,y;
}position;

typedef struct
{
	position p1,p2;
    int distance;
}side;

typedef enum { false, true } bool;

position * get_free_positions(int [N][N],int );
int num_free_positions(int [N][N]);
position * populate_free_positions(int [N][N], int );
int combinations_AllPositions(position [], int , int , int , position [], int ,int flag);
bool isSquare(side [], position []);
int distance(position , position );
void create_GameTree(int [N][N],int );
int max(int [N][N], int ,int ,int ,int );
int min(int [N][N], int ,int ,int ,int );
int Maximum(int , int );
int Minimum(int , int );

// Main function
// TODOS : 1. Implement minimax algorithm -----DONE
//         2. Include Depth in the implementation of minimax algorithm -----DONE
//         3. Implement alpha-beta pruning -----DONE
//         4. Write test cases and find the accuracy of the algorithm
//         5. Optimize the code
int main()
{
	int board[N][N];
	int player;

	printf("\nEnter the current Player.... 1. Red     2. Blue");
	scanf("%d",&player);

	printf("\n Enter the Grid elements!\n\n 1--> To represent red tokens\n\n 2--> To represent blue tokens\n\n 3---> To represent blank position\n\n");

	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
            printf("\n Position (%d,%d):", i,j);
			scanf("%d",&board[i][j]);
		}	
    }
    if(num_free_positions(board))
    {
        create_GameTree(board,player);
    }
    else
    {
        printf("\nNo next possible boards available");
    }
    return 1;
}

// Function to find all the next possible states and return if the game ends or not
void create_GameTree(int board[N][N], int player)
{
    int possible_board[N][N];
    int best_child[N][N];
	position *free_positions;
    position empty_positions[N*N];
    int free_pos_size;
    int pos = 0;  // To track the size of the positions array 
    int previous = -5000000;
    int depth = -1;
    int a1 = -5000000;
    int b1 = 5000000;
	
    // ----------------------------------------- Sample printing for verification ---------------------------------------------
    printf("\nInitial Matrix\n");
    for(int i=0;i<N;i++)
    {
    	for(int j=0;j<N;j++)
    	{
    		printf("%d",board[i][j]);
    	}
    	printf("\n");
    }	
    // ------------------------------------------------------------------------------------------------------------------------

    
    // Populating free positions to substitute values and find all the next possible positions
    free_positions = populate_free_positions(board,0);
    free_pos_size = (free_positions + 0)->x;      // Size of the free positions array


    // Copying the array values into a seperate array (Empty positios array)
    for(int i = 1; i <= free_pos_size; i++)
    {
        empty_positions[pos].x = (free_positions + i)->x;
        empty_positions[pos].y = (free_positions + i)->y;
        pos++;
    }

    // Free the memory after copying the values
    free(free_positions);


    // ----------------------------------------- Sample printing for verification ---------------------------------------------
    printf("\nPossible position board ----- free positions\n");

    for (int i = 0; i < free_pos_size; i++ )
    {
        printf("\n%d,%d ---- ",empty_positions[i].x,empty_positions[i].y);
    }

    // ------------------------------------------------------------------------------------------------------------------------
    

    // Iterating through the free positions to evaluate all the next possible positions
    for (int i = 0; i < free_pos_size; i++ )
    {
        // Refreshing the board to get ready for the next possible position
        for(int r=0; r<N; r++)
        {
            for(int s=0; s<N; s++)
            {
                possible_board[r][s] = board[r][s];
            }
        }   

        // Replacing each empty board position with the player token
        possible_board[empty_positions[i].x][empty_positions[i].y] = player;


        // ----------------------------------------- Sample printing for verification ---------------------------------------------
        printf("\nPossible boards\n");
        for(int r=0; r<N; r++)
        {
            for(int s=0; s<N; s++)
            {
                printf("%d", possible_board[r][s]);
            }
            printf("\n");
        }  
        // ------------------------------------------------------------------------------------------------------------------------

        int current = min(possible_board,player,depth,a1,b1);
        printf("\nChild Score: %d",current);

        if(current > previous)
        {
            for(int r=0; r<N; r++)
            {
                for(int s=0; s<N; s++)
                {
                    best_child[r][s] = possible_board[r][s];
                }
            }
            previous = current;
        }
    }
    printf("\nThe final best child is:\n");
    for(int r=0; r<N; r++)
    {
        for(int s=0; s<N; s++)
        {
            printf("%d",best_child[r][s]);
        }
        printf("\n");
    }
    return;
}	


int max(int possible_board[N][N], int player, int depth, int a1, int b1)
{
    position *possible_board_positions;
    position player_positions[N*N];
    int board[N][N];

    position *free_positions;
    int free_pos_size;
    position empty_positions[N*N];
    // To hold the size of the position array
    int pos = 0;
    int flag;
    int move;

    // Populate the player token positions to see if any combination of 4 tokens form a square
    possible_board_positions = populate_free_positions(possible_board,player);

    // Copying the array values into a seperate array (Player positios array)
    for(int k = 1; k <= (possible_board_positions + 0)->x; k++)
    {
        player_positions[pos].x = (possible_board_positions + k)->x;
        player_positions[pos].y = (possible_board_positions + k)->y;
        pos++;
    }

    // Declare an empty array --- for storing the four positions in combinations_AllPositions()
    position data[(possible_board_positions + 0)->x];

    // Call the function which takes a board as parameter to find whether the player tokens form a square
    flag = combinations_AllPositions(player_positions, (possible_board_positions + 0)->x, 4, 0, data, 0, 0);
    depth++;

    // Displaying the result of the current board state
    if(flag == 1 && player == 1)
        return 1000-depth;
    else if(flag == 1 && player == 2)
        return depth-1000;
    else if (flag == 0 && num_free_positions(possible_board) == 0)
        return 0;
    else
    {
        free_positions = populate_free_positions(possible_board,0);
        free_pos_size = (free_positions + 0)->x;      // Size of the free positions array
        pos = 0;
        int alpha = -5000000;
        int beta = 5000000;

        // ----------------------------------------- Sample printing for verification ---------------------------------------------

        // Copying the array values into a seperate array (Empty positios array)
        printf("\n---------------Inside max ------------ empty positions");
        for(int i = 1; i <= free_pos_size; i++)
        {
            empty_positions[pos].x = (free_positions + i)->x;
            empty_positions[pos].y = (free_positions + i)->y;
            printf("\n%d,%d", empty_positions[pos].x,empty_positions[pos].y);
            pos++;
        }
        // ------------------------------------------------------------------------------------------------------------------------

        for(int i=0; i<pos; i++)
        {
            // Refreshing the board to get ready for the next possible position
            for(int r=0; r<N; r++)
            {
                for(int s=0; s<N; s++)
                {
                    board[r][s] = possible_board[r][s];
                }
            }   

            // Replacing each empty board position with the player token
            board[empty_positions[i].x][empty_positions[i].y] = 2;

            // ----------------------------------------- Sample printing for verification ---------------------------------------------

            printf("\nBoard ---------\n");
            for(int r=0; r<N; r++)
            {
                for(int s=0; s<N; s++)
                {
                    printf("%d",board[r][s]);
                }
                printf("\n");
            }
            // ------------------------------------------------------------------------------------------------------------------------

            move = min(board,2,depth,a1,Minimum(b1,beta));
            beta = Minimum(beta,move);
            if(a1 > beta)
                return beta;
        }
        return beta;
    }

    // Free the possible positions array
    free(possible_board_positions);
    free(free_positions);
}


int min(int possible_board[N][N], int player, int depth, int a1, int b1)
{

    position *possible_board_positions;
    position player_positions[N*N];
    int board[N][N];

    position *free_positions;
    int free_pos_size;
    position empty_positions[N*N];
    // To hold the size of the position array
    int pos = 0;
    int flag;
    int move;

    // Populate the player token positions to see if any combination of 4 tokens form a square
    possible_board_positions = populate_free_positions(possible_board,player);

    // Copying the array values into a seperate array (Player positios array)
    for(int k = 1; k <= (possible_board_positions + 0)->x; k++)
    {
        player_positions[pos].x = (possible_board_positions + k)->x;
        player_positions[pos].y = (possible_board_positions + k)->y;
        pos++;
    }

    // Declare an empty array --- for storing the four positions in combinations_AllPositions()
    position data[(possible_board_positions + 0)->x];

    // Call the function which takes a board as parameter to find whether the player tokens form a square
    flag = combinations_AllPositions(player_positions, (possible_board_positions + 0)->x, 4, 0, data, 0, 0);
    depth++;

    // Displaying the result of the current board state
    if(flag == 1 && player == 1)
        return 1000-depth;
    else if(flag == 1 && player == 2)
        return depth-1000;
    else if (flag == 0 && num_free_positions(possible_board) == 0)
        return 0;
    else
    {
        int alpha = -5000000;
        int beta = 5000000;
        free_positions = populate_free_positions(possible_board,0);
        free_pos_size = (free_positions + 0)->x;      // Size of the free positions array
        pos = 0;

        // ----------------------------------------- Sample printing for verification ---------------------------------------------

        // Copying the array values into a seperate array (Empty positios array)
        printf("\n---------------Inside min ------------ empty positions");
        for(int i = 1; i <= free_pos_size; i++)
        {
            empty_positions[pos].x = (free_positions + i)->x;
            empty_positions[pos].y = (free_positions + i)->y;
            printf("\n%d,%d", empty_positions[pos].x,empty_positions[pos].y);
            pos++;
        }
        // ------------------------------------------------------------------------------------------------------------------------


        for(int i=0; i<pos; i++)
        {
            // Refreshing the board to get ready for the next possible position
            for(int r=0; r<N; r++)
            {
                for(int s=0; s<N; s++)
                {
                    board[r][s] = possible_board[r][s];
                }
            }   

            // Replacing each empty board position with the player token
            board[empty_positions[i].x][empty_positions[i].y] = 1;

            // ----------------------------------------- Sample printing for verification ---------------------------------------------
            printf("\nBoard ---------\n");
            for(int r=0; r<N; r++)
            {
                for(int s=0; s<N; s++)
                {
                    printf("%d",board[r][s]);
                }
                printf("\n");
            }
            // ------------------------------------------------------------------------------------------------------------------------

            move = max(board,1,depth,Maximum(a1,alpha),b1);
            alpha = Maximum(alpha,move);
            if(alpha > b1)
                return alpha;
        }
        return alpha;
    }

    // Free the possible positions array
    free(possible_board_positions);
    free(free_positions);
}

int Maximum(int a, int b)
{
    if(a > b)
        return a;
    else
        return b;
}

int Minimum(int a, int b)
{
    if(a < b)
        return a;
    else
        return b;
}


// Function to take the current board state and and the player and populates the positions of the tokens
position * populate_free_positions(int board[N][N], int player)
{
	position *positions;
    positions=(position*)calloc(N*N,sizeof(position));
    int pos =1;
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            if(board[i][j] == player)
            {
                (positions+pos)->x = i;
                (positions+pos)->y = j;
                pos++;
            }
        }   
        (positions+0)->x = pos-1;
        (positions+0)->y = pos-1;
    }
    return positions;
}

// This function takes the board as input and returns tha number of free positions in the board
int num_free_positions(int board[N][N])
{
	int count = 0; 
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			if(board[i][j] == 0)
			{
				count++;	
			}
		}
	}
	return(count);
}

// Function to produce all the combinations of 4 eleents of all the positions given 
int combinations_AllPositions(position arr[], int n, int r, int index, position data[], int i, int flag)
{
    // ----------------------------------------- Sample printing for verification ---------------------------------------------
	// printf("\nInitial matrix of all combinations .... ");
	// for(int q=0; q<n; q++)
	// {
	// 	printf("\n%d,%d", arr[q].x,arr[q].y);
	// }
    // ------------------------------------------------------------------------------------------------------------------------


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
            flag = 1;
            for (int j=0; j<r; j++)
            printf("\n(%d,%d) ",data[j].x, data[j].y);
            printf("\n");
            printf("\n The points form a square!\n");
            return 1;
        }
		return 0;
    }
    // When no more elements are there to put in data[]
    else if (i >= n && flag==0)
       return 0;
    // 1st recursive statement - current is included, put next at next location
    // 2nd recursive statement - current is excluded, replace it with next (Note that i+1 is passed, but index is not changed)
    else if(flag == 0)
    {
        data[index] = arr[i];
        return (combinations_AllPositions(arr, n, r, index+1, data, i+1, flag) || combinations_AllPositions(arr, n, r, index, data, i+1, flag));	
    }
    else
    {
	   return 0;
    }
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

// Function to find the distance between any two tokens on the baord
int distance(position point1, position point2)
{
    int dist = pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2);
    return dist;
}