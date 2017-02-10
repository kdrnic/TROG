#include "Game.h"

#include "BarbedWire.h"
#include "Zombie.h"
#include "Bat.h"
#include "Skeleton.h"
#include "Rock.h"
#include "Sign.h"
#include "Door.h"
#include "NPC.h"
#include "Portal.h"
#include "Vampire.h"
#include "Trap.h"
#include "Plague.h"
#include "Slime.h"
#include "Archer.h"
#include "Werewolf.h"
#include "Painting.h"
#include "Saver.h"
#include "VillageWall.h"
#include "Stairs.h"
#include "KnifeSkeleton.h"
#include "Button.h"
#include "Statue.h"

#include "AK47.h"
#include "AKMagazine.h"
#include "BombItem.h"
#include "Sword.h"

#include "Keys.h"
#include "Utils.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <cctype>

GameManager game;

volatile bool tick;
volatile int fpsFrame;
volatile int fps;

void Ticker()
{
	tick = true;
}
END_OF_FUNCTION(Ticker)

void SaveFrame()
{
	fps = game.frame - fpsFrame;
	fpsFrame = game.frame;
}

void *GameManager::GetData(const char *name)
{
	DATAFILE *obj = find_datafile_object(data, name);
	if(obj == 0)
	{
		std::cerr << "WARNING: Datafile object not found: " << name << "\n";
		return 0;
	}
	return (void *) obj->dat;
}

void GameManager::Init()
{
	data = load_datafile("game.dat");

	RegisterEntities();
	RegisterItems();

	mapManager.LoadTileSet("tiles/tileset.tls");
	mapManager.LoadAllMaps("maps/map");

	doubleBuffer = create_bitmap(640, 480);
	transitionBitmap = create_bitmap(630, 420);
	playArea = create_bitmap(630, 420);

	hud = (BITMAP *) GetData("gui_hud"); // load_bitmap("hud.bmp", 0);
	inventoryManager.inventoryBackground = (BITMAP *) GetData("gui_inventory"); // load_bitmap("inventory.bmp", 0);
	inventoryManager.itemSelection = (BITMAP *) GetData("gui_itemSelection"); // load_bitmap("itemSelection.bmp", 0);

	selectedItem = 0;
	transition = TransitionNone;
	currentDialogLines[0] = "";
	currentDialogLines[1] = "";
	currentDialogLine = 0;
	dialogProgress = 0;
	dialogCounter = 0;
	dialogInverseSpeed = 5;

	dialogBox = (BITMAP *) GetData("gui_dialogBox"); // load_bitmap("dialogBox.bmp", 0);
	dialogFont = (FONT *) GetData("gui_font"); // load_bitmap_font("font.bmp", 0, 0);
	facePicture = (BITMAP *) GetData("gui_face"); // load_bitmap("face.bmp", 0);

	fpsFrame = 0;
	transitionFadingSpeed = 8;
	pauseFadingSpeed = 0.75;

	heartSprite = (BITMAP *) GetData("gui_heart"); // load_bitmap("heart.bmp", 0);
	continueBg = (BITMAP *) GetData("gui_continue"); // load_bitmap("continue.bmp", 0);
	
	blip = (SAMPLE *) GetData("snd_blip");
}

void GameManager::Start(int f)
{
	file = f;
	continuePlaying = true;
	while(continuePlaying)
	{
		player = new Player;
		entitiesManager.Add(player);
		gameState = GameStateEnteringMap;
		frame = 0;
		Load();
		Play();
	}
}

