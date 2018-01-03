#include <allegro.h>
#include "Keys.h"

KeyState aKey, sKey, xKey, cKey, f11Key, leftKey, rightKey, upKey, downKey;

bool trogStartKey;

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

enum {
	kc_a = 0,
	kc_s,
	kc_x,
	kc_c,
	kc_f11,
	kc_left,
	kc_right,
	kc_up,
	kc_down
};

int keyCodePause;
int joyCodePause;

int keyCodes[9];
int joyCodes[4];
int joystickNumber, joystickStick;

void LoadControls()
{
	#define GETKC(a, b) keyCodes[kc_ ## a] = get_config_int("keyboard", #a, b);
	GETKC(a, KEY_A);
	GETKC(s, KEY_S);
	GETKC(x, KEY_X);
	GETKC(c, KEY_C);
	GETKC(f11, KEY_F11);
	GETKC(left, KEY_LEFT);
	GETKC(right, KEY_RIGHT);
	GETKC(down, KEY_DOWN);
	GETKC(up, KEY_UP);
	
	keyCodePause = get_config_int("keyboard", "pause", KEY_ESC);
	
	joystickNumber = get_config_int("joystick", "number", 0);
	joystickStick = get_config_int("joystick", "stick", 0);
	#define GETJC(a, b) joyCodes[kc_ ## a] = get_config_int("joystick", #a, b);
	GETJC(a, 0);
	GETJC(s, 1);
	GETJC(x, 2);
	GETJC(c, 3);
	
	joyCodePause = get_config_int("joystick", "pause", 4);
}

void UpdateKeys()
{
	poll_joystick();
	
	trogStartKey = key[keyCodePause] || ((joystickNumber < num_joysticks) && (joyCodePause < joy[joystickNumber].num_buttons) && joy[joystickNumber].button[joyCodePause].b);
	
	const int kcToAxis[] = 
	{
		0, //a
		0, //s
		0, //x
		0, //c
		0, //f11
		0, //left
		0, //right
		1, //up
		1  //down
	};
	
	const float kcToCoeff[] =
	{
		0, //a
		0, //s
		0, //x
		0, //c
		0, //f11
		-1.0, //left
		1.0, //right
		-1.0, //up
		1.0 //down
	};
	
	#define READC(a) key[keyCodes[kc_ ## a]] \
	|| ((kc_ ## a <= kc_c) && (joystickNumber < num_joysticks) && (joyCodes[kc_ ## a] < joy[joystickNumber].num_buttons) && joy[joystickNumber].button[joyCodes[kc_ ## a]].b) \
	|| ((kc_ ## a >= kc_left) && (joystickNumber < num_joysticks) && (joystickStick < joy[joystickNumber].num_sticks) && (joy[joystickNumber].stick[joystickStick].num_axis >= 2) && (joy[joystickNumber].stick[joystickStick].axis[kcToAxis[kc_ ## a]].pos * kcToCoeff[kc_ ## a] > 0.75))
	
	UpdateKey(READC(a), aKey);
	UpdateKey(READC(s), sKey);
	UpdateKey(READC(x), xKey);
	UpdateKey(READC(c), cKey);
	UpdateKey(READC(f11), f11Key);
	UpdateKey(READC(left), leftKey);
	UpdateKey(READC(right), rightKey);
	UpdateKey(READC(up), upKey);
	UpdateKey(READC(down), downKey);
}