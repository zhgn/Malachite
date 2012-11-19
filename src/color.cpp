#include <QtGui>
#include "misc.h"
#include "color.h"

namespace Malachite
{

double Color::component(Component component) const
{
	switch (component)
	{
	case Red:
		return red();
	case Green:
		return green();
	case Blue:
		return blue();
	case Hue:
		return hue();
	case Saturation:
		return saturation();
	case Value:
		return value();
	default:
		return 0;
	}
}

double Color::intervaledComponent(Component component) const
{
	double result = this->component(component);
	return component == Hue ? result / 360.0 : result;
}

void Color::setComponent(Component component, double x)
{
	switch (component)
	{
	case Red:
		setRed(x);
		break;
	case Green:
		setGreen(x);
		break;
	case Blue:
		setBlue(x);
		break;
	case Hue:
		setHue(x);
		break;
	case Saturation:
		setSaturation(x);
		break;
	case Value:
		setValue(x);
		break;
	default:
		break;
	}
}

void Color::setNormalizedComponent(Component component, double x)
{
	setComponent(component, component == Hue ? x * 360.0 : x);
}

void Color::rgbChanged()
{
	double max = max3(_r, _g, _b);
	double min = min3(_r, _g, _b);
	
	_v = max;
	double d = max - min;
	
	if (max) {
		_s = d / max;
	}
	
	if (max == min) {
		return;
	}
	
	if (max == _r) {
		_h = 60.0 * (_g - _b) / d;
	} else if (max == _g) {
		_h = 60.0 * (_b - _r) / d + 120.0;
	} else {
		_h = 60.0 * (_r - _g) / d + 240.0;
	}
	
	_h = fmod(_h, 360.0);
	if (_h < 0)
		_h += 360.0;
}

void Color::hsvChanged()
{
	double d = _h / 60.0;
	int i = floor(d);
	double f = d - i;
	
	switch (i) {
	case 0:
		_r = _v;
		_g = _v * (1 - (1 - f) * _s);
		_b = _v * (1 - _s);
		break;
	case 1:
		_r = _v * (1 - f * _s);
		_g = _v;
		_b = _v * (1 - _s);
		break;
	case 2:
		_r = _v * (1 - _s);
		_g = _v;
		_b = _v * (1 - (1 - f) * _s);
		break;
	case 3:
		_r = _v * (1 - _s);
		_g = _v * (1 - f * _s);
		_b = _v;
		break;
	case 4:
		_r = _v * (1 - (1 - f) * _s);
		_g = _v * (1 - _s);
		_b = _v;
		break;
	case 5:
		_r = _v;
		_g = _v * (1 - _s);
		_b = _v * (1 - f * _s);
		break;
	default:
		break;
	}
}

QString Color::toWebColor() const
{
	Color color = *this;
	color.setAlpha(1.0);
	Vec4U8 argb = color.toFastArgb8();
	
	QString rText = QString::number(argb.r, 16).toUpper();
	if (rText.size() == 1)
		rText = "0" + rText;
	
	QString gText = QString::number(argb.g, 16).toUpper();
	if (gText.size() == 1)
		gText = "0" + gText;
	
	QString bText = QString::number(argb.b, 16).toUpper();
	if (bText.size() == 1)
		bText = "0" + bText;
	
	return "#" + rText + gText + bText;
}

Color Color::fromWebColor(const QString &webColor, bool *ok)
{
	if (webColor.size() != 7 || webColor.at(0) != '#')
	{
		if (ok)
			*ok = false;
		return Color();
	}
	
	Vec4U8 argb;
	bool textOk;
	
	argb.a = 0xFF;
	
	argb.r = webColor.mid(1, 2).toInt(&textOk, 16);
	if (!textOk)
	{
		if (ok)
			*ok = false;
		return Color();
	}
	
	argb.g = webColor.mid(3, 2).toInt(&textOk, 16);
	if (!textOk)
	{
		if (ok)
			*ok = false;
		return Color();
	}
	
	argb.b = webColor.mid(5, 2).toInt(&textOk, 16);
	if (!textOk)
	{
		if (ok)
			*ok = false;
		return Color();
	}
	
	if (ok)
		*ok = true;
	
	return Color::fromFastArgb8(argb);
}

}
