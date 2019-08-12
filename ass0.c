/*********************************************************************************************************************
Filename: ass0.c
Version: 1.0
Author: Felipe de Paula Souza Filho
Student Number: 040843714
Course: Numerical CST8233
Lab Section: 300
Assignment number : 0
Due date: January 27 2019
Submition date: January 25 2019
Professor name: Andrew Tyler
Purpose: To run a c program that allows the user to insert, edit, report, and delete a frame using a linked list.
*********************************************************************************************************************/
// ass0.c
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC	// need this to get the line identification
//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF); // in main, after local declarations
//NB must be in debug build

#include <crtdbg.h>
#include <stdio.h>
#include <string.h>

typedef enum { FALSE = 0, TRUE } BOOL;

struct Frame {
	char* frameName;
	struct Frame* pNext;
};

typedef struct {
	char* animationName;
	struct Frame* frames;
}Animation;

// Forward declarations
void InitAnimation(Animation*);
void InsertFrame(Animation*);
void DeleteFrame(Animation*);
void EditFrame(Animation*);
void ReportAnimation(Animation*);
void CleanUp(Animation*);

int main(void)
{
	char response;
	BOOL RUNNING = TRUE;
	Animation RG;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	InitAnimation(&RG);

	while (RUNNING)
	{
		printf("MENU\n 1. Insert a Frame at the front\n 2. Delete last Frame\n 3. Edit a Frame\n 4. Report the Animation\n 5. Quit\n");
		scanf("%c", &response);
		switch (response)
		{
		case '1':InsertFrame(&RG); break;
		case '2':DeleteFrame(&RG); break;
		case '3':EditFrame(&RG); break;
		case '4':ReportAnimation(&RG); break;
		case '5':RUNNING = FALSE; CleanUp(&RG); break;
		default:printf("Please enter a valid option\n");
		}
	}
	return 0;
}

/***********************************************************************************************************
Function name: InitAnimation
Purpose: set frames to zero
In parameters: It takes a ponter called animation which ponts to animation
Out parameters: void
Version: 1.0
Author: Felipe de Paula
***********************************************************************************************************/
void InitAnimation(Animation* animation) { // Forward declarations - set frames to zero 
	animation->frames = NULL;
}

/***********************************************************************************************************
Function name: InsertFrame
Purpose: To insert a frame into the animation giving it a name
In parameters: It takes a ponter called animation which ponts to animation
Out parameters: void
Version: 3.1
Author: Felipe de Paula
***********************************************************************************************************/
void InsertFrame(Animation* animation) {

	char name[256];
	char *fName;

	struct Frame* nFrame = (struct Frame*)malloc(sizeof(struct Frame));

	struct Frame* tempFrame = animation->frames; // points to the first which is the head of the list

	//Animation * new_animation;
	//new_animation = malloc(strlen(Animation) + 1);

	printf("Insert a Frame in the Animation \nPlease enter the Frame filename: ");
	scanf("%s", &name);
	fName = (char*)malloc((strlen(name) + 1) * sizeof(char));
	strcpy(fName, name);

	if (animation->frames == NULL)
	{
		nFrame->frameName = fName;
		animation->frames = nFrame;
		animation->frames->pNext = NULL;
		getchar();
		return;
	}

	nFrame->frameName = fName;
	animation->frames = nFrame;
	nFrame->pNext = tempFrame;

	getchar();	
}

/***********************************************************************************************************
Function name: DeleteFrame
Purpose: To delete the last frame in the animation
In parameters: It takes a ponter called animation which ponts to animation
Out parameters: void
Version: 2.3
Author: Felipe de Paula
***********************************************************************************************************/
void DeleteFrame(Animation* animation) { //a4 a3 a2 a1 
	struct Frame* tempFrame = animation->frames; //head a4
	struct Frame* tempFrameTwo = animation->frames; //head a4
	int counter = 0;

	if (tempFrame == NULL) {
		printf("There are no frames in the animation\n");
		getchar();
		return;
	}

	while (tempFrame->pNext != NULL) {
		tempFrameTwo = tempFrame; // a4 a3 a2
		tempFrame = tempFrame->pNext; // a3 a2 a1
		counter++;

	}

	//printf("Last frame is: %s\n", tempFrame->frameName);
	free(tempFrame->frameName);
	free(tempFrame);
	tempFrameTwo->pNext = NULL;

	if (counter == 0) {
		animation->frames = NULL;
	}

	getchar();
}

/***********************************************************************************************************
Function name: EditFrame
Purpose: To replaced a existing frame
In parameters: It takes a ponter called animation which ponts to animation
Out parameters: void
Version: 3.7
Author: Felipe de Paula
***********************************************************************************************************/
void EditFrame(Animation* animation) {
	struct Frame* numOfFrames = animation->frames;
	char name[256];
	char *fName;
	int counter = 0;
	int indexToSpecify = counter + 1;
	int index = 0;

	if (numOfFrames == NULL) {
		printf("There are no frames in the animation\n");
		getchar();
		return;
	}

	while (numOfFrames) {
		numOfFrames = numOfFrames->pNext;
		counter++;
	}

	printf("Edit a Frame in the animation\nThere are %d frame(s) in the list. Please specify the index (<= %d) to edit at : ", counter, counter - 1);
	scanf("%d", &index);

	if (index >= counter || index < 0) {
		printf("This index number does not exist... please try again\n");
		getchar();
		return;
	}

	numOfFrames = animation->frames; //reset back to the beginning
	counter = 0; //reset counter
	while (numOfFrames) {
		if (index == counter) {
			printf("The name of this Frame is %s. What do you wish to replace it with? ", numOfFrames->frameName);
			scanf("%s", &name);
			fName = (char*)malloc((strlen(name) + 1) * sizeof(char));
			strcpy(fName, name);
			free(numOfFrames->frameName);
			numOfFrames->frameName = fName;
			break;
		}
		numOfFrames = numOfFrames->pNext; //continue iterating through the list until it finds the index I want
		counter++;
	}

	getchar();
}

/***********************************************************************************************************
Function name: ReportAnimation
Purpose: To print all created frames in the animation
In parameters: It takes a ponter called animation which ponts to animation
Out parameters: void
Version: 1.5
Author: Felipe de Paula
***********************************************************************************************************/
void ReportAnimation(Animation* animation) {
	int counter = 0;
	//printf("Animation name is ");
	struct Frame* numOfFrames = animation->frames;

	if (numOfFrames == NULL) {
		printf("There are no frames in the animation\n");
		getchar();
		return;
	}
	printf("Report the Animation\n");
	while (numOfFrames) {
		printf("Image #%d, file name = %s\n", counter, numOfFrames->frameName);
		counter++;
		numOfFrames = numOfFrames->pNext;
	}
	getchar();
}

/***********************************************************************************************************
Function name: ReportAnimation
Purpose: To free all the space in memory when the program stop running
In parameters: It takes a ponter called animation which ponts to animation
Out parameters: void
Version: 3.5
Author: Felipe de Paula
***********************************************************************************************************/
void CleanUp(Animation* animation) {
	struct Frame* tempFrame = animation->frames;
	struct Frame* tempFrame2;

	while (tempFrame) {
		tempFrame2 = tempFrame;
		tempFrame = tempFrame->pNext;
		free(tempFrame2->frameName);
		free(tempFrame2);
	}

	animation->frames = NULL;
}
