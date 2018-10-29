//========================================= file = maze.cpp ====================
//=  A program to help Apollo go from start to the bull's eye using a graphing =
//=  algorithm.                                                                =
//==============================================================================
//   Input: Reads from an input file input.txt                                 =
//   Output: Writes to an output file output.txt                               =
//=----------------------------------------------------------------------------=
//=  Build: g++ -g -o maze maze.cpp                                            =
//=----------------------------------------------------------------------------=
//=  Execute: ./maze                                                           =
//=----------------------------------------------------------------------------=
//=  Author:  My Nguyen [U71337744]                                            =
//=----------------------------------------------------------------------------=
//=  Notes: Input file must be named input.txt                                 =
//==============================================================================
#include <iostream>
#include <fstream>
#include <string>
#include <stack>

// Define the maximum number of vertices to have a 500x500 matrix
#define MAX_NUMBER_OF_VERTICES 500*500

// Declare the specifiers for colors and directions
typedef enum { NOCOLOR, RED, BLUE } Color;
typedef enum { NONE, NORTH, NORTHEAST, EAST, SOUTHEAST, SOUTH, SOUTHWEST, WEST, NORTHWEST } Direction;

// Create a struct called Vertex
typedef struct Vertex {
	Color C;                // Hold a color
	Direction D;            // Hold a direction
	int NumberofNeighbors;  // Hold number of neighbors
	int Neighbor[500];      // An integer array called Neighbor with 500 elements
} Vertex;

int NumberOfVertices, N, M;             // Initialize num. of vertices, N = row, and M = col
Vertex Graph[MAX_NUMBER_OF_VERTICES];   // Create a graph with max # of vertices
bool Visited[MAX_NUMBER_OF_VERTICES];   // Create a boolean Visted with max # of vertices
bool SolutionFound;                     // Create a boolean solutionFound
std::stack<int> Solution;               // Create a stack of int called solution

// Create a void function to read the inputs from the files
void ReadInputFile() {
	std::ifstream File;                 // Create ifstream to open file
	std::string SquareStr;              // Create string called row_start for starting point
	File.open("input.txt");             // Read inputs from input.txt file
    
    // To open file and get the inputs from file
	if (File) {
		File >> N;                  // Get information from rows
		File >> M;                  // Get information from columns
		NumberOfVertices = 0;       // Current number of vertices is 0
        
        // Enter all possible elements for bulls-eye, red and blue with all directions
		while(File >> SquareStr) {
			if (SquareStr == "O") {
				Graph[NumberOfVertices].C = NOCOLOR;
				Graph[NumberOfVertices].D = NONE;
			}
			else if (SquareStr == "R-N") {
				Graph[NumberOfVertices].C = RED;
				Graph[NumberOfVertices].D = NORTH;
			}
			else if (SquareStr == "R-NE") {
				Graph[NumberOfVertices].C = RED;
				Graph[NumberOfVertices].D = NORTHEAST;
			}
			else if (SquareStr == "R-E") {
				Graph[NumberOfVertices].C = RED;
				Graph[NumberOfVertices].D = EAST;
			}
			else if (SquareStr == "R-SE") {
				Graph[NumberOfVertices].C = RED;
				Graph[NumberOfVertices].D = SOUTHEAST;
			}
			else if (SquareStr == "R-S") {
				Graph[NumberOfVertices].C = RED;
				Graph[NumberOfVertices].D = SOUTH;
			}
			else if (SquareStr == "R-SW") {
				Graph[NumberOfVertices].C = RED;
				Graph[NumberOfVertices].D = SOUTHWEST;
			}
			else if (SquareStr == "R-W") {
				Graph[NumberOfVertices].C = RED;
				Graph[NumberOfVertices].D = WEST;
			}
			else if (SquareStr == "R-NW") {
				Graph[NumberOfVertices].C = RED;
				Graph[NumberOfVertices].D = NORTHWEST;
			}
			else if (SquareStr == "B-N") {
				Graph[NumberOfVertices].C = BLUE;
				Graph[NumberOfVertices].D = NORTH;
			}
			else if (SquareStr == "B-NE") {
				Graph[NumberOfVertices].C = BLUE;
				Graph[NumberOfVertices].D = NORTHEAST;
			}
			else if (SquareStr == "B-E") {
				Graph[NumberOfVertices].C = BLUE;
				Graph[NumberOfVertices].D = EAST;
			}
			else if (SquareStr == "B-SE") {
				Graph[NumberOfVertices].C = BLUE;
				Graph[NumberOfVertices].D = SOUTHEAST;
			}
			else if (SquareStr == "B-S") {
				Graph[NumberOfVertices].C = BLUE;
				Graph[NumberOfVertices].D = SOUTH;
			}
			else if (SquareStr == "B-SW") {
				Graph[NumberOfVertices].C = BLUE;
				Graph[NumberOfVertices].D = SOUTHWEST;
			}
			else if (SquareStr == "B-W") {
				Graph[NumberOfVertices].C = BLUE;
				Graph[NumberOfVertices].D = WEST;
			}
			else if (SquareStr == "B-NW") {
				Graph[NumberOfVertices].C = BLUE;
				Graph[NumberOfVertices].D = NORTHWEST;
			}
            // Currently none of the vertices have been visited
			Visited[NumberOfVertices] = false;
            // Increment no. of vertices
			NumberOfVertices++;
		}
        // Close the file
		File.close();
	}
}

