#pragma once
#include "source\math\yuki_math.h"
#include "source\system\object\sprite\sprite.h"
#include <memory>
class WidgetBase
{
public:
	WidgetBase(VECTORII size, VECTORII pos_init):
		size(size),
		position(pos_init)
	{}
	~WidgetBase() {}
protected:
	VECTORII size;
	VECTORII position;
public:

};

class GaugeWidget :public WidgetBase
{
public:
	GaugeWidget(VECTORII widget_size, VECTORII pos_init, float gauge_init, const wchar_t* fill_imagename, const wchar_t* back_imagename) :
		WidgetBase(widget_size, pos_init),
		gauge(gauge_init)
	{
		fill_image			= std::make_unique<Sprite>(fill_imagename);
		background_image	= std::make_unique<Sprite>(back_imagename);
		gauge = 0.5f;
	}
	~GaugeWidget() {}
private:
	//0.0f ~ 1.0f
	std::unique_ptr<Sprite> fill_image;
	std::unique_ptr<Sprite> background_image;

public:
	float gauge;
	//
	//¡‰ñ‚ÍLeft to Right‚Ì‚Ýì¬
	//‚¢‚¸‚ê‚Í‚»‚Ì‹t‹y‚Ñã‰ºƒQ[ƒW‚àì¬—\’è



	void Render()
	{

		background_image->Render(position, size, {},  size , {}, 0);
		fill_image->Render(position, { size.x*gauge,size.y }, {}, size, {}, 0);
	}
};