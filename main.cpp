//main.cpp
//This program will solve the nQueens problem assignment

// Include all the nescessary libraries for the program.
#include <iostream>
#include <stack>
#include <vector>
#include <cstdlib>

// Below are the prototypes that we will use for the execution of this program.
int getN();
bool isItValid();
void miniMain();

// Bellow are the variables we will need to execute this program sucessfully.
// We need a filled integer so we can count how many columns are already filled.
int filled = 1;  // Set the counter to 1 to start with assuming (1,1) has already been placed.
// Then we create a integer N which we will use for the majority of the program to determin the amount of Queens/Columns/Rows.
int n;
// Create a stack to hold the locations of which row the queens currently are.
std::stack<int> row;
// Create a stack to holf the location of which column the queens currently are.
std::stack<int> column;
// We use a vector to keep track of the previously used columns so we can check to make sure there is never a conflict.
std::vector<int> usedColumns;
// Use a boolean variable named valid to dictate whether or not a queen location is valid.
bool valid;
//Create a integer for the temporary storage of the row a queen is currently in.
int tempRow;
//Creata a temp for the position of a queen in a column before we confirm if its valid or not.
int tempColumn;

//Below we have a main function that will be used to house our methods and call upon them.
int main(){
    // Push the starting coordinates of a queen to the stack for both row and column. We assume all queens start at 1,1.
    row.push(1);
    column.push(1);
    // Add column 1 to a list of columns that cannot be caught in the same column.
    usedColumns.push_back(1);

    //Call upon our method to ask the user for a number.
    getN();

    //After getting our N we go into my method called mini main where the brunt of the work is done.
    miniMain();
    
}

int getN() {
    // This function will ask the user to input a number to be used to determine the number of queens, columns, and rows.

    // Ask the user for a number. 
    std::cout << "Please enter a number: " << std:: endl;
    
    // Create a loop that will only accept valid integer responses.
    while(!(std::cin >> n)) {
        std::cout << "Error: Please enter a valid Integer: " << std:: endl;
        std::cin.clear();
        std::cin.ignore(100, '\n');
        
    }

    //For the n-queens problem, all solutions are valid except the numbers less than 4. We make sure the program does not fall into an endless loop or use unnescessary processing.
    if(n < 4){
        n = 0;
        std::cout << "This number cannot be used for the N-Queens Problem." << std::endl;
        std::cout << "Thanks for trying though." << std::endl;
        //If we find the user has input a number less than 4, I clear both stacks and the vector then use the exit command to hard quit the program.
        row.empty();
        column.empty();
        usedColumns.empty();
        std::exit(0);
    }


    // Return the input to other functions.
    return n;
}

bool isItValid(){
    //This will check and see if a temporary coordinate of a queen is valid and passes all check to be added to the stack of valid coordinates.

    // We start by assuming the coordinates are valid so we set it to true.
    valid = true;
    // I created a temporary integer X to be used to sort through a vector list.
    int x = 0;

    //This makes sure that we continue checking to see if a coordinate is valid as long as the stacks are not empty.
    while(!column.empty()){

        // For this if loop I check and see if the column coordinate is larger then n. If it is then that coordinate is not valid.
        if(tempColumn > n){
            valid = false;
        }

        //I then create a loop to loop through for the amount of times that filled is.
        for(int y = 0; y < filled; y++){
            //This check statement makes sure that the column is the same column as any other queen on the chess board at the time.
            if(tempColumn == usedColumns.at(x)){
                valid = false;
            }
            x++;
        }
        //This check statement makes sure that the queen is not directly above the previous queen.
        if(tempColumn == column.top()){
            valid = false;
        }   
        //This check statement makes sure that the queen is not one to the right of the queen below it.
        if(tempColumn == column.top() + 1){
            valid = false;
        }
        //This check make sure that the queen is not one unit to the left of the queen below it.
        if(tempColumn == column.top() -1){
            valid = false;
        }
        //We then break from the while loop to get back to mini main.
        break;
    }
    //We return the current state of the boolean variable valid.
    return valid; 
}

void miniMain(){
    //This method will do a lot of the adding and subracting of the coordinates from the stack.

    //We make sure that the temp row is preset to 1 to make sure we've already got one row going.
    tempRow = 1;

    while(filled != n){
        //This while loop will loop through until the filled variable and n are equivalent.

        // Create a temp variable to house the row we're currently in.
        tempRow++;

        //Create a loop to loop through until it reaches the edge of the chess board.
        valid = false; //set valid to false to re set the valid variable. 
        while(valid == false){


            // If the border is reached then we need to pop the rows and start back again.
            if(tempColumn >= n + 1){
                tempColumn = column.top(); //set the new temp column to the top of the stack.
                tempRow = row.top(); //set the new temp row to the value at the top of the row stack.
                row.pop(); //pop the stack to delete the top value.
                column.pop(); //pop the stack to delete the top value.
                filled = filled - 1; //Subtract one from the filled variable.
                usedColumns.pop_back(); //pop the vector adn subract the latest column addition.
            }
            tempColumn++; // add one more to the temp column. 
            // Now we check to see if the coordinate of a queen on the chessboard is valid. 
            isItValid();

        }


        //If it is found that the coordinates are valid then we add the coordinates to each of the stacks.
        //We also add the column value into the vector of previously valid columns.
        //We also add one to the filled variable.
        usedColumns.push_back(tempColumn);
        row.push(tempRow);
        column.push(tempColumn);
        filled = filled + 1;
        tempColumn = 0;
    }


    //This for loop will loop through until a we've printed out the entire chess board.
    for(int q = 0; q < n; q++){
        for(int w = 1; w <= n; w++){
            if(column.top() == w){
                std::cout << " " << "X" << " ";
            }
            else{
                std::cout << " 0 ";
            }   
        }
        //This will output the coordinates of each queen and delete that queen from the stack.
        std::cout << "   Queen " << filled << "  " << "(" << row.top() << "," << column.top() << ")";
        std::cout << std::endl << std::endl;
        filled = filled - 1;
        row.pop();
        column.pop();
    }
}