void GameManager::Load()
{
	std::string files[4] = {"saves/game1.sav", "saves/game2.sav", "saves/game3.sav", "saves/game4.sav"};
	std::string fileName;
	if(file < 0) fileName = "saves/newgame.sav";
	else fileName = files[file];
	std::fstream gameStream(fileName.c_str(), std::fstream::in);
	std::stringstream hashStream;

	std::string _line;

	getline(gameStream, _line);
	mapManager.SetMap(_line);
	hashStream << _line.c_str() << '\n';

	getline(gameStream, _line);
	player->x = std::atoi(_line.c_str());
	hashStream << _line.c_str() << '\n';

	getline(gameStream, _line);
	player->y = std::atoi(_line.c_str());
	hashStream << _line.c_str() << '\n';

	getline(gameStream, _line);
	player->gold = std::atoi(_line.c_str());
	hashStream << _line.c_str() << '\n';

	getline(gameStream, _line);
	player->health = player->maxHealth = std::atoi(_line.c_str());
	hashStream << _line.c_str() << '\n';

	getline(gameStream, _line);
	std::vector<std::string> items = StringToStrings(_line);
	hashStream << _line.c_str() << '\n';
	
	for(int i = 0; i < items.size(); i++)
	{
		Item *newItem = itemsFactory.Create(items[i].substr(0, items[i].find(":")));
		newItem->SetAmount(std::atoi(items[i].substr(items[i].find(":") + 1).c_str()));
		inventoryManager.Add(newItem);
	}

	getline(gameStream, _line);
	if(_line != "none") player->equippedItems[0] = inventoryManager.Find(_line);
	hashStream << _line.c_str() << '\n';

	getline(gameStream, _line);
	if(_line != "none") player->equippedItems[1] = inventoryManager.Find(_line);
	hashStream << _line.c_str() << '\n';

	getline(gameStream, _line);
	std::vector<std::string> questStateStrings = StringToStrings(_line);
	hashStream << _line.c_str() << '\n';
	
	for(int i = 0; i < questStateStrings.size(); i++)
	{
		questStates[questStateStrings[i].substr(0, questStateStrings[i].find(":"))] = questStateStrings[i].substr(questStateStrings[i].find(":") + 1).c_str();
	}
	
	std::string temp(hashStream.str());
	const char *toHash = temp.c_str();
	Int64Tuple hash = {0, 0};
	CustomHash((std::uint8_t *) toHash, strlen(toHash), &hash);
	std::stringstream hexStream;
	hexStream << std::hex << hash.a << '\n' << hash.b;
	std::string strA, strB;
	getline(hexStream, strA);
	getline(hexStream, strB);
	
	if(file >= 0)
	{
		getline(gameStream, _line);
		if(gameStream.eof())
		{
			std::cerr << "WARNING: save file missing validation\n";
		}
		if(_line != strA)
		{
			std::cerr << "WARNING: save file has been tampered\n";
			std::cerr << "hash.a\t\t\t: " << strA.c_str() << "\n";
			std::cerr << "read\t\t\t: " << _line.c_str() << "\n";
		}
		getline(gameStream, _line);
		if(_line != strB)
		{
			std::cerr << "WARNING: save file has been tampered\n";
			std::cerr << "hash.a\t\t\t: " << strB.c_str() << "\n";
			std::cerr << "read\t\t\t: " << _line.c_str() << "\n";
		}
	}
	
	gameStream.close();
}

