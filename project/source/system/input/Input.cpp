#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>
#include "source\system\input\Input.h"
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"XInput9_1_0.lib")

#include "source\math\Vector.h"

HRESULT InputBrain::Initialize(HWND hWnd)
{
	d_input = NULL;
	key_device = NULL;
	mouse_device = NULL;

	ZeroMemory(&key_input, sizeof(BYTE)*INPUT_BUFFER_SIZE);
	ZeroMemory(&key_input_preview, sizeof(BYTE)*INPUT_BUFFER_SIZE);
	ZeroMemory(&mouse_input, sizeof(DIMOUSESTATE2));
	ZeroMemory(&mouse_input_preview, sizeof(DIMOUSESTATE2));

	hwnd = hWnd;
	//InputBrainオブジェクトの作成
	if (FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&d_input, NULL)))
		return E_FAIL;

	//キーボードの初期化処理
	if (FAILED(initKey()))
		return E_FAIL;

	return S_OK;
}

HRESULT InputBrain::initKey()
{
	//デバイスオブジェクトを作成
	if (FAILED(d_input->CreateDevice(GUID_SysKeyboard, &key_device, NULL)))
		return E_FAIL;

	if (FAILED(d_input->CreateDevice(GUID_SysMouse, &mouse_device, NULL)))
		return E_FAIL;

	//データ形式を設定
	if (FAILED(key_device->SetDataFormat(&c_dfDIKeyboard)))
		return E_FAIL;
	//データ形式を設定
	if (FAILED(mouse_device->SetDataFormat(&c_dfDIMouse)))
		return E_FAIL;

	//モードを設定
	if (FAILED(key_device->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
		return E_FAIL;

	//入力制御開始
	key_device->Acquire();

	return S_OK;
}

HRESULT InputBrain::UpData()
{
	//キーボードの更新
	HRESULT hresult = key_device->Acquire();
	hresult = mouse_device->Acquire();

	//x-boxコンが認知できればxconデータを更新
	XINPUT_STATE x_in_state;
	if (XInputGetState(0, &x_in_state) != ERROR_DEVICE_NOT_CONNECTED)
	{
		memcpy(&xcon_input_preview, &xcon_input, sizeof(unsigned int));
		/*memcpy(&left_stick_input_preview, &left_stick_input, sizeof(VECTORII));
		memcpy(&right_stick_input_preview, &right_stick_input, sizeof(VECTORII));*/


		xcon_input = 0;
		xcon_input |= x_in_state.Gamepad.wButtons;
		//xcon_input |= x_in_state.Gamepad.bLeftTrigger;
		//xcon_input |= x_in_state.Gamepad.bRightTrigger;
		/*xcon_input |= x_in_state.Gamepad.sThumbLX;
		xcon_input |= x_in_state.Gamepad.sThumbLY;
		xcon_input |= x_in_state.Gamepad.sThumbRX;
		xcon_input |= x_in_state.Gamepad.sThumbRY;*/
		left_stick_input.x = static_cast<float>(x_in_state.Gamepad.sThumbLX);
		left_stick_input.y = static_cast<float>(x_in_state.Gamepad.sThumbLY);
		right_stick_input.x = static_cast<float>(x_in_state.Gamepad.sThumbRX);
		right_stick_input.y = static_cast<float>(x_in_state.Gamepad.sThumbRY);

		VibrateUpdate();
	}


	if ((hresult == DI_OK) || (hresult == S_FALSE))
	{
		//前回のキー入力情報を退避
		memcpy(key_input_preview, key_input, sizeof(BYTE)*INPUT_BUFFER_SIZE);

		memcpy(&mouse_input_preview, &mouse_input, sizeof(DIMOUSESTATE));
		//状態ワーク
		BYTE tKeyInputWork[INPUT_BUFFER_SIZE];
		key_device->GetDeviceState(sizeof(key_input), &tKeyInputWork);
		mouse_device->GetDeviceState(sizeof(DIMOUSESTATE), &mouse_input);

		//mouse_device->GetDeviceState(sizeof(mouse_input), &mouse_input);
		for (int ii = 0; ii < INPUT_BUFFER_SIZE; ii++)
		{
			if (tKeyInputWork[ii])
			{
				//押されているカウンタUP
				if (key_input[ii] < 255) {
					key_input[ii]++;
				}
				else {
					key_input[ii] = 255;
				}
			}
			else {
				//0固定
				key_input[ii] = 0;
			}
		}
	}
	return S_OK;
}

bool InputBrain::KeyPush(int code)
{
	if (key_input[code])
		return TRUE;

	return FALSE;
}

bool InputBrain::KeyTrigger(int code)
{
	//前回離していて現在押している
	//	if( !(key_input_preview[code] & PUSH_INPUT) && (key_input[code] & PUSH_INPUT) )
	if (!key_input_preview[code] && key_input[code])
		return TRUE;

	return FALSE;
}

bool InputBrain::KeyRelease(int code)
{

	if (key_input_preview[code] && !key_input[code])
		return TRUE;
	return FALSE;
}

// キーを押している時間 
BYTE InputBrain::KeyPushTime(int code)
{
	return key_input[code];
}

HRESULT InputBrain::free()
{
	if (mouse_device) {
		mouse_device->Unacquire();
		mouse_device->Release();
	}
	if (key_device) {
		key_device->Unacquire();
		key_device->Release();
	}
	d_input->Release();
	return S_OK;
}


int InputBrain::KeyGet(int code)
{
	if (KeyTrigger(code))
	{
		return KEY_PUSH_FIRST;
	}
	else if (KeyRelease(code))
	{
		return KEY_RELEASE;
	}
	else if (KeyPush(code))
	{
		return KEY_PUSH_STAY;
	}
	else return NONE;
}

int InputBrain::XConGet(int code)
{
	if (XConTrigger(code))
	{
		return KEY_STATE::KEY_PUSH_FIRST;
	}
	else if (XConRelease(code))
	{
		return  KEY_STATE::KEY_RELEASE;
	}
	else if (XConPush(code))
	{
		return  KEY_STATE::KEY_PUSH_STAY;
	}
	else return  KEY_STATE::NONE;



	return 0;
}

void InputBrain::XConVib(unsigned int frame, unsigned int strong)
{
	vib_list.push_back(Vibrate(frame, strong));
}

bool	InputBrain::XConPush(int code)
{
	if (xcon_input&code)
		return true;

	return false;
}

bool	InputBrain::XConTrigger(int code)
{
	if ((xcon_input&code) && !(xcon_input_preview&code))
		return true;

	return false;
}

bool	InputBrain::XConRelease(int code)
{
	if (!(xcon_input&code) && (xcon_input_preview&code))
		return true;
	return false;
}


void	InputBrain::VibrateUpdate()
{
	if (!vib_list.empty())
	{
		XINPUT_VIBRATION vibration;

		int vib_power = 0;
		for (auto&vib_it = vib_list.begin(); vib_it != vib_list.end();)
		{
			if ((vib_it)->Update())
			{

				vib_it = vib_list.erase(vib_it);
			}
			else
			{
				if (vib_power < vib_it->stronger) vib_power = vib_it->stronger;
				vib_it++;
			}
		}

		vibration.wRightMotorSpeed = vib_power;
		vibration.wLeftMotorSpeed = vib_power;
		XInputSetState(0, &vibration);

	}
}


//void InputBrain::GetXConStickState()
//{
//
//}

Vector2D InputBrain::GetXConRightStick()
{
	return right_stick_input;
}


Vector2D InputBrain::GetXConLeftStick()
{
	if (Absolute(left_stick_input.Length()) < 6000)
		return Vector2D();
	return left_stick_input/32767.0f;
}


LONG InputBrain::GetMouseWheelDelta()
{
	return mouse_input.lZ /*- mouse_input_preview.lZ*/;
}

Vector2D InputBrain::GetMouseTranslationOnViewport()
{
	

	return Vector2D(mouse_input.lX - mouse_input_preview.lX, mouse_input.lY - mouse_input_preview.lY);
}