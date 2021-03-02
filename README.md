# Route-Suggestion-Metro-Line-
This program suggests a route to get from a start point to a target point on a metro line. The details of the program are given below: 
Definitions:
•	 Define a constant SIZE with the value 10. 
•	 Write a MetroStation struct that has to contain a char array of size 20, named name (example: Haydarpasa); a double x and a double y that represent the location of a metro station. typedef it to MetroStation. 
•	 Write a MetroLine struct that has to contain a char array of size 20, named color (example: red) and a MetroStation[] array of size SIZE, named MetroStations that contains all metro stations in this metro line ordering from start to end. typedef it to MetroLine. 
•	 Write a MetroSystem struct that has to contain a char array of size 20, named name (example: Istanbul) and a MetroLine[] array of size SIZE, named MetroLines that contains all metro lines in this metro system. typedef it to MetroSystem. 
Functions:
•	Write a function equals(MetroStation s1, MetroStation s2)which returns a non-zero value if the name property of the MetroStation s1 is equal to the name property of MetroStation s2; zero otherwise. 
•	Write a function addStation which takes as input a MetroLine* and a MetroStation; and adds the given metro station to the end of the MetroStations[] array pointed by the MetroLine* pointer. It should return void. 
•	Write a function hasStation which takes as input a MetroLine and a MetroStation and returns a non-zero value if the given metro line has a metro station with the same name as the given metro station; zero otherwise. 
•	Write a function getFirstStop which takes as input a MetroLine and returns the MetroStation representing the first stop of the given metro line. If there is no such station, your function should return an empty MetroStation. 
•	Write a function getPriorStop which takes as input a MetroLine and a MetroStation and returns a MetroStation prior to the MetroStation passed as input. If the given station is the first stop on the MetroLine then this function should return an empty MetroStation. 
You may assume that there are no “loops” in the MetroLine that is, no station is present on the same line twice. 
•	Write a function getNextStop which takes as input a MetroLine and a MetroStation and returns a MetroStation after the MetroStation passed as input. If the given station is the last stop on the MetroLine, then this function should return an empty MetroStation. 
•	Write a function addLine which takes as input a MetroSystem* and a MetroLine and adds the given metro line to the end of the MetroLines[] array pointed by MetroSystem pointer. The function should return void. 
•	Write a function printLine which takes as input a MetroLine and prints the metro stations of the given metro line. The function should return void. 
•	Write a function printPath which takes as input a MetroStations[] array and prints the metro stations in the given array. The function should return void. 
•	Write a function getDistanceTravelled which takes as input a MetroStation[] array as path, and returns a double value representing the total distance travelled along a path that goes from the first MetroStation in the array, to the second MetroStation and so on, until the end of the array. For each MetroStation along the journey, it should calculate the distance between the MetroStation and the prior one. If the array path contains less than 2 values, your function should return 0.0. You may assume that the variable path is not null. For example, if the array path contains five MetroStation your code should calculate the sum of the distance between the first and second stations, the second and third stations, the third and fourth, and lastly the fourth and final stations. Hint: The distance between two metro stations should be calculated using x and y coordinates of the metro stations. You should know how to calculate the distance between two points in 2D space. 
•	Write a function findNearestStation which takes as input a MetroSystem, double x and a double y and returns the MetroStation which is nearest to the x and y. To do this, it should look through all the MetroStations of all the MetroLines inside of the given MetroSystem and find the MetroStation that is the smallest distance away. You may assume that there is at least one MetroLine defined in the MetroSystem and every MetroLine has at least one MetroStation in it. 
•	Write a function getNeighboringStations which takes as input a MetroSystem, a MetroStation and a MetroStation[] array named as neigboringStations and fills the given neigboringStations array containing all neighboring stations to the given station (possibly many if the station is on many lines). For example, if a station is the 3rd stop on the blue line, the 6th stop on the red line, and the 1st stop on the green line, then the function should update the neigboringStations containing the MetroStation that is the 2nd stop on the blue line, the 4th stop on the blue line, the 5th stop on the red line, the 7th stop on the red line, and the 2nd stop on the green line. Remember, that a MetroStation will not necessarily be on every MetroLine. However, you may assume that the MetroStation is on at least one MetroLine. 
•Finally, there will be 2 functions that will help you to find a path from one MetroStation to another MetroStation on the given MetroStation[] array. The first function will take as input the two MetroStation arguments and a MetroStation[] array you want. The second function will be a recursive function that will take as input a 4th argument. 
o First, write a function findPath that takes as input a MetroStation start, a MetroStation finish and a MetroStation[] array path. This function should simply call the recursiveFindPath function by passing to it as input start, finish, given MetroStation array path[] and a new, empty MetroStation array partialPath[]. The content of the partialPath will be filled by the recursiveFindPath function.
o Write a function recursiveFindPath that takes as input a MetroStation start, a MetroStation finish,aMetroStation arraypartialPath[]andaMetroStation array bestPath[]. The content of the bestPath should contain a full path that goes from start until finish. If no such path exists without requiring “doubling back” (i.e. go from A to B and then back to A), then the function should return immediately. The function should return void.
To do this, your function should do the following: 
•	-  If start is contained in the partialPath[] passed in as input, then your 
function should return immediately. 
•	-  If start and finish are the same based on the equals() function then your function should return immediately after setting partialPath[] as bestPath[]. 
•	-  If neither of the above are true, then you should do the following: 
•	-  (a) Compute a MetroStation array neighbors[] of possible places you can get to from start (You can of course, use the function getNeighboringStations defined before). 
•	-  (b) For each MetroStation station in neighbors do the following: 
i.	Create a duplicate copy of the array partialPath[]. Call this copy  duplicatePath[].
ii.	Add the station start to the end of the array duplicatePath[]. 
iii.	Calculate the path from the current neighboring station until finish by using recursion to call the function recursiveFindPath, but this time with input of the current neighboring station, finish, the duplicatePath[], and the currentPath[]. In the recursive call, the function should update the content of the currentPath[] given as a parameter to the function (4th parameter named bestPath[]). 
iv.	If the content of the currentPath[] is not null, then calculate the total distance travelled on this path using the function getDistanceTravelled that you wrote above. 
v.	Your function should construct whichever bestPath[] with the smallest associated distance travelled. 

Other Details:
o It should be noted that there is a path from Sogutlucesme to Bostanci on the red line; however, it is not the path with minimum distance travelled. Therefore, the suggested path is located on the green line with minimum distance travelled. 


