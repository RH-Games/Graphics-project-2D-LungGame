#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

//--- OpenGL ---
#include "GL\glew.h"
#include "GL\wglew.h"
#include "GL\freeglut.h"
#pragma comment(lib, "glew32.lib")

//--------------
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "FreeImage.h"
#include "Circle.h"
#include "Sprite.h"
#include "FreeType.h"
#include "Var.h"
//#include "Contorls.cpp"

//----------Game concept---------

// This game is based of a idea of a young boy in hospital drawing what happens in his lungs while fighting off a chest infection.
// the player plays a character that based of the drawing and imagination of myself when i was young.
// the design of the game was to make it less scary then what the lungs look like in real life.
// 
// the objective is to fight bugs and a virus in the lungs.
// if the bugs make contact with the player character the player will lose health if zero you player loses.

//Created By Ryan Hughes using OpenGl and C++. 

#define PI 3.1415926535897932384626433832795
const double ToRadians = PI / 180.0;

//matrix
glm::mat4 ViewMatrix;  // matrix for the modelling and viewing
glm::mat4 ProjectionMatrix; // matrix for the orthographic projection
glm::mat4 ProjectionMatrixBackground;
glm::mat4 ModelViewMatrix;

//OPENGL FUNCTION PROTOTYPES
void display();						   //used as callback in glut for display.
void reshape(int width, int height);  //used as callback for reshape function in glut
void init();						 //called in main when the program starts.

/*************    START OF OPENGL FUNCTIONS   ****************/

void reshape(int width, int height)		// Resize the OpenGL window
{
	screenWidth = width;
	screenHeight = height;
	
	glViewport(myPlayer.GetXPos(), myPlayer.GetPos(), width, height);

	// set Viewport dimensions
	ProjectionMatrix = glm::ortho(-200.0, 200.0, -200.0, 200.0);

}

//creates walls for the edge of the game.

