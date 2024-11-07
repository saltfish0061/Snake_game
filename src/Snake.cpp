#include <iostream>
#include <conio.h>
#include "Snake.h"

void Snake::initializeSnake(){
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


bool Snake::snakeCollide(){

    if(body[0].x > 0 && body[0].x < width -1 && body[0].y > 0 && body[0].y < height - 1){
        for(int i = 1; i < size; i++){
            if(body[0].x == body[i].x && body[0].y == body[i].y){
                return true;
            }
        }
    }else{
        return true;
    }

    return false;
}

char key = 'd';
char previousKey = 'd';

void Snake::snakeMove(){

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

void Food::generateFood() {
        // Generate random coordinates within the boundaries
        location.x = rand() % (width - 2) + 1;
        location.y = rand() % (height - 2) + 1;

}


