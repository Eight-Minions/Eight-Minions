#include "game_host.h"

int game_host::init_net()
{
	if (SDLNet_Init() < 0)
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
		//maybe go through here and replace them with more easy to notice errors?
	}

	if (SDLNet_ResolveHost(&ip, NULL, this->port) < 0)
	{
		fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	if (!(sd = SDLNet_TCP_Open(&ip)))
	{
		fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	if (!(this->p1UDPsock = SDLNet_UDP_Open(this->port)))
	{
		cout << "UDP socket failed to open" << SDLNet_GetError() << "\n";
		exit(EXIT_FAILURE);
	}

	if (!(this->UDPpack1 = SDLNet_AllocPacket(512)))
	{
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	if (!(this->UDPpack2 = SDLNet_AllocPacket(512)))
	{
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	socketset = SDLNet_AllocSocketSet(4);

	cout << "Init completed\n";

	return 0; // temporary
}

int game_host::waitForClients()
{
	cout << "waiting for first player to connect...\n";
	while(!(player1sd = SDLNet_TCP_Accept(sd))) //wait for first connection, with 50ms delay to keep CPU down
		SDL_Delay(50);
	string ipMess = "";
	while(SDLNet_UDP_Recv(p1UDPsock, UDPpack1) == 0)
		SDL_Delay(5);
	SDLNet_UDP_Bind(p1UDPsock,10,&(UDPpack1->address));
	cout << this->recieveMessagep1() << "\n"; //client sends its IP

	SDLNet_TCP_AddSocket(socketset, player1sd); //could error check here
	this->player1ip = SDLNet_TCP_GetPeerAddress(player1sd);
	//UDPpack1->address.port = player1ip.port;
	//UDPpack1->address.host = player1ip.host;
	cout << "waiting for second player to connect...\n";
	while(!(player2sd = SDLNet_TCP_Accept(sd)))
		SDL_Delay(50);
	while(!SDLNet_UDP_Recv(p1UDPsock, UDPpack2))
		SDL_Delay(5);
	SDLNet_UDP_Bind(p1UDPsock,20,&(UDPpack2->address));
	//cout << this->recieveMessagep2() << "\n";
	SDLNet_TCP_AddSocket(socketset, player2sd); //could error check here as well
	player2ip = SDLNet_TCP_GetPeerAddress(player2sd);
	//UDPpack2->address.port = player2ip.port;
	//UDPpack2->address.host = player2ip.host;
	sendToClients("SIG:START");
	cout << "both clients connected, continuing...\n";
	return 1;
}

int game_host::waitForClient_test()
{
	cout << "waiting for first player to connect...\n";
	while(!(player1sd = SDLNet_TCP_Accept(sd))) //wait for first connection, with 50ms delay to keep CPU down
		SDL_Delay(50);

	string ipMess = "";
	while(SDLNet_UDP_Recv(p1UDPsock, UDPpack1) == 0)
		SDL_Delay(5);
	SDLNet_UDP_Bind(p1UDPsock,10,&(UDPpack1->address));

	cout << this->recieveMessagep1() << "\n"; //on successful connect, client sends a message

	SDLNet_TCP_AddSocket(socketset, player1sd); //could error check here
	this->player1ip = SDLNet_TCP_GetPeerAddress(player1sd);
	//SDLNet_ResolveHost(&(UDPpack1->address), cl.c_str(), port);
	//player2ip->host = SDLNet_TCP_GetPeerAddress(player1sd)->host;
	//player2ip->port = port;

	//UDPpack1->address = *player1ip;

	sendtoP1_test("SIG:START");
	cout << "client connected, continuing...\n";
	return 1;
}

void game_host::setPort(unsigned int setPort)
{
	//Last Changed: 3-5-12 @ 12:13
	//changelog:
	//made function set port
	//validated the input
	//added confirmation
	//todo:
	//
	if(setPort > 65535)
	{
		cout << "INVALID PORT!\n";
		system("pause");
		exit(1);
	}else
	{
		this->port = setPort;
		cout << "Port Set!\n";
	}
}

int game_host::sendToClients(string buff)
{
	if(!this->player1sd || !this->player2sd)
	{
		cout << "No Connection!\n";
		return -1;
	}
	else
	{
		if(SDLNet_TCP_Send(player1sd, (void *)buff.c_str(), 16 /* buff.length()+1*/) < buff.length() + 1)
		{
			cout << "Message to client 1 failed to send...\n";
			return -1;
		}
		if(SDLNet_TCP_Send(player2sd, (void *)buff.c_str(), 16 /*buff.length()+1*/) < buff.length() + 1)
		{
			cout << "Message to client 2 failed to send...\n";
			return -1;
		}
	}
	return 1;
}

int game_host::sendtoP1_test(string buff)
{
	if(SDLNet_TCP_Send(player1sd, (void *)buff.c_str(), 16 /* buff.length()+1*/) < buff.length() + 1)
	{
		cout << "Message to client 1 failed to send...\n";
		return -1;
	}
	return 1;
}

int game_host::sendToClientsUDP(string mess)
{
	char *temp = (char *)malloc(mess.length() + 1);
	strcpy(temp,mess.c_str());
	strcpy((char *)UDPpack1->data,(char *) temp);
	UDPpack1->len = mess.length() + 1;
	SDLNet_UDP_Send(p1UDPsock,10,UDPpack1); //<--should send to both clients
	cout << mess << "\n";
	/*
	strcpy((char *)UDPpack2->data, mess.c_str());
	UDPpack2->len = mess.length();
	SDLNet_UDP_Send(p1UDPsock,-1,UDPpack2);
	free(temp);*/
	return 0;
}

int game_host::sendtop1UDP(string mess)
{
	//char *temp = (char *)malloc(mess.length() + 1);
	//strcpy(temp,mess.c_str());
	//strcpy((char *)UDPpack1->data,(char *) temp);

	//<test code>
	strcpy((char*)UDPpack1->data, (char*)mess.c_str());
	//</test code>

	UDPpack1->len = mess.length() + 1;
	SDLNet_UDP_Send(p1UDPsock,10,UDPpack1);

	return 1;
}

string game_host::recieveMessagep1()
{
	char buff[512];
	while(!SDLNet_TCP_Recv(this->player1sd, buff, 512));
	//cout << buff << "\n";
	string ret = buff;
	return ret;
}

string game_host::recieveMessagep2()
{
	char buff[512];
	while(!SDLNet_TCP_Recv(this->player2sd, buff, 512));
	//cout << buff << "\n";
	string ret = buff;
	return ret;
}

void game_host::sendMessageToQueue(string mess)
{
	if(this->updateCollection.length() + mess.length() + 1 > MAX_MESSAGE_LENGTH || mess == "SEND")
	{
		cout << updateCollection << endl;
		if(updateCollection != "") //ensure a NULL message is not sent
			sendToClientsUDP(updateCollection);
		if(mess != "SEND")
			updateCollection = mess;
		else
			updateCollection = "";
	}
	else
	{
		if(updateCollection != "")
			updateCollection += "\n";
		updateCollection += mess;
	}
}