void walls() {

	//add in walls and areas in which the player cant go through

	//game walls, these ojbects stop the player or other ojects from leave the game area. 

	//Left wall

	ModelViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(-980, -150.0, 0.0));
	LeftWall.Render(ModelViewMatrix, ProjectionMatrix);

	if (myPlayer.IsInCollision(LeftWall.GetOBB())) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		myPlayer.SetXIncPos(10.0f);
		printf("hit left wall \n ");
		/*if (myPlayer.GetXPos() < LeftWall.GetXPos()) {


			myPlayer.SetXIncPos(10.0f);

			printf("hit left wall \n ");
		}*/
	}


	//right wall 
	AngleWall = 0.12;
	ModelViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(1250, 580, 0.0));
	ModelViewMatrix = glm::rotate(ModelViewMatrix, AngleWall, glm::vec3(0.0, 0.0, 10.0));
	RightWall.Render(ModelViewMatrix, ProjectionMatrix);

	if (myPlayer.IsInCollision(RightWall.GetOBB())) {

		if (myPlayer.GetXPos() > RightWall.GetXPos()) {

			myPlayer.SetXIncPos(-10.0f);

			printf("hit right wall  \n ");
		}
	}

	//top wall
	ModelViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(500, 1670, 0.0));
	TopWall.Render(ModelViewMatrix, ProjectionMatrix);

	if (myPlayer.IsInCollision(TopWall.GetOBB())) {

		if (myPlayer.GetYPos() > TopWall.GetYPos()) {

			myPlayer.SetYIncPos(-10.0f);

			printf("hit top wall \n ");
		}
	}

	//BOTTOM WALL 
	AngleWall = -0.45;
	ModelViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(-458, -1550, 0.0));
	ModelViewMatrix = glm::rotate(ModelViewMatrix, AngleWall, glm::vec3(0.0, 0.0, 10.0));
	BottomWall.Render(ModelViewMatrix, ProjectionMatrix);

	if (myPlayer.IsInCollision(BottomWall.GetOBB())) {

		if (myPlayer.GetYPos() < BottomWall.GetYPos()) {

			myPlayer.SetYIncPos(10.0f);

			printf("hit top wall \n ");
		}
	}
	AngleWall = -0.9;
	ModelViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(24, -1510, 0.0));
	ModelViewMatrix = glm::rotate(ModelViewMatrix, AngleWall, glm::vec3(0.0, 0.0, 10.0));
	BottomWall2.Render(ModelViewMatrix, ProjectionMatrix);

	if (myPlayer.IsInCollision(BottomWall2.GetOBB())) {

		if (myPlayer.GetYPos() < BottomWall2.GetYPos()) {

			myPlayer.SetYIncPos(10.0f);

			printf("hit top wall \n ");
		}
	}

	//topright corner wall

	AngleWall = 101;
	ModelViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(1033, 1326, 0.0));
	ModelViewMatrix = glm::rotate(ModelViewMatrix, AngleWall, glm::vec3(0.0, 0.0, 10.0));
	TopRightCorner.Render(ModelViewMatrix, ProjectionMatrix);

	if (myPlayer.IsInCollision(TopRightCorner.GetOBB())) {

		if (myPlayer.GetXPos() > TopRightCorner.GetXPos()) {

			myPlayer.SetXIncPos(-10.0f);

			printf("hit test wall \n ");
		}
	}

	//top left corner wall
	AngleWall = 2.25;
	ModelViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(0.0, 1480, 0.0));
	ModelViewMatrix = glm::rotate(ModelViewMatrix, AngleWall, glm::vec3(0.0, 0.0, 10.0));
	TopLeftWall.Render(ModelViewMatrix, ProjectionMatrix);

	if (myPlayer.IsInCollision(TopLeftWall.GetOBB())) {

		if (myPlayer.GetYPos() > TopLeftWall.GetYPos()) {

			myPlayer.SetYIncPos(-10.0f);

			printf("hit test wall \n ");
		}
	}


	AngleWall = 2.25;
	ModelViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(703, -1071, 0.0));
	ModelViewMatrix = glm::rotate(ModelViewMatrix, AngleWall, glm::vec3(0.0, 0.0, 10.0));
	BottomRightWall.Render(ModelViewMatrix, ProjectionMatrix);

	if (myPlayer.IsInCollision(BottomRightWall.GetOBB())) {

		if (myPlayer.GetYPos() < BottomRightWall.GetYPos()) {


			myPlayer.SetYIncPos(10.0f);

			printf("hit test wall \n ");
		}
	}


	AngleWall = 0.32;
	ModelViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(-770, -1000, 0.0));
	ModelViewMatrix = glm::rotate(ModelViewMatrix, AngleWall, glm::vec3(0.0, 0.0, 10.0));
	BottomLeftWall.Render(ModelViewMatrix, ProjectionMatrix);


	if (myPlayer.IsInCollision(BottomLeftWall.GetOBB())) {

		if (myPlayer.GetXPos() < BottomLeftWall.GetXPos()) {


			myPlayer.SetXIncPos(10.0f);

			printf("hit test wall \n ");
		}
	}

	AngleWall = 2.7;
	ModelViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(-840, 415, 0.0));
	ModelViewMatrix = glm::rotate(ModelViewMatrix, AngleWall, glm::vec3(0.0, 0.0, 10.0));
	MiddleLeftWall.Render(ModelViewMatrix, ProjectionMatrix);


	if (myPlayer.IsInCollision(MiddleLeftWall.GetOBB())) {

		if (myPlayer.GetXPos() < MiddleLeftWall.GetXPos()) {


			myPlayer.SetXIncPos(10.0f);

			printf("hit test wall \n ");
		}
	}

	//left
	AngleWall = 2.27;
	ModelViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(-580, 840, 0.0));
	ModelViewMatrix = glm::rotate(ModelViewMatrix, AngleWall, glm::vec3(0.0, 0.0, 10.0));
	TopLeftWall2.Render(ModelViewMatrix, ProjectionMatrix);

	if (myPlayer.IsInCollision(TopLeftWall2.GetOBB())) {

		if (myPlayer.GetYPos() > TopLeftWall2.GetYPos()) {

			myPlayer.SetYIncPos(-10.0f);

			printf("hit test wall \n ");
		}
	}

	AngleWall = 2.70;
	ModelViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(-465, 1015, 0.0));
	ModelViewMatrix = glm::rotate(ModelViewMatrix, AngleWall, glm::vec3(0.0, 0.0, 10.0));
	TopLeftWall3.Render(ModelViewMatrix, ProjectionMatrix);

	if (myPlayer.IsInCollision(TopLeftWall3.GetOBB())) {

		if (myPlayer.GetXPos() < TopLeftWall3.GetXPos()) {

			myPlayer.SetXIncPos(10.0f);

			printf("hit test wall \n ");
		}
	}

	AngleWall = 2.95;
	ModelViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(1120, -540, 0.0));
	ModelViewMatrix = glm::rotate(ModelViewMatrix, AngleWall, glm::vec3(0.0, 0.0, 10.0));
	BottomRightWall2.Render(ModelViewMatrix, ProjectionMatrix);

	if (myPlayer.IsInCollision(BottomRightWall2.GetOBB())) {

		if (myPlayer.GetXPos() > BottomRightWall2.GetXPos()) {

			myPlayer.SetXIncPos(-10.0f);

			printf("hit test wall right 2 \n ");
		}
	}

	AngleWall = 2.57;
	ModelViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(1253, -244, 0.0));
	ModelViewMatrix = glm::rotate(ModelViewMatrix, AngleWall, glm::vec3(0.0, 0.0, 10.0));
	WallLeft2.Render(ModelViewMatrix, ProjectionMatrix);

	if (myPlayer.IsInCollision(WallLeft2.GetOBB())) {

		if (myPlayer.GetXPos() > WallLeft2.GetXPos()) {

			myPlayer.SetXIncPos(-10.0f);

			printf("hit test wall \n ");
		}
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

//NpcMovement functions and Collison
void npc1Movement(Sprite x) {
	
	if (x.IsInCollision(TopWall.GetOBB())) {

		Vnpc = -4.0f;
		headingNpc1 = rand();

	}

	if (x.IsInCollision(TopLeftWall.GetOBB())) {

		Vnpc = -4.0f;
		headingNpc1 = rand();
		//heading += 2.0f;
		//heading -= 2.0f;
	}
	if (x.IsInCollision(TopLeftWall2.GetOBB())) {

		Vnpc = -4.0f;
		headingNpc1 = rand();
		//heading += 2.0f;
		//heading -= 2.0f;
	}
	if (x.IsInCollision(TopLeftWall3.GetOBB())) {

		Vnpc = -4.0f;

		headingNpc1 = rand();
		//heading += 2.0f;
		//heading -= 2.0f;
	}
	if (x.IsInCollision(TopRightCorner.GetOBB())) {

		Vnpc = 4.0f;

		headingNpc1 = rand();
		//heading -= 2.0f;
	}
	if (x.IsInCollision(LeftWall.GetOBB())) {

		Vnpc = 4.0f;

		headingNpc1 = rand();
		//heading -= 2.0f;
	}
	if (x.IsInCollision(WallLeft2.GetOBB())) {

		Vnpc = 4.0f;

		headingNpc1 = rand();
		//heading -= 2.0f;
	}
	if (x.IsInCollision(MiddleLeftWall.GetOBB())) {

		Vnpc = 4.0f;

		//heading += 2.0f;
		headingNpc1 = rand();
	}
	if (x.IsInCollision(RightWall.GetOBB())) {

		Vnpc = 4.0f;

		headingNpc1 = rand();
		//heading -= 2.0f;
	}
	if (x.IsInCollision(BottomRightWall.GetOBB())) {

		Vnpc = -4.0f;

		//heading += 2.0f;
		headingNpc1 = rand();
	}
	if (x.IsInCollision(BottomRightWall2.GetOBB())) {

		Vnpc = -4.0f;

		headingNpc1 = rand();
		//heading -= 2.0f;
	}
	if (x.IsInCollision(BottomWall.GetOBB())) {

		Vnpc = 4.0f;
		headingNpc1 = rand();

	}
	if (x.IsInCollision(BottomWall2.GetOBB())) {

		Vnpc = 4.0f;
		headingNpc1 = rand();
	}
	if (x.IsInCollision(BottomLeftWall.GetOBB())) {
			Vnpc = 4.0f;
			headingNpc1 = rand();
	}

}

void npc2Movement(Sprite x) {

	if (x.IsInCollision(TopWall.GetOBB())) {

		Vnpc2 = -4.0f;
		headingNpc2 = rand();
	
	}

	if (x.IsInCollision(TopLeftWall.GetOBB())) {

		Vnpc2 = -4.0f;
		headingNpc2 = rand();
		
	}
	if (x.IsInCollision(TopLeftWall2.GetOBB())) {

		Vnpc2 = -4.0f;
		headingNpc2 = rand();
	
	}
	if (x.IsInCollision(TopLeftWall3.GetOBB())) {

		Vnpc2 = -4.0f;
		headingNpc2 = rand();

	}
	if (x.IsInCollision(TopRightCorner.GetOBB())) {

		Vnpc2 = 4.0f;
		headingNpc2 = rand();
	}
	if (x.IsInCollision(LeftWall.GetOBB())) {

		Vnpc2 = 4.0f;
		headingNpc2 = rand();

	}
	if (x.IsInCollision(WallLeft2.GetOBB())) {

		Vnpc2 = 4.0f;
		headingNpc2 = rand();
		
	}
	if (x.IsInCollision(MiddleLeftWall.GetOBB())) {

		Vnpc2 = 4.0f;
		headingNpc2 = rand();
	}
	if (x.IsInCollision(RightWall.GetOBB())) {

		Vnpc2 = 4.0f;
		headingNpc2 = rand();

	}
	if (x.IsInCollision(BottomRightWall.GetOBB())) {

		Vnpc2 = -4.0f;
		headingNpc2 = rand();
	}
	if (x.IsInCollision(BottomRightWall2.GetOBB())) {

		Vnpc2 = -4.0f;
		headingNpc2 = rand();
	
	}
	if (x.IsInCollision(BottomWall.GetOBB())) {

		Vnpc2 = 4.0f;
		headingNpc2 = rand();

	}
	if (x.IsInCollision(BottomWall2.GetOBB())) {

		Vnpc2 = 4.0f;
		headingNpc2 = rand();
	}
	if (x.IsInCollision(BottomLeftWall.GetOBB())) {
		Vnpc2 = 4.0f;
		headingNpc2 = rand();
	}

}

void npc3Movement(Sprite x) {


	if (x.IsInCollision(TopWall.GetOBB())) {

		Vnpc3 = -4.0f;
		headingNpc3 = rand();

	}

	if (x.IsInCollision(TopLeftWall.GetOBB())) {

		Vnpc3 = -4.0f;
		headingNpc3 = rand();

	}
	if (x.IsInCollision(TopLeftWall2.GetOBB())) {


		Vnpc3 = -4.0f;
		headingNpc3 = rand();
	}
	if (x.IsInCollision(TopLeftWall3.GetOBB())) {


		Vnpc3 = -4.0f;
		headingNpc3 = rand();
	}
	if (x.IsInCollision(TopRightCorner.GetOBB())) {

		Vnpc3 = 4.0f;
		headingNpc3 = rand();
	}
	if (x.IsInCollision(LeftWall.GetOBB())) {

		Vnpc3 = 4.0f;
		headingNpc3 = rand();
	}
	if (x.IsInCollision(WallLeft2.GetOBB())) {

		Vnpc3 = 4.0f;
		headingNpc3 = rand();
	}
	if (x.IsInCollision(MiddleLeftWall.GetOBB())) {

		Vnpc3 = 4.0f;
		headingNpc3 = rand();
	}
	if (x.IsInCollision(RightWall.GetOBB())) {

		Vnpc3 = 4.0f;
		headingNpc3 = rand();
	}
	if (x.IsInCollision(BottomRightWall.GetOBB())) {

		Vnpc3 = -4.0f;
		headingNpc3 = rand();
	}
	if (x.IsInCollision(BottomRightWall2.GetOBB())) {

		Vnpc3 = -4.0f;
		headingNpc3 = rand();
	}
	if (x.IsInCollision(BottomWall.GetOBB())) {

		Vnpc3 = 4.0f;
		headingNpc3 = rand();

	}
	if (x.IsInCollision(BottomWall2.GetOBB())) {

		Vnpc3 = 4.0f;
		headingNpc3 = rand();
	}
	if (x.IsInCollision(BottomLeftWall.GetOBB())) {
		Vnpc3 = 4.0f;
		headingNpc3 = rand();
	}

}

void npc4Movement(Sprite x) {


	if (x.IsInCollision(TopWall.GetOBB())) {

		Vnpc4 = -4.0f;
		headingNpc4 = rand();

	}

	if (x.IsInCollision(TopLeftWall.GetOBB())) {

		Vnpc4 = -4.0f;
		headingNpc4 = rand();

	}
	if (x.IsInCollision(TopLeftWall2.GetOBB())) {


		Vnpc4 = -4.0f;
		headingNpc4 = rand();
	}
	if (x.IsInCollision(TopLeftWall3.GetOBB())) {


		Vnpc4 = -4.0f;
		headingNpc4 = rand();
	}
	if (x.IsInCollision(TopRightCorner.GetOBB())) {

		Vnpc4 = 4.0f;
		headingNpc4 = rand();
	}
	if (x.IsInCollision(LeftWall.GetOBB())) {

		Vnpc4 = 4.0f;
		headingNpc4 = rand();
	}
	if (x.IsInCollision(WallLeft2.GetOBB())) {

		Vnpc4 = 4.0f;
		headingNpc4 = rand();
	}
	if (x.IsInCollision(MiddleLeftWall.GetOBB())) {

		Vnpc4 = 4.0f;
		headingNpc4 = rand();
	}
	if (x.IsInCollision(RightWall.GetOBB())) {

		Vnpc4 = 4.0f;
		headingNpc4 = rand();
	}
	if (x.IsInCollision(BottomRightWall.GetOBB())) {

		Vnpc4 = -4.0f;
		headingNpc4 = rand();
	}
	if (x.IsInCollision(BottomRightWall2.GetOBB())) {

		Vnpc4 = -4.0f;
		headingNpc4 = rand();
	}
	if (x.IsInCollision(BottomWall.GetOBB())) {

		Vnpc4 = 4.0f;
		headingNpc4 = rand();

	}
	if (x.IsInCollision(BottomWall2.GetOBB())) {

		Vnpc4 = 4.0f;
		headingNpc4 = rand();
	}
	if (x.IsInCollision(BottomLeftWall.GetOBB())) {
		Vnpc4 = 4.0f;
		headingNpc4 = rand();
	}

}

void npc5Movement(Sprite x) {


	if (x.IsInCollision(TopWall.GetOBB())) {

		Vnpc5 = -4.0f;
		headingNpc5 = rand();

	}

	if (x.IsInCollision(TopLeftWall.GetOBB())) {

		Vnpc5 = -4.0f;
		headingNpc5 = rand();

	}
	if (x.IsInCollision(TopLeftWall2.GetOBB())) {


		Vnpc5 = -4.0f;
		headingNpc5 = rand();
	}
	if (x.IsInCollision(TopLeftWall3.GetOBB())) {


		Vnpc5 = -4.0f;
		headingNpc5 = rand();
	}
	if (x.IsInCollision(TopRightCorner.GetOBB())) {

		Vnpc5 = 4.0f;
		headingNpc5 = rand();
	}
	if (x.IsInCollision(LeftWall.GetOBB())) {

		Vnpc5 = 4.0f;
		headingNpc5 = rand();
	}
	if (x.IsInCollision(WallLeft2.GetOBB())) {

		Vnpc5 = 4.0f;
		headingNpc5 = rand();
	}
	if (x.IsInCollision(MiddleLeftWall.GetOBB())) {

		Vnpc5 = 4.0f;
		headingNpc5 = rand();
	}
	if (x.IsInCollision(RightWall.GetOBB())) {

		Vnpc5 = 4.0f;
		headingNpc5 = rand();
	}
	if (x.IsInCollision(BottomRightWall.GetOBB())) {

		Vnpc5 = -4.0f;
		headingNpc5 = rand();
	}
	if (x.IsInCollision(BottomRightWall2.GetOBB())) {

		Vnpc5 = -4.0f;
		headingNpc5 = rand();
	}
	if (x.IsInCollision(BottomWall.GetOBB())) {

		Vnpc5 = 4.0f;
		headingNpc5 = rand();

	}
	if (x.IsInCollision(BottomWall2.GetOBB())) {

		Vnpc5 = 4.0f;
		headingNpc5 = rand();
	}
	if (x.IsInCollision(BottomLeftWall.GetOBB())) {
		Vnpc5 = 4.0f;
		headingNpc5 = rand();
	}

}

void npc6Movement(Sprite x) {


	if (x.IsInCollision(TopWall.GetOBB())) {

		Vnpc6 = -4.0f;
		headingNpc6 = rand();

	}

	if (x.IsInCollision(TopLeftWall.GetOBB())) {

		Vnpc6 = -4.0f;
		headingNpc6 = rand();

	}
	if (x.IsInCollision(TopLeftWall2.GetOBB())) {


		Vnpc6 = -4.0f;
		headingNpc6 = rand();
	}
	if (x.IsInCollision(TopLeftWall3.GetOBB())) {


		Vnpc6 = -4.0f;
		headingNpc6 = rand();
	}
	if (x.IsInCollision(TopRightCorner.GetOBB())) {

		Vnpc6 = 4.0f;
		headingNpc6 = rand();
	}
	if (x.IsInCollision(LeftWall.GetOBB())) {

		Vnpc6 = 4.0f;
		headingNpc6 = rand();
	}
	if (x.IsInCollision(WallLeft2.GetOBB())) {

		Vnpc6 = 4.0f;
		headingNpc6 = rand();
	}
	if (x.IsInCollision(MiddleLeftWall.GetOBB())) {

		Vnpc6 = 4.0f;
		headingNpc6 = rand();
	}
	if (x.IsInCollision(RightWall.GetOBB())) {

		Vnpc6 = 4.0f;
		headingNpc6 = rand();
	}
	if (x.IsInCollision(BottomRightWall.GetOBB())) {

		Vnpc6 = -4.0f;
		headingNpc6 = rand();
	}
	if (x.IsInCollision(BottomRightWall2.GetOBB())) {

		Vnpc6 = -4.0f;
		headingNpc6 = rand();
	}
	if (x.IsInCollision(BottomWall.GetOBB())) {

		Vnpc6 = 4.0f;
		headingNpc6 = rand();

	}
	if (x.IsInCollision(BottomWall2.GetOBB())) {

		Vnpc6 = 4.0f;
		headingNpc6 = rand();
	}
	if (x.IsInCollision(BottomLeftWall.GetOBB())) {
		Vnpc6 = 4.0f;
		headingNpc6 = rand();
	}

}

void npc61Movement(Sprite x) {


	if (x.IsInCollision(TopWall.GetOBB())) {

		Vnpc61 = -4.0f;
		headingNpc61 = rand();

	}

	if (x.IsInCollision(TopLeftWall.GetOBB())) {

		Vnpc61 = -4.0f;
		headingNpc61 = rand();

	}
	if (x.IsInCollision(TopLeftWall2.GetOBB())) {


		Vnpc61 = -4.0f;
		headingNpc61 = rand();
	}
	if (x.IsInCollision(TopLeftWall3.GetOBB())) {


		Vnpc61 = -4.0f;
		headingNpc61 = rand();
	}
	if (x.IsInCollision(TopRightCorner.GetOBB())) {

		Vnpc61 = 4.0f;
		headingNpc61 = rand();
	}
	if (x.IsInCollision(LeftWall.GetOBB())) {

		Vnpc61 = 4.0f;
		headingNpc61 = rand();
	}
	if (x.IsInCollision(WallLeft2.GetOBB())) {

		Vnpc61 = 4.0f;
		headingNpc61 = rand();
	}
	if (x.IsInCollision(MiddleLeftWall.GetOBB())) {

		Vnpc61 = 4.0f;
		headingNpc61 = rand();
	}
	if (x.IsInCollision(RightWall.GetOBB())) {

		Vnpc61 = 4.0f;
		headingNpc61 = rand();
	}
	if (x.IsInCollision(BottomRightWall.GetOBB())) {

		Vnpc61 = -4.0f;
		headingNpc61 = rand();
	}
	if (x.IsInCollision(BottomRightWall2.GetOBB())) {

		Vnpc61 = -4.0f;
		headingNpc61 = rand();
	}
	if (x.IsInCollision(BottomWall.GetOBB())) {

		Vnpc61 = 4.0f;
		headingNpc61 = rand();

	}
	if (x.IsInCollision(BottomWall2.GetOBB())) {

		Vnpc61 = 4.0f;
		headingNpc61 = rand();
	}
	if (x.IsInCollision(BottomLeftWall.GetOBB())) {
		Vnpc61 = 4.0f;
		headingNpc61 = rand();
	}

}

void npc62Movement(Sprite x) {


	if (x.IsInCollision(TopWall.GetOBB())) {

		Vnpc62 = -4.0f;
		headingNpc62 = rand();

	}

	if (x.IsInCollision(TopLeftWall.GetOBB())) {

		Vnpc62 = -4.0f;
		headingNpc62 = rand();

	}
	if (x.IsInCollision(TopLeftWall2.GetOBB())) {


		Vnpc62 = -4.0f;
		headingNpc62 = rand();
	}
	if (x.IsInCollision(TopLeftWall3.GetOBB())) {


		Vnpc62 = -4.0f;
		headingNpc62 = rand();
	}
	if (x.IsInCollision(TopRightCorner.GetOBB())) {

		Vnpc62 = 4.0f;
		headingNpc62 = rand();
	}
	if (x.IsInCollision(LeftWall.GetOBB())) {

		Vnpc62 = 4.0f;
		headingNpc62 = rand();
	}
	if (x.IsInCollision(WallLeft2.GetOBB())) {

		Vnpc62 = 4.0f;
		headingNpc62 = rand();
	}
	if (x.IsInCollision(MiddleLeftWall.GetOBB())) {

		Vnpc62 = 4.0f;
		headingNpc62 = rand();
	}
	if (x.IsInCollision(RightWall.GetOBB())) {

		Vnpc62 = 4.0f;
		headingNpc62 = rand();
	}
	if (x.IsInCollision(BottomRightWall.GetOBB())) {

		Vnpc62 = -4.0f;
		headingNpc62 = rand();
	}
	if (x.IsInCollision(BottomRightWall2.GetOBB())) {

		Vnpc62 = -4.0f;
		headingNpc62 = rand();
	}
	if (x.IsInCollision(BottomWall.GetOBB())) {

		Vnpc62 = 4.0f;
		headingNpc62 = rand();

	}
	if (x.IsInCollision(BottomWall2.GetOBB())) {

		Vnpc62 = 4.0f;
		headingNpc62 = rand();
	}
	if (x.IsInCollision(BottomLeftWall.GetOBB())) {
		Vnpc62 = 4.0f;
		headingNpc62 = rand();
	}

}

void npc63Movement(Sprite x) {


	if (x.IsInCollision(TopWall.GetOBB())) {

		Vnpc63 = -4.0f;
		headingNpc63 = rand();

	}

	if (x.IsInCollision(TopLeftWall.GetOBB())) {

		Vnpc63 = -4.0f;
		headingNpc63 = rand();

	}
	if (x.IsInCollision(TopLeftWall2.GetOBB())) {


		Vnpc63 = -4.0f;
		headingNpc63 = rand();
	}
	if (x.IsInCollision(TopLeftWall3.GetOBB())) {


		Vnpc63 = -4.0f;
		headingNpc63 = rand();
	}
	if (x.IsInCollision(TopRightCorner.GetOBB())) {

		Vnpc63 = 4.0f;
		headingNpc63 = rand();
	}
	if (x.IsInCollision(LeftWall.GetOBB())) {

		Vnpc63 = 4.0f;
		headingNpc63 = rand();
	}
	if (x.IsInCollision(WallLeft2.GetOBB())) {

		Vnpc63 = 4.0f;
		headingNpc63 = rand();
	}
	if (x.IsInCollision(MiddleLeftWall.GetOBB())) {

		Vnpc63 = 4.0f;
		headingNpc63 = rand();
	}
	if (x.IsInCollision(RightWall.GetOBB())) {

		Vnpc63 = 4.0f;
		headingNpc63 = rand();
	}
	if (x.IsInCollision(BottomRightWall.GetOBB())) {

		Vnpc63 = -4.0f;
		headingNpc63 = rand();
	}
	if (x.IsInCollision(BottomRightWall2.GetOBB())) {

		Vnpc63 = -4.0f;
		headingNpc63 = rand();
	}
	if (x.IsInCollision(BottomWall.GetOBB())) {

		Vnpc63 = 4.0f;
		headingNpc63 = rand();

	}
	if (x.IsInCollision(BottomWall2.GetOBB())) {

		Vnpc63 = 4.0f;
		headingNpc63 = rand();
	}
	if (x.IsInCollision(BottomLeftWall.GetOBB())) {
		Vnpc63 = 4.0f;
		headingNpc63 = rand();
	}

}

void npc7Movement(Sprite x) {


	if (x.IsInCollision(TopWall.GetOBB())) {

		Vnpc7 = -7.0f;
		headingNpc7 = rand();
		

	}

	if (x.IsInCollision(TopLeftWall.GetOBB())) {

		Vnpc7 = -7.0f;
		headingNpc7 = rand();

	}
	if (x.IsInCollision(TopLeftWall2.GetOBB())) {


		Vnpc7 = -7.0f;
		headingNpc7 = rand();
	}
	if (x.IsInCollision(TopLeftWall3.GetOBB())) {


		Vnpc7 = -7.0f;
		headingNpc7 = rand();
	}
	if (x.IsInCollision(TopRightCorner.GetOBB())) {

		Vnpc7 = 7.0f;
		headingNpc7 = rand();
	}
	if (x.IsInCollision(LeftWall.GetOBB())) {

		Vnpc7 = 7.0f;
		headingNpc7 = rand();
	}
	if (x.IsInCollision(WallLeft2.GetOBB())) {

		Vnpc7 = 7.0f;
		headingNpc7 = rand();
	}
	if (x.IsInCollision(MiddleLeftWall.GetOBB())) {

		Vnpc7 = 7.0f;
		headingNpc7 = rand();
	}
	if (x.IsInCollision(RightWall.GetOBB())) {

		Vnpc7 = 7.0f;
		headingNpc7 = rand();
	}
	if (x.IsInCollision(BottomRightWall.GetOBB())) {

		Vnpc7 = -7.0f;
		headingNpc7 = rand();
	}
	if (x.IsInCollision(BottomRightWall2.GetOBB())) {

		Vnpc7 = -7.0f;
		headingNpc7 = rand();
	}
	if (x.IsInCollision(BottomWall.GetOBB())) {

		Vnpc7 = 7.0f;
		headingNpc7 = rand();

	}
	if (x.IsInCollision(BottomWall2.GetOBB())) {

		Vnpc7 = 7.0f;
		headingNpc7 = rand();
	}
	if (x.IsInCollision(BottomLeftWall.GetOBB())) {
		Vnpc7 = 7.0f;
		headingNpc7 = rand();
	}

}

void npc8Movement(Sprite x) {


	if (x.IsInCollision(TopWall.GetOBB())) {

		Vnpc8 = -4.0f;
		headingNpc8 = rand();

	}

	if (x.IsInCollision(TopLeftWall.GetOBB())) {

		Vnpc8 = -4.0f;
		headingNpc8 = rand();

	}
	if (x.IsInCollision(TopLeftWall2.GetOBB())) {


		Vnpc8 = -4.0f;
		headingNpc8 = rand();
	}
	if (x.IsInCollision(TopLeftWall3.GetOBB())) {


		Vnpc8 = -4.0f;
		headingNpc8 = rand();
	}
	if (x.IsInCollision(TopRightCorner.GetOBB())) {

		Vnpc8 = 4.0f;
		headingNpc8 = rand();
	}
	if (x.IsInCollision(LeftWall.GetOBB())) {

		Vnpc8 = 4.0f;
		headingNpc8 = rand();
	}
	if (x.IsInCollision(WallLeft2.GetOBB())) {

		Vnpc8 = 4.0f;
		headingNpc8 = rand();
	}
	if (x.IsInCollision(MiddleLeftWall.GetOBB())) {

		Vnpc8 = 4.0f;
		headingNpc8 = rand();
	}
	if (x.IsInCollision(RightWall.GetOBB())) {

		Vnpc8 = 4.0f;
		headingNpc8 = rand();
	}
	if (x.IsInCollision(BottomRightWall.GetOBB())) {

		Vnpc8 = -4.0f;
		headingNpc8 = rand();
	}
	if (x.IsInCollision(BottomRightWall2.GetOBB())) {

		Vnpc8 = -4.0f;
		headingNpc8 = rand();
	}
	if (x.IsInCollision(BottomWall.GetOBB())) {

		Vnpc8 = 4.0f;
		headingNpc8 = rand();

	}
	if (x.IsInCollision(BottomWall2.GetOBB())) {

		Vnpc8 = 4.0f;
		headingNpc8 = rand();
	}
	if (x.IsInCollision(BottomLeftWall.GetOBB())) {
		Vnpc8 = 4.0f;
		headingNpc8 = rand();
	}

}

void npc9Movement(Sprite x) {


	if (x.IsInCollision(TopWall.GetOBB())) {

		Vnpc9 = -4.0f;
		headingNpc9 = rand();

	}

	if (x.IsInCollision(TopLeftWall.GetOBB())) {

		Vnpc9 = -4.0f;
		headingNpc9 = rand();

	}
	if (x.IsInCollision(TopLeftWall2.GetOBB())) {


		Vnpc9 = -4.0f;
		headingNpc9 = rand();
	}
	if (x.IsInCollision(TopLeftWall3.GetOBB())) {


		Vnpc9 = -4.0f;
		headingNpc9 = rand();
	}
	if (x.IsInCollision(TopRightCorner.GetOBB())) {

		Vnpc9 = 4.0f;
		headingNpc9 = rand();
	}
	if (x.IsInCollision(LeftWall.GetOBB())) {

		Vnpc9 = 4.0f;
		headingNpc9 = rand();
	}
	if (x.IsInCollision(WallLeft2.GetOBB())) {

		Vnpc9 = 4.0f;
		headingNpc9 = rand();
	}
	if (x.IsInCollision(MiddleLeftWall.GetOBB())) {

		Vnpc9 = 4.0f;
		headingNpc9 = rand();
	}
	if (x.IsInCollision(RightWall.GetOBB())) {

		Vnpc9 = 4.0f;
		headingNpc9 = rand();
	}
	if (x.IsInCollision(BottomRightWall.GetOBB())) {

		Vnpc9 = -4.0f;
		headingNpc9 = rand();
	}
	if (x.IsInCollision(BottomRightWall2.GetOBB())) {

		Vnpc9 = -4.0f;
		headingNpc9 = rand();
	}
	if (x.IsInCollision(BottomWall.GetOBB())) {

		Vnpc9 = 4.0f;
		headingNpc9 = rand();

	}
	if (x.IsInCollision(BottomWall2.GetOBB())) {

		Vnpc9 = 4.0f;
		headingNpc9 = rand();
	}
	if (x.IsInCollision(BottomLeftWall.GetOBB())) {
		Vnpc9 = 4.0f;
		headingNpc9 = rand();
	}

}

void npc10Movement(Sprite x) {


	if (x.IsInCollision(TopWall.GetOBB())) {

		Vnpc10 = -10.0f;
		headingNpc10 = rand();

	}

	if (x.IsInCollision(TopLeftWall.GetOBB())) {

		Vnpc10 = -10.0f;
		headingNpc10 = rand();

	}
	if (x.IsInCollision(TopLeftWall2.GetOBB())) {


		Vnpc10 = -10.0f;
		headingNpc10 = rand();
	}
	if (x.IsInCollision(TopLeftWall3.GetOBB())) {


		Vnpc10 = -10.0f;
		headingNpc10 = rand();
	}
	if (x.IsInCollision(TopRightCorner.GetOBB())) {

		Vnpc10 = 10.0f;
		headingNpc10 = rand();
	}
	if (x.IsInCollision(LeftWall.GetOBB())) {

		Vnpc10 = 10.0f;
		headingNpc10 = rand();
	}
	if (x.IsInCollision(WallLeft2.GetOBB())) {

		Vnpc10 = 10.0f;
		headingNpc10 = rand();
	}
	if (x.IsInCollision(MiddleLeftWall.GetOBB())) {

		Vnpc10 = 10.0f;
		headingNpc10 = rand();
	}
	if (x.IsInCollision(RightWall.GetOBB())) {

		Vnpc10 = 10.0f;
		headingNpc10 = rand();
	}
	if (x.IsInCollision(BottomRightWall.GetOBB())) {

		Vnpc10 = -10.0f;
		headingNpc10 = rand();
	}
	if (x.IsInCollision(BottomRightWall2.GetOBB())) {

		Vnpc10 = -10.0f;
		headingNpc10 = rand();
	}
	if (x.IsInCollision(BottomWall.GetOBB())) {

		Vnpc10 = 10.0f;
		headingNpc10 = rand();

	}
	if (x.IsInCollision(BottomWall2.GetOBB())) {

		Vnpc10 = 10.0f;
		headingNpc10 = rand();
	}
	if (x.IsInCollision(BottomLeftWall.GetOBB())) {
		Vnpc10 = 10.0f;
		headingNpc10 = rand();
	}

}

void npcHitnpc(Sprite x, Sprite y) {

	if (x.IsInCollision(y.GetOBB())) {
		
		Vnpc = (-4.0f);

	}
	
}

void npcHitnpc2(Sprite x, Sprite y) {

	if (x.IsInCollision(y.GetOBB())) {

		Vnpc2 = (-4.0f);

	}

}

void npcHitnpc3(Sprite x, Sprite y) {

	if (x.IsInCollision(y.GetOBB())) {

		Vnpc3 = (-4.0f);

	}

}

void npcHitnpc4(Sprite x, Sprite y) {

	if (x.IsInCollision(y.GetOBB())) {

		Vnpc4 = (-4.0f);

	}

}

void npcHitnpc5(Sprite x, Sprite y) {

	if (x.IsInCollision(y.GetOBB())) {

		Vnpc5 = (-4.0f);

	}

}

void npcHitnpc6(Sprite x, Sprite y) {

	if (x.IsInCollision(y.GetOBB())) {

		Vnpc6 = (-4.0f);

	}

}

void npcHitnpc7(Sprite x, Sprite y) {

	if (x.IsInCollision(y.GetOBB())) {

		Vnpc7 = (-4.0f);

	}

}

void npcHitnpc8(Sprite x, Sprite y) {

	if (x.IsInCollision(y.GetOBB())) {

		Vnpc8 = (-4.0f);

	}

}

void npcHitnpc9(Sprite x, Sprite y) {

	if (x.IsInCollision(y.GetOBB())) {

		Vnpc4 = (-4.0f);

	}
}

void NpcHeading() {

	Xnpc += Vnpc * cos((90.0f + headingNpc1) * (PI / 180.0f));
	Ynpc += Vnpc * sin((90.0f + headingNpc1) * (PI / 180.0f));

	Xnpc2 += Vnpc2 * cos((90.0f + headingNpc2) * (PI / 180.0f));
	Ynpc2 += Vnpc2 * sin((90.0f + headingNpc2) * (PI / 180.0f));

	Xnpc3 += Vnpc5 * cos((90.0f + headingNpc3) * (PI / 180.0f));
	Ynpc3 += Vnpc5 * sin((90.0f + headingNpc3) * (PI / 180.0f));

	Xnpc4 += Vnpc5 * cos((90.0f + headingNpc4) * (PI / 180.0f));
	Ynpc4 += Vnpc5 * sin((90.0f + headingNpc4) * (PI / 180.0f));

	Xnpc5 += Vnpc5 * cos((90.0f + headingNpc5) * (PI / 180.0f));
	Ynpc5 += Vnpc5 * sin((90.0f + headingNpc5) * (PI / 180.0f));

	Xnpc6 += Vnpc6 * cos((90.0f + headingNpc6) * (PI / 180.0f));
	Ynpc6 += Vnpc6 * sin((90.0f + headingNpc6) * (PI / 180.0f));

	Xnpc61 += Vnpc61 * cos((90.0f + headingNpc61) * (PI / 180.0f));
	Ynpc61 += Vnpc61 * sin((90.0f + headingNpc61) * (PI / 180.0f));

	Xnpc62 += Vnpc62 * cos((90.0f + headingNpc62) * (PI / 180.0f));
	Ynpc62 += Vnpc62 * sin((90.0f + headingNpc62) * (PI / 180.0f));

	Xnpc63 += Vnpc63 * cos((90.0f + headingNpc63) * (PI / 180.0f));
	Ynpc63 += Vnpc63 * sin((90.0f + headingNpc63) * (PI / 180.0f));
	
}

void HarderNpcHeading() {
	Xnpc7 += Vnpc7 * cos((90.0f + headingNpc7) * (PI / 180.0f));
	Ynpc7 += Vnpc7 * sin((90.0f + headingNpc7) * (PI / 180.0f));

	Xnpc8 += Vnpc8 * cos((90.0f + headingNpc8) * (PI / 180.0f));
	Ynpc8 += Vnpc8 * sin((90.0f + headingNpc8) * (PI / 180.0f));
}

//updates 
void display()								
{	
	//clear the colour and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//carmea postion 
	ViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, 0.0));

	glEnable(GL_BLEND);

	//----Game background------
	//background is a lung which is highly infected by bugs and virus

	ModelViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(150.0, -100.0, 0.0));
	MybackGround.Render(ModelViewMatrix, ProjectionMatrix);

	//-----walls----- 
	walls();

	//---------NPCS--------------------------------------------------------
	//Non Playerable characters
	 
	//--Npc1 
	ModelViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(Xnpc + 350 , Ynpc + 400, 0.0));
	ModelViewMatrix = glm::rotate(ModelViewMatrix, glm::radians(headingNpc1), glm::vec3(0.0, 0.0, 1.0));
	Npc1.Render(ModelViewMatrix, ProjectionMatrix);

	npc1Movement(Npc1);
	npcHitnpc(Npc1, Npc2);
	npcHitnpc(Npc1, Npc3);
	npcHitnpc(Npc1, Npc4);
	npcHitnpc(Npc1, Npc5);
	npcHitnpc(Npc1, Npc6);
	npcHitnpc(Npc1, Npc61);
	npcHitnpc(Npc1, Npc62);
	npcHitnpc(Npc1, Npc63);
	npcHitnpc(Npc1, Npc7);
	npcHitnpc(Npc1, Npc8);
	npcHitnpc(Npc1, Npc9);
	//when playerweapn hits npc it will set that size so it cant be seen anymore 
	//and set the ncp death to 1 which makes the npc unable to be hit player after death.
	if (playerWeapon.IsInCollision(Npc1.GetOBB()) && Npc1death == 0) {
		Npc1death = 1;
		NpcsKilled += 1;
		Npc1.SetYpos(1400);
		Npc1.SetXpos(1000);
		Npc1.SetHeight(0.0f);
		Npc1.SetWidth(0.0f);
		Npc1.Init(green, "textures/easy1.png");

	}
	
	//--Npc2
	ModelViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(Xnpc2 -320.0,Ynpc2 -300, 0.0));
	ModelViewMatrix = glm::rotate(ModelViewMatrix, glm::radians(headingNpc2), glm::vec3(0.0, 0.0, 1.0));
	Npc2.Render(ModelViewMatrix, ProjectionMatrix);
	npc2Movement(Npc2);

	npcHitnpc2(Npc2, Npc1);
	npcHitnpc2(Npc2, Npc3);
	npcHitnpc2(Npc2, Npc4);
	npcHitnpc2(Npc2, Npc5);
	npcHitnpc2(Npc2, Npc6);
	npcHitnpc2(Npc2, Npc61);
	npcHitnpc2(Npc2, Npc62);
	npcHitnpc2(Npc2, Npc63);
	npcHitnpc2(Npc2, Npc7);
	npcHitnpc2(Npc2, Npc8);
	npcHitnpc2(Npc2, Npc9);

	if (myPlayer.IsInCollision(Npc2.GetOBB()) && Npc2death == 0) {
		
		PlayerHp -= 1;
	}


	if (playerWeapon.IsInCollision(Npc2.GetOBB()) && Npc2death == 0) {
		Npc2death = 1;
		//Npc health go done which time hit if zero it die
		//set up so move random when hit 
		NpcsKilled += 1;
		Npc2.SetYpos(1400);
		Npc2.SetXpos(1000);
		Npc2.SetHeight(0.0f);
		Npc2.SetWidth(0.0f);
		Npc2.Init(green, "textures/easy1.png");
		

	}

	//--Npc3												
	ModelViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(Xnpc3 + -300.0, Ynpc3 + -1200.0, 0.0));
	ModelViewMatrix = glm::rotate(ModelViewMatrix, glm::radians(headingNpc3), glm::vec3(0.0, 0.0, 1.0));
	Npc3.Render(ModelViewMatrix, ProjectionMatrix);
	npc3Movement(Npc3);
	npcHitnpc3(Npc3, Npc1);
	npcHitnpc3(Npc3, Npc2);
	npcHitnpc3(Npc3, Npc4);
	npcHitnpc3(Npc3, Npc5);
	npcHitnpc3(Npc3, Npc6);
	npcHitnpc3(Npc3, Npc61);
	npcHitnpc3(Npc3, Npc62);
	npcHitnpc3(Npc3, Npc63);
	npcHitnpc3(Npc3, Npc7);
	npcHitnpc3(Npc3, Npc8);
	npcHitnpc3(Npc3, Npc9);

	if (myPlayer.IsInCollision(Npc3.GetOBB()) && Npc3death == 0) {

		PlayerHp -= 1;
	}

	if (playerWeapon.IsInCollision(Npc3.GetOBB()) && Npc3death == 0) {
		Npc3death = 1;
		//Npc health go done which time hit if zero it die
		//set up so move random when hit 
		NpcsKilled += 1;
		Npc3.SetYpos(1400);
		Npc3.SetXpos(1000);
		Npc3.SetHeight(0.0f);
		Npc3.SetWidth(0.0f);
		Npc3.Init(green, "textures/easy1.png");

	}

	//--Npc4
	ModelViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(Xnpc4 + 100.0, Ynpc4 + 1400.0, 0.0));
	ModelViewMatrix = glm::rotate(ModelViewMatrix, glm::radians(headingNpc4), glm::vec3(0.0, 0.0, 1.0));
	Npc4.Render(ModelViewMatrix, ProjectionMatrix);
	npc4Movement(Npc4);

	npcHitnpc4(Npc4, Npc1);
	npcHitnpc4(Npc4, Npc2);
	npcHitnpc4(Npc4, Npc3);
	npcHitnpc4(Npc4, Npc5);
	npcHitnpc4(Npc4, Npc6);
	npcHitnpc4(Npc4, Npc61);
	npcHitnpc4(Npc4, Npc62);
	npcHitnpc4(Npc4, Npc63);
	npcHitnpc4(Npc4, Npc7);
	npcHitnpc4(Npc4, Npc8);
	npcHitnpc4(Npc4, Npc9);
	if (myPlayer.IsInCollision(Npc4.GetOBB()) && Npc4death == 0) {

		PlayerHp -= 1;
	}

	if (playerWeapon.IsInCollision(Npc4.GetOBB()) && Npc4death == 0) {
		Npc4death = 1;
		//Npc health go done which time hit if zero it die
		//set up so move random when hit 
		NpcsKilled += 1;
		Npc4.SetYpos(1400);
		Npc4.SetXpos(1000);
		Npc4.SetHeight(0.0f);
		Npc4.SetWidth(0.0f);
		Npc4.Init(green, "textures/easy1.png");

	}
	
	//--Npc5
	ModelViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(Xnpc5 + -700.0, Ynpc5 -300.0, 0.0));
	ModelViewMatrix = glm::rotate(ModelViewMatrix, Angle * 5, glm::vec3(0.0, 0.0, 10.0));
	ModelViewMatrix = glm::rotate(ModelViewMatrix, glm::radians(headingNpc4), glm::vec3(0.0, 0.0, 1.0));
	Npc5.Render(ModelViewMatrix, ProjectionMatrix);
	npc5Movement(Npc5);

	npcHitnpc5(Npc5, Npc1);
	npcHitnpc5(Npc5, Npc2);
	npcHitnpc5(Npc5, Npc3);
	npcHitnpc5(Npc5, Npc4);
	npcHitnpc5(Npc5, Npc6);
	npcHitnpc5(Npc5, Npc61);
	npcHitnpc5(Npc5, Npc62);
	npcHitnpc5(Npc5, Npc63);
	npcHitnpc5(Npc5, Npc7);
	npcHitnpc5(Npc5, Npc8);
	npcHitnpc5(Npc5, Npc9);

	if (myPlayer.IsInCollision(Npc5.GetOBB()) && Npc5death == 0) {
		PlayerHp -= 2;

	}
	if (playerWeapon.IsInCollision(Npc5.GetOBB()) && Npc5death == 0) {
		Npc5death = 1;
		NpcsKilled += 1;
		Npc5.SetYpos(2400);
		Npc5.SetXpos(2000);
		Npc5.SetHeight(0.0f);
		Npc5.SetWidth(0.0f);
		Npc5.Init(green, "textures/easy1.png");

	}

	//--Npc6 
	ModelViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(Xnpc6 + 350.0, Ynpc6 + 500.0, 0.0));
	ModelViewMatrix = glm::rotate(ModelViewMatrix, Angle , glm::vec3(0.0, 0.0, 1.0));
	ModelViewMatrix = glm::rotate(ModelViewMatrix, glm::radians(headingNpc4), glm::vec3(0.0, 0.0, 1.0));
	Npc6.Render(ModelViewMatrix, ProjectionMatrix);
	npc6Movement(Npc6);

	if (myPlayer.IsInCollision(Npc6.GetOBB()) && Npc6death == 0) {
		PlayerHp -= 1;

	}
	if (playerWeapon.IsInCollision(Npc6.GetOBB()) && Npc6death == 0) {
		Npc6death = 1;
		NpcsKilled += 1;
		Npc6.SetYpos(2400);
		Npc6.SetXpos(2000);
		Npc6.SetHeight(0.0f);
		Npc6.SetWidth(0.0f);
		Npc6.Init(green, "textures/easy1.png");

	}
	
	//--Npc6.1
	ModelViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(Xnpc61 + 700.0, Xnpc61 + 130.0, 0.0));
	ModelViewMatrix = glm::rotate(ModelViewMatrix, Angle, glm::vec3(0.0, 0.0, 10.0));
	ModelViewMatrix = glm::rotate(ModelViewMatrix, glm::radians(headingNpc61), glm::vec3(0.0, 0.0, 1.0));
	Npc61.Render(ModelViewMatrix, ProjectionMatrix);
	npc61Movement(Npc61);

	if (myPlayer.IsInCollision(Npc61.GetOBB()) && Npc61death == 0) {
		PlayerHp -= 1;

	}
	if (playerWeapon.IsInCollision(Npc61.GetOBB()) && Npc61death == 0) {
		Npc61death = 1;
		NpcsKilled += 1;
		Npc61.SetYpos(2400);
		Npc61.SetXpos(2000);
		Npc61.SetHeight(0.0f);
		Npc61.SetWidth(0.0f);
		Npc61.Init(green, "textures/easy1.png");

	}

	//--Npc6.2
	ModelViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(Xnpc62 + -600.0, Ynpc62 + -1000.0, 0.0));
	ModelViewMatrix = glm::rotate(ModelViewMatrix, Angle, glm::vec3(0.0, 0.0, 10.0));
	ModelViewMatrix = glm::rotate(ModelViewMatrix, glm::radians(headingNpc62), glm::vec3(0.0, 0.0, 1.0));
	Npc62.Render(ModelViewMatrix, ProjectionMatrix);
	npc62Movement(Npc62);

	if (myPlayer.IsInCollision(Npc62.GetOBB()) && Npc62death == 0) {
		PlayerHp -= 1;

	}

	if (playerWeapon.IsInCollision(Npc62.GetOBB()) && Npc62death == 0) {
		Npc62death = 1;
		NpcsKilled += 1;
		Npc62.SetYpos(2400);
		Npc62.SetXpos(2000);
		Npc62.SetHeight(0.0f);
		Npc62.SetWidth(0.0f);
		Npc62.Init(green, "textures/easy1.png");
	}

	//--Npc6.3
	ModelViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(Xnpc63 + 150.0, Ynpc63 + 300.0, 0.0));
	ModelViewMatrix = glm::rotate(ModelViewMatrix, Angle, glm::vec3(0.0, 0.0, 10.0));
	ModelViewMatrix = glm::rotate(ModelViewMatrix, glm::radians(headingNpc63), glm::vec3(0.0, 0.0, 1.0));
	Npc63.Render(ModelViewMatrix, ProjectionMatrix);
	npc63Movement(Npc63);

	
	if (myPlayer.IsInCollision(Npc63.GetOBB()) && Npc63death == 0) {
		PlayerHp -= 1;

	}
	if (playerWeapon.IsInCollision(Npc63.GetOBB()) && Npc63death == 0) {
		Npc63death = 1;
		NpcsKilled += 1;
		Npc63.SetYpos(2400);
		Npc63.SetXpos(2000);
		Npc63.SetHeight(0.0f);
		Npc63.SetWidth(0.0f);
		Npc63.Init(green, "textures/easy1.png");
	}

	
	//Spawn Npc7 and Npc8 when NpcKiled count is 8 or greater
	if (NpcsKilled >= 8) {

		HarderNpcHeading();
		//Npc7
		ModelViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(Xnpc7 + Npc7.GetXPos(), Ynpc7 + Npc7.GetYPos(), 0.0));
		ModelViewMatrix = glm::rotate(ModelViewMatrix, glm::radians(headingNpc7), glm::vec3(0.0, 0.0, 1.0));
		Npc7.Render(ModelViewMatrix, ProjectionMatrix);
		npc7Movement(Npc7);
		npcHitnpc7(Npc7, Npc1);
		npcHitnpc7(Npc7, Npc2);
		npcHitnpc7(Npc7, Npc3);
		npcHitnpc7(Npc7, Npc4);
		npcHitnpc7(Npc7, Npc5);
		npcHitnpc7(Npc7, Npc61);
		npcHitnpc7(Npc7, Npc62);
		npcHitnpc7(Npc7, Npc63);
		npcHitnpc7(Npc7, Npc6);
		npcHitnpc7(Npc7, Npc8);
		npcHitnpc7(Npc7, Npc9);
		if (myPlayer.IsInCollision(Npc7.GetOBB()) && Npc7death == 0) {
			PlayerHp -= 1;

		}
		if (playerWeapon.IsInCollision(Npc7.GetOBB()) && Npc7death == 0) {
			Npc7death = 1;
			NpcsKilled += 1;
			Npc7.SetHeight(0.0f);
			Npc7.SetWidth(0.0f);
			Npc7.Init(green, "textures/easy1.png");
		}

		//Npc8 
		ModelViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(Xnpc8 + -450, Ynpc8 + -1200, 0.0));
		ModelViewMatrix = glm::rotate(ModelViewMatrix, glm::radians(headingNpc8), glm::vec3(0.0, 0.0, 1.0));
		Npc8.Render(ModelViewMatrix, ProjectionMatrix);
		npc8Movement(Npc8);

		if (myPlayer.IsInCollision(Npc8.GetOBB()) && Npc8death == 0) {
			PlayerHp -= 1;

		}
		if (playerWeapon.IsInCollision(Npc8.GetOBB()) && Npc8death == 0) {
			Npc8death = 1;
			NpcsKilled += 1;
			Npc8.SetHeight(0.0f);
			Npc8.SetWidth(0.0f);
			Npc8.Init(green, "textures/easy1.png");
		}

		npcHitnpc8(Npc8, Npc1);
		npcHitnpc8(Npc8, Npc2);
		npcHitnpc8(Npc8, Npc3);
		npcHitnpc8(Npc8, Npc4);
		npcHitnpc8(Npc8, Npc5);
		npcHitnpc8(Npc8, Npc61);
		npcHitnpc8(Npc8, Npc62);
		npcHitnpc8(Npc8, Npc63);
		npcHitnpc8(Npc8, Npc7);
		npcHitnpc8(Npc8, Npc6);
		npcHitnpc8(Npc8, Npc9);

	}

	if (Npc7death == 1 && Npc8death == 1) {

		Xnpc9 += Vnpc9 * cos((90.0f + headingNpc9) * (PI / 180.0f));
		Ynpc9 += Vnpc9 * sin((90.0f + headingNpc9) * (PI / 180.0f));

		ModelViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(Xnpc9 + 750, Ynpc9 + -800, 0.0));
		ModelViewMatrix = glm::rotate(ModelViewMatrix, glm::radians(headingNpc9), glm::vec3(0.0, 0.0, 1.0));
		Npc9.Render(ModelViewMatrix, ProjectionMatrix);

		npc9Movement(Npc9);
		npcHitnpc9(Npc9, Npc1);
		npcHitnpc9(Npc9, Npc2);
		npcHitnpc9(Npc9, Npc3);
		npcHitnpc9(Npc9, Npc4);
		npcHitnpc9(Npc9, Npc5);
		npcHitnpc9(Npc9, Npc61);
		npcHitnpc9(Npc9, Npc62);
		npcHitnpc9(Npc9, Npc63);
		npcHitnpc9(Npc9, Npc7);
		npcHitnpc9(Npc9, Npc6);
		npcHitnpc9(Npc9, Npc8);

		if (myPlayer.IsInCollision(Npc9.GetOBB()) && Npc9death == 0) {
			PlayerHp -= 1;

		}
		if (playerWeapon.IsInCollision(Npc9.GetOBB()) && Npc9death == 0) {
			NpcHealth -= 1;

			if (NpcHealth == 0) {
				Npc9death = 1;
				NpcsKilled += 1;
				Npc9.SetHeight(0.0f);
				Npc9.SetWidth(0.0f);
				Npc9.Init(green, "textures/easy1.png");
			}
		}

	}	
	
	//spawns boss when 12 npcs are killed
	if (NpcsKilled >= 12 || Npc9death == 1) {

		//renderings in boss
		Xnpc10 += Vnpc10 * cos((90.0f + headingNpc10) * (PI / 180.0f));
		Ynpc10 += Vnpc10 * sin((90.0f + headingNpc10) * (PI / 180.0f));
		ModelViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(Xnpc10 + -200, Ynpc10 + -1300, 0.0));
		ModelViewMatrix = glm::rotate(ModelViewMatrix, glm::radians(headingNpc10), glm::vec3(0.0, 0.0, 1.0));
		Npc10.Render(ModelViewMatrix, ProjectionMatrix);
		npc10Movement(Npc10);

		//render new item for player
		ModelViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(386, 1423, 1.0));
		playerWeapon2pickup.Render(ModelViewMatrix, ProjectionMatrix);

		//adds text message to screen
		ProjectionMatrix = glm::ortho(-350.0 + myPlayer.GetXPos(), 350.0 + myPlayer.GetXPos(), -350.0 + myPlayer.GetYPos(), 350.0 + myPlayer.GetYPos());
		print(ProjectionMatrix, fontBossfight, myPlayer.GetXPos() + -350.0, myPlayer.GetYPos() + 300, " B.Cepica has infected the lungs! \nGrab the Tigercycline from the port at top of the lung");

		//when player collide with playerpickup item that will hide the item from player and set pickup to 1;
		if (myPlayer.IsInCollision(playerWeapon2pickup.GetOBB()) && pickup == 0)
		{
			pickup = 1;
			playerWeapon2pickup.SetHeight(0.0f);
			playerWeapon2pickup.SetWidth(0.0f);
			playerWeapon2pickup.Init(green, "textures/easy1.png");
			fontBossfight.init("arialbd.TTF", 0.0);
		}

		//when pick is 1 this will render in a new weapon for the player and add hp to player.
		if (pickup == 1) {
			
			ModelViewMatrix = glm::translate(ViewMatrix, glm::vec3(myPlayer.GetXPos(), myPlayer.GetYPos(), 0.0));
			ModelViewMatrix = glm::rotate(ModelViewMatrix, AngleWeapon2, glm::vec3(0.0, 0.0, 1.0));
			ModelViewMatrix = glm::translate(ModelViewMatrix, glm::vec3(200, 50.0, -1.0));
			ModelViewMatrix = glm::rotate(ModelViewMatrix, AngleWeapon2, glm::vec3(0.0, 0.0, -5.0));
			playerWeapon2.Render(ModelViewMatrix, ProjectionMatrix);
		}

		//player will lose hp when collide with boss
		if (myPlayer.IsInCollision(Npc10.GetOBB()) && NpcBossDeath == 0) {
			PlayerHp -= 1;

		}

		//boss will lose 1 hp when player weapon collides with boss sprite
		if (playerWeapon.IsInCollision(Npc10.GetOBB()) && NpcBossDeath == 0) {
			NpcBossHp -= 1;
			
			//when boss hp is zero that will remove the boss for the map inturn ending the game as well
			if (NpcBossHp == 0) {
				NpcBossDeath = 1;
				NpcsKilled += 1;
				Npc10.SetHeight(0.0f);
				Npc10.SetWidth(0.0f);
				Npc10.Init(green, "textures/easy1.png");
			}
		}
		//when collide the boss will lose 2hp 
		if (playerWeapon2.IsInCollision(Npc10.GetOBB()) && NpcBossDeath == 0) {
			NpcBossHp -= 3;
			//when boss hp is zero that will remove the boss for the map inturn ending the game as well
			if (NpcBossHp == 0) {
				NpcBossDeath = 1;
				NpcsKilled += 1;
				Npc10.SetHeight(0.0f);
				Npc10.SetWidth(0.0f);
				Npc10.Init(green, "textures/easy1.png");
			}
		}

	}


	// player & weapon
   //------------------------------------
	ModelViewMatrix = glm::translate(ViewMatrix, glm::vec3(myPlayer.GetXPos(), myPlayer.GetYPos(), 0.0));
	ProjectionMatrix = glm::ortho(-350.0 + myPlayer.GetXPos(), 350.0 + myPlayer.GetXPos(), -350.0 + myPlayer.GetYPos(), 350.0 + myPlayer.GetYPos());
	myPlayer.Render(ModelViewMatrix, ProjectionMatrix);

	
	ModelViewMatrix = glm::rotate(ModelViewMatrix, AngleWeapon, glm::vec3(0.0, 0.0, 1.0));
	ModelViewMatrix = glm::translate(ModelViewMatrix, glm::vec3(150, 25.0, 1.0));
	ModelViewMatrix = glm::rotate(ModelViewMatrix, AngleWeapon, glm::vec3(0.0, 0.0, 5.0));
	playerWeapon.Render(ModelViewMatrix, ProjectionMatrix);

	//sets a heading for Npcs to go to.
	NpcHeading();

	glDisable(GL_BLEND);

	//--angles
	//changes the the angle in which the weapon sprite rotates at.
	AngleWeapon += 0.009f;
	if (AngleWeapon >= 360)
		AngleWeapon = 0;

	AngleWeapon2 -= 0.01f;
	if (AngleWeapon >= 360)
		AngleWeapon = 0;

	///this setup the angle rotate and the speed of it 
	Angle += 0.01f;
	if (Angle >= 360)
		Angle = 0;

	//---text---
	//Text for info on contorls hp and kills, stays with the player postion as it moves round the map
	print(ProjectionMatrix, fontControls, myPlayer.GetXPos()-290, myPlayer.GetYPos() -320, "w: up a: left  s: down d: right \n rightmousebutton: run leftmousebutton: use weapon ");
	print(ProjectionMatrix, fontNpcDes, myPlayer.GetXPos() + 200, myPlayer.GetYPos() + 320, "Bugs killed: %i", NpcsKilled);
	print(ProjectionMatrix, fontNpcDes, myPlayer.GetXPos() + 200, myPlayer.GetYPos() + 280, "Hp: %i", PlayerHp); 

	//glutPostRedisplay();
	glutSwapBuffers();

	//this was to see and test the x and y pos of the player, it also helped with setup up where other objects would render.
    //printf("X : %f \n", myPlayer.GetXPos());
	//printf("Y : %f \n", myPlayer.GetYPos());
	
}