void GameManager::Save()
{
	std::string files[4] = {"saves/game1.sav", "saves/game2.sav", "saves/game3.sav", "saves/game4.sav"};
	std::string imageFiles[4] = {"saves/game1.bmp", "saves/game2.bmp", "saves/game3.bmp", "saves/game4.bmp"};
	std::string fileName;
	if(file < 0) return;
	fileName = files[file];

	BITMAP *temp = create_bitmap(160, 120);
	SmoothScale(playArea, temp);
	save_bitmap(imageFiles[file].c_str(), temp, 0);
	destroy_bitmap(temp);

	std::fstream gameStream(fileName.c_str(), std::fstream::out | std::fstream::trunc);
	std::stringstream hashStream;

	gameStream << mapManager.currentMapName.c_str() << '\n';
	hashStream << mapManager.currentMapName.c_str() << '\n';
	gameStream << player->x << '\n';
	hashStream << player->x << '\n';
	gameStream << player->y << '\n';
	hashStream << player->y << '\n';
	gameStream << player->gold << '\n';
	hashStream << player->gold << '\n';
	gameStream << player->maxHealth << '\n';
	hashStream << player->maxHealth << '\n';
	gameStream << inventoryManager.ToString() << '\n';
	hashStream << inventoryManager.ToString() << '\n';
	if(player->equippedItems[0] != 0)
	{
		gameStream << player->equippedItems[0]->name << '\n';
		hashStream << player->equippedItems[0]->name << '\n';
	}
	else
	{
		gameStream << "none" << '\n';
		hashStream << "none" << '\n';
	}
	if(player->equippedItems[1] != 0)
	{
		gameStream << player->equippedItems[1]->name << '\n';
		hashStream << player->equippedItems[1]->name << '\n';
	}
	else
	{
		gameStream << "none" << '\n';
		hashStream << "none" << '\n';
	}
	bool b = false;
	for(std::map<std::string, std::string>::iterator i = questStates.begin(); i != questStates.end(); i++)
	{
		if(b)
		{
			gameStream << ' ';
			hashStream << ' ';
		}
		gameStream << i->first << ':' << i->second;
		hashStream << i->first << ':' << i->second;
		b = true;
	}
	gameStream << '\n';
	hashStream << '\n';
	
	std::string temp(hashStream.str());
	const char *toHash = temp.c_str();
	Int64Tuple hash = {0, 0};
	CustomHash((std::uint8_t *) toHash, strlen(toHash), &hash);
	gameStream << std::hex << hash.a << '\n' << hash.b;
	
	gameStream.close();
}

void GameManager::SaveStatus()
{
	std::string files[4] = {"saves/game1.sav", "saves/game2.sav", "saves/game3.sav", "saves/game4.sav"};
	std::string fileName;
	if(file < 0) return;
	fileName = files[file];

	std::fstream loadStream(fileName.c_str(), std::fstream::in);
	std::string lines[5];
	for(int i = 0; i < 5; i++) getline(loadStream, lines[i]);
	loadStream.close();

	std::fstream saveStream(fileName.c_str(), std::fstream::out | std::fstream::trunc);
	std::stringstream hashStream;
	
	for(int i = 0; i < 5; i++)
	{
		saveStream << lines[i] << '\n';
		hashStream << lines[i] << '\n';
	}
	saveStream << inventoryManager.ToString() << '\n';
	hashStream << inventoryManager.ToString() << '\n';
	if(player->equippedItems[0] != 0)
	{
		saveStream << player->equippedItems[0]->name << '\n';
		hashStream << player->equippedItems[0]->name << '\n';
	}
	else
	{
		saveStream << "none" << '\n';
		hashStream << "none" << '\n';
	}
	if(player->equippedItems[1] != 0)
	{
		saveStream << player->equippedItems[1]->name << '\n';
		hashStream << player->equippedItems[1]->name << '\n';
	}
	else
	{
		saveStream << "none" << '\n';
		hashStream << "none" << '\n';
	}
	bool b = false;
	for(std::map<std::string, std::string>::iterator i = questStates.begin(); i != questStates.end(); i++)
	{
		if(b)
		{
			saveStream << ' ';
			hashStream << ' ';
		}
		saveStream << i->first << ':' << i->second;
		hashStream << i->first << ':' << i->second;
		b = true;
	}
	saveStream << '\n';
	hashStream << '\n';
	
	std::string temp(hashStream.str());
	const char *toHash = temp.c_str();
	Int64Tuple hash = {0, 0};
	CustomHash((std::uint8_t *) toHash, strlen(toHash), &hash);
	saveStream << std::hex << hash.a << '\n' << hash.b;
	
	saveStream.close();
}

void GameManager::SetFadingTransition()
{
	transition = TransitionFading;
}

void GameManager::SetScrollingTransition(int direction, int speed)
{
	transitionDirection = direction;
	transitionSpeed = speed;
	transition = TransitionScrolling;
}

