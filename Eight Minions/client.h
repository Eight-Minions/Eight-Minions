#ifndef CLIENT_H
#define CLIENT_H

#include "resources.h"
#include "SDL_ttf.h"
#include "creep.h"
#include "tower.h"
#include "player.h"
#include "attackAnim.h"

#define CONNECTION_SUCCESSFUL 1
#define CONNECTION_FAILURE 0 //generic error
#define SERVER_NOT_FOUND -1

class client
{
private:
	ofstream dump;
	string server_addr;
	unsigned int port;
	IPaddress *ip;
	TCPsocket sd;
	SDLNet_SocketSet socketset;
	UDPsocket UDPsock;
	UDPpacket *UDPpack;

	//Surfaces - surfaces are basically loaded images that we can readily blit(display) to the screen
	SDL_Surface* screen;
	SDL_Surface* background;
	SDL_Surface* creepImages[NUM_CREEPS]; //holds sprite sheets for each creep
	SDL_Surface* attackImage;
	SDL_Surface* textTest;

	SDL_Event event;
	SDL_Rect *Buttons[NUM_BUTTONS];
	SDL_Rect *SpriteMaps[4][ANIM_NUM];

	cList<creep*> creeps;
	cList<tower*> towers;

	vector<attackAnim*> attacks;

	string updateQueue;

	player *self;

	//Fonts here.
	TTF_Font *font; //testing font

	//Colors
	SDL_Color Cblack;
	SDL_Color Cwhite;

public:
	client();
	int init();
	void loadFiles();
	void initButtons();
	void cleanup();
	void display();
	void displayCreeps();
	void displayTowers();
	void displayMisc();
	void displayUI();

	int run();
	int testrun();

	coord getClickCoord(int x, int y);

	void setServerAddress(string);
	void setPort(unsigned int);
	int connectToServer();
	int sendToServer(string);
	string recieveMessage();
	string recieveMessageUDP();
	int recieveMessageToQueue();
	int performUpdate(string upd);

	void savePlayerProfile();
	
	//this function will take any of the players individual stats, experience, purchased upgrades, and any other
	//relevant data, save it to a file, lock it with the players password, and encrypt it so they cant cheat and modify it.
};

#endif