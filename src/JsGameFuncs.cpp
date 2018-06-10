#include <cmath>
#include <string>
#include <map>
#include <iostream>

#include <allegro.h>

#include "duktape.h"

#include "Utils.h"
#include "Game.h"
#include "JsEngine.h"
#include "Player.h"
#include "Entity.h"
#include "Item.h"

#define JS_FUNC(name) static duk_ret_t Js ## name (duk_context *ctx)

JS_FUNC(SetMusic)
{
	if(duk_is_string(ctx, 0)) game.SetMusic(duk_get_string(ctx, 0));
	return 0;
}

JS_FUNC(DialogLine)
{
	if(duk_is_string(ctx, 0)) game.PushDialogLine(duk_get_string(ctx, 0));
	return 0;
}

JS_FUNC(SetQuest)
{
	if(duk_is_string(ctx, 0) && duk_is_string(ctx, 1))
	{
		game.SetQuestState(duk_get_string(ctx, 0), duk_get_string(ctx, 1));
	}
	return 0;
}

JS_FUNC(GetQuest)
{
	if(duk_is_string(ctx, 0)) duk_push_string(ctx, game.GetQuestState(duk_get_string(ctx, 0)).c_str());
	return 1;
}

JS_FUNC(GetTextData)
{
	DATAFILE *d = 0;
	std::string str;
	if(duk_is_string(ctx, 0)) d = (DATAFILE *) game.GetData(duk_get_string(ctx, 0));
	if(d)
	{
		str = DatafileToString(d);
		duk_push_string(ctx, str.c_str());
	}
	else duk_push_null(ctx);
	return 1;
}

JS_FUNC(GetMapName)
{
	duk_push_string(ctx, game.mapManager.currentMapName.c_str());
	return 1;
}

static void PushEntity(duk_context *ctx, Entity *e)
{
	duk_push_object(ctx);
	duk_push_number(ctx, e->x);
	duk_put_prop_string(ctx, -2, "x");
	duk_push_number(ctx, e->y);
	duk_put_prop_string(ctx, -2, "y");
	duk_push_number(ctx, e->width);
	duk_put_prop_string(ctx, -2, "width");
	duk_push_number(ctx, e->height);
	duk_put_prop_string(ctx, -2, "height");
	duk_push_boolean(ctx, e->alive);
	duk_put_prop_string(ctx, -2, "alive");
	duk_push_boolean(ctx, e->persistent);
	duk_put_prop_string(ctx, -2, "persistent");
	duk_push_number(ctx, e->layer);
	duk_put_prop_string(ctx, -2, "layer");
}

JS_FUNC(GetEntity)
{
	Entity *e = 0;
	if(duk_is_pointer(ctx, 0)) e = (Entity *) duk_get_pointer(ctx, 0);
	PushEntity(ctx, e);
	return 1;
}

JS_FUNC(GetPlayer)
{
	PushEntity(ctx, game.player);
	duk_push_number(ctx, game.player->health);
	duk_put_prop_string(ctx, -2, "health");
	duk_push_number(ctx, game.player->maxHealth);
	duk_put_prop_string(ctx, -2, "maxHealth");
	return 1;
}

JS_FUNC(Heal)
{
	int amount;
	if(!duk_is_number(ctx, 0)) return 0;
	amount = duk_get_int(ctx, 0);
	if(amount < 0)
	{
		game.player->OnHit(amount);
	}
	else
	{
		game.player->Heal(amount);
	}
	return 0;
}

JS_FUNC(GiveItem)
{
	Item *i;
	int amount = 1;
	std::string n;
	if(!duk_is_string(ctx, 0)) return 0;
	n = duk_get_string(ctx, 0);
	if(duk_is_number(ctx, 1)) amount = duk_get_int(ctx, 1);
	if(!(i = game.inventoryManager.Find(n)))
	{
		i = game.itemsFactory.Create(n);
		game.inventoryManager.Add(i);
	}
	i->SetAmount(i->amount + amount);
	return 0;
}

JS_FUNC(TakeItem)
{
	Item *i = 0;
	int amount = 1;
	bool remove = false;
	std::string n;
	if(!duk_is_string(ctx, 0)) return 0;
	n = duk_get_string(ctx, 0);
	if(duk_is_number(ctx, 1)) remove = true;
	i = game.inventoryManager.Find(n);
	if(i)
	{
		if(!remove)
		{
			int newA = i->amount - amount;
			if(newA < 0) newA = 0;
			i->SetAmount(newA);
		}
		else
		{
			game.inventoryManager.Remove(i);
		}
	}
	return 0;
}

