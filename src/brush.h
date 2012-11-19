#ifndef MLBRUSH_H
#define MLBRUSH_H

//ExportName: Brush

#include <QVariant>
#include <QSharedDataPointer>
#include "color.h"
#include "colorgradient.h"
#include "image.h"
#include "surface.h"
#include <QTransform>
#include <QScopedPointer>

namespace Malachite
{

class BrushData : public QSharedData
{
public:
	BrushData() :
		type(Malachite::BrushTypeNull),
		spreadType(Malachite::SpreadTypeRepeat)
	{}
	
	BrushData(const Vec4F &argb) :
		type(Malachite::BrushTypeColor),
		spreadType(Malachite::SpreadTypeRepeat),
		data(QVariant::fromValue(argb))
	{}
	
	BrushData(const Image &image) :
		type(Malachite::BrushTypeImage),
		spreadType(Malachite::SpreadTypeRepeat),
		data(QVariant::fromValue(image))
	{}
	
	BrushData(const ColorGradient &gradient, const LinearGradientInfo &info) :
		type(Malachite::BrushTypeLinearGradient),
		spreadType(Malachite::SpreadTypePad),
		data(QVariant::fromValue(info)),
		gradient(gradient.clone())
	{}
	
	BrushData(const ColorGradient &gradient, const RadialGradientInfo &info) :
		type(Malachite::BrushTypeRadialGradient),
		spreadType(Malachite::SpreadTypePad),
		data(QVariant::fromValue(info)),
		gradient(gradient.clone())
	{}
	
	BrushData(const Surface &surface) :
		type(Malachite::BrushTypeSurface),
		spreadType(Malachite::SpreadTypeRepeat),
		data(QVariant::fromValue(surface))
	{}
	
	BrushData(const BrushData &other) :
		QSharedData(other),
		type(other.type),
		spreadType(other.spreadType),
		data(other.data),
		transform(other.transform),
		gradient(gradient->clone())
	{}
	
	Malachite::BrushType type;
	Malachite::SpreadType spreadType;
	QVariant data;
	QTransform transform;
	QScopedPointer<ColorGradient> gradient;
};


class MALACHITESHARED_EXPORT Brush
{
public:
	
	Brush() {}
	
	Brush(const Color &color)
	{
		d = new BrushData(color.toArgb());
	}
	
	Brush(const Vec4F &argb)
	{
		d = new BrushData(argb);
	}
	
	Brush(const ColorGradient &gradient, const LinearGradientInfo &info)
	{
		d = new BrushData(gradient, info);
	}
	
	Brush(const ColorGradient &gradient, const RadialGradientInfo &info)
	{
		d = new BrushData(gradient, info);
	}
	
	Brush(const Image &image)
	{
		d = new BrushData(image);
	}
	
	Brush(const Surface &surface)
	{
		d = new BrushData(surface);
	}
	
	static Brush fromLinearGradient(const ColorGradient &gradient, const Vec2D &start, const Vec2D &end)
	{
		return Brush(gradient, LinearGradientInfo(start, end));
	}
	
	static Brush fromRadialGradient(const ColorGradient &gradient, const Vec2D &center, double radius, const Vec2D &focal)
	{
		return Brush(gradient, RadialGradientInfo(center, radius, focal));
	}
	
	static Brush fromRadialGradient(const ColorGradient &gradient, const Vec2D &center, const Vec2D &radius, const Vec2D &focal)
	{
		return Brush(gradient, RadialGradientInfo(center, radius, focal));
	}
	
	static Brush fromRadialGradient(const ColorGradient &gradient, const Vec2D &center, double radius)
	{
		return Brush(gradient, RadialGradientInfo(center, radius));
	}
	
	static Brush fromRadialGradient(const ColorGradient &gradient, const Vec2D &center, const Vec2D &radius)
	{
		return Brush(gradient, RadialGradientInfo(center, radius));
	}
	
	bool isValid() { return d; }
	
	Malachite::BrushType type() const { return d->type; }
	
	void setSpreadType(Malachite::SpreadType type) { d->spreadType = type; }
	Malachite::SpreadType spreadType() const { return d->spreadType; }
	
	Vec4F argb() const { return d->type == Malachite::BrushTypeColor ? d->data.value<Vec4F>() : Vec4F(0); }
	Image image() const { return d->type == Malachite::BrushTypeImage ? d->data.value<Image>() : Image(); }
	Surface surface() const { return d->type == Malachite::BrushTypeSurface ? d->data.value<Surface>() : Surface(); }
	
	LinearGradientInfo linearGradientInfo() const { return d->type == Malachite::BrushTypeLinearGradient ? d->data.value<LinearGradientInfo>() : LinearGradientInfo(); }
	RadialGradientInfo radialGradientInfo() const { return d->type == Malachite::BrushTypeRadialGradient ? d->data.value<RadialGradientInfo>() : RadialGradientInfo(); }
	
	const ColorGradient *gradient() const { return d->gradient.data(); }
	
	void setTransform(const QTransform &transform) { d->transform = transform; }
	QTransform transform() const { return d->transform; }
	
	void translate(double dx, double dy) { d->transform.translate(dx, dy); }
	void translate(const QPointF &d) { translate(d.x(), d.y()); }
	void translate(const QPoint &d) { translate(d.x(), d.y()); }
	void scale(double sx, double sy) { d->transform.scale(sx, sy); }
	void rotate(double angle) { d->transform.rotate(angle); }
	
private:
	
	QSharedDataPointer<BrushData> d;
};

}

Q_DECLARE_METATYPE(Malachite::Brush)

#endif // MLBRUSH_H