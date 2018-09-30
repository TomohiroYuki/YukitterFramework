#pragma once


#include <dinput.h>
#include <Xinput.h>
#include <list>
#include "source\math\Vector2D.h"


using namespace Yukitter;


//Xboxコン振動制御
class Vibrate {
public:
	Vibrate(int frame,int stronger):
		vib_frame(frame),
		stronger(stronger),
		current_vib_frame(0)
	{}
private:
	const int vib_frame;
	
	int current_vib_frame;
	
public:
	int stronger;
	bool Update()
	{
		if (++current_vib_frame > vib_frame)
			return true;
		return false;
	}
	
};


class InputBrain {
	// Singleton
	InputBrain() = default;					
	~InputBrain() = default;	
public:
	// Singleton
	InputBrain(const InputBrain&) = delete;				
	InputBrain& operator=(const InputBrain&) = delete;	
	InputBrain(InputBrain&&) = delete;					
	InputBrain& operator=(InputBrain&&) = delete;		

private:
	enum KEY_STATE{NONE,KEY_RELEASE,KEY_PUSH_STAY,KEY_PUSH_FIRST};
	enum { INPUT_BUFFER_SIZE = 256 };			

	LPDIRECTINPUT8			d_input;			
	LPDIRECTINPUTDEVICE8	key_device;			
	LPDIRECTINPUTDEVICE8	mouse_device;		

	BYTE key_input[INPUT_BUFFER_SIZE];			
	BYTE key_input_preview[INPUT_BUFFER_SIZE];	

	unsigned int xcon_input;					
	unsigned int xcon_input_preview;


	Vector2D left_stick_input;
	Vector2D left_stick_input_preview;
	Vector2D right_stick_input;
	Vector2D right_stick_input_preview;

	DIMOUSESTATE mouse_input;					
	DIMOUSESTATE mouse_input_preview;			
	HWND		hwnd;

	std::list<Vibrate> vib_list;
	HRESULT initKey();

public:

	HRESULT Initialize(HWND hwnd);
	HRESULT UpData();
	HRESULT free();

	//	mouse=========================================================================

	LONG GetMouseWheelDelta();

	Vector2D GetMouseTranslationOnViewport();


	//	Keyboard====================================================================
	bool	KeyPush(int code);
	bool	KeyTrigger(int code);//押した瞬間
	bool	KeyRelease(int code);
	BYTE	KeyPushTime(int code);
	int		KeyGet(int code);

	Vector2D GetKeyboardWASD()
	{
		Vector2D ret{};
		if (KeyPush(DIK_W))
			ret.y = 1;
		if (KeyPush(DIK_S))
			ret.y = -1;
		if (KeyPush(DIK_A))
			ret.x = -1;
		if (KeyPush(DIK_D))
			ret.x = 1;
		return ret;
	}

	//==============================================================================


	//	XInput (XBox360 controller )================================================
	



	//複数コントローラ対応はまた今度！！！！！！！
	int		XConGet(int code);
	void	XConVib(unsigned int frame, unsigned int stronger);//バイブレーションの長さ(uint)と強さ(uint)0~65535
	bool	XConPush(int code);
	bool	XConTrigger(int code);//押した瞬間
	bool	XConRelease(int code);
	void	VibrateUpdate();
	//void	GetXConStickState();
	
	Vector2D GetXConRightStick();
	Vector2D GetXConLeftStick();
	//==============================================================================

	

										// Singleton
	static InputBrain* getInstance() {
		static InputBrain inst;			// privateなコンストラクタを呼び出す
		return &inst;
	}

};





#define INPUT (InputBrain::getInstance() )
#define KEY_TRIGGER	3
#define KEY_STAY	2
#define KEY_RELEASE_	1