//start screen
void StartScreen(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//welcome screen with contorls for game, a start button or press a button to start, exit button 

	glEnable(GL_BLEND);

	ProjectionMatrix = glm::ortho(-300.0, 300.0, -300.0, 300.0);
	print(ProjectionMatrix, fontStartScreen, -85.0, 180.0, "Cystic fibrosis\n  Lung Game");
	print(ProjectionMatrix, fontStartScreen2, -240, 50, "        You play as a rogue bug been recruited by the Ivs.Inc\nyour misson is to use antibiotics called Tazocin to destroy the bugs\n             and save the lungs from being destroyed.");

	print(ProjectionMatrix, fontStartScreen2, -85,-20, "Press x to Start Game");

	ModelViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(-150,-200 , 0.0));
	MovementControl.Render(ModelViewMatrix, ProjectionMatrix);

	ModelViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(150, -180.0, 0.0));
	MouseControl.Render(ModelViewMatrix, ProjectionMatrix);

	ModelViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(-200, 180, 0.0));
	myPlayer.Render(ModelViewMatrix, ProjectionMatrix);

	glDisable(GL_BLEND);

	glutSwapBuffers();

}
 
//end screen display all bugs killed
void EndScreen(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);
	ProjectionMatrix = glm::ortho(-300.0, 300.0, -300.0, 300.0);
	print(ProjectionMatrix, fontEndScreen, -80.0, 180.0, "Well done.");
	print(ProjectionMatrix, fontEndScreen, -220, 100.0, "you saved the lungs from B.Cepica");
	print(ProjectionMatrix, fontEndScreen, -150.0,0.0, "Thank you for playing");
	

	if (Restart == true) {
		init();
		PlayerHp = 200;
	}

	glDisable(GL_BLEND);

	glutSwapBuffers();
}

