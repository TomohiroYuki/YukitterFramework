#include "source\game\YQCamera.h"



void ViewerCamera::Update()
{



	l -= static_cast<float>(INPUT->GetMouseWheelDelta() / 8.0f);
	if (l < 0)
		l = 0;


	//INPUT->GetMouseTranslationOnViewport()


	if (INPUT->KeyGet(DIK_LALT) || (INPUT->KeyGet(DIK_RALT)))
	{
	}

	if (INPUT->KeyGet(DIK_A))
	{

		a += 0.01f;
	}
	if (INPUT->KeyGet(DIK_D))
	{

		a -= 0.01f;
	}
	if (INPUT->KeyGet(DIK_W))
	{

		transform.AddLocation(Vector(0, 10.1f, 0));
	}
	if (INPUT->KeyGet(DIK_S))
	{

		transform.AddLocation(Vector(0, -10.1f, 0));
	}

	transform.SetLocation(Vector(l*cosf(a), transform.translation.y, l*sinf(a)));


}