void GameManager::PushDialogLine(std::string s)
{
	dialogLines.push(s);
}

void GameManager::RegisterEntities()
{
	#define REGISTER_ENTITY(e) entitiesFactory.Register<e>(#e);
	REGISTER_ENTITY(BarbedWire)
	REGISTER_ENTITY(Zombie)
	REGISTER_ENTITY(Rock)
	REGISTER_ENTITY(Sign)
	REGISTER_ENTITY(Door)
	REGISTER_ENTITY(Bat)
	REGISTER_ENTITY(Skeleton)
	REGISTER_ENTITY(NPC)
	REGISTER_ENTITY(Portal)
	REGISTER_ENTITY(Vampire)
	REGISTER_ENTITY(Trap)
	REGISTER_ENTITY(Plague)
	REGISTER_ENTITY(Slime)
	REGISTER_ENTITY(Archer)
	REGISTER_ENTITY(Werewolf)
	REGISTER_ENTITY(Painting)
	REGISTER_ENTITY(Saver)
	REGISTER_ENTITY(VillageWall)
	REGISTER_ENTITY(Stairs)
	REGISTER_ENTITY(KnifeSkeleton)
	REGISTER_ENTITY(Button)
	REGISTER_ENTITY(Statue)
	#undef REGISTER_ENTITY
}

void GameManager::RegisterItems()
{
	#define REGISTER_ITEM(i) itemsFactory.Register<i>(#i);
	REGISTER_ITEM(AK47)
	REGISTER_ITEM(AKMagazine)
	REGISTER_ITEM(Sword)
	#undef REGISTER_ITEM
	itemsFactory.Register<BombItem>("Bomb");
}

