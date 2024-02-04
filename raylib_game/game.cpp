#include "raylib.h"
#include "raymath.h"
#include "SpaceShip.cpp"
#include "Wanderer.cpp"
#include "Hybrid.cpp"
#include "Header.h"

#include <iostream>


using namespace std;

struct ball
{
    Vector2 enemyLocation;
};


int main(void)
{
    InitWindow(800, 450, "raylib [core] example - basic window");
    SetTargetFPS(30);
    int count = 0;
    int time = 10;
    float minDistance;
    int evolutions = 0;
    int closestBallIndex = 0;
    int amountOfHybrids = 0;
    //int amountOfSeekers = 5;
    
    ball balls[100];
    for (int i = 0; i < 100; i++)
        balls[i].enemyLocation = randomPosition();
    
    Hybrid hybridList[5];
    SpaceShip spaceShipList[5];
    Vector2 locList[5];
    Vector2 locListHybrid[5];
    Vector2 locListWanderer[5];
    Wanderer wandererList[5];
    for (int i = 0; i < 5; i++) {
        spaceShipList[i].setLocation(randomPosition());
        locList[i] = spaceShipList[i].targetReturn();
        wandererList[i].setLocation(randomPosition());
        locListHybrid[i] = hybridList[i].targetReturn();
        locListWanderer[i] = wandererList[i].targetReturn();
    }
    


    //Image image = LoadImage("C:/Users/AmarS/Downloads/C++ Project1/raylib template - do not change names/raylib-game-template-main/projects/VS2022/raylib_game/resources/ship.png");
    Image image = LoadImage("C:/Users/AmarS/Downloads/C++ Project1/raylib template - do not change names/raylib/examples/textures/spaceship3.png");
    Image wandererImage = LoadImage("C:/Users/AmarS/Downloads/C++ Project1/raylib template - do not change names/raylib/examples/textures/spaceship.png");
    
    Texture2D texture = LoadTextureFromImage(image);
    Texture2D wandererTexture = LoadTextureFromImage(wandererImage);
    
    //texture.height = (100/3);
    //texture.width = (70/3);
    texture.height = (90 / 3);
    texture.width = (170 / 3);
    UnloadImage(image);

    wandererTexture.width = (160 / 3);
    wandererTexture.height = (100 / 3);
    UnloadImage(wandererImage);

    bool hit = false;
 
    


    while (!WindowShouldClose())
    {
        count++;

        time = (10*(evolutions+1)) - abs((count / 30));
        string text = to_string(time) + " seconds left";
        DrawText(text.data(), 50, 400, 22, BLACK);
        

        

        if (time==0) {
            //cout << time;
            for (int i = 0; i < 100; i++)
                balls[i].enemyLocation = randomPosition();

            int minSpaceShipFood = INT_MAX;
            int minWandererFood = INT_MAX;
            int maxSpaceShipFood = INT_MIN;
            int maxWandererFood = INT_MIN;
            int indexOfSpaceShipLowest = 0;
            int indexOfWandererLowest = 0;
            int indexOfSpaceShipBiggest = 0;
            int indexOfWandererBiggest = 0;
            for (int i = 0; i < 5; i++) {
                if (spaceShipList[i].lifeStatus && minSpaceShipFood > spaceShipList[i].amountEaten) {
                    minSpaceShipFood = spaceShipList[i].amountEaten;
                    indexOfSpaceShipLowest = i;
                }
                if (wandererList[i].lifeStatus && minWandererFood > wandererList[i].amountEaten) {
                    minWandererFood = wandererList[i].amountEaten;
                    indexOfWandererLowest = i;
                }
                if (spaceShipList[i].lifeStatus && maxSpaceShipFood < spaceShipList[i].amountEaten) {
                    maxSpaceShipFood = spaceShipList[i].amountEaten;
                    indexOfSpaceShipBiggest = i;
                }
                if (wandererList[i].lifeStatus && maxWandererFood < wandererList[i].amountEaten) {
                    maxWandererFood = wandererList[i].amountEaten;
                    indexOfWandererBiggest = i;
                }
            }
            
            if (minWandererFood < minSpaceShipFood) {
                wandererList[indexOfWandererLowest].lifeStatus = false;
                //cout << "\n\nWandererKilled\n";
            }
            else if (minWandererFood > minSpaceShipFood) {
                spaceShipList[indexOfSpaceShipLowest].lifeStatus = false;
                //cout << "\n\nSpaceshipKilled\n";
            }
            else {
                wandererList[indexOfWandererLowest].lifeStatus = false;
                spaceShipList[indexOfSpaceShipLowest].lifeStatus = false;
                //cout << "\n\nBothKilled\n";
            }
            
            wandererList[indexOfWandererBiggest].cooldown = wandererList[indexOfWandererBiggest].cooldown - 10;
            wandererList[indexOfWandererBiggest].grabRadius = wandererList[indexOfWandererBiggest].grabRadius + 10.0f;
            spaceShipList[indexOfSpaceShipBiggest].seekRadius = spaceShipList[indexOfSpaceShipBiggest].seekRadius + 20.0f;
            evolutions++;


            int minDistance = INT_MAX;
            int spaceShipIndex = -1;
            int wandererIndex = -1;
            bool oneIsAlive = false;
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    if (spaceShipList[j].lifeStatus && wandererList[i].lifeStatus && minDistance > Vector2Distance(wandererList[i].getLocation(), spaceShipList[j].getLocation())) {
                        minDistance = Vector2Distance(wandererList[i].getLocation(), spaceShipList[j].getLocation());
                        spaceShipIndex = j;
                        wandererIndex = i;
                        
                    }
                    if (spaceShipList[i].lifeStatus || wandererList[i].lifeStatus)
                        oneIsAlive = true;
                }
            }
           
            if (!oneIsAlive)
                amountOfHybrids--;
            if (rand() % 100 < 50 && spaceShipIndex != -1 && wandererIndex != -1) {
                spaceShipList[spaceShipIndex].lifeStatus = false;
                spaceShipList[wandererIndex].lifeStatus = false;
                amountOfHybrids++;
                //hybridList[amountOfHybrids-1] = Hybrid(spaceShipList[spaceShipIndex].getLocation().x, spaceShipList[spaceShipIndex].getLocation().y);
     
            }
            cout << amountOfHybrids << " ";
            int a = rand() % (amountOfHybrids) -1;
            if (rand() % 100 < 50 && amountOfHybrids!=0)
                hybridList[a].seekRadius = hybridList[a].seekRadius + 20.0f;
            a = rand() % (amountOfHybrids)-1;
            if (rand() % 100 < 50 && amountOfHybrids != 0)
                hybridList[a].grabRadius = hybridList[a].grabRadius + 10.0f;
            for (int i = 0; i < 5; i++) {
                spaceShipList[i].amountEaten = 0;
                wandererList[i].amountEaten = 0;
                if(i < amountOfHybrids)
                    hybridList[i].amountEaten = 0;
            }
            
        }


        for (int i = 0; i < 5; i++) {
            spaceShipList[i].setClosestBallIndex(-1);
            if(i < amountOfHybrids)
                hybridList[i].setClosestBallIndex(-1);
        }
        
  
        BeginDrawing();
        ClearBackground(WHITE);
        
        for (int i = 0; i < 100; i++)
            DrawCircleV(balls[i].enemyLocation, 5.0f, BLACK);

        for (int j = 0; j < 5; j++) {
            minDistance = INT_MAX;
            int minDistanceHybrid = INT_MAX;
            for (int i = 0; i < 100; i++) {
                if (j < amountOfHybrids) {
                    //locListHybrid[j] = hybridList[j].targetReturn();
                    if (Vector2Distance(hybridList[j].getLocation(), balls[i].enemyLocation) < hybridList[j].seekRadius) {
                        if (minDistanceHybrid > Vector2Distance(hybridList[j].getLocation(), balls[i].enemyLocation)) {
                            minDistanceHybrid = Vector2Distance(hybridList[j].getLocation(), balls[i].enemyLocation);
                            hybridList[j].setClosestBallIndex(i);
                        }
                    }
                    if (hybridList[j].lifeStatus && hybridList[j].canEat && (Vector2Distance(hybridList[j].getLocation(), balls[i].enemyLocation) < hybridList[j].grabRadius)) {
                        balls[i].enemyLocation = Vector2{ 1000000,1000000 };
                        hybridList[j].addAmountEaten();
                        //hybridList[j].canEat = false;
                    }
                }
                if (Vector2Distance(spaceShipList[j].getLocation(), balls[i].enemyLocation) < spaceShipList[j].seekRadius) {
                    if (minDistance > Vector2Distance(spaceShipList[j].getLocation(), balls[i].enemyLocation)) {
                        minDistance = Vector2Distance(spaceShipList[j].getLocation(), balls[i].enemyLocation);
                        spaceShipList[j].setClosestBallIndex(i);
                    }
                }
                if (spaceShipList[j].lifeStatus && Vector2Distance(spaceShipList[j].getLocation(), balls[i].enemyLocation) < 10.0f) {
                    balls[i].enemyLocation = Vector2{ 1000000,1000000 };
                    spaceShipList[j].addAmountEaten();
                }
                if (wandererList[j].lifeStatus && wandererList[j].canEat && (Vector2Distance(wandererList[j].getLocation(), balls[i].enemyLocation) < wandererList[j].grabRadius)) {
                    balls[i].enemyLocation = Vector2{ 1000000,1000000 };
                    wandererList[j].addAmountEaten();
                    wandererList[j].canEat = false;
                }
            }
        }



        for (int i = 0; i < 5; i++) {
            if (i < amountOfHybrids) {
            
                if (hybridList[i].getClosestBallIndex() != -1)
                    hybridList[i].seek(balls[hybridList[i].getClosestBallIndex()].enemyLocation);
                else
                    hybridList[i].seek(locListHybrid[i]);
                if (Vector2Distance(hybridList[i].getLocation(), locListHybrid[i]) < 10.0f)
                    locListHybrid[i] = hybridList[i].targetReturn();
                hybridList[i].update();
            }
            if (spaceShipList[i].getClosestBallIndex() != -1)
                spaceShipList[i].seek(balls[spaceShipList[i].getClosestBallIndex()].enemyLocation);
            else
                spaceShipList[i].seek(locList[i]);
            wandererList[i].seek(locListWanderer[i]);
            if (Vector2Distance(spaceShipList[i].getLocation(), locList[i]) < 10.0f) 
                locList[i] = spaceShipList[i].targetReturn();
            if (Vector2Distance(wandererList[i].getLocation(), locListWanderer[i]) < 10.0f)
                locListWanderer[i] = wandererList[i].targetReturn();
            spaceShipList[i].update();
            wandererList[i].update();
            double anglev = 180 + (180 / PI) * Vector2LineAngle(spaceShipList[i].getVelocity(), Vector2{ 0,1 });
            int a = 255 - (spaceShipList[i].amountEaten * 5);
            if(spaceShipList[i].lifeStatus)
                DrawTexturePro(texture, Rectangle{ 0,0,(170 / 3),(90 / 3) }, Rectangle{ spaceShipList[i].getLocation().x,spaceShipList[i].getLocation().y,(170 / 3),(90 / 3) }, Vector2{ (190 / 6),(90 / 6) }, anglev, Color{ 255, (unsigned char)a, 255, 255 });
            anglev = 180 + (180 / PI) * Vector2LineAngle(wandererList[i].getVelocity(), Vector2{ 0,1 });
            if (wandererList[i].lifeStatus) {
                int a = 255 - (wandererList[i].amountEaten * 5);
                if (wandererList[i].canEat)
                    DrawTexturePro(wandererTexture, Rectangle{ 0,0,(160 / 3),(100 / 3) }, Rectangle{ wandererList[i].getLocation().x,wandererList[i].getLocation().y,(160 / 3),(100 / 3) }, Vector2{ (160 / 6),(100 / 6) }, anglev, Color{ 255, (unsigned char)a, 255, 255 });
                else
                    DrawTexturePro(wandererTexture, Rectangle{ 0,0,(160 / 3),(100 / 3) }, Rectangle{ wandererList[i].getLocation().x,wandererList[i].getLocation().y,(160 / 3),(100 / 3) }, Vector2{ (160 / 6),(100 / 6) }, anglev, Color{ 255, (unsigned char)a, 255, 255 });
            }
                
            if (i < amountOfHybrids) {
                anglev = 180 + (180 / PI) * Vector2LineAngle(hybridList[i].getVelocity(), Vector2{ 0,1 });
                int a = 255 - (hybridList[i].amountEaten * 5);
                DrawTexturePro(wandererTexture, Rectangle{ 0,0,(160 / 3),(100 / 3) }, Rectangle{ hybridList[i].getLocation().x,hybridList[i].getLocation().y,(160 / 3),(100 / 3) }, Vector2{ (160 / 6),(100 / 6) }, anglev, Color{ 255, (unsigned char)a, 255, 255});
            }
        }
            
     
        
       
        

        
        /*for (int i = 0; i < 10; i++) {
            if (count > 110 || (Vector2Distance(spaceShip.getLocation(), balls[i].enemyLocation) < 10)) {
                count = 0;
                //minDistance = INT_MAX;
                for (int i = 0; i < 10; i++) {
                    balls[i].enemyLocation = randomPosition();
                    
                }
                


            }
        }   */
        
        //if (count == 600)
        //    count = 0;
        


        EndDrawing();
    }

    
    CloseWindow();

    return 0;
}




Vector2 randomPosition() {

    return Vector2{(float)(rand() % 650+25),(float)(rand() % 350+25)};


}


