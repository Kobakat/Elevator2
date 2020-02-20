#include <stdio.h>
#include <stdlib.h>


void ChangeFloor(int start, int size, int floors[], int * list)
{
	printf("\nHere we go!\n\n");

	for(int i = 0; i < size; i++)
	{
		int difference = *(list + i) - start;
		
		//decrease if change in floors is negative
		if (difference < 0) 
		{
			for(int k = start; k > *(list + i); k--) 
			{
				printf("%d, ", floors[k-2]);
			}
			printf("Ding!\n");
		}	
	
		//increase if change in floors is positive
		else if (difference > 0)
		{
			for(int k = start; k < *(list + i); k++)
			{
				printf("%d, ", floors[k]);
			}
			printf("Ding!\n");
		}

		//If no net floor change occurs
		else
		{
			printf("Oops! You're already on that floor!\n");
		}
		
		start = *(list + i);
	}	
}


//Organizes the desired floors input by the user into a dynamically sized array
int * AssignFloors(int numOfFloors) 
{
	int * list;
	

	//Clear/allocate memory for a list array
	list = calloc(numOfFloors, sizeof(int));
	
	for(int j = 0; j < numOfFloors; j++) 
	{
		int chosenFloor = 0;
		
		printf("Enter floor number #%d\n", j+1);
		scanf("%d", &chosenFloor);

		//incorrect floor chosen
		if(chosenFloor > 15 || chosenFloor < 1) 
		{
			printf("That is not a valid floor! Choose between 1-15.\n");
			j--;
		}
		
		//proper floor chosen
		else
		{	
			*(list + j) = chosenFloor;
		}
	}

	//Organize the array by least to greatest
	for(int first = 0; first < numOfFloors; first++) 
	{
		for(int second = first + 1; second < numOfFloors; second++)
		{
			if(*(list + first) > *(list + second))
			{
				int hold = *(list + first);
				*(list + first) = *(list + second);
				*(list + second) = hold;
			}
		}
	}

	return list;
}

int main() 
{
	int floors[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
	char again = 'y';
	int currentFloor = floors[0];
	
	do 
	{
		int numOfFloors = 0;
		
		printf("You are currently on floor %d. The top floor is 15.\n", currentFloor);
		printf("How many floors would you like to go to? ");

		//Used to determine the size of the array
		scanf("%d", &numOfFloors);
		//floorList points to an array of size numOfFloors
		int * floorList = AssignFloors(numOfFloors);



		//Text showing the changing of floors
		ChangeFloor(currentFloor, numOfFloors, floors, floorList);
		currentFloor = *(floorList + numOfFloors - 1);
		free(floorList);

		
		printf("Would you like to change floors? Enter y if yes or any other key if not.\n");

		//This scanf function turns floor[0] = 0. Why?
		scanf("%s", &again);

		//"Fixing" the above issue?
		floors[0] = 1; 

		printf("\n");

	} while(again == 'y');

	return 0;
}

