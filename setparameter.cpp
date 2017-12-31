// sed -n /::SetParameter/,/^^}/p *.cpp miscEntities/*.cpp enemies/*.cpp
void Entity::SetParameter(std::string p, std::string v)
{
	if(p == "x" && !ignorePos) x = std::atoi(v.c_str());
	if(p == "y" && !ignorePos) y = std::atoi(v.c_str());
	if(p == "randomize_pos")
	{
		ignorePos = true;
		MoveToFreeSpot();
	}
}
void Button::SetParameter(std::string p, std::string v)
{
	if(p == "trigger")
	{
		trigger = std::atoi(v.c_str());
		return;
	}
	Entity::SetParameter(p, v);
}
void Chest::SetParameter(std::string p, std::string v)
{
	if(p == "uid")
	{
		uid = std::atoi(v.c_str());
		return;
	}
	if(p == "item")
	{
		item = v;
		return;
	}
	Entity::SetParameter(p, v);
}
void Door::SetParameter(std::string p, std::string v)
{
	if(p == "toMap")
	{
		map = v;
		return;
	}
	if(p == "toX")
	{
		toX = std::atoi(v.c_str());
		return;
	}
	if(p == "toY")
	{
		toY = std::atoi(v.c_str());
		return;
	}
	if(p == "skin")
	{
		frameStart = frameEnd = std::atoi(v.c_str()) * 4;
		return;
	}
	Entity::SetParameter(p, v);
}
void MusicSetter::SetParameter(std::string p, std::string v)
{
	if(p == "midi") game.SetMusic(v);
}
void NPC::SetParameter(std::string p, std::string v)
{
	if(p == "skin")
	{
		skin = std::atoi(v.c_str());
		return;
	}
	if(p == "text")
	{
		UnderlinesToSpaces(v);
		text.push_back(v);
		return;
	}
	if(p == "walkTime")
	{
		walkTime = std::atoi(v.c_str());
		return;
	}
	if(p == "speed")
	{
		walkSpeed = std::atof(v.c_str());
		return;
	}
	if(p == "agitation")
	{
		agitation = std::atoi(v.c_str());
		return;
	}
	if(p == "sprite")
	{
		sprite = (BITMAP *) game.GetData(v.c_str());
		return;
	}
	Entity::SetParameter(p, v);
}
void Painting::SetParameter(std::string p, std::string v)
{
	if(p == "file")
	{
        file = std::atoi(v.c_str());
        std::string canvasFileName = "saves/game";
        canvasFileName += Itoa(file + 1);
        canvasFileName += ".bmp";
        canvas = load_bitmap(canvasFileName.c_str(), 0);
		return;
	}
	Entity::SetParameter(p, v);
}
void Portal::SetParameter(std::string p, std::string v)
{
	if(p == "toMap")
	{
		map = v;
		return;
	}
	if(p == "toX")
	{
		toX = std::atoi(v.c_str());
		return;
	}
	if(p == "toY")
	{
		toY = std::atoi(v.c_str());
		return;
	}
	if(p == "width")
	{
		width = std::atoi(v.c_str());
		return;
	}
	if(p == "height")
	{
		height = std::atoi(v.c_str());
		return;
	}
	Entity::SetParameter(p, v);
}
void Sign::SetParameter(std::string p, std::string v)
{
	if(p == "text")
	{
		UnderlinesToSpaces(v);
		text.push_back(v);
		return;
	}
	Entity::SetParameter(p, v);
}
void Stairs::SetParameter(std::string p, std::string v)
{
	if(p == "toMap")
	{
		toMap = v;
		return;
	}
	if(p == "toX")
	{
		toX = std::atoi(v.c_str());
		return;
	}
	if(p == "toY")
	{
		toY = std::atoi(v.c_str());
		return;
	}
	if(p == "type")
	{
		type = std::atoi(v.c_str());
		return;
	}
	if(p == "id")
	{
		id = v;
		type = TYPE_KEY;
	}
	if(p == "trigger")
	{
		trigger = std::atoi(v.c_str());
		type = TYPE_TRIGGERED;
	}
	Entity::SetParameter(p, v);
}
void Trap::SetParameter(std::string p, std::string v)
{
	if(p == "stakeO")
	{
		stakeO = std::atoi(v.c_str());
		return;
	}
	if(p == "trigger")
	{
		trigger = std::atoi(v.c_str());
		return;
	}
	Entity::SetParameter(p, v);
}
void VillageWall::SetParameter(std::string p, std::string v)
{
	Entity::SetParameter(p, v);
	if(x < 0)
	{
		x = -30;
		y = 0;
		width = 30;
		height = 480;
	}
	else if(y < 0)
	{
		y = -30;
		x = 0;
		width = 640;
		height = 30;
	}
	else if(x >= 640)
	{
		x = 640;
		y = 0;
		width = 30;
		height = 480;
	}
	else if(y >= 480)
	{
		y = 480;
		x = 0;
		width = 640;
		height = 30;
	}
}
void Gargoyle::SetParameter(std::string p, std::string v)
{
	if(p == "orientation") orientation = std::atoi(v.c_str());
	else Entity::SetParameter(p, v);
}
void Slime::SetParameter(std::string p, std::string v)
{
	Entity::SetParameter(p, v);
}
void Statue::SetParameter(std::string what, std::string value)
{
	if((what == "timer")||(what == "phase"))
	{
		attackTimer = atoi(value.c_str());
		return;
	}
	Entity::SetParameter(what, value);
}
