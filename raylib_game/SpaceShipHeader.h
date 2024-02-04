#pragma once
#include "raylib.h"
#include "raymath.h"

void update();
void applyForce(Vector2 force);
void seek(Vector2 target);
void display();
Vector2 getLocation();
void randomMovement();
Vector2 setLocation(Vector2 loc);
float getSeekRadius();
void setClosestBallIndex(int a);
int getClosestBallIndex();
void addAmountEaten();
bool isAlive();
void turnDead();