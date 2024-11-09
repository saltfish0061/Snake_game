#include <iostream>
#include <conio.h>
#include "Snake.h"

void Snake::initializeSnake(){
    //head and body
    // "o@"
    size = 2;

    body[0].x = width/2;
    body[0].y = height/2;

    body[1].x = width/2 - 1;
    body[1].y = height/2;

}

bool Snake::snakeCapture(Food &food){
    if(body[0].x == food.location.x && body[0].y == food.location.y){
        return true;
    }

    return false;
}

void Snake::snakeGrow(){
    size++;
}


bool Snake::snakeCollide(Obstacle obstacle){
    //check if snake collides with the fence
    if(body[0].x > 0 && body[0].x < width - 1 && body[0].y > 0 && body[0].y < height - 1){
        //check if snake collides with obstacle
        for(int i = 0; i < obstacle.no.size(); i++){
            if(body[0].x == obstacle.no[i].x && body[0].y == obstacle.no[i].y){
                return true;
            }
        }
        //check if snake collides with itself
        for(int i = 1; i < size; i++){
            if(body[0].x == body[i].x && body[0].y == body[i].y){
                return true;
            }
        }

    } else {
        return true;
    }

    return false;
}

char key = 'd';
char previousKey = key;

void Snake::snakeMove(){
   
    //move the snake, previous body part will take the position of the next body part
    /*
    ->    oo@
    ->     oo@
    ->      oo@
    */
    for(int i = size - 1; i > 0; i--){
        body[i].x = body[i - 1].x;
        body[i].y = body[i - 1].y;
    }

    if(_kbhit()){
        char newKey = _getch();
        // Prevent reversing direction
        if ((newKey == 'w' && previousKey != 's') ||
            (newKey == 's' && previousKey != 'w') ||
            (newKey == 'a' && previousKey != 'd') ||
            (newKey == 'd' && previousKey != 'a')) {
            key = newKey;
        } 
    }

    switch(key){
        case 'w': body[0].y--; break;
        case 's': body[0].y++; break;
        case 'a': body[0].x--; break;
        case 'd': body[0].x++; break;
        default: break;
    }

    previousKey = key;
}

bool Food::generateFood(Snake &snake) {
    // Generate random coordinates within the boundaries
    location.x = rand() % (width - 2) + 1;
    location.y = rand() % (height - 2) + 1;

    bool validPosition = false;
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            //if the food is not on the snake's body
            if(location.x != snake.body[i].x && location.y != snake.body[i].y){
                validPosition = true;
            } else {
                validPosition = false;
            }
        }
    }
    return validPosition;
}

bool Obstacle::generateObstacle(Snake &snake, Food &food, int numObstacles) {
    no.resize(numObstacles);
    bool validPosition = false;
    for(int i = 0; i < numObstacles; i++){
        do{
        // Generate random coordinates within the boundaries but not sticking to the fence
        location.x = rand() % (width - 4) + 2;
        location.y = rand() % (height - 4) + 2;

        for(int i = 0; i < width; i++){
            for(int j = 0; j< height; j++){
                //if the obstacle is not on the snake's body and food
                if(location.x != snake.body[i].x && location.y != snake.body[i].y 
                && location.x != food.location.x && location.y != food.location.y
                ){
                    for(int k = 0; k < no.size(); k++){
                        //if the obstacle is not on the other obstacles
                        if(location.x != no[k].x && location.y != no[k].y){
                            validPosition = true;
                        }
                    }                  
                }else{
                    validPosition = false;
                    break;
                    }
                }
            }

        }while(validPosition == false);

        //store the obstacles coordinates
        no[i].x = location.x;
        no[i].y = location.y;  
    }
    return validPosition;
}

