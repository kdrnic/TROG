#ifndef GAME_H
#define GAME_H

#include <map>
#include <queue>

#include "MapManager.h"
#include "EntitiesManager.h"
#include "InventoryManager.h"
#include "Factory.h"

class Player;

enum GameState
{
	GameStateEnteringMap,
	GameStateTransition,
	GameStatePlaying,
	GameStateSaving,
	GameStateInventory,
	GameStateDialog,
	GameStateDead,
	GameStateFinished,
	GameStateQuit
};

enum TransitionType
{
	TransitionNone,
	TransitionScrolling,
	TransitionFading
};

struct SAMPLE;
struct BITMAP;
struct DATAFILE;
struct FONT;

class GameManager
{
	public:
		GameState gameState;
		MapManager mapManager;
		EntitiesManager entitiesManager;
		InventoryManager inventoryManager;
		Factory<Item *> itemsFactory;
		Factory<Entity *> entitiesFactory;
		Player *player;
		int frame;
		int file;
		bool tampered;
		bool shallPause;
		bool zoomMode;

		void *GetData(const char *name);
		bool HasData(const char *name);
		DATAFILE *GetDataRaw(const char *name);

		void Init();
		void Start(int f);
		void Load();
		void Save();
		void SaveStatus();
		
		void SetMusic(std::string m);
		
		void SetFadingTransition();
		void SetScrollingTransition(int direction, int speed = 10);
		void PushDialogLine(std::string s);
		void SetQuestState(std::string s, std::string v);
		std::string GetQuestState(std::string s);
	private:
		DATAFILE *data;

		BITMAP *doubleBuffer;
		BITMAP *playArea;
		BITMAP *zoomBuffer;
		BITMAP *hud;
		BITMAP *transitionBitmap;
		FONT *dialogFont;
		BITMAP *dialogBox;
		BITMAP *facePicture;
		BITMAP *heartSprite;
		BITMAP *continueBg;
		SAMPLE *blip;
		
		std::string currentMusic;

		Item *selectedItem;
		TransitionType transition, currentTransition;
		int transitionDirection, transitionSpeed, transitionFrame;
		int transitionFadingSpeed;
		std::queue<std::string> dialogLines;
		std::string currentDialogLines[2];
		int currentDialogLine, dialogProgress, dialogCounter, dialogInverseSpeed;
		float pauseFading, pauseFadingSpeed;
		bool continuePlaying;

		std::map<std::string, std::string> questStates;

		void RegisterEntities();
		void RegisterItems();

		void Update();
		void Draw();
		void DoFrame();
		void Play();
		
		float preTransPlayerX, preTransPlayerY;
		void GetZoomPos(int &zx, int &zy);
};

extern GameManager game;

#endif
