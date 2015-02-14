#include<stdio.h>

int main()
{
	// 9x9 matrix to represent the board
	int board[3][3];

	// get a sample board state from the user (grid containing 0s and 1s, 1s representing the presents of a token)
	printf("\n Enter the Grid elements!\n");
	for(int i=0; i<3; i++)
		for(int j=0; j<3; j++)
			scanf("%d",&board[i][j]);

	/*for(int i=0;i<3;i++)
	{
		for(int j=0; j<3; j++)
		{
			printf("\tboard[%d][%d]: %d", i,j,board[i][j]);
		}
		printf("\n");
	}*/
	return 1;
}

//TODOs:	1. create a function that takes the state of the board as input and returns whether it contains a square or not
// 			2. Generalize the function to take two kinds of tokens which represent two kinds of tokens