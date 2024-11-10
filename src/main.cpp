#include <iostream>
#include <vector>
#include <conio.h>
#include <sstream>
#include <windows.h>
#include <ctime>
#include "Snake.h"

using namespace std;

#define width 40
#define height 20

int tailX, tailY, numObstacles;
int score, delay, speedLv, delayLimit;

void clearBuffer();
void updateBuffer(Snake& snake, Food& food, Obstacle& obstacle);
void render(Snake &snake, Obstacle &obstacle);
void game(Snake &snake, Food &food, Obstacle &obstacle);
void homepage();
int difficultyMenu();
void gameOver(Snake &snake);
 
vector<vector<char>> board(width, vector<char>(height, ' ')); //2D array

int main(){

    //hide console
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = sizeof(cci);
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);


    while (true) {

        //create objects
        Snake snake;
        Food food;
        Obstacle obstacle;

        //reset the score and delay after each game
        score = 0, delay = 150, speedLv = 0;
        //welcome!
        int terminate = 0;
        do{
            homepage();
            terminate = difficultyMenu();
        }while(terminate == 4); //if user press 'q' return to homepage

        //initialize random seed
        srand(time(NULL)); 

        //get the attributes of the snake, food and obstacles, and initialize the setup
        snake.initializeSnake();
        food.generateFood(snake);
        obstacle.generateObstacle(snake, food, numObstacles);
 
        //start game
        game(snake, food, obstacle);

        //game over animation
        gameOver(snake);

    }
    
}

void clearBuffer() {
    // Clear the buffer 
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (y == 0 || y == height - 1 || x == 0 || x == width - 1)
                board[x][y] = '#'; // Draw borders
            else
                board[x][y] = ' '; // Clear inside
        }
    }

    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void updateBuffer(Snake& snake, Food& food, Obstacle& obstacle) {
    clearBuffer(); // Start with a fresh buffer

    // Draw food
    board[food.location.x][food.location.y] = '*';

    // Draw snake
    for (int i = 0; i < snake.size; i++) {
        if (i == 0)
            board[snake.body[i].x][snake.body[i].y] = '@'; // Snake head
        else
            board[snake.body[i].x][snake.body[i].y] = 'o'; // Snake body
    }

    // Draw obstacles
    for(int i = 0; i < numObstacles; i++){
        board[obstacle.no[i].x][obstacle.no[i].y] = 'X';
    }
}

void render(Snake &snake, Obstacle &obstacle) {
    ostringstream output;

    // Construct the game board in output stream
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            output << board[x][y];
        }
        output << '\n';
    }

    // Add score, snake size, and delay information
    output << "Score: " << score << "\n";
    output << "Snake Size: " << snake.size << "\n";
    output << "Speed Level: " << speedLv << "\n";
    
    // Display the game board
    cout << output.str();
    
}

void game(Snake &snake, Food &food, Obstacle &obstacle) {

    //game continue while snake is not colliding
    while(!snake.snakeCollide(obstacle)){
    
        //if snake captures the food
        if(snake.snakeCapture(food)){
            snake.snakeGrow();
            bool validPosition = false;
            do{
                //generate food and obstacles
                validPosition = food.generateFood(snake); 
                if(validPosition == true){
                    validPosition = obstacle.generateObstacle(snake, food, numObstacles);
                }

            }while(validPosition == false);//regenerate if the position is invalid

            score += 10; //increment score
            if(delay > delayLimit){ //increment speed
                delay -= 10;
                speedLv++; //increment speed level
            } 
        }

        snake.snakeMove(); 

        updateBuffer(snake, food, obstacle);   
        render(snake, obstacle);
        
        //delay base on current delay level
        Sleep(delay);
    }

}

void homepage(){

            cout << "##########################################" << endl;
            cout << "#                                        #" << endl;
            cout << "#       WELCOME TO THE SNAKE GAME!       #" << endl;
            cout << "#                                        #" << endl;
            cout << "#                                        #" << endl;
            cout << "#       Use WASD to Move the Snake       #" << endl;
            cout << "#     Capture * to Grow, Avoid Walls     #" << endl;
            cout << "#    and X (gamemode normal and above)   #" << endl;
            cout << "#         Press Any Key to Start         #" << endl;
            cout << "#            Enter 'q' to Exit           #" << endl;
            cout << "#                                        #" << endl;
            cout << "##########################################" << endl;
            
            //detect key press
            char key = _getch();

            if(key == 'q'){
                cout << "Exiting Game..." << endl;
                Sleep(1500);
                exit(0);
            }
            
            system("cls");
            
}

int difficultyMenu() {
    char choice;
    int exitValue;

    bool activate = true;
    while (activate) {
        // Display difficulty options
        cout << "##########################################" << endl;
        cout << "#       SELECT GAME DIFFICULTY           #" << endl;
        cout << "#                                        #" << endl;
        cout << "#           1. Easy                      #" << endl;
        cout << "#           2. Normal                    #" << endl;
        cout << "#           3. Hard                      #" << endl;
        cout << "#                                        #" << endl;
        cout << "#     Press 'q' to return to Main Menu   #" << endl;
        cout << "##########################################" << endl;

        choice = _getch();
        
        system("cls");

        // Handle difficulty selection
        switch (choice) {
            case '1':
                //Difficulty settings
                delayLimit = 100;
                numObstacles = 1;
                //Transition message
                cout << "Easy difficulty selected." << endl;
                cout << "Game Starting..." << endl;
                Sleep(2000);
                system("cls");
                exitValue = 1;
                break;
            case '2':
                //Difficulty settings
                delayLimit = 70;
                numObstacles = 3;
                //Transition message
                cout << "Normal difficulty selected." << endl;
                cout << "Game Starting..." << endl;
                Sleep(2000);
                system("cls");
                exitValue = 2;
                break;
            case '3':
                //Difficulty settings
                delayLimit = 50;
                numObstacles = 5;
                //Transition message
                cout << "Hard difficulty selected." << endl;
                cout << "Game Starting..." << endl;
                Sleep(2000);
                system("cls");
                exitValue = 3;
                break;
            case 'q':
                // Return to home page
                exitValue = 4;
                break;
            default:
                cout << "Invalid choice. Please select 1, 2, 3, or 'q'." << endl;
                exitValue = 0;
                break;
        }
        if(exitValue != 0){ //1,2,3 for difficulty and 4 for quit
            activate = false;   
        }
        
    } 

    return exitValue;
}

void gameOver(Snake &snake){

    COORD deathBody, middle;
    //death animation
    for (int i = 0; i < snake.size; i++) {
        deathBody.X = snake.body[i].x;
        deathBody.Y = snake.body[i].y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), deathBody);
        cout << '+'; 
        
        Sleep(150);
    }

    //center the text
    middle.X = 1;
    middle.Y = height/2;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), middle );
    cout << "           Game   Over!            " << endl;
    cout << "#             Score: " << score << "\n#   ";
    system("pause");
    system("cls");
}
