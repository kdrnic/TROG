#ifndef KEYS_H
#define KEYS_H

enum KeyState
{
	KeyUnpressed,
	KeyDown,
	KeyPressed,
	KeyUp
};

extern bool trogStartKey;

extern KeyState aKey, sKey, xKey, cKey, f11Key, leftKey, rightKey, upKey, downKey;

void LoadControls();
void SaveControls();

void UpdateKey(bool key, KeyState &_key);
void UpdateKeys();

#endif