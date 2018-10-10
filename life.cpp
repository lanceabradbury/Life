#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

//This is one of the bugs in conway's game of life
//It has functions that return and alter status
class bug
{
	int alive, lastTurn;
	public:
		int isAlive() { return alive; }
		void live() { alive = 1; }
		void die() { alive = 0; }
		int last() { return lastTurn; }
		void sLast() { lastTurn = alive; }
};

//printgrid is a way to print a grid of bugs to check 
//on how the game of life is going
void printgrid(bug grid[60][60])
{
	for(int i = 0; i < 60; i++)
	{
		for(int j = 0; j < 60; j++)
		{
			printf("%d ", grid[i][j].isAlive());
		}
		printf("\n");
	}
}

int main()
{
	//using a 60 by 60 grid for the game of life
	bug grid[60][60];

	
	srand(time(NULL));
	int r;
	int numAlive = 0;

	//randomly generating the starting board
	for(int i = 0; i < 60; i++)
	{
		for(int j = 0; j < 60; j++)
		{
			r = rand() % 10 + 1;
			if(r==1)
			{
				grid[i][j].live();
				numAlive++;
			}
			else
				grid[i][j].die();
		}
	}
	printf("Number of starting alive: %d\n", numAlive);
	printgrid(grid);
	int numTurns = 0;

	while(numAlive > 0)
	{
		for(int i = 0; i < 60; i++)
		{
			for(int j = 0; j < 60; j++)
			{
				grid[i][j].sLast();
			}
		}
		for(int i = 0; i < 60; i++)
		{
			for(int j = 0; j < 60; j++)
			{
				int neighbors;
				if(i == 0)
				{
					if(j == 0)
					{
						neighbors = grid[59][59].last() + grid[59][j].last() + grid[59][j+1].last() +
						grid[i][59].last() + grid[i][j+1].last() + grid[i+1][59].last() + grid[i+1][j].last() + grid[i+1][j+1].last();
					}
					else
					{
						neighbors = grid[59][j-1].last() + grid[59][j].last() + grid[59][j+1].last() +
						grid[i][j-1].last() + grid[i][j+1].last() + grid[i+1][j-1].last() + grid[i+1][j].last() + grid[i+1][j+1].last();
					}
				}
				else if(j == 0)
				{
					neighbors = grid[i-1][59].last() + grid[i-1][j].last() + grid[i-1][j+1].last() +
					grid[i][59].last() + grid[i][j+1].last() + grid[i+1][59].last() + grid[i+1][j].last() + grid[i+1][j+1].last();
				}
				else
				{
					neighbors = grid[i-1][j-1].last() + grid[i-1][j].last() + grid[i-1][j+1].last() +
					grid[i][j-1].last() + grid[i][j+1].last() + grid[i+1][j-1].last() + grid[i+1][j].last() + grid[i+1][j+1].last();
				}
				if(neighbors < 2 && grid[i][j].isAlive() == 1)
				{
					grid[i][j].die();
					numAlive--;
				}
				else if (neighbors > 3 && grid[i][j].isAlive() == 1)
				{
					grid[i][j].die();
					numAlive--;
				}
				else if (grid[i][j].isAlive() == 0 && neighbors == 3)
				{
					grid[i][j].live();
					numAlive++;
				}
			}
		}
		numTurns++;
		printf("Number alive after %d turns is %d\n", numTurns, numAlive);
		printgrid(grid);
	}
	
	
	
	return 0;
}
