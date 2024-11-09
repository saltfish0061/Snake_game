#ifndef SNAKE_H
#define SNAKE_H

#include <vector>

#define width 40
#define height 20

class Structure;
class Snake;
class Food;
class Obstacle;

class Structure{
    public: 
    // x and y coordinates
    int x, y;
};

class Snake{
    public:
    int size;
    //Max size of snake
    Structure body[width * height];

    void initializeSnake();
    bool snakeCapture(Food &food);
    bool snakeCollide(Obstacle obstacle);
    void snakeGrow();
    void snakeMove();
};

class Food{
    public:
    Structure location;

    bool generateFood(Snake &snake);
};

class Obstacle{
    public:
    int numObstacles;
    Structure location;
    //Store the obstacles coordinate if there are more than one
    std::vector<Structure> no;
    
    bool generateObstacle(Snake &snake, Food &food, int numObstacles);

};

#endif