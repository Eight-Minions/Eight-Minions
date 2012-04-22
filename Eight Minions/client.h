#ifndef CLIENT_H
#define CLIENT_H

#include "resources.h"
#include "SDL_ttf.h"
#include "creep.h"
#include "tower.h"
#include "obstacle.h"
#include "mine.h"
#include "player.h"
#include "attackAnim.h"
#include "button.h"

#define CONNECTION_SUCCESSFUL 1
#define CONNECTION_FAILURE 0 //generic error
#define SERVER_NOT_FOUND -1

//Mouse click mode definitions
#define DEFAULT_MODE 0
#define PLACE_FOUNDATION_MODE 1
#define PLACE_MINE_MODE 2
#define SELECT_TOWER_MODE 3

class client
{
private:
	string server_addr;
	unsigned int port;
	IPaddress *ip;
	TCPsocket sd;
	SDLNet_SocketSet socketset;
	UDPsocket UDPsock;
	UDPpacket *UDPpack;

	int mouseClickMode;
	int menuMode;
	coord curSelectedTower;
	structure *curSelectedTowerPtr;
	int curTowerId;

	int baseLevel;

	//Surfaces - surfaces are basically loaded images that we can readily blit(display) to the screen
	SDL_Surface* screen;
	SDL_Surface* background;
	SDL_Surface* creepImages[2][NUM_CREEPS]; //holds sprite sheets for each creep
	SDL_Surface* towerImages[2][NUM_TOWERS];
	SDL_Surface* attackImage;
	SDL_Surface* text[TEXT_NUM];
	FadeMessage *pMess;
	

	SDL_Event event;
	SDL_Rect *SpriteMaps[4][ANIM_NUM];
	SDL_Rect *textRects[TEXT_NUM];

	Button *buttons[NUM_BUTTONS];

	cList<creep*> creeps;
	cList<structure*> towers;


	vector<attackAnim*> attacks;

	string updateQueue;

	int run_game;

	player *self;

	//Fonts here.
	TTF_Font *font; //testing font
	TTF_Font *font10;

	//Colors
	SDL_Color Cblack;
	SDL_Color Cwhite;
	SDL_Color Cblue;

public:
	client();
	int init();
	void handleInput();
	void loadFiles();
	void initButtons();
	void initText();
	void cleanup();
	void display();
	void displayCreeps();
	void displayTowers();
	void displayMisc();
	void displayUI();

	int run();
	int testrun();

	coord getClickCoord(int x, int y);

	bool boardWasClicked(int x, int y);

	bool removeTowerSend(int x, int y);
	bool removeTowerRecieve(int towerID);
	bool upgradeTowerSend(int x, int y);
	bool upgradeTowerRecieve(int towerID);
	bool changeTowerTypeSend(int Tid, int newType);
	bool changeTowerRecieve(int towerID, int newType);
	bool toggleTowerSend(int Tid);
	bool toggleTowerRecieve(int towerID, int newState);
	bool upgradeBaseSend();
	bool upgradeBaseRecieve();
	bool addTypeToBaseSend(int newType);
	bool addTypeToBaseRecieve(int newType);
	bool changeSpawnerTypeSend(int x, int y, int newType);
	bool changeSpawnerTypeRecieve(int towerID, int newType);
	int gameOverRecieve(int winner);

	void setServerAddress(string);
	void setPort(unsigned int);
	int connectToServer();
	int sendToServer(string);
	string recieveMessage();
	string recieveMessageUDP();
	int recieveMessageToQueue();
	int performUpdate(string upd);
	int sendToServerUDP(string mess);

	void savePlayerProfile();
	bool towerExistsAt( coord curSelectedTower );

	//this function will take any of the players individual stats, experience, purchased upgrades, and any other
	//relevant data, save it to a file, lock it with the players password, and encrypt it so they cant cheat and modify it.
};

#endif