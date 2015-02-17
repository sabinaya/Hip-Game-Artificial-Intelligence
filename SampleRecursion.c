#include<stdio.h>
#define N 3


// node of the graph = data+list(pointers) representing the children 
// look at : http://pages.cs.wisc.edu/~vernon/cs367/notes/13.GRAPH.html
// http://scienceblogs.com/goodmath/2007/09/16/games-and-graphs-searching-for/
// https://www.cs.bu.edu/teaching/c/graph/linked/

void recursion_game(int element[N][N], int row, int col);

int main()
{
	int game_state[3][3] = {0,0,0,2,0,2,1,0,1};
	recursion_game(game_state,0,0);
	return 1;
}

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