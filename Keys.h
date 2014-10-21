#ifndef KEYS_H
#define KEYS_H

#include <allegro.h>

enum KeyState
{
	KeyUnpressed,
	KeyDown,
	KeyPressed,
	KeyUp
};

extern KeyState aKey, sKey, xKey, cKey, f11Key, leftKey, rightKey, upKey, downKey;

void UpdateKey(bool key, KeyState &_key);
void UpdateKeys();

#endif