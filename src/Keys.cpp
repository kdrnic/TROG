#include "Keys.h"

KeyState aKey, sKey, xKey, cKey, f11Key, leftKey, rightKey, upKey, downKey;

void UpdateKey(bool key, KeyState &_key)
{
	if(key)
	{
		if((_key == KeyUnpressed) || (key == KeyUp)) _key = KeyDown;
		else _key = KeyPressed;
	}
	if(!key)
	{
		if(_key == KeyPressed) _key = KeyUp;
		else _key = KeyUnpressed;
	}
}

void UpdateKeys()
{
	UpdateKey(key[KEY_A], aKey);
	UpdateKey(key[KEY_S], sKey);
	UpdateKey(key[KEY_X], xKey);
	UpdateKey(key[KEY_C], cKey);
	UpdateKey(key[KEY_F11], f11Key);
	UpdateKey(key[KEY_LEFT], leftKey);
	UpdateKey(key[KEY_RIGHT], rightKey);
	UpdateKey(key[KEY_UP], upKey);
	UpdateKey(key[KEY_DOWN], downKey);
}