JS_FUNC(Blink)
{
	if(!duk_is_number(ctx, 0)) return 0;
	if(!duk_is_number(ctx, 1)) return 0;
	float toX = duk_get_number(ctx, 0);
	float toY = duk_get_number(ctx, 1);
	game.SetFadingTransition();
	game.player->x = toX;
	game.player->y = toY;
	game.gameState = GameStateTransition;
	return 0;
}

JS_FUNC(Teleport)
{
	if(!duk_is_string(ctx, 0)) return 0;
	if(!duk_is_number(ctx, 1)) return 0;
	if(!duk_is_number(ctx, 2)) return 0;
	std::string map = duk_get_string(ctx, 0);
	float toX = duk_get_number(ctx, 1);
	float toY = duk_get_number(ctx, 2);
	game.SetFadingTransition();
	game.player->x = toX;
	game.player->y = toY;
	game.mapManager.SetMap(map);
	game.gameState = GameStateEnteringMap;
	return 0;
}

JS_FUNC(PlaySample)
{
	Entity *e = 0;
	std::string n;
	int vol = 255;
	
	int volIdx = 2;
	if(!duk_is_string(ctx, 0)) return 0;
	n = duk_get_string(ctx, 0);
	if(!duk_is_pointer(ctx, 1)) volIdx--;
	else e = (Entity *) duk_get_pointer(ctx, 1);
	if(duk_is_number(ctx, volIdx)) vol = std::floor(255.0 * duk_get_number(ctx, volIdx));
	if(e)
	{
		e->PlaySample(n.c_str(), vol);
	}
	else
	{
		SAMPLE *spl = (SAMPLE *) game.GetData(n.c_str());
		if(spl)
		{
			play_sample(spl, vol, (315 / 630) * 255, 1000, 0);
		}
	}
	return 0;
}

JS_FUNC(ConsolePrint)
{
	if(duk_is_string(ctx, 0))
	{
		std::cout << duk_get_string(ctx, 0) << "\n";
	}
	return 0;
}

JS_FUNC(Spawn)
{
	std::string type;
	std::map<std::string, std::string> params;
	if(!duk_is_string(ctx, 0)) return 0;
	type = duk_get_string(ctx, 0);
	if(duk_is_object(ctx, 1))
	{
		duk_enum(ctx, 1, 0);
		while(duk_next(ctx, -1, 1))
		{
			if(duk_is_string(ctx, -1)) params[duk_get_string(ctx, -2)] = duk_get_string(ctx, -1);
			duk_pop_2(ctx);
		}
		duk_pop(ctx);
	}
	
	Entity *e = game.entitiesFactory.Create(type);
	for(std::map<std::string, std::string>::iterator it = params.begin() ; it != params.end(); ++it)
	{
		e->SetParameter(it->first, it->second);
	}
	e->mapId = -999;
	game.entitiesManager.Add(e);
	PushEntity(ctx, e);
	return 1;
}

void InitJsGameFuncs()
{
	#define CHECK_ERR(a) if(game.scriptEngine->err)\
	{\
	std::cout << "InitJsGameFuncs ERROR on function " #a ": " << game.scriptEngine->err << "\n";\
	game.scriptEngine->ClearError();\
	}
	#define PUSHFUNC(a,b) game.scriptEngine->Set(#a)->PushCFunction((void *) Js ## a, (b)); CHECK_ERR(a)
	PUSHFUNC(SetMusic, 1)
	PUSHFUNC(DialogLine, 1)
	PUSHFUNC(SetQuest, 2)
	PUSHFUNC(GetQuest, 1)
	PUSHFUNC(GetTextData, 1)
	PUSHFUNC(GetMapName, 0)
	PUSHFUNC(GetEntity, 1)
	PUSHFUNC(GetPlayer, 0)
	PUSHFUNC(Heal, 1)
	PUSHFUNC(GiveItem, DUK_VARARGS)
	PUSHFUNC(TakeItem, DUK_VARARGS)
	PUSHFUNC(Blink, 2)
	PUSHFUNC(Teleport, 3)
	PUSHFUNC(PlaySample, DUK_VARARGS)
	PUSHFUNC(ConsolePrint, 1)
	PUSHFUNC(Spawn, DUK_VARARGS)
}