void GameManager::Update()
{
	switch(gameState)
	{
		case GameStateEnteringMap:
			entitiesManager.RemoveDead();
			entitiesManager.RemoveNonPersistent();
			mapManager.SpawnEntities();
			
			player->speedX = 0;
			player->speedY = 0;
			
			if(transition == TransitionNone) gameState = GameStatePlaying;
			else
			{
				currentTransition = transition;
				transition = TransitionNone;
				transitionFrame = 0;
				draw_sprite(transitionBitmap, playArea, 0, 0);
				gameState = GameStateTransition;
			}
			break;
		case GameStateTransition:
			transitionFrame++;
			if(currentTransition == TransitionScrolling)
			{
				if(((transitionFrame + 1) * transitionSpeed >= 420) && (transitionDirection <= 1)) gameState = GameStatePlaying;
				if(((transitionFrame + 1) * transitionSpeed >= 630) && (transitionDirection >= 2)) gameState = GameStatePlaying;
			}
			if(currentTransition == TransitionFading)
			{
				if(transitionFrame * transitionFadingSpeed >= 510) gameState = GameStatePlaying;
			}
			break;
		case GameStatePlaying:
			if(dialogLines.size() != 0)
			{
				currentDialogLines[0] = dialogLines.front();
				currentDialogLines[1] = "";
				dialogLines.pop();
				currentDialogLine = 0;
				dialogProgress = 0;
				dialogCounter = 0;
				gameState = GameStateDialog;
			}
			entitiesManager.Update();
			if(player->dead)
			{
				gameState = GameStateDead;
				pauseFading = 0;
				draw_sprite(transitionBitmap, playArea, 0, 0);
				ToGrayscale(transitionBitmap);
				continuePlaying = true;
			}
			if(key[KEY_ESC])
			{
				gameState = GameStateQuit;
				pauseFading = 0;
				draw_sprite(transitionBitmap, playArea, 0, 0);
				ToGrayscale(transitionBitmap);
				continuePlaying = true;
			}
			frame++;
			break;
		case GameStateInventory:
			if(sKey == KeyDown) gameState = GameStatePlaying;
			if(leftKey == KeyDown) selectedItem = inventoryManager.PreviousEquippable(selectedItem);
			if(rightKey == KeyDown) selectedItem = inventoryManager.NextEquippable(selectedItem);
			if(xKey == KeyDown) player->equippedItems[0] = selectedItem;
			if(cKey == KeyDown) player->equippedItems[1] = selectedItem;
			break;
		case GameStateDialog:
			if(dialogProgress >= currentDialogLines[currentDialogLine].size())
			{
				if(aKey == KeyDown)
				{
					if(dialogLines.size() == 0)
					{
						gameState = GameStatePlaying;
						break;
					}
					if(currentDialogLine == 1)
					{
						currentDialogLine = 0;
						currentDialogLines[1] = "";
						currentDialogLines[0] = dialogLines.front();
						dialogLines.pop();
						dialogProgress = 0;
						break;
					}
				}
				if((currentDialogLine == 0) && (dialogLines.size() != 0))
				{
					currentDialogLine = 1;
					currentDialogLines[1] = dialogLines.front();
					dialogLines.pop();
					dialogProgress = 0;
					break;
				}
			}
			dialogCounter++;
			if(dialogCounter >= dialogInverseSpeed)
			{
				if(dialogProgress < currentDialogLines[currentDialogLine].size())
				{
					if(std::isalnum(currentDialogLines[currentDialogLine][dialogProgress]) != 0)
					{
						if(dialogProgress % 3 == 0) play_sample(blip, 128, 0, 1000, false);
					}
				}
				dialogProgress++;
			}
			break;
		case GameStateDead:
			pauseFading += pauseFadingSpeed;
			if(pauseFading > 255) pauseFading = 255;
			if(upKey == KeyDown) continuePlaying = true;
			if(downKey == KeyDown) continuePlaying = false;
			if((aKey == KeyDown) || (sKey == KeyDown)) gameState = GameStateFinished;
			break;
		case GameStateQuit:
			pauseFading += pauseFadingSpeed;
			if(pauseFading > 255) pauseFading = 255;
			if(upKey == KeyDown) continuePlaying = true;
			if(downKey == KeyDown) continuePlaying = false;
			if((aKey == KeyDown) || (sKey == KeyDown))
			{
				if(!continuePlaying)
				{
					SaveStatus();
					gameState = GameStateFinished;
				}
				else gameState = GameStatePlaying;
			}
			break;
	}
	UpdateKeys();
	if(f11Key == KeyDown)
	{
		std::string fileName = "screenshots/screenshot_frame";
		fileName += Itoa(frame);
		fileName += ".bmp";
		save_bitmap(fileName.c_str(), doubleBuffer, 0);
	}
}

