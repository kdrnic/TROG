#include <allegro.h>

#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stack>

struct MapEntity
{
	int respawnTime;
	std::string name;
	std::list<std::pair<std::string, std::string> > parameters;
};

int ***tiles = 0;
int **blocks = 0;
int numberOfLayers = 3;
std::string fileName;
BITMAP **tileSet;
int numberOfTiles;
BITMAP *db;
int frame = 0;
int inverseSpeed = 5;
std::string exits[4];
std::string name;
std::list<MapEntity> entities;

std::string itoa(int value)
{
	std::stringstream ss;
	ss << value;
	return ss.str();
}

std::string MozDong(std::string s)
{
	if(s.size() > 4)
	{
		std::string t = "";
		if(s.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") != s.find_last_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ"))
		{
			t += s[s.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ")];
			t += s.substr(s.find_last_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
		}
		else t = s;
		if(t.size() > 4)
		{
			t = t.substr(0, 4);
		}
		return t;
	}
	else return s;
}

std::vector<std::string> StringToStrings(std::string s)
{
	std::vector<std::string> v;
	while(s.size() > 0 || s != " ")
	{
		std::string e = s.substr(0, s.find(' '));
		v.push_back(e);
		if(e.size() + 1 < s.size()) s = s.substr(e.size() + 1);
		else break;
	}
	return v;
}

void LoadTilesLayer(int **&l, std::istream &is)
{
	if(l == 0)
	{
		l = new int *[21];
		for(int x = 0; x < 21; x++) l[x] = new int[14];
	}
	for(int y = 0; y < 14; y++)
	{
		std::string line;
		std::getline(is, line);
		std::vector<std::string> lv = StringToStrings(line);
		for(int x = 0; x < 21; x++)
		{
			l[x][y] = std::atoi(lv[x].c_str());
		}
	}
}

void LoadBlocksLayer(int **&l, std::istream &is)
{
	if(l == 0)
	{
		l = new int *[42];
		for(int x = 0; x < 42; x++) l[x] = new int[28];
	}
	for(int y = 0; y < 28; y++)
	{
		std::string line;
		std::getline(is, line);
		std::vector<std::string> lv = StringToStrings(line);
		for(int x = 0; x < 42; x++)
		{
			l[x][y] = std::atoi(lv[x].c_str());
		}
	}
}

void LoadMapEntity(std::string l)
{
	std::vector<std::string> lv  = StringToStrings(l);
	MapEntity me;
	me.respawnTime = std::atoi(lv[0].c_str());
	me.name = lv[1];
	for(int i = 2; i < lv.size(); i++)
	{
		std::pair<std::string, std::string> parameter;
		parameter.first = lv[i].substr(0, lv[i].find(":"));
		parameter.second = lv[i].substr(lv[i].find(":") + 1);
		me.parameters.push_back(parameter);
	}
	entities.push_back(me);
}

void LoadMap()
{
	std::fstream is;
	is.open(fileName.c_str(), std::fstream::in);
	if(!is.is_open())
	{
		std::cout << "Farewell, oh cruel world!" << '\n';
		std::cout.flush();
		int x = 5;
		int y = 10;
		y /= x - 5;
	}
	getline(is, name);
	LoadBlocksLayer(blocks, is);
	if(tiles == 0)
	{
		tiles = new int **[3];
		for(int i = 0; i < 3; i++) tiles[i] = 0;
	}
	for(int i = 0; i < 3; i++)
	{
		LoadTilesLayer(tiles[i], is);
	}
	for(int i = 0; i < 4; i++) getline(is, exits[i]);
	entities.clear();
	while(!is.eof())
	{
		std::string e;
		getline(is, e);
		if(e != "") LoadMapEntity(e);
	}
	numberOfLayers = 3;
	is.close();
}

void LoadTileSet(std::string _fileName)
{
	std::fstream tileSetFile;
	tileSetFile.open(_fileName.c_str(), std::fstream::in);
	std::vector<std::string> bmpNames;

	while(!tileSetFile.eof())
	{
		std::string bmpName;
		std::getline(tileSetFile, bmpName);
		if(bmpName == "") continue;
		bmpNames.push_back(bmpName);
	}

	tileSet = new BITMAP *[bmpNames.size()];
	numberOfTiles = bmpNames.size();
	for(int i = 0; i < bmpNames.size(); i++) tileSet[i] = load_bitmap(bmpNames[i].c_str(), 0);
	tileSetFile.close();
	bmpNames.clear();
}

void DrawLayer(int layer)
{
	for(int y = 0; y < 14; y++)
	{
		for(int x = 0; x < 21; x++)
		{
			masked_blit(tileSet[tiles[layer][x][y]], db, ((frame / inverseSpeed) % (tileSet[tiles[layer][x][y]]->w / 30)) * 30, 0, 0 + x * 30, 0 + y * 30, 30, 30);
		}
	}
}

void DrawMap()
{
	for(int i = 0; i < 3; i++) DrawLayer(i);
	frame++;
}

void SaveTilesLayer(int **&l, std::ostream &mf)
{
	for(int y = 0; y < 14; y++)
	{
		for(int x = 0; x < 21; x++)
		{
			mf << l[x][y];
			if(x != 20) mf << ' ';
		}
		mf << '\n';
	}
}

void SaveBlocksLayer(int **&l, std::ostream &mf)
{
	for(int y = 0; y < 28; y++)
	{
		for(int x = 0; x < 42; x++)
		{
			mf << l[x][y];
			if(x != 41) mf << ' ';
		}
		mf << '\n';
	}
}

void SaveEntity(MapEntity me, std::ostream &mf)
{
	mf << me.respawnTime << ' ' << me.name;
	for(std::list<std::pair<std::string, std::string> >::iterator i = me.parameters.begin(); i != me.parameters.end(); i++)
	{
		mf << ' ' << i->first << ':' << i->second;
	}
	mf << '\n';
}

void SaveMap()
{
	std::fstream mf;
	mf.open(fileName.c_str(), std::fstream::out);
	mf << name << '\n';
	SaveBlocksLayer(blocks, mf);
	for(int i = 0; i < 3; i++) SaveTilesLayer(tiles[i], mf);
	for(int i = 0; i < 4; i++) mf << exits[i] << '\n';
	for(std::list<MapEntity>::iterator i = entities.begin(); i != entities.end(); i++) SaveEntity(*i, mf);
	mf.close();
}

std::string GetFile(const char *msg, const char *ext, std::string dir = "")
{
	char n[1024];
	for(int i = 0; i < 1024; i++) n[i] = 0;
	for(int i = 0; i < dir.size(); i++) n[i] = dir[i];
	if(file_select_ex(msg, n, ext, 1024, 640, 480) == 0) return "";
	return std::string(n);
}

#define numberOfButtons 256

class EditMode
{
	public:
		int buttons[numberOfButtons][5];
		std::string text[numberOfButtons];
		int focus;
		BITMAP *bg;

		void OnClick(int x, int y)
		{
			if(y < 420) OnMClick(x, y);
			for(int i = 0; i < numberOfButtons; i++)
			{
				if(x > buttons[i][0])
				{
					if(y > 420 + buttons[i][1])
					{
						if(x < buttons[i][2])
						{
							if(y < 420 + buttons[i][3])
							{
								if(buttons[i][4]) focus = i;
								else
								{
									OnBClick(i);
									focus = -1;
								}
								return;
							}
						}
					}
				}
			}
			focus = -1;
		}

		virtual void Draw()
		{
			draw_sprite(db, bg, 0, 420);
			if(focus >= 0) DrawButton(focus, 0xFF);
			for(int i = 0; i < numberOfButtons; i++)
			{
				textprintf_ex(db, font, buttons[i][0] + 1, 420 + 1 - 4 + (buttons[i][1] + buttons[i][3]) / 2, 0xFF00, -1, "%s", text[i].c_str());
			}
		}

		virtual void OnMClick(int x, int y)
		{
		}

		virtual void OnBClick(int b)
		{
		}

		void DrawButton(int b, int c = 0xFF0000)
		{
			rect(db, buttons[b][0], 420 +  buttons[b][1], buttons[b][2], 420 +  buttons[b][3], c);
		}

		void OnKey(int k)
		{
			if(focus < 0) return;
			int ascii = k & 0xFF;
			int scanCode = k >> 8;
			if((ascii >= 32) && (ascii <= 126))
			{
				if(buttons[focus][4] == 1) text[focus] += char(ascii);
				else if((ascii >= 48) && (ascii <= 57)) text[focus] += char(ascii);
			}
			else
			{
				switch(scanCode)
				{
					case KEY_ENTER:
						focus = -1;
						break;
					case KEY_BACKSPACE:
						if(text[focus].size() > 0) text[focus].erase(text[focus].size() - 1);
						break;
				}
			}
			OnTextChange(focus);
		}

		virtual void OnTextChange(int b)
		{
		}

		virtual void OnSelectMode()
		{
		}

		EditMode()
		{
			for(int i = 0; i < numberOfButtons; i++)
			{
				for(int j = 0; j < 5; j++) buttons[i][j] = 0;
			}
			focus = -1;
		}
};

class FileMode : public EditMode
{
	public:
		void OnBClick(int b)
		{
			if(b == 0)
			{
				SaveMap();
			}
			if(b == 1)
			{
				fileName = GetFile("Select map file to save:", "map", "./maps/");
				SaveMap();
			}
			if(b == 2)
			{
				fileName = GetFile("Select map file to load:", "map", "./maps/");
				LoadMap();
			}
		}

		FileMode()
		{
			/*
			buttons[][0] = ;
			buttons[][1] = ;
			buttons[][2] = ;
			buttons[][3] = ;
			*/
			buttons[0][0] = 9;
			buttons[0][1] = 9;
			buttons[0][2] = 101;
			buttons[0][3] = 48;
			buttons[1][0] = 108;
			buttons[1][1] = 8;
			buttons[1][2] = 247;
			buttons[1][3] = 46;
			buttons[2][0] = 256;
			buttons[2][1] = 12;
			buttons[2][2] = 342;
			buttons[2][3] = 49;
			bg = load_bitmap("./mapedgfx/bg2.bmp", 0);
		}
};

class TilesMode : public EditMode
{
	public:
		int stiles[19];
		int l, st;
		int tool;
		int lastTx, lastTy, lastTool;
		bool rect;

		void FloodFill(int x, int y)
		{
			int t = tiles[l][x][y];
			static std::stack<int> tStack;
			if(st == t) return;
			tStack.push(x * 21 + y);
			while(!tStack.empty())
			{
				int top = tStack.top();
				tStack.pop();
				x = top / 21;
				y = top % 21;
				tiles[l][x][y] = st;
				if((x + 1 < 21) && (tiles[l][x + 1][y] == t)) tStack.push((x + 1) * 21 + y);
				if((x - 1 >= 0) && (tiles[l][x - 1][y] == t)) tStack.push((x - 1) * 21 + y);
				if((y + 1 < 14) && (tiles[l][x][y + 1] == t)) tStack.push(x * 21 + y + 1);
				if((y - 1 >= 0) && (tiles[l][x][y - 1] == t)) tStack.push(x * 21 + y - 1);
			}
		}

		void Draw()
		{
			EditMode::Draw();
			for(int i = 0; i < 19; i++)
			{
				if((stiles[i] >= 0) && (stiles[i] < numberOfTiles)) blit(tileSet[stiles[i]], db, ((frame / inverseSpeed) % (tileSet[stiles[i]]->w / 30)) * 30, 0, 36 + i * 30, 424, 30, 30);
				if(stiles[i] == st) DrawButton(i + 1);
			}
			DrawButton(l + 21);
			DrawButton(tool + 24);
		}

		void OnMClick(int x, int y)
		{
			int tx = x / 30;
			int ty = y / 30;
			switch(tool)
			{
				case 0:
					tiles[l][tx][ty] = st;
					break;
				case 1:
					if(lastTool == 1)
					{
						if(rect)
						{
							if(lastTx < tx)
							{
								for(int _x = lastTx; _x <= tx; _x++)
								{
									if(lastTy < ty)	for(int _y = lastTy; _y <= ty; _y++) tiles[l][_x][_y] = st;
									else for(int _y = ty; _y <= lastTy; _y++) tiles[l][_x][_y] = st;
								}
							}
							else
							{
								for(int _x = tx; _x <= lastTx; _x++)
								{
									if(lastTy < ty)	for(int _y = lastTy; _y <= ty; _y++) tiles[l][_x][_y] = st;
									else for(int _y = ty; _y <= lastTy; _y++) tiles[l][_x][_y] = st;
								}
							}
							rect = false;
						}
						else
						{
							rect = true;
						}
					}
					else rect = true;
					break;
				case 2:
					break;
				case 3:
					FloodFill(tx, ty);
					break;
			}
			lastTx = tx;
			lastTy = ty;
			lastTool = tool;
		}

		void OnBClick(int b)
		{
			if(b == 0)
			{
				if(stiles[0] > 0)
				{
					for(int i = 0; i < 19; i++) stiles[i]--;
				}
			}
			else if(b == 20)
			{
				if(stiles[18] < numberOfTiles - 1)
				{
					for(int i = 0; i < 19; i++) stiles[i]++;
				}
			}
			else if(b == 21) l = 0;
			else if(b == 22) l = 1;
			else if(b == 23) l = 2;
			else if(b > 23) tool = b - 24;
			else st = stiles[b - 1];
		}

		TilesMode()
		{
			bg = load_bitmap("./mapedgfx/bg3.bmp", 0);
			for(int i = 0; i < 21; i++)
			{
				buttons[i][0] = 6 + i * 30;
				buttons[i][1] = 4;
				buttons[i][2] = 6 + 29 + i * 30;
				buttons[i][3] = 4 + 29;
			}
			buttons[21][0] = 10;
			buttons[21][1] = 39;
			buttons[21][2] = 103;
			buttons[21][3] = 55;
			buttons[22][0] = 135;
			buttons[22][1] = 37;
			buttons[22][2] = 260;
			buttons[22][3] = 55;
			buttons[23][0] = 306;
			buttons[23][1] = 39;
			buttons[23][2] = 376;
			buttons[23][3] = 56;
			buttons[24][0] = 415;
			buttons[24][1] = 40;
			buttons[24][2] = 442;
			buttons[24][3] = 54;
			buttons[25][0] = 444;
			buttons[25][1] = 40;
			buttons[25][2] = 472;
			buttons[25][3] = 54;
			buttons[26][0] = 474;
			buttons[26][1] = 40;
			buttons[26][2] = 503;
			buttons[26][3] = 54;
			buttons[27][0] = 505;
			buttons[27][1] = 40;
			buttons[27][2] = 555;
			buttons[27][3] = 54;
			l = 0;
			st = 0;
			tool = 0;
			rect = false;
			for(int i = 0; i < 19; i++) stiles[i] = i;
		}
};

class BlocksMode : public EditMode
{
	public:
		int action;
		int block;
		int rx, ry;
		bool r;

		void Draw()
		{
			const int powers[8] = {1, 2, 4, 8, 16, 32, 64, 128};
			EditMode::Draw();
			DrawButton(10, 0xFF00);
			if(action == 0) DrawButton(0);
			if(action == 1) DrawButton(1);
			if(action == 2) DrawButton(10);
			for(int i = 2; i < 10; i++)
			{
				if(block & powers[9 - i]) DrawButton(i);
			}
			for(int y = 0; y < 28; y++)
			{
				for(int x = 0; x < 42; x++)
				{
					if(blocks[x][y] == block) rect(db, x * 15, y * 15, 14 + x * 15, 14 + y * 15, 0);
				}
			}
		}

		void OnMClick(int _x, int _y)
		{
			if(action == 0)
			{
				blocks[_x / 15][_y / 15] = block;
			}
			if(action == 1)
			{
				for(int y = 0; y < 28; y++)
				{
					for(int x = 0; x < 42; x++)
					{
						if(x % 2 != (_x / 15) % 2) continue;
						if(y % 2 != (_y / 15) % 2) continue;
						if(tiles[1][x / 2][y / 2] == tiles[1][_x / 30][_y / 30]) blocks[x][y] = block;
					}
				}
			}
			if(action == 2)
			{
				if(!r)
				{
					rx = _x / 15;
					ry = _y / 15;
					r = true;
				}
				else
				{
					int X = _x / 15;
					int Y = _y / 15;
					if(X < rx)
					{
						int temp = X;
						X = rx;
						rx = temp;
					}
					if(Y < ry)
					{
						int temp = Y;
						Y = ry;
						ry = temp;
					}
					for(int x = rx; x <= X; x++)
					{
						for(int y = ry; y <= Y; y++)
						{
							blocks[x][y] = block;
						}
					}
					r = false;
				}
			}
		}

		void OnBClick(int b)
		{
			const int powers[8] = {1, 2, 4, 8, 16, 32, 64, 128};
			if(b < 2) action = b;
			if(b == 10)
			{
				action = 2;
				r = false;
			}
			if((b > 2) && (b < 10))
			{
				if(block & powers[9 - b])
				{
					block = (block & (~powers[9 - b]));
				}
				else
				{
					block = block | powers[9 - b];
				}
			}
		}

		BlocksMode()
		{
			buttons[0][0] = 5;
			buttons[0][1] = 8;
			buttons[0][2] = 143;
			buttons[0][3] = 24;
			buttons[1][0] = 158;
			buttons[1][1] = 8;
			buttons[1][2] = 403;
			buttons[1][3] = 24;
			for(int i = 2; i < 10; i++)
			{
				buttons[i][0] = 87 + 6 * (i - 2);
				buttons[i][1] = 41;
				buttons[i][2] = 87 + 5 + 6 * (i - 2);
				buttons[i][3] = 46;
			}
			buttons[10][0] = 423;
			buttons[10][1] = 8;
			buttons[10][2] = 423 + 8 * 4 + 2;
			buttons[10][3] = 18;
			buttons[10][4] = false;
			text[10] = "Rect";
			block = 0;
			action = 0;
			bg = load_bitmap("mapedgfx/bg1.bmp", 0);
		}
};

class MapInfoMode : public EditMode
{
	public:
		void OnTextChange(int b)
		{
			name = text[0];
			exits[0] = text[1];
			exits[1] = text[2];
			exits[2] = text[3];
			exits[3] = text[4];
		}

		void OnSelectMode()
		{
			text[0] = name;
			text[1] = exits[0];
			text[2] = exits[1];
			text[3] = exits[2];
			text[4] = exits[3];
		}

		MapInfoMode()
		{
			buttons[0][0] = 64;
			buttons[0][1] = 4;
			buttons[0][2] = 634;
			buttons[0][3] = 12;
			buttons[1][0] = 64;
			buttons[1][1] = 14;
			buttons[1][2] = 634;
			buttons[1][3] = 23;
			buttons[2][0] = 64;
			buttons[2][1] = 25;
			buttons[2][2] = 634;
			buttons[2][3] = 34;
			buttons[3][0] = 64;
			buttons[3][1] = 36;
			buttons[3][2] = 634;
			buttons[3][3] = 45;
			buttons[4][0] = 64;
			buttons[4][1] = 47;
			buttons[4][2] = 634;
			buttons[4][3] = 56;
			buttons[0][4] = buttons[1][4] = buttons[2][4] = buttons[3][4] = buttons[4][4] = true;
			bg = load_bitmap("./mapedgfx/bg4.bmp", 0);

		}
};

class EntityMode : public EditMode
{
	public:
		std::list<MapEntity>::iterator entityIt;
		std::list<std::pair<std::string, std::string> >::iterator parameterIt;
		int tool;
		bool alignToGrid;

		void Draw()
		{
			EditMode::Draw();
			DrawButton(0, 0xFF00);
			DrawButton(1, 0xFF00);
			DrawButton(2, 0xFF00);
			DrawButton(4, 0xFF00);
			DrawButton(6, 0xFF00);
			DrawButton(7, 0xFF00);
			DrawButton(8, 0xFF00);
			DrawButton(9, 0xFF00);
			DrawButton(11, 0xFF00);
			DrawButton(12, 0xFF00);
			DrawButton(13, 0xFF00);
			DrawButton(15, 0xFF00);
			DrawButton(16, 0xFF00);
			DrawButton(17, 0xFF00);
			DrawButton(18, 0xFF00);
			DrawButton(19, 0xFF00);
			DrawButton(21, 0xFF00);
			if(focus != 0) DrawButton(focus);
			DrawButton(tool);
			if(alignToGrid) DrawButton(20);
			for(std::list<MapEntity>::iterator i = entities.begin(); i != entities.end(); i++)
			{
				int color = 0;
				if(i == entityIt) color = 0xFF0000;
				int x = 0xB16B00B5;
				int y = 0xB16B00B5;
				for(std::list<std::pair<std::string, std::string> >::iterator j = i->parameters.begin(); j != i->parameters.end(); j++)
				{
					if(j->first == "x") x = std::atoi(j->second.c_str());
					if(j->first == "y") y = std::atoi(j->second.c_str());
				}
				if(x == 0xB16B00B5) continue;
				if(y == 0xB16B00B5) continue;
				rect(db, x, y, x + 29, y + 29, color);
				textprintf_ex(db, font, x, y + 15 - 4, color, -1, "%s", MozDong(i->name).c_str());
			}
		}

		void OnMClick(int _x, int _y)
		{
			if(tool == 2)
			{
				std::list<MapEntity>::iterator i = entityIt;
				std::list<std::pair<std::string, std::string> >::iterator itx = i->parameters.end();
				std::list<std::pair<std::string, std::string> >::iterator ity = i->parameters.end();
				for(std::list<std::pair<std::string, std::string> >::iterator j = i->parameters.begin(); j != i->parameters.end(); j++)
				{
					if(j->first == "x")
					{
						itx = j;
					}
					if(j->first == "y")
					{
						ity = j;
					}
				}
				if(itx == i->parameters.end())
				{
					std::pair<std::string, std::string> p;
					p.first = "x";
					p.second = "0";
					i->parameters.insert(parameterIt, p);
				}
				if(ity == i->parameters.end())
				{
					std::pair<std::string, std::string> p;
					p.first = "y";
					p.second = "0";
					i->parameters.insert(parameterIt, p);
				}
				for(std::list<std::pair<std::string, std::string> >::iterator j = i->parameters.begin(); j != i->parameters.end(); j++)
				{
					if(j->first == "x")
					{
						itx = j;
					}
					if(j->first == "y")
					{
						ity = j;
					}
				}
				if(itx != i->parameters.end())
				{
					if(ity != i->parameters.end())
					{
						if(alignToGrid)
						{
							itx->second = itoa(_x - (_x % 15));
							ity->second = itoa(_y - (_y % 15));
						}
						else
						{
							itx->second = itoa(_x - 15);
							ity->second = itoa(_y - 15);
						}
					}
				}
			}

			for(std::list<MapEntity>::iterator i = entities.begin(); i != entities.end(); i++)
			{
				int x = 0xB16B00B5;
				int y = 0xB16B00B5;
				std::list<std::pair<std::string, std::string> >::iterator itx, ity;
				for(std::list<std::pair<std::string, std::string> >::iterator j = i->parameters.begin(); j != i->parameters.end(); j++)
				{
					if(j->first == "x")
					{
						x = std::atoi(j->second.c_str());
						itx = j;
					}
					if(j->first == "y")
					{
						y = std::atoi(j->second.c_str());
						ity = j;
					}
				}
				if(x == 0xB16B00B5) continue;
				if(y == 0xB16B00B5) continue;
				if(_x > x)
				{
					if(_y > y)
					{
						if(_x < x + 30)
						{
							if(_y < y + 30)
							{
								switch(tool)
								{
									case 0:
										if(alignToGrid)
										{
											itx->second = itoa(_x - (_x % 15));
											ity->second = itoa(_y - (_y % 15));
										}
										else
										{
											itx->second = itoa(_x - 15);
											ity->second = itoa(_y - 15);
										}
										break;
									case 1:
										entityIt = i;
										break;
								}
							}
						}
					}
				}
			}
			if(entities.size() != 0)
			{
				text[4] = entityIt->name;
				text[6] = itoa(entityIt->respawnTime);
				parameterIt = entityIt->parameters.begin();
				if(entityIt->parameters.size() != 0)
				{
					text[11] = parameterIt->first;
					text[15] = parameterIt->second;
				}
			}
		}

		EntityMode()
		{
			bg = create_bitmap(640, 420);
			clear_to_color(bg, 0x008800);
			buttons[0][0] = 8;	// Move
			buttons[0][1] = 8;
			buttons[0][2] = 42;
			buttons[0][3] = 18;
			buttons[0][4] = false;
			text[0] = "Move";
			buttons[1][0] = 52; // Select
			buttons[1][1] = 8;
			buttons[1][2] = 102;
			buttons[1][3] = 18;
			buttons[1][4] = false;
			text[1] = "Select";
			buttons[2][0] = 104; // Place
			buttons[2][1] = 8;
			buttons[2][2] = 146;
			buttons[2][3] = 18;
			buttons[2][4] = false;
			text[2] = "Place";
			buttons[3][0] = 8; // Name:
			buttons[3][1] = 20;
			buttons[3][2] = 50;
			buttons[3][3] = 30;
			buttons[3][4] = false;
			text[3] = "Name:";
			buttons[4][0] = 52; // [name]
			buttons[4][1] = 20;
			buttons[4][2] = 150;
			buttons[4][3] = 30;
			buttons[4][4] = true;
			text[4] = "";
			buttons[5][0] = 152; // Resp.time:
			buttons[5][1] = 20;
			buttons[5][2] = 234;
			buttons[5][3] = 30;
			buttons[5][4] = false;
			text[5] = "Resp.time:";
			buttons[6][0] = 236; // [respawn time]
			buttons[6][1] = 20;
			buttons[6][2] = 278;
			buttons[6][3] = 30;
			buttons[6][4] = 2;
			text[6] = "";
			buttons[7][0] = 280; // Prev.entity
			buttons[7][1] = 20;
			buttons[7][2] = 370;
			buttons[7][3] = 30;
			buttons[7][4] = false;
			text[7] = "Prev.entity";
			buttons[8][0] = 372; // Next entity
			buttons[8][1] = 20;
			buttons[8][2] = 462;
			buttons[8][3] = 30;
			buttons[8][4] = false;
			text[8] = "Next entity";
			buttons[9][0] = 464; // New entity
			buttons[9][1] = 20;
			buttons[9][2] = 546;
			buttons[9][3] = 30;
			buttons[9][4] = false;
			text[9] = "New entity";
			buttons[10][0] = 8; // Parameter:
			buttons[10][1] = 32;
			buttons[10][2] = 90;
			buttons[10][3] = 42;
			buttons[10][4] = false;
			text[10] = "Parameter:";
			buttons[11][0] = 92; // [Parameter]
			buttons[11][1] = 32;
			buttons[11][2] = 182;
			buttons[11][3] = 42;
			buttons[11][4] = true;
			text[11] = "";
			buttons[12][0] = 184; // Prev.parameter
			buttons[12][1] = 32;
			buttons[12][2] = 184+114;
			buttons[12][3] = 42;
			buttons[12][4] = false;
			text[12] = "Prev.parameter";
			buttons[13][0] = 184+114+2; // Next parameter
			buttons[13][1] = 32;
			buttons[13][2] = 184+114+2+114;
			buttons[13][3] = 42;
			buttons[13][4] = false;
			text[13] = "Next parameter";
			buttons[14][0] = 8; // Value:
			buttons[14][1] = 44;
			buttons[14][2] = 50;
			buttons[14][3] = 54;
			buttons[14][4] = false;
			text[14] = "Value:";
			buttons[15][0] = 52; // [value]
			buttons[15][1] = 44;
			buttons[15][2] = 52 + 320 + 2;
			buttons[15][3] = 54;
			buttons[15][4] = true;
			text[15] = "";
			buttons[16][0] = 52 + 320 + 2 + 2; // Add
			buttons[16][1] = 44;
			buttons[16][2] = 52 + 320 + 2 + 2 + 24 + 2;
			buttons[16][3] = 54;
			buttons[16][4] = false;
			text[16] = "Add";
			buttons[17][0] = 52 + 320 + 2 + 2 + 24 + 2 + 2; // Set
			buttons[17][1] = 44;
			buttons[17][2] = 52 + 320 + 2 + 2 + 24 + 2 + 2 + 24 + 2;
			buttons[17][3] = 54;
			buttons[17][4] = false;
			text[17] = "Set";
			buttons[18][0] = 52 + 320 + 2 + 2 + 24 + 2 + 2 + 24 + 2; // Remove
			buttons[18][1] = 44;
			buttons[18][2] = 52 + 320 + 2 + 2 + 24 + 2 + 2 + 24 + 2 + 2 + 48;
			buttons[18][3] = 54;
			buttons[18][4] = false;
			text[18] = "Remove";
			buttons[19][0] = 546 + 2; // Remove entity
			buttons[19][1] = 20;
			buttons[19][2] = 546 + 2 + 88 + 2;
			buttons[19][3] = 30;
			buttons[19][4] = false;
			text[19] = "Remove ent.";
			buttons[20][0] = 300; // Align to grid:
			buttons[20][1] = 8;
			buttons[20][2] = 406;
			buttons[20][3] = 18;
			buttons[20][4] = false;
			text[20] = "Align to grid";
			buttons[21][0] = 546 + 2; // Copy entity
			buttons[21][1] = 32;
			buttons[21][2] = 546 + 2 + 88 + 2;
			buttons[21][3] = 42;
			buttons[21][4] = false;
			text[21] = "Copy entity";
			tool = 0;
			alignToGrid = false;
		}

		void OnSelectMode()
		{
			entityIt = entities.begin();
			if(entities.size() != 0)
			{
				text[4] = entityIt->name;
				text[6] = itoa(entityIt->respawnTime);
				parameterIt = entityIt->parameters.begin();
				if(entityIt->parameters.size() != 0)
				{
					text[11] = parameterIt->first;
					text[15] = parameterIt->second;
				}
				else
				{
					text[11] = "";
					text[15] = "";
				}
			}
			else
			{
				text[4] = "";
				text[6] = "";
				text[11] = "";
				text[15] = "";
			}
		}

		void OnTextChange(int b)
		{
			if(b == 4)
			{
				if(entities.size() != 0) entityIt->name = text[4];
			}
			if(b == 6)
			{
				if(entities.size() != 0) entityIt->respawnTime = std::atoi(text[6].c_str());
			}
		}

		void OnBClick(int b)
		{
			switch(b)
			{
				case 0:
				case 1:
				case 2:
					tool = b;
					break;
				case 7:
					if(entityIt != entities.begin()) entityIt--;
					if(entities.size() != 0)
					{
						text[4] = entityIt->name;
						text[6] = itoa(entityIt->respawnTime);
						parameterIt = entityIt->parameters.begin();
						if(entityIt->parameters.size() != 0)
						{
							text[11] = parameterIt->first;
							text[15] = parameterIt->second;
						}
						else
						{
							text[11] = "";
							text[15] = "";
						}
					}
					else
					{
						text[4] = "";
						text[6] = "";
						text[11] = "";
						text[15] = "";
					}
					break;
				case 8:
					entityIt++;
					if(entityIt == entities.end()) entityIt--;
					if(entities.size() != 0)
					{
						text[4] = entityIt->name;
						text[6] = itoa(entityIt->respawnTime);
						parameterIt = entityIt->parameters.begin();
						if(entityIt->parameters.size() != 0)
						{
							text[11] = parameterIt->first;
							text[15] = parameterIt->second;
						}
						else
						{
							text[11] = "";
							text[15] = "";
						}
					}
					else
					{
						text[4] = "";
						text[6] = "";
						text[11] = "";
						text[15] = "";
					}
					break;
				case 12:
					if(entities.size() != 0)
					{
						if(parameterIt != entityIt->parameters.begin()) parameterIt--;
						if(entityIt->parameters.size() != 0)
						{
							text[11] = parameterIt->first;
							text[15] = parameterIt->second;
						}
					}
					break;
				case 13:
					if(entities.size() != 0)
					{
						parameterIt++;
						if(parameterIt == entityIt->parameters.end()) parameterIt--;
						if(entityIt->parameters.size() != 0)
						{
							text[11] = parameterIt->first;
							text[15] = parameterIt->second;
						}
					}
					break;
				case 16:
					if(entities.size() != 0)
					{
						std::pair<std::string, std::string> p;
						p.first = text[11];
						p.second = text[15];
						entityIt->parameters.insert(parameterIt, p);
					}
					break;
				case 17:
					if(entities.size() != 0)
					{
						if(entityIt->parameters.size() != 0)
						{
							parameterIt->first = text[11];
							parameterIt->second = text[15];
						}
					}
					break;
				case 18:
					if(entities.size() != 0)
					{
						if(entityIt->parameters.size() != 0)
						{
							std::list<std::pair<std::string, std::string> >::iterator npit = entityIt->parameters.erase(parameterIt);
							if(npit == entityIt->parameters.end()) npit = entityIt->parameters.begin();
							parameterIt = npit;
							if(entityIt->parameters.size() > 0)
							{
								text[11] = parameterIt->first;
								text[15] = parameterIt->second;
							}
							else
							{
								text[11] = "";
								text[15] = "";
							}
						}
					}
					break;
				case 9:
					if(true)
					{
						MapEntity me;
						me.name = "";
						text[11] = "";
						text[15] = "";
						me.respawnTime = 0;
						text[6] = "0";
						text[4] = "";
						entityIt = entities.insert(entityIt, me);
						parameterIt = entityIt->parameters.begin();
					}
					break;
				case 19:
					if(entities.size() > 0)
					{
						std::list<MapEntity>::iterator neit = entities.erase(entityIt);
						if(neit == entities.end())
						{
							neit = entities.begin();
						}
						entityIt = neit;
						if(entities.size() > 0)
						{
							text[4] = entityIt->name;
							text[6] = itoa(entityIt->respawnTime);
							parameterIt = entityIt->parameters.begin();
							if(entityIt->parameters.size() != 0)
							{
								text[11] = parameterIt->first;
								text[15] = parameterIt->second;
							}
							else
							{
								text[11] = "";
								text[15] = "";
							}
						}
						else
						{
							text[4] = "";
							text[6] = "";
							text[11] = "";
							text[15] = "";
						}
					}
					break;
				case 20:
					if(alignToGrid) alignToGrid = false;
					else alignToGrid = true;
					break;
				case 21:
					if(entities.size() != 0)
					{
						entityIt = entities.insert(entityIt, *entityIt);
					}
					break;
				default:
					break;
			}
		}
};

bool exist(std::string f)
{
	return (file_exists(f.c_str(), 0, 0) != 0);
}

int main()
{
	allegro_init();
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
	install_mouse();
	install_keyboard();
	install_timer();
	if(exists("tiles/tileset.tls") != 0) LoadTileSet("tiles/tileset.tls");
	else
	{
		LoadTileSet(GetFile("Select tileset file:", "tls", "tiles/"));
	}
	if(exists("maps/empty.map") != 0) fileName = "maps/empty.map";
	else fileName = GetFile("Select map file to load:", "map", "maps/");
	LoadMap();
	EditMode *editModes[12];
	for(int i = 0; i < 12; i++) editModes[i] = 0;
	editModes[0] = new FileMode;
	editModes[1] = new TilesMode;
	editModes[2] = new BlocksMode;
	editModes[3] = new MapInfoMode;
	editModes[4] = new EntityMode;
	int mode = 0;
	bool mb = false;
	db = create_bitmap(640, 480);
	show_os_cursor(MOUSE_CURSOR_ARROW);
	while(!key[KEY_ESC])
	{

		std::string title;
		int titleStart = 0;
		if(fileName.length() > 32)
		{
			title.append("...");
			title.append(fileName.substr(fileName.length() - 32));
		}
		else title = fileName;
		set_window_title(title.c_str());

		clear(db);
		int m = 0;
		bool editModeKey = false;
		int _key = 0;
		if(keypressed()) _key = readkey();
		for(int i = KEY_F1; i < KEY_F12; i++)
		{
			if((_key >> 8 == i) && (editModes[m] != 0))
			{
				mode = m;
				editModeKey = true;
			}
			m++;
		}
		if(!editModeKey) editModes[mode]->OnKey(_key);
		else editModes[mode]->OnSelectMode();
		if(mouse_b & 1)
		{
			if((!mb) || (mouse_b & 2))
			{
				mb = true;
				editModes[mode]->OnClick(mouse_x, mouse_y);
			}
		}
		else mb = false;
		DrawMap();
		editModes[mode]->Draw();
		blit(db, screen, 0, 0, 0, 0, 640, 480);
	}
	return 0;
}
END_OF_MAIN();
