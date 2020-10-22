#pragma once
#include "Quarantine.hpp"

enum keys_t {
	BUTTON_A = 1,
	BUTTON_B = 2,
	BUTTON_X = 3,
	BUTTON_Y = 4,
	BUTTON_LSHLDR = 5,
	BUTTON_RSHLDR = 6,
	BUTTON_START = 14,
	BUTTON_BACK = 15,
	BUTTON_LSTICK = 16,
	BUTTON_RSTICK = 17,
	BUTTON_LTRIG = 18,
	BUTTON_RTRIG = 19,
	DPAD_UP = 22,
	DPAD_DOWN = 23,
	DPAD_LEFT = 24,
	DPAD_RIGHT = 25,
};

enum eMenus {
	MenuBase,
	Cheats,
	ESP,
	Aimbot,
	AntiAim,
	Names,
	Stats,
	MenuSettings
};

enum eKeyboardType {
	KB_NONE,
	KB_EDITVALUE
};

extern uint32_t stats_list;

void SelectMenu(int menuID);

class Menu {
public:
	Menu();
	virtual ~Menu();

	bool isMenuOpen;
	bool KeyPressed[32];
	int CurrentMenu;
	int CurrentOption;
	int LastMenu[32];
	int LastOption[32];
	int MaxScroll;
	int keyboard_type;

	virtual bool MenuOpened();
	virtual void ResetMaxScroll();
	virtual int GetMaxScroll();
	virtual void RenderMenu();
	virtual void RunControls();

	virtual void AddTitle(const char * title);
	virtual void AddOption(const char * opt, void(*func)());
	virtual void AddOption(const char * opt, void(*func)(int value), int value);
	virtual void AddBool(const char * opt, bool * value);
	virtual void AddBool(const char * opt, bool * value, void(*func)(bool value));
	virtual void AddSlider(const char * opt, float * value, float min, float max, float scale, bool useShader);
	virtual void AddSlider(const char * opt, float * value, float min, float max, float scale, bool useShader, void(*func)(float val));
	virtual void AddStringSlider(const char * opt, int * value, int min, int max, char ** options);
	virtual void AddStringSlider(const char * opt, int * value, int min, int max, char ** options, void(*func)(int iVal));
};

extern Menu * menu;

