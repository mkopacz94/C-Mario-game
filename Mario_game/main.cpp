#include "Rectangle.h"
#include "Player.h"
#include "enemyMushroom.h"
#include "Brick.h"
#include "blockWithObject.h"
#include "flowerEnemy.h"
#include "turtleEnemy.h"
#include "SDL_mixer.h"
#include "coin.h"
#include <math.h>
#include "spartanHelmet.h"
#include "AudioManager.h"
#include "aspirine.h"

using namespace std;

void scrollObjects(Rectangle &objectToScroll);
void scrollFlyingHelmet(spartanHelmet &objectToScroll);
void backgroundRenderShift(Rectangle &background1, Rectangle &background2, int &mapSection);

const float Gravity = 3;

int main(int argc, char **argv)
{
	const float fps = 60;
	const float frameDelay = 1000 / fps; // 1000ms / 60 (zadana ilosc fps), daje to czas trwania jednej ramki
	float frameTime;
	Uint32 frameStart;
	
	int currentMapSection = 1;

	vector<int> playerPosition(2), background1Position(2), background2Position(2),
				groundSection1(2), groundSection2(2);

	Window main_window("Mario", 800, 600);

	


	Rectangle background1(main_window, 0, 0, 800, 600, "images/background.png");
	Rectangle background2 (main_window, 800, 0, 800, 600, "images/background.png");
	Rectangle ground_section1(main_window, -20, 490, 3200, 110, "images/ground_first.png");
	Rectangle ground_section2(main_window, 3400, 490, 3200, 110, "images/ground_first.png");

	Rectangle smallPipe1(main_window, 600, 352, 109, 138, "images/small_pipe.png");

	turtleEnemy turtle1(main_window, 700, 440, 55, 50, 3, "images/turtleEnemyAnim.png");

	Brick brick1(main_window, 1000, 320, 55, 55, "images/brick_animated.png", 1, 0);

	coin coin1(main_window, 1070, 320, 20, 20, "images/coinAnimated.png");
	blockWithObject question1(main_window, 1055, 320, 55, 55, "images/question_block.png", 0, 1);

	Brick brick2(main_window, 1110, 320, 55, 55, "images/brick_animated.png", 1, 0);
	Brick brick3(main_window, 1110, 150, 55, 55, "images/brick_animated.png", 0, 0);

	coin coin2(main_window, 800, 250, 20, 20, "images/coinAnimated.png");
	coin coin3(main_window, 850, 200, 20, 20, "images/coinAnimated.png");
	coin coin4(main_window, 900, 150, 20, 20, "images/coinAnimated.png");

	Rectangle bigPipe1(main_window, 1400, 190, 109, 300, "images/big_pipe.png");

	blockWithObject question2(main_window, 1900, 250, 55, 55, "images/question_block.png", 0, 0);
	aspirine aspirine1(main_window, 1910, 250, 35, 35, "images/aspirineAnimated.png");

	enemyMushroom mushroom1(main_window, 1700, 440, 55, 50, 5, "images/mushroomEnemyAnim.png");

	Rectangle smallPipe2(main_window, 2200, 352, 109, 138, "images/small_pipe.png");
	flowerEnemy flowerEnemy1(main_window, 2212, 352, 85, 90, "images/flowerEnemyAnim.png");

	enemyMushroom mushroom2(main_window, 2500, 440, 55, 50, -5, "images/mushroomEnemyAnim.png");
	enemyMushroom mushroom3(main_window, 2900, 440, 55, 50, 5, "images/mushroomEnemyAnim.png");

	Rectangle treeLog1(main_window, 3040, 400, 140, 90, "images/treeLog.png");

	Brick brick4(main_window, 3700, 300, 55, 55, "images/brick_animated.png", 1, 0);

	spartanHelmet helmet1(main_window, 3738, 294, 90, 59, "images/spartanHelmetAnim.png");
	blockWithObject question3(main_window, 3755, 300, 55, 55, "images/question_block.png", 0, 1);

	Brick brick5(main_window, 3810, 300, 55, 55, "images/brick_animated.png", 1, 0);


	

	
//	turtleEnemy turtle2(main_window, 150, 50, 55, 50, 4, "images/turtleEnemyAnim.png");


	Player mario(main_window, 20, 400, 48, 90, "images/marioSpartaAnim.png"); //406




	SDL_Rect clip;
	clip.w = 48;
	clip.h = 90;
	clip.y = 0;


	while (!main_window.isClosed() && mario.getPlayerHealth() >= 1)
	{
		//cout << currentMapSection << endl; 

		frameStart = SDL_GetTicks();

		main_window.clear();

		//RENDERING AND DRAWING SECTION
		
		mario.update(0.5, main_window);
		
		background1.draw();
		background2.draw();
		ground_section1.draw();
		ground_section2.draw();

		//SCROLLING SCREEN AND OBJECT SECTION
		if (mario.getPosX() >= 352 && mario.isPlayerMovingRight())
		{
			scrollFlyingHelmet(helmet1);
			scrollObjects(background1);
			scrollObjects(background2);
			scrollObjects(ground_section1);
			scrollObjects(ground_section2);
			scrollObjects(smallPipe1);
			scrollObjects(bigPipe1);
			scrollObjects(brick1);

			scrollObjects(question1);
			scrollObjects(coin1);

			scrollObjects(coin2);
			scrollObjects(coin3);
			scrollObjects(coin4);


			scrollObjects(brick2);
			scrollObjects(brick3);
			scrollObjects(question2);
			scrollObjects(aspirine1);

			scrollObjects(smallPipe2);
			scrollObjects(flowerEnemy1);
			scrollObjects(treeLog1);
			scrollObjects(mushroom1);

			scrollObjects(brick4);
			scrollObjects(question3);
			scrollObjects(brick5);
			
			scrollObjects(turtle1);
			scrollObjects(mushroom2);
			scrollObjects(mushroom3);
			//scrollObjects(turtle2);

			backgroundRenderShift(background1, background2, currentMapSection);
		}

		//COLLISION HANDLING

		if (currentMapSection == 1 || currentMapSection == 2)
		{
			turtle1.update(0.5);
			question1.updateBlock();

			mario.turtleCollision(turtle1);
			turtle1.collision(ground_section1);
			turtle1.collision(ground_section2);
			turtle1.collision(smallPipe1);
			turtle1.collision(bigPipe1);

			mario.newCollision(smallPipe1);

			mario.brickCollision(brick1);
			mario.blockCollision(question1);
			mario.brickCollision(brick2);
			mario.brickCollision(brick3);

			mario.newCollision(bigPipe1);

			smallPipe1.draw();
			bigPipe1.draw();

			if (question1.isItemVisible())
			{
				coin1.updateCoin(&mario);
			}

			coin2.updateCoin(&mario);
			coin3.updateCoin(&mario);
			coin4.updateCoin(&mario);

			brick1.drawBrick();
			question1.drawBlock();

			brick2.drawBrick();
			brick3.drawBrick();

			turtle1.draw();

		}

		if (currentMapSection == 2 || currentMapSection == 3)
		{
			mushroom1.update(0.5);
			flowerEnemy1.update(0.5);
			question2.updateBlock();
			
			flowerEnemy1.drawFlowerEnemy();
			smallPipe2.draw();

			mario.newCollision(smallPipe2);
			mario.blockCollision(question2);

			mario.enemyCollision(mushroom1);
			mario.flowerEnemyCollision(flowerEnemy1);

			mushroom1.collision(ground_section1);
			mushroom1.collision(ground_section2);
			mushroom1.collision(bigPipe1);
			mushroom1.collision(smallPipe2);

			if (question2.isItemVisible())
			{
				aspirine1.update(&mario);
			}

			if (aspirine1.isBumped())
			{
				aspirine1.collision(bigPipe1);
				aspirine1.collision(smallPipe2);
				aspirine1.collision(question2);
				aspirine1.collision(ground_section1);
				aspirine1.collision(ground_section2);
			}

			question2.drawBlock();
			mushroom1.draw();
		}


		if (currentMapSection == 3 || currentMapSection == 4)
		{
			mario.newCollision(treeLog1);
			mario.enemyCollision(mushroom2);
			mario.enemyCollision(mushroom3);

			mushroom2.update(0.5);
			mushroom3.update(0.5);

			mushroom2.collision(smallPipe2);
			mushroom2.collision(treeLog1);
			mushroom2.collision(ground_section1);
			mushroom2.collision(ground_section2);
			mushroom2.collision(mushroom3);

			mushroom3.collision(smallPipe2);
			mushroom3.collision(treeLog1);
			mushroom3.collision(ground_section1);
			mushroom3.collision(ground_section2);
			mushroom3.collision(mushroom2);

			treeLog1.draw();
			mushroom2.draw();
			mushroom3.draw();

		}

		if (currentMapSection == 4 || currentMapSection == 5)
		{

			question3.updateBlock();

			if (question3.isItemVisible())
			{
				helmet1.update(0.5);
				helmet1.collisionWithPlayer(&mario);
				helmet1.drawHelmet();
			}

			mario.brickCollision(brick4);
			mario.blockCollision(question3);
			mario.brickCollision(brick5);

			brick4.drawBrick();
			question3.drawBlock();
			brick5.drawBrick();
		}


		mario.newCollision(ground_section1);
		mario.newCollision(ground_section2);
		
		//GET EVENTS AND RENDER THE UPDATED WINDOW

		mario.drawPlayer(&clip);
		
		main_window.updateRender();
			
		//LIMITING GAME FRAMERATE

		frameTime = static_cast<float>(SDL_GetTicks() - frameStart);
		if (frameTime < frameDelay) SDL_Delay(static_cast<Uint32>(frameDelay - frameTime));	
	}

	return 0;
}



void scrollObjects(Rectangle &objectToScroll)
{
	vector<int>objectPosition(2);
	objectPosition = objectToScroll.getPositionxy();

	objectToScroll.changeRectanglePosition((objectPosition[0]-5), objectPosition[1]);
}

void scrollFlyingHelmet(spartanHelmet &objectToScroll)
{
	vector<int>objectPosition(2);
	objectPosition = objectToScroll.getPositionxy();

	objectToScroll.changeRectanglePosition((objectPosition[0] - 5), objectPosition[1]);
	objectToScroll.changeStartPosX(objectToScroll.getStartPosX() - 5);
}

void backgroundRenderShift(Rectangle &background1, Rectangle &background2, int &mapSection)
{
	vector<int>background2Position(2);
	vector<int>groundPosition(2);

	background2Position = background2.getPositionxy();
	//groundPosition = ground1.getPositionxy();

	if (background2Position[0] <= 0)
	{
		background1.changeRectanglePosition(0, 0);
		background2.changeRectanglePosition(800, 0);
	//	ground1.changeRectanglePosition(0, groundPosition[1]);
	//	ground2.changeRectanglePosition(800, groundPosition[1]);

		mapSection++;
	}
}
