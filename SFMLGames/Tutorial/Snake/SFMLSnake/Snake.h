/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Snake.h
 * Author: DooM
 *
 * Created on January 22, 2019, 9:27 PM
 */

#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/System/Vector2.hpp>
#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


struct SnakeSegment {
    SnakeSegment(int x, int y) : position{x, y} {}
    sf::Vector2i position;
};

using SnakeContainer = std::vector<SnakeSegment>;

enum class Direction {
    NONE,
    UP, 
    DOWN,
    LEFT, 
    RIGHT
};

class Snake {
public:
    Snake(int l_blockSize);
    virtual ~Snake();
    
    //Helper methods
    void SetDirection(Direction l_dir);
    Direction GetDirection() const;
    int GetSpeed() const;
    sf::Vector2i GetPosition() const;
    int GetLives() const;
    int GetScore() const;
    void IncraseScore();
    bool HasLost() const;
    
    Direction GetPhysicalDiretion();
    
    void Lose();    //Handle losing here
    void ToggleLost();
    
    void Extend();  //Grow the snake
    void Reset();   //Reset the starting position
    
    void Move();    //Movement Method
    void Tick();    //Update Method
    void Cut(int l_segments);   //Method for cutting snake.
    void Render(sf::RenderWindow& l_window);
private:
    
    void CheckCollision();
    SnakeContainer m_snakeBody;     //Segment vector
    int m_size;                     //Size of the graphics    
    Direction m_dir;                //Current direction
    int m_speed;                    //Speed of the snake
    int m_lives;                    //Lives
    int m_score;                    //Score
    bool m_lost;                    //Losing state.
    sf::RectangleShape m_bodyRect;  //Shape using in rendering
};

#endif /* SNAKE_H */

