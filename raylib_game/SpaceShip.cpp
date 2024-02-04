#include "raylib.h"
#include "raymath.h"
#include "SpaceShipHeader.h"
#include <iostream>


class SpaceShip {       
public: 
    Vector2 location;
    Vector2 velocity;
    Vector2 acceleration;
    float r;
    float maxforce;
    float maxspeed;
    Vector2 futureLoc;
    float seekRadius;
    int amountEaten;
    int closestBallIndex;
    bool lifeStatus; 
    int timeSinceEaten;
    bool canEat;

    SpaceShip(float x, float y){
        location = Vector2{ x,y };
        //velocity = Vector2{ 0,0 };
        velocity = Vector2{ 3,3};
        acceleration = Vector2{ 0,0 };
        r = 3.0;
        maxspeed = 4;
        seekRadius = 60.0f;
        //maxspeed = 1;
        maxforce = 0.1f;
        //maxforce = 1.0f;
        amountEaten = 0;
        closestBallIndex = -1;
        lifeStatus = true;
        timeSinceEaten = 0;
        canEat = true;
    }
    SpaceShip() {
        location = Vector2{0,0};
        //velocity = Vector2{ 0,0 };
        velocity = Vector2{ 3,3 };
        acceleration = Vector2{ 0,0 };
        r = 3.0;
        maxspeed = 4;
        seekRadius = 60.0f;
        //maxspeed = 1;
        maxforce = 0.1f;
        //maxforce = 1.0f;
        amountEaten = 0;
        closestBallIndex = -1;
        lifeStatus = true;
        timeSinceEaten = 0;
        canEat = true;
    }
    
    Vector2 getLocation() {
        //std::cout << "hi";
        return location;
        
    }
    Vector2 getVelocity() {
        //std::cout << "hi";
        return velocity;

    }
    float getSeekRadius() {
        //std::cout << "hi";
        return seekRadius;

    }
    void setLocation(Vector2 loc) {
        //std::cout << "hi";
        location = loc;

    }

    void setClosestBallIndex(int a) {
        //std::cout << "hi";
        closestBallIndex = a;

    }
    int getClosestBallIndex() {
        //std::cout << "hi";
        return closestBallIndex;

    }

    void addAmountEaten() {
        //std::cout << "hi";
        amountEaten++;

    }

    bool isAlive() {
        return lifeStatus;
    }
    

    void turnDead() {
        //std::cout << "hi";
        lifeStatus = false;

    }

   

    Vector2 targetReturn() {
        Vector2 velScale = Vector2Scale(velocity, 10);
        Vector2 futureLoc = Vector2Add(location, velScale);
        futureLoc = Vector2AddValue(futureLoc, 20);


        //double futurex = location.x + abs(velocity.x);
        // double futurey = location.y + abs(velocity.y);
        // Vector2 futureLoc = (Vector2){futurex,futurey};
        int angle = rand() % 360;
        //Vector2 tempV = Vector2Rotate(velocity, angle);
        //tempV = Vector2Scale(tempV, 10);
        
        float xtemp = 40.0 * cos(angle);
        float ytemp = 40.0 * sin(angle);
        Vector2 targetAdd = Vector2{ xtemp,ytemp };
        Vector2 target = Vector2Add(futureLoc, targetAdd);
        //DrawCircleV(target, 40.0f, RED);
        //std::cout << "targetx" << target.x << "      targety" << target.y << "\n";
        if (target.x > 750 || target.x < 50 || target.y > 400 || target.y < 50) {

            xtemp = rand() % 750;
            ytemp = rand() % 400;
            target = Vector2{ xtemp, ytemp };
        }
      
        return target;
    }

    void update() {
        /*
        velocity = Vector2Add(velocity, acceleration);
        //std::cout << "\nX Velocity: " << velocity.x << "\tY Velocity: " << velocity.y;
        //std::cout << "\nAccel X: " << acceleration.x << "\tAccel X: " << acceleration.y;
        velocity = Vector2ClampValue(velocity, -maxspeed, maxspeed);
        location = Vector2Add(location, velocity);
        acceleration = Vector2Scale(acceleration, 0);
        */


        velocity = Vector2Add(velocity, acceleration);
        velocity = Vector2ClampValue(velocity, 0, maxspeed);
        location = Vector2Add(location, velocity);
        acceleration = Vector2Scale(acceleration, 0);

        if(lifeStatus)
            DrawCircleLines(location.x, location.y, seekRadius, GREEN);

    }

    void applyForce(Vector2 force) {
        acceleration = Vector2Add(acceleration, force);
    }

    void seek(Vector2 target) {
        /*
        Vector2 desired = Vector2Subtract(target, location);
        desired = Vector2Normalize(desired);
        desired = Vector2Scale(desired, maxspeed);
        Vector2 steer = Vector2Subtract(desired, velocity);
        //
        steer = Vector2ClampValue(steer, 0, maxforce);
        applyForce(steer);
        */

        Vector2 desired = Vector2Subtract(target, location);
        desired = Vector2Normalize(desired);
        desired = Vector2Scale(desired, maxspeed);
        Vector2 steer = Vector2Subtract(desired, velocity);
        steer = Vector2ClampValue(steer, 0, maxforce);
        applyForce(steer);



    }



};