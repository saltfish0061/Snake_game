//main game interface

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

int tailX, tailY;
int score, speed, speedLv, speedCapped;

void clearBuffer();
void updateBuffer(Snake& snake, Food& food);
void render(Snake &snake);
void game(Snake &snake, Food &food);
void homepage();
int difficultyMenu();

 
vector<vector<char>> board(height, vector<char>(width, ' ')); //2D array

void clearBuffer() {
    // Clear buffer with spaces or reset values
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (y == 0 || y == height - 1 || x == 0 || x == width - 1)
                board[y][x] = '#'; // Draw borders
            else
                board[y][x] = ' '; // Clear inside
        }
    }

    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void updateBuffer(Snake& snake, Food& food) {
    clearBuffer(); // Start with a fresh buffer

    // Draw food
    board[food.location.y][food.location.x] = '*';

    // Draw snake
    for (int i = 0; i < snake.size; i++) {
        if (i == 0)
            board[snake.body[i].y][snake.body[i].x] = '@'; // Snake head
        else
            board[snake.body[i].y][snake.body[i].x] = 'o'; // Snake body
    }
}

void render(Snake &snake) {
    ostringstream output;

    // Construct the game board in output stream
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            output << board[y][x];
        }
        output << '\n';
    }

    // Add score, snake size, and speed information
    output << "Score: " << score << "\n";
    output << "Snake Size: " << snake.size << "\n";
    output << "Speed Level: " << speedLv << "\n";

    cout << output.str();
}

void game(Snake &snake, Food &food){

    //game continue while snake is not colliding
    while(!snake.snakeCollide()){
    
        //if snake captures the food
        if(snake.snakeCapture(food)){
            snake.snakeGrow();
            bool validPosition = false;
            do{
                food.generateFood();
                for(int i = 0; i < width; i++){
                    for(int j = 0; j< height; j++){
                        if(food.location.x != ' ' && food.location.y != ' '){
                            validPosition = true;
                        }else{
                            validPosition = false;
                        }
                    }
                }

            }while(validPosition == false);

            score += 10;
            if(speed > speedCapped){
                speed -= 10;
                speedLv++;
            } 
        }

        snake.snakeMove(); 

        //setObject(snake, food);
        updateBuffer(snake, food);
        render(snake);
        
        Sleep(speed);
    }

}

bool activate;

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

            activate = true;
            cout << "Activate: "   << activate << endl;
            

            char key = _getch();
            if(key == 'q'){
                cout << "Exiting Game..." << endl;
                Sleep(1200);
                exit(0);
            }
            
            system("cls");
            
}

int difficultyMenu() {
    char choice;
    int exitValue;

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

        cout << "Activate: " << activate << endl;

        choice = _getch();
        
        system("cls");

        // Handle difficulty selection
        switch (choice) {
            case '1':
                speedCapped = 100;
                cout << "Easy difficulty selected." << endl;
                cout << "Game Starting..." << endl;
                Sleep(2000);
                system("cls");
                // Add game initialization code for Easy here
                exitValue = 1;
                break;
            case '2':
                speedCapped = 70;
                cout << "Normal difficulty selected." << endl;
                cout << "Game Starting..." << endl;
                Sleep(2000);
                system("cls");
                // Add game initialization code for Normal here
                exitValue = 2;
                break;
            case '3':
                speedCapped = 50;
                cout << "Hard difficulty selected." << endl;
                cout << "Game Starting..." << endl;
                Sleep(2000);
                system("cls");
                // Add game initialization code for Hard here
                exitValue = 3;
                break;
            case 'q':
                // Return to main menu
                exitValue = 4;
                break;
            default:
                cout << "Invalid choice. Please select 1, 2, 3, or 'q'." << endl;
                exitValue = 0;
                break;
        }
        if(exitValue != 0){
            activate = false;   
        }
        
    } 

    return exitValue;
}

void gameOver(Snake &snake){

    COORD deathBody, middle;
    // Draw snake
    for (int i = 0; i < snake.size; i++) {
        deathBody.X = snake.body[i].x;
        deathBody.Y = snake.body[i].y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), deathBody);
        cout << '+'; 
        
        Sleep(150);
    }
    
    middle.X = width/2 - 6; //center the text
    middle.Y = height/2;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), middle );
    cout << "Game   Over! " << endl;
    cout << "\t       Score: " << score << "\n#   ";
    system("pause");
    system("cls");
}

int main(){

    while (true) {
        //reset the score and speed after each game
        score = 0, speed = 150, speedLv = 0;
        //welcome!
        int terminate = 0;
        do{
            homepage();
            terminate = difficultyMenu();
        }while(terminate == 4);

        //initialize random seed
        srand(time(NULL)); 

        //create objects
        Snake snake;
        Food food;

        //get the attributes of the snake
        snake.initializeSnake();
        food.generateFood();

        //start game
        game(snake, food);

        //game over animation
        gameOver(snake);
        
    }
    
}