//game over screen called if player  hp is zero
void GameOverScreen(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);

	ProjectionMatrix = glm::ortho(-300.0, 300.0, -300.0, 300.0);
	print(ProjectionMatrix, fontGameOverScreen, -100, 180.0, "Game Over");
	print(ProjectionMatrix, fontGameOverScreen, -200, 100.0, "the infection was too \n           strong.");
	
	glDisable(GL_BLEND);

	glutSwapBuffers();

}

//calls endscreen when if statment is ture
void endgame() {

	if (NpcBossDeath == 1) {
		glutDisplayFunc(EndScreen);
	}
}

//ends game when player is zero
void gameover() {
	if (PlayerHp <= 0)
	{
		
		glutDisplayFunc(GameOverScreen);
	}
}

//setup the start
void init()
{
	FreeImage_Initialise();

	Npc1.SetNpcHp(1);

	glClearColor(0.3,0.0,0.0,0.0);	//sets the clear colour to black

	//this is the background Texture
	MybackGround.SetWidth(2480.0);
	MybackGround.SetHeight(3508.0);
	MybackGround.Init(rgb, "textures/map.png");
	
	//player texture
	myPlayer.SetWidth(100.0f *(339 / 258.0));
	myPlayer.SetHeight(100.0f);
	myPlayer.Init(green, "textures/Player.png");

	playerWeapon.SetWidth(50);
	playerWeapon.SetHeight(50);
	playerWeapon.Init(green, "textures/ivs.png");

	playerWeapon2.SetWidth(50);
	playerWeapon2.SetHeight(50);
	playerWeapon2.Init(green, "textures/ivs2.png");

	playerWeapon2pickup.SetWidth(100);
	playerWeapon2pickup.SetHeight(100);
	playerWeapon2pickup.Init(green, "textures/ivs.png");

	//None playerable characters
	Npc1.SetWidth(164);
	Npc1.SetHeight(164);
	Npc1.Init(green,"textures/easy1.png");


	Npc2.SetWidth(174);
	Npc2.SetHeight(178);
	Npc2.Init(green, "textures/easy2.png");
	
	Npc3.SetWidth(100.0f *(312.0/258.0));
	Npc3.SetHeight(100.0f);
	Npc3.Init(green, "textures/normal1.png");
	

	//CHANGE TO DIFFERENT TEXTURE LOOK AT PHOTOSHOP FILES 
	Npc4.SetWidth(100.0f * (312.0 / 258.0));
	Npc4.SetHeight(100.0f);
	Npc4.Init(green, "textures/normal1.png");

	Npc5.SetWidth(263);
	Npc5.SetHeight(226);
	Npc5.Init(rgb, "textures/hard1.png");

	Npc6.SetWidth(78);
	Npc6.SetHeight(62);
	Npc6.Init(rgb, "textures/Small.png");

	Npc61.SetWidth(78);
	Npc61.SetHeight(62);
	Npc61.Init(rgb, "textures/Small.png");

	Npc62.SetWidth(78);
	Npc62.SetHeight(62);
	Npc62.Init(rgb, "textures/Small.png");

	Npc63.SetWidth(78);
	Npc63.SetHeight(62);
	Npc63.Init(rgb, "textures/Small.png");

	//Change these the shape makes the suck 
	Npc7.SetWidth(342 / 2);
	Npc7.SetHeight(331 / 2);
	Npc7.Init(rgb, "textures/yellow.png");
	Npc7.SetXpos(rand() / XLimt *2);
	Npc7.SetYpos(rand() / YLimt *2);

	Npc8.SetWidth(342/2);
	Npc8.SetHeight(331/2);
	Npc8.Init(rgb, "textures/yellow.png");

	Npc9.SetWidth(297);
	Npc9.SetHeight(237);
	Npc9.Init(rgb, "textures/darkgreen.png");

	Npc10.SetWidth(226);
	Npc10.SetHeight(200);
	Npc10.Init(rgb, "textures/b-cepacia.png");

	//all these walls texures are hidden in the game to stop players and npcs from going out of bounds of the map.

	LeftWall.SetWidth(50);
	LeftWall.SetHeight(800.0);
	LeftWall.Init(red, "textures/objectWall.png");

	WallLeft2.SetWidth(50);
	WallLeft2.SetHeight(300);
	WallLeft2.Init(red, "textures/objectWall.png");

	MiddleLeftWall.SetWidth(50);
	MiddleLeftWall.SetHeight(800);
	MiddleLeftWall.Init(red, "textures/objectWall.png");

	RightWall.SetWidth(50);
	RightWall.SetHeight(1300.0);
	RightWall.Init(red, "textures/objectWall.png");

	TopWall.SetWidth(1000.0);
	TopWall.SetHeight(50);
	TopWall.Init(red, "textures/objectWall.png");

	TopRightCorner.SetWidth(50);
	TopRightCorner.SetHeight(620);
	TopRightCorner.Init(red, "textures/objectWall.png");

	TopLeftWall.SetWidth(50);
	TopLeftWall.SetHeight(1000);
	TopLeftWall.Init(red,"textures/objectWall.png");

	TopLeftWall2.SetWidth(50);
	TopLeftWall2.SetHeight(200);
	TopLeftWall2.Init(red,"textures/objectWall.png");

	TopLeftWall3.SetWidth(50);
	TopLeftWall3.SetHeight(320);
	TopLeftWall3.Init(red,"textures/objectWall.png");

	BottomWall.SetWidth(600.0);
	BottomWall.SetHeight(50);
	BottomWall.Init(red, "textures/objectWall.png");

	BottomRightWall.SetWidth(50);
	BottomRightWall.SetHeight(1200);
	BottomRightWall.Init(red,"textures/objectWall.png");

	BottomLeftWall.SetWidth(110);
	BottomLeftWall.SetHeight(1000);
	BottomLeftWall.Init(red,"textures/objectWall.png");

	BottomRightWall2.SetWidth(50);
	BottomRightWall2.SetHeight(320);
	BottomRightWall2.Init(red,"textures/objectWall.png");

	BottomWall2.SetWidth(50);
	BottomWall2.SetHeight(800);
	BottomWall2.Init(red, "textures/objectWall.png");

	MovementControl.SetWidth(999/4);
	MovementControl.SetHeight(543/4);
	MovementControl.Init(rgb, "textures/Movement.png");

	MouseControl.SetWidth(879/4);
	MouseControl.SetHeight(890/4);
	MouseControl.Init(rgb, "textures/mouse.png");


	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	fontControls.init("arialbd.TTF", 16);
	fontNpcDes.init("arialbd.TTF", 16);
	fontPlayerHP.init("arialbd.TTF", 16);
	fontStartScreen.init("arialbd.TTF", 20);
	fontStartScreen2.init("arialbd.TTF", 12);
	fontEndScreen.init("arialbd.TTF", 20);
	fontGameOverScreen.init("arialbd.TTF", 32);
	fontBossfight.init("arialbd.TTF", 16);

}	

