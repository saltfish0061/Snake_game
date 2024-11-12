#ifndef SNAKE_H
#define SNAKE_H

#include <vector>

#define width 40
#define height 20

struct Structure;
struct Snake;
struct Food;
struct Obstacle;

struct Structure{
    int x, y;
};

struct Snake{
    int size;
    //Max size of snake
    Structure body[width * height];

    void initializeSnake();
    bool snakeCapture(Food &food);
    bool snakeCollide(Obstacle obstacle);
    void snakeGrow();
    void snakeMove();
};

struct Food{
    Structure location;

    bool generateFood(Snake &snake);
};

struct Obstacle{
    int numObstacles;
    Structure location;
    //Store the obstacles coordinate if there are more than one
    std::vector<Structure> no;
    
    bool generateObstacle(Snake &snake, Food &food, int numObstacles);

};

#endif