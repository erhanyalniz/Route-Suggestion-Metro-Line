//Erhan Yalniz
/**The purpose of this program is to create a metro line and create the most suitable route 
to the user by using this metro line according to the data entered by the user.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define SIZE 10

typedef struct{
	char name[20];
	double x;
	double y;
}MetroStation;

typedef struct{
	char color[20];
	MetroStation MetroStations[SIZE];
}MetroLine;

typedef struct{
	char name[20];
	MetroLine MetroLines[SIZE];
}MetroSystem;

int equals(MetroStation s1, MetroStation s2);

void addStation(MetroLine* line,MetroStation station);

int hasStation(MetroLine line,MetroStation station);

MetroStation getFirstStop(MetroLine line);

MetroStation getPriorStop(MetroLine line,MetroStation station);

MetroStation getNextStop(MetroLine line,MetroStation station);

void addLine(MetroSystem* system,MetroLine line);

void printLine(MetroLine line);

void printPath(MetroStation stations[]);

double getDistanceTravelled(MetroStation stations[]);

MetroStation findNearestStation(MetroSystem system,double x,double y);

void getNeighboringStations(MetroSystem system,MetroStation station,MetroStation neighboringStations[]);

void createDuplicate(MetroStation source[],MetroStation dest[],MetroStation start);

void findPath(MetroStation start,MetroStation end,MetroStation path[]);

void recursiveFindPath(MetroStation start,MetroStation end,MetroStation partialPath[],MetroStation bestPath[]);

//Declare a MetroSystem with the name of istanbul and an empty content.
MetroSystem istanbul = {"istanbul", '\0'};

int main()
{
	int i;
	double myX=1, myY=2; 
	double goalX=62, goalY=45; 
	
	// define 3 metro lines, 9 metro stations, and an empty myPath
	MetroLine red={'\0'}, blue={'\0'}, green={'\0'};
	MetroStation s1, s2, s3, s4, s5, s6, s7, s8, s9;
	MetroStation myPath[SIZE]={'\0'};
	
	strcpy(red.color, "red"); 
	strcpy(blue.color, "blue");
	strcpy(green.color, "green");

	
	strcpy(s1.name, "Haydarpasa"); 		s1.x=0; 	s1.y=0;
	strcpy(s2.name, "Sogutlucesme"); 	s2.x=10; 	s2.y=5;
	strcpy(s3.name, "Goztepe"); 		s3.x=20; 	s3.y=10;
	strcpy(s4.name, "Kozyatagi"); 		s4.x=30; 	s4.y=35;
	strcpy(s5.name, "Bostanci"); 		s5.x=45; 	s5.y=20;
	strcpy(s6.name, "Kartal"); 			s6.x=55; 	s6.y=20;
	strcpy(s7.name, "Samandira"); 		s7.x=60; 	s7.y=40;
	strcpy(s8.name, "Icmeler"); 		s8.x=70; 	s8.y=15;
	
	//Add several metro stations to the given metro lines.
	addStation(&red, s1); addStation(&red, s2); addStation(&red, s3); addStation(&red, s4); addStation(&red, s5); addStation(&red, s8);
	
	addStation(&blue, s2); addStation(&blue, s3); addStation(&blue, s4); addStation(&blue, s6); addStation(&blue, s7);
	
	addStation(&green, s2); addStation(&green, s3); addStation(&green, s5); addStation(&green, s6); addStation(&green, s8);
	
	// Add red, blue, green metro lines to the Istanbul metro system.
	addLine(&istanbul, red);
	addLine(&istanbul, blue);
	addLine(&istanbul, green);
	
	// print the content of the red, blue, green metro lines
	printLine(red);
	printLine(blue);
	printLine(green);
		
		
	// find the nearest stations to the current and target locations
	MetroStation nearMe = findNearestStation(istanbul, myX, myY);
	MetroStation nearGoal = findNearestStation(istanbul, goalX, goalY);
	
	printf("\n");
	
	printf("The best path from %s to %s is:\n", nearMe.name, nearGoal.name);
	
	// if the nearest current and target stations are the same, then print a message and exit.
	if(equals(nearMe, nearGoal)){
		printf("It is better to walk!\n");
		return 0;
	}
	
	// Calculate and print the myPath with the minimum distance travelled from start to target stations.
	findPath(nearMe, nearGoal, myPath);
	
	if(strlen(myPath[0].name) == 0)
		printf("There is no path on the metro!\n");
	else{
		printPath(myPath);
	}
	return 0;

}

int equals(MetroStation s1, MetroStation s2){
	if(strcmp(s1.name,s2.name)==0){
		// If both stations have the same name then function will return 1.
		return 1; 
	}else{
		// 0 otherwise.
		return 0;
	}
}

void addStation(MetroLine* line,MetroStation station){
	int i;
	// Iterate over whole MetroLine until a MetroStation with no name reached.
	for(i=0;i<SIZE;i++){
		if(line->MetroStations[i].name[0]=='\0'){
			break;
		}
	}
	// Then set it to our parameter.
	line->MetroStations[i]=station;
}

int hasStation(MetroLine line,MetroStation station){
	int i;
	// Iterate over whole MetroLine until name of our parameter matches with current station.
	for(i=0;i<SIZE;i++){
		if(strcmp(line.MetroStations[i].name,station.name)==0){
			// Function will return 1 if matches.
			return 1;
		}
	}
	// 0 otherwise.
	return 0;
}

MetroStation getFirstStop(MetroLine line){
	// If first station doesn't have a name then return a empty MetroStation.
	if(line.MetroStations[0].name[0]=='\0'){
		MetroStation res;
		return res;
	}
	// Otherwise return first stop of MetroLine.
	return line.MetroStations[0];
}

MetroStation getPriorStop(MetroLine line,MetroStation station){
	MetroStation res;
	int i;
	// Iterate over whole MetroLine starting from second MetroStation because first MetroStation doesn't have a prior stop.
	for(i=1;i<SIZE;i++){
		// If we locate station we are looking for than return MetroStation before it.
		if(strcmp(line.MetroStations[i].name,station.name)==0){
			return line.MetroStations[i-1];
		}
	}
	// If not found than return empty MetroStation.
	return res;
}

MetroStation getNextStop(MetroLine line,MetroStation station){
	MetroStation res;
	int i;
	// Iterate over whole MetroLine until the last MetroStation because last MetroStation doesn't have a stop after itself.
	for(i=0;i<SIZE-1;i++){
		// If we locate station we are looking for than return MetroStation after it.
		if(strcmp(line.MetroStations[i].name,station.name)==0){
			return line.MetroStations[i+1];
		}
	}
	return res;
}

void addLine(MetroSystem* system,MetroLine line){
	int i;
	// Iterate over whole MetroSystem until a MetroLine with no color reached.
	for(i=0;i<SIZE;i++){
		if(system->MetroLines[i].color[0]=='\0'){
			break;
		}
	}
	// Then set it to our parameter.
	system->MetroLines[i]=line;
}

void printLine(MetroLine line){
	int i;
	// Print color of MetroStation.
	printf("Metroline %s:",line.color);
	// If first MetroStation is unnamed then MetroLine is empty.
	if(line.MetroStations[0].name[0]!='\0'){
		// First print first MetroStation of MetroLine with a long whitespace than print others.
		printf("    %s",line.MetroStations[0].name);
		for(i=1;i<SIZE;i++){
			// If current MetroStation is unnamed then we have reached end of MetroLine.
			if(line.MetroStations[i].name[0]=='\0'){
				break;
			}
			else{
				//Print MetroStations of MetroLine seperating by comma and whitespace.
				printf(", %s",line.MetroStations[i].name);
			}
		}
		// If all MetroStations printed then end line with dot.
		printf(".\n");
	}
	else{
		printf("\tEmpty.\n");
	}
}

void printPath(MetroStation stations[]){
	int i=0;
	// Print all elements of path until a unnamed MetroStation is reached.
	while(stations[i].name[0]!='\0'){
		printf("\t\t%d.  %s",i+1,stations[i].name);
		i++;
	}
}

double getDistanceTravelled(MetroStation stations[]){
	double res=0;
	int i;
	// Calculate distance using Pythagorean theorem. (a^2+b^2=c^2)
	// Repeat this process for whole stations inside stations array.
	while(stations[i+1].name[0]!='\0'){
		res+=sqrt(pow(stations[i+1].x-stations[i].x,2)+pow(stations[i+1].y-stations[i].y,2));
	}
	return res;
}

MetroStation findNearestStation(MetroSystem system,double x,double y){
	MetroStation station;
	double deltaX,deltaY,min_distance,distance;
	// Set min indexes to 0,0 they will be changed by loop.
	int i,j,min_i=0,min_j=0;
	deltaX = system.MetroLines[0].MetroStations[0].x-x;
	deltaY = system.MetroLines[0].MetroStations[0].y-y;
	// Set min distance to distance from x,y to first MetroStation of first MetroLine.
	min_distance = sqrt(pow(deltaX,2)+pow(deltaY,2));
	// Get distance between by using pythagorean theorem on differences from x,y to current station.
	for(i=0;i<SIZE;i++){
		// If current MetroLine doesn't have a color then MetroLines of MetroSystem ended.
		if(system.MetroLines[i].color[0]=='\0'){
			break;
		}
		// Iterate over whole current MetroLine to find indexes of min distance.
		for(j=1;j<SIZE;j++){
			deltaX = system.MetroLines[i].MetroStations[j].x-x;
			deltaY = system.MetroLines[i].MetroStations[j].y-y;
			// Calculate distance from x,y to current MetroStation.
			distance = sqrt(pow(deltaX,2)+pow(deltaY,2));
			// If current metroStation is unnamed then current MetroLine ended.
			if(system.MetroLines[i].MetroStations[j].name[0]=='\0'){
				continue;
			}
			// If distance calculated from current point is less than min distance then this point is new point with min distance.
			if(distance<min_distance){
				min_distance = distance;
				min_i = i;
				min_j = j;
			}
		}
	}
	// Get MetroStation with min distance.
	station = system.MetroLines[min_i].MetroStations[min_j];
	return station;
}

void getNeighboringStations(MetroSystem system,MetroStation station,MetroStation neighboringStations[]){
	// count will be used to index neighboring stations.
	int i,j,count=0;
	// Iterate over whole MetroSystem.
	for(i=0;i<SIZE;i++){
		// Iterate over whole current MetroLine.
		for(j=0;j<SIZE;j++){
			// If current MetroStation matches with our parameter than there is 3 cases that can happen.
			if(strcmp(system.MetroLines[i].MetroStations[j].name,station.name)==0){
				// Current MetroStation is either first MetroStation of MetroLine. In this case we only have to add element after this one to neighboringStations.
				if(j==0){
					neighboringStations[count] = system.MetroLines[i].MetroStations[j+1];
					count++;
				}
				// Or current MetroStation is the last MetroStation of MetroLine. In this case we only have to add element before this one to neighboringStations.
				else if(j==SIZE-1){
					neighboringStations[count] = system.MetroLines[i].MetroStations[j-1];
					count++;
				}
				// Current MetroStation is neither of cases above. In this case we only have to add element after and before this one to neighboringStations.
				else{
					neighboringStations[count] = system.MetroLines[i].MetroStations[j-1];
					neighboringStations[count+1] = system.MetroLines[i].MetroStations[j+1];
					count+=2;
				}
			}
		}
	}
}

void createDuplicate(MetroStation source[],MetroStation dest[],MetroStation start){
	int i;
	// Create duplicate of source named dest.
	for(i=0;i<SIZE;i++){
		// If current element is unnamed then stop.
		if(source[i].name[0]=='\0'){
			break;
		}
		strcpy(dest[i].name,source[i].name);
		dest[i].x = source[i].x;
		dest[i].y = source[i].y;
	}
	// add start to last of dest.
	strcpy(dest[i].name,start.name);
	dest[i].x = start.x;
	dest[i].y = start.y;
}

void findPath(MetroStation start,MetroStation finish,MetroStation path[]){
	MetroStation partialPath[SIZE];
	recursiveFindPath(start,finish,path,partialPath);
}

void recursiveFindPath(MetroStation start,MetroStation finish,MetroStation partialPath[],MetroStation bestPath[]){
	int i;
	static int count=0;
	// Base case 1: If start and finish are same stations then the bestPath is just an empty array.
	if(equals(start,finish)){
		bestPath = partialPath;
		return;
	}
	// Base case 2: If finish is contained inside partialPath then partialPath is finished then it is bestPath.
	for(i=0;i<SIZE;i++){
		if(strcmp(partialPath[i].name,finish.name)==0){
			return;
		}		
	}
	MetroStation neighbors[SIZE];
	// Calculate neighbors.
	getNeighboringStations(istanbul,start,neighbors);
	MetroStation duplicatePath[SIZE];
	// Duplicate partialPath and add start to end of array.
	createDuplicate(partialPath,duplicatePath,start);
	MetroStation currentPath[SIZE];
	// Recurse until finish is reached with new current start as naighbor of start.
	recursiveFindPath(neighbors[count++],finish,duplicatePath,partialPath);
}