void controls(unsigned char key, int x, int y) {

	switch (key) {
	case 'a':
		Left = true;
		break;
	case 'd':
		Right = true;
		break;
	case 'w':
		Up = true;
		break;
	case 's':
		Down = true;
		break;
	case 'x':
		Start = true;
		break;
	case 'm':
		BackMenu = true;
		break;
	case 'b':
		Restart = true;
		break;
	}
 }

void controlsup(unsigned char key, int x, int y) {
	
	switch (key) {
	case 'a':
		Left = false;
		break;
	case 'd':
		Right = false;
		break;
	case 'w':
		Up = false;
		break;
	case 's':
		Down = false;
		break;
	case 'x':
		Start = false;
		break;
	case 'm':
		BackMenu = false;
		break;
	case 'b':
		Restart = false;
		break;
	}
	}

void processKeys()
{

	if (Left)
	{
		myPlayer.IncPos(-1.5f, 0.0f);
	}		
	if (Right)
	{
		myPlayer.IncPos(1.5f, 0.0f);
	}	
	if (Up)
	{
		myPlayer.IncPos(0.0f, 1.5f);
	}
	if (Down)
	{
		myPlayer.IncPos(0.0f, -1.5f);
	}
	if (RightClick && Left)
	{
		myPlayer.IncPos(-5.0f, 0.0f);
	}
	if (RightClick && Right)
	{
		myPlayer.IncPos(5.0f, 0.0f);
	}
	if (RightClick && Up)
	{
		myPlayer.IncPos(0.0f, 5.0f);
	}
	if (RightClick && Down)
	{
		myPlayer.IncPos(0.0f, -5.0f);
	}
	if (LeftClick) {
		AngleWeapon += 0.1f;
		AngleWeapon2 -= 0.15f;
	}
	if (RightClick) {
		playerWeapon.IncPos(50.0f, 50.0f);
	}
	
	}