void GameManager::Draw()
{
	if(gameState != GameStateEnteringMap) clear(doubleBuffer);
	if((gameState == GameStatePlaying) || (gameState == GameStateTransition) || (gameState == GameStateInventory) || (gameState == GameStateDialog))
	{
		mapManager.BeginDrawing(playArea, 0, 0);
		entitiesManager.BeginDrawing(playArea, 0, 0);
		
		for(int i = 0; i < 14; i++)
		{
			entitiesManager.DrawRow();
			mapManager.DrawRow();
		}
		
		entitiesManager.FinishDrawing();
		mapManager.FinishDrawing();
	}
	if((gameState == GameStatePlaying) || (gameState == GameStateInventory) || (gameState == GameStateDialog) || (gameState == GameStateDead) || (gameState == GameStateQuit)) draw_sprite(doubleBuffer, playArea, 5, 5);
	if(gameState == GameStateTransition)
	{
		if(currentTransition == TransitionScrolling)
		{
			switch(transitionDirection)
			{
				case 0:
					draw_sprite(doubleBuffer, transitionBitmap, 5, (transitionSpeed * transitionFrame) + 5);
					draw_sprite(doubleBuffer, playArea, 5, (transitionSpeed * transitionFrame) - 415);
					break;
				case 1:
					draw_sprite(doubleBuffer, transitionBitmap, 5, 5 - (transitionSpeed * transitionFrame));
					draw_sprite(doubleBuffer, playArea, 5, 425 - (transitionSpeed * transitionFrame));
					break;
				case 2:
					draw_sprite(doubleBuffer, transitionBitmap, (transitionSpeed * transitionFrame) + 5, 5);
					draw_sprite(doubleBuffer, playArea, (transitionSpeed * transitionFrame) - 625, 5);
					break;
				case 3:
					draw_sprite(doubleBuffer, transitionBitmap, 5 - (transitionSpeed * transitionFrame), 5);
					draw_sprite(doubleBuffer, playArea, 635 - (transitionSpeed * transitionFrame), 5);
					break;
			}
		}
		if(currentTransition == TransitionFading)
		{
			if(transitionFrame * transitionFadingSpeed <= 255)
			{
				rectfill(doubleBuffer, 5, 5, 635, 425, 0);
				set_trans_blender(0, 0, 0, 255 - (transitionFrame * transitionFadingSpeed));
				draw_trans_sprite(doubleBuffer, transitionBitmap, 5, 5);
			}
			else
			{
				rectfill(doubleBuffer, 5, 5, 635, 425, 0);
				set_trans_blender(0, 0, 0, (transitionFrame * transitionFadingSpeed) - 255);
				draw_trans_sprite(doubleBuffer, playArea, 5, 5);
			}
		}
	}
	if(gameState == GameStateDead)
	{
		set_trans_blender(0, 0, 0, int(pauseFading));
		draw_trans_sprite(doubleBuffer, transitionBitmap, 5, 5);
		float bgx, bgy;
		bgx = player->x - 315;
		bgy = player->y - 210;
		float l = std::sqrt(bgx * bgx + bgy * bgy);
		bgx /= l;
		bgy /= l;
		bgx = 315 - (bgx * 150);
		bgy = 210 - (bgy * 150);
		if(continuePlaying) blit(continueBg, doubleBuffer, 0, 0, bgx, bgy, 109, 52);
		else blit(continueBg, doubleBuffer, 0, 52, bgx, bgy, 109, 52);
		textprintf_ex(doubleBuffer, dialogFont, bgx + 5, bgy + 5, 0, -1, "Game over");
		textprintf_ex(doubleBuffer, dialogFont, bgx + 5, bgy + 5 + 14, 0, -1, " Continue");
		textprintf_ex(doubleBuffer, dialogFont, bgx + 5, bgy + 5 + 14 + 14, 0, -1, " Quit");
	}
	if(gameState == GameStateQuit)
	{
		set_trans_blender(0, 0, 0, int(pauseFading));
		draw_trans_sprite(doubleBuffer, transitionBitmap, 5, 5);
		float bgx, bgy;
		bgx = player->x - 315;
		bgy = player->y - 210;
		float l = std::sqrt(bgx * bgx + bgy * bgy);
		bgx /= l;
		bgy /= l;
		bgx = 315 - (bgx * 150);
		bgy = 210 - (bgy * 150);
		if(continuePlaying) blit(continueBg, doubleBuffer, 0, 0, bgx, bgy, 109, 52);
		else blit(continueBg, doubleBuffer, 0, 52, bgx, bgy, 109, 52);
		textprintf_ex(doubleBuffer, dialogFont, bgx + 5, bgy + 5, 0, -1, "Paused");
		textprintf_ex(doubleBuffer, dialogFont, bgx + 5, bgy + 5 + 14, 0, -1, " Continue");
		textprintf_ex(doubleBuffer, dialogFont, bgx + 5, bgy + 5 + 14 + 14, 0, -1, " Quit");
	}
	if(gameState == GameStateInventory)
	{
		inventoryManager.Draw(doubleBuffer, 218, 138, selectedItem);
	}
	if((gameState == GameStatePlaying) || (gameState == GameStateTransition) || (gameState == GameStateInventory) || (gameState == GameStateDialog) || (gameState == GameStateDead) || (gameState == GameStateQuit))
	{
		draw_sprite(doubleBuffer, hud, 0, 0);
		if(player->equippedItems[0] != 0) draw_sprite(doubleBuffer, player->equippedItems[0]->icon, 222, 432);
		if(player->equippedItems[1] != 0) draw_sprite(doubleBuffer, player->equippedItems[1]->icon, 272, 432);
		if(player->health > 0)
		{
			for(int i = 0, j = 4; i < 5; i++, j--)
			{
				if(float(player->health)  < float(i) * float(player->maxHealth) / 5.0) break;
				masked_blit(facePicture, doubleBuffer, j * 45, 0, 5, 430, 45, 45);
			}
		}
		else
		{
			masked_blit(facePicture, doubleBuffer, 270 - 45, 0, 5, 430, 45, 45);
		}
		int h;
		for(h = 0; h < player->health / 2; h++)
		{
			masked_blit(heartSprite, doubleBuffer, 0, 0, 55 + h * 20, 430, 20, 20);
		}
		if(player->health >= 0)
		{
			if(player->health % 2 != 0)
			{
				masked_blit(heartSprite, doubleBuffer, 0, 20, 55 + h * 20, 430, 20, 20);
				h++;
			}
		}
		for( ; h < player->maxHealth / 2; h++)
		{
			masked_blit(heartSprite, doubleBuffer, 0, 40, 55 + h * 20, 430, 20, 20);
		}
	}
	if(gameState == GameStateDialog)
	{
		std::string linesToDraw[2];
		switch(currentDialogLine)
		{
			case 0:
				linesToDraw[0] = currentDialogLines[0].substr(0, dialogProgress);
				linesToDraw[1] = currentDialogLines[1];
				break;
			case 1:
				linesToDraw[1] = currentDialogLines[1].substr(0, dialogProgress);
				linesToDraw[0] = currentDialogLines[0];
				break;
		}
		draw_sprite(doubleBuffer, dialogBox, 320 - (dialogBox->w / 2), 430 + ((45 - dialogBox->h) / 2));
		textprintf_ex(doubleBuffer, dialogFont, 320 - (dialogBox->w / 2) + 5, 430 + ((45 - dialogBox->h) / 2) + 5, 0, -1, "%s", linesToDraw[0].c_str());
		textprintf_ex(doubleBuffer, dialogFont, 320 - (dialogBox->w / 2) + 5, 430 + ((45 - dialogBox->h) / 2) + 5 + 14, 0, -1, "%s", linesToDraw[1].c_str());
	}
	textprintf_ex(doubleBuffer, font, 0, 0, 0xFFFFFF, 0, "FPS:%d gameState:%d file: %d currentMapName: %s Entity count: %d", fps, gameState, file, mapManager.currentMapName.c_str(), entitiesManager.Count());
	draw_sprite(screen, doubleBuffer, 0, 0);
}

void GameManager::DoFrame()
{
	Update();
	Draw();
	while(tick == false) continue;
	tick = false;
}

void GameManager::Play()
{
	LOCK_VARIABLE(tick);
	LOCK_FUNCTION(Ticker);
	LOCK_VARIABLE(fpsFrame);
	LOCK_VARIABLE(fps);
	LOCK_FUNCTION(SaveFrame);
	install_int_ex(Ticker, BPS_TO_TIMER(60));
	install_int_ex(SaveFrame, BPS_TO_TIMER(1));

	while(gameState != GameStateFinished) DoFrame();

	entitiesManager.Clear();
	inventoryManager.Clear();
	mapManager.ResetTimes();
	questStates.clear();

	remove_int(Ticker);
	remove_int(SaveFrame);

}

void GameManager::SetQuestState(std::string s, std::string v)
{
	questStates[s] = v;
}

std::string GameManager::GetQuestState(std::string s)
{
	return questStates[s];
}
