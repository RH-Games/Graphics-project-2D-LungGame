#pragma once
//var.h has all the variables

float Angle = 0.0f;
float AngleWeapon = 0.0f;
float AngleWeapon2 = 0.0f;
float xmoveNpc = 0;
float pickup = 0;

float x = 200.0;
float y = 150.0;
float AngleWall = 0.0;
float value = 0.0f;

//for all npc speed for x and y is 0.2;
float NpcXSpeed = 0.2f;
float NpcYSpeed = 0.2f;

//sets floats for each npc for the v x y and heading, 
//setting them for each because having one will change for all npcs

float headingNpc1 = 0;
float Vnpc = 2.0f;
float Xnpc = 0;
float Ynpc = 0;

float headingNpc2 = 0;
float Vnpc2 = -2.0f;
float Xnpc2 = 0;
float Ynpc2 = 0;

float headingNpc3 = 0;
float Vnpc3 = 2.0f;
float Xnpc3 = 0;
float Ynpc3 = 0;

float headingNpc4 = 0;
float Vnpc4 = 2.0f;
float Xnpc4 = 0;
float Ynpc4 = 0;

float headingNpc5 = 0;
float Vnpc5 = 1.5f;
float Xnpc5 = 0;
float Ynpc5 = 0;

float headingNpc6 = 0;
float Vnpc6 = -2.5f;
float Xnpc6 = 1;
float Ynpc6 = 1;

float headingNpc61 = 0;
float Vnpc61 = 2.5f;
float Xnpc61 = -1;
float Ynpc61 = -1;

float headingNpc62 = 0;
float Vnpc62 = 2.5f;
float Xnpc62 = 0;
float Ynpc62 = 0;

float headingNpc63 = 0;
float Vnpc63 = 2.5f;
float Xnpc63 = 0;
float Ynpc63 = 0;

float headingNpc7 = 0;
float Vnpc7 = 5.0f;
float Xnpc7 = 0;
float Ynpc7 = 0;

float headingNpc8 = 0;
float Vnpc8 = 2.0f;
float Xnpc8 = 0;
float Ynpc8 = 0;

float headingNpc9 = 0;
float Vnpc9 = 2.0f;
float Xnpc9 = 0;
float Ynpc9 = 0;

float headingNpc10 = 0;
float Vnpc10 = 10.0f;
float Xnpc10 = 0;
float Ynpc10 = 0;

//int
int screenWidth = 1920, screenHeight = 1080;
int mouse_y = 0, mouse_x = 0;
int PlayerHp = 200;

int NpcHealth = 50;
int NpcBossHp = 80;

//Npcdeath is set to zero when it goes to 1 if statments can't be used
int Npc1death = 0, Npc2death = 0, Npc3death = 0,
Npc4death = 0, Npc5death = 0, Npc6death = 0,
Npc61death = 0, Npc62death = 0, Npc63death = 0,
Npc7death = 0, Npc8death = 0, Npc9death = 0, NpcBossDeath =0;
int NpcsKilled = 0;

//booleans to handle when the arrow keys are pressed or released
bool Left = false;
bool Right = false;
bool Up = false;
bool Down = false;
bool Fire = false;
bool info = false;
bool Start = false;
bool LeftClick = false;
bool RightClick = false;
bool Restart = false;
bool BackMenu = false;

//limts a spawn range for some npcs
float XLimt = 1000;
float YLimt = 1200;

//floats of colours
				//R G B
float rgb[3] = { 1,1,1 };
float green[3] = { 0,1,0 };
float red[3] = { 1,0,0 };
float blue[3] = { 0,0,1 };

//Sprite ojects to be rendered
//background 
Sprite MybackGround;
//player objects

Sprite myPlayer;
Sprite playerWeapon;
Sprite playerWeapon2;
Sprite playerWeapon2pickup;

//homescreen  objects
Sprite MovementControl;
Sprite MouseControl;
Sprite lungs;

//NPC Sprite 
Sprite Npc1, Npc2, Npc3, Npc4, Npc5, Npc6, Npc61, Npc62, Npc63, Npc64, Npc7, Npc8, Npc9, Npc10, Npc11;

//Font
freetype::Font fontControls;
freetype::Font fontNpcDes;
freetype::Font fontPlayerHP;
freetype::Font fontStartScreen;
freetype::Font fontStartScreen2;
freetype::Font fontEndScreen;
freetype::Font fontGameOverScreen;
freetype::Font fontBossfight;

/// GameWalls
Sprite LeftWall;
Sprite RightWall;
Sprite BottomWall;
Sprite TopWall;
Sprite TopRightCorner;
Sprite TopLeftWall;
Sprite BottomRightWall;
Sprite BottomLeftWall;
Sprite MiddleLeftWall;
Sprite TopLeftWall2;
Sprite TopLeftWall3;
Sprite BottomRightWall2;
Sprite WallLeft2;
Sprite BottomWall2;