void menukeys() {

	if (BackMenu) {
		glutDisplayFunc(StartScreen);
	}
	if (Start) {

		glutDisplayFunc(display);
	}
}

//mouse controls
void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			LeftClick = true;
		}
		else
			LeftClick = false;
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
		{
			RightClick = true;
		}
		else
			RightClick = false;
		break;
	default:
		break;
	}
}

void idle()
{	
	glutPostRedisplay();
	gameover();
	endgame();
	processKeys();
	menukeys();
	
}

/**************** END OPENGL FUNCTIONS *************************/

// FREEGLUT WINDOW SET UP
int main(int argc, char **argv)
{
	Circle Fire;
	Fire.SetRadius(0.5f);

	//vector<fire> Fire;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Lung game");
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);

	//This initialises glew - it must be called after the window is created.
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		cout << " GLEW ERROR" << endl;
	}

	//Check the OpenGL version being used
	int OpenGLVersion[2];
	glGetIntegerv(GL_MAJOR_VERSION, &OpenGLVersion[0]);
	glGetIntegerv(GL_MINOR_VERSION, &OpenGLVersion[1]);
	cout << OpenGLVersion[0] << " " << OpenGLVersion[1] << endl;

	//initialise the objects for rendering
	init();

	//specify which function will be called to refresh the screen.
	// 
	// displays startscreen
	glutDisplayFunc(StartScreen);

	//uses W,A,S,D to move and x to start game. 
	glutKeyboardFunc(controls);
	glutKeyboardUpFunc(controlsup);

	glutIdleFunc(idle);
	
	//starts the main loop. Program loops and calls callback functions as appropriate.

	glutMainLoop();
	
	return 0;
}