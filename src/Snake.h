#ifndef SNAKE_H
#define SNAKE_H

#define width 40
#define height 20

class Food;
class Snake;

class Structure{
    public:
    int x, y;
};

class Snake{
    public:
    int size;
    Structure body[width * height];

    void initializeSnake();
    bool snakeCapture(Food &food);
    bool snakeCollide();
    void snakeGrow();
    void snakeMove();
};

class Food{
    public:
    Structure location;

    void generateFood();
};


#endif