// Create a void function to build the Graph
void BuildGraph() {
    // First for loop for rows
	for(int i = 0; i < N; i++)
        // Second for loop for columns
		for(int j = 0; j < M; j++) {
            // If the first position is not equal to bullseye, enter graph
			if (Graph[i * M + j].D != NONE) {
				int Row = i, Column = j;
                // Set the current vertex as the first position
				int CurrentVertex = i * M + j;
				Graph[CurrentVertex].NumberofNeighbors = 0;
                
                // While within bounds
				while(Row >= 0 && Row < N && Column >= 0 && Column < M) {
					int PotentialNeighbor = Row * M + Column;
                    // If the color is not the same, put potentialNeighbor into graph and increment the number of neighbors count
					if (Graph[CurrentVertex].C != Graph[PotentialNeighbor].C) {
						Graph[CurrentVertex].Neighbor[Graph[CurrentVertex].NumberofNeighbors++] = PotentialNeighbor;
					}
					switch(Graph[CurrentVertex].D) {
						case NORTH:
							Row--;
						break;
						case NORTHEAST:
							Row--;
							Column++;
						break;
						case EAST:
							Column++;
						break;
						case SOUTHEAST:
							Row++;
							Column++;
						break;
						case SOUTH:
							Row++;
						break;
						case SOUTHWEST:
							Row++;
							Column--;
						break;
						case WEST:
							Column--;
						break;
						case NORTHWEST:
							Row--;
							Column--;
						break;
						default:
						break;
					}
				}
			}
		}
}

// Create a void function using Depth-First Search (DFS) algorithm to find the solution
void DFS(int Vertex) {
	Visited[Vertex] = true;
    // If the vertex is equal to no. of vertices - 1 as in bullseye
	if (Vertex == NumberOfVertices - 1) {
		SolutionFound = true;
		Solution.push(Vertex);
	}
    // Else if the vertex is not the bullseye, find the solution
	else {
		for(int i = 0; i < Graph[Vertex].NumberofNeighbors; i++) {
            // If the neighbors have not been visited, use DFS to find the vertexes
			if (!Visited[Graph[Vertex].Neighbor[i]]) {
				DFS(Graph[Vertex].Neighbor[i]);
                
                // If solution has been found, push the solution onto the stack and return
				if (SolutionFound) {
					Solution.push(Vertex);
					return;
				}
			}
		}
	}
}

// Create a void function to the find the exit
void FindExit() {
	SolutionFound = false;
	DFS(0);
}

// Create a void function to print the solutions
void PrintSolution() {
	std::ofstream File;         // Create ofstream to open output file
	File.open("output.txt");    // Write solution to output.txt file
    
    // Enter file
	if (File) {
        // If the current position is the solution, pop the solution from stack
		if (SolutionFound) {
			int CurrentVertex = Solution.top();
			Solution.pop();
            
            // While the stack is not empty, print the solutions
			while (!Solution.empty()) {
				int NextVertex = Solution.top();
				Solution.pop();
                
                // Find the distance between the current and next position
                int steps;
                // calculate the distance
                if (CurrentVertex / M != NextVertex / M)
                    steps = (CurrentVertex / M) - (NextVertex / M);
                else            // same row, find the difference
                    steps = CurrentVertex - NextVertex;
                if (steps < 0)  // invert the steps count
                    steps = -steps;
                
                // Output to file
                File << steps;
				switch(Graph[CurrentVertex].D) {
						case NORTH:
							File << "N ";
						break;
						case NORTHEAST:
							File << "NE ";
						break;
						case EAST:
							File << "E ";
						break;
						case SOUTHEAST:
							File << "SE ";
						break;
						case SOUTH:
							File << "S ";
						break;
						case SOUTHWEST:
							File << "SW ";
						break;
						case WEST:
							File << "W ";
						break;
						case NORTHWEST:
							File << "NW ";
						break;
						default:
						break;
					}
                // Set the next vertex as the current vertex
				CurrentVertex = NextVertex;
			}
		}
        // Else, no solution was found
		else {
			File << "No solution was found!";
		}
        // Close file
		File.close();
	}
}

int main() {
	ReadInputFile();
	BuildGraph();
	FindExit();
	PrintSolution();
	return 0;
}
