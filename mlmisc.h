#ifndef MLMISC_H
#define MLMISC_H

#include <QList>
#include <QVector>
#include <QSet>
#include <QPoint>
#include <QString>
#include <QSize>
#include <QTransform>
#include <cmath>
#include <cstring>
#include "mlglobal.h"

class QPolygonF;
class MLPolygon;

#include <cstdlib>
#ifdef __MINGW32__
#include <malloc.h>
#endif

#define	MAX(a, b)	(((a) > (b)) ? (a) : (b))
#define	MIN(a, b)	(((a) < (b)) ? (a) : (b))
#define MAX3(a, b, c)	(((a) > (b) && (a) > (c)) ? (a) : ((b) > (c)) ? (b) : (c))
#define MIN3(a, b, c)	(((a) < (b) && (a) < (c)) ? (a) : ((b) < (c)) ? (b) : (c))
#define	ABS(a)	(((a) < 0) ? -(a) : (a))
#define	CLAMP(x, low, high)	(((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))

typedef QList<QPoint>	QPointList;
typedef QSet<QPoint>	QPointSet;

#define ML_CURRENT_FUNCTION	__PRETTY_FUNCTION__

template <typename T>
inline T mlMax(const T &a, const T &b, const T &c)
{
	if (a > b && a > c) {
		return a;
	} else {
		if (b > c)
			return b;
		else
			return c;
	}
}

template <typename T>
inline T mlMin(const T &a, const T &b, const T &c)
{
	if (a < b && a < c) {
		return a;
	} else {
		if (b < c)
			return b;
		else
			return c;
	}
}


inline QPointF operator*(const QTransform &transform, const QPointF &point)
{
	return transform.map(point);
}

template <typename T>
QList<T> mlListFromValue(const T &value)
{
	QList<T> list;
	list << value;
	return list;
}

template <typename T>
QList<const T *> mlConstList(const QList<T *> &list) {
	QList<const T *> result;
	result.reserve(list.size());
	foreach (T *p, list) {
		result << p;
	}
	return result;
}

template <typename T>
QList<T *> mlNonConstList(const QList<const T *> &list) {
	QList<T *> result;
	result.reserve(list.size());
	foreach (const T *p, list) {
		result << const_cast<T *>(p);
	}
	return result;
}

template <typename Container>
Container mlReversedContainer(const Container &container) {
	Container reversed;
	reversed.reserve(container.size());
	std::reverse_copy(container.begin(), container.end(), std::back_inserter(reversed));
	return reversed;
}

inline uint qHash(const QSize &key)
{
	QPair<int, int> pair(key.width(), key.height());
	return qHash(pair);
}

inline uint qHash(const QPoint &key)
{
	QPair<int, int> pair(key.x(), key.y());
	return qHash(pair);
}

template <typename T>
class MALACHITESHARED_EXPORT QVectorCountableIterator
{
public:
	QVectorCountableIterator(const QVector<T> &vector) :
		i(0),
		size(vector.size()),
		p(vector.constData())
	{}
	
	bool hasNext() const { return i < size; }
	bool hasPrevious() const { return i > 0; }
	const T &peekNext() const { return *p; }
	const T &peekPrevious() const { return *(p-1); }
	
	const T &next()
	{
		i++;
		p++;
		return peekNext();
	}
	const T &previous()
	{
		i--;
		p--;
		return peekPrevious();
	}
	
	void toFront()
	{
		p -= i;
		i = 0;
	}
	
	void toBack()
	{
		p = p - i + size;
		i = size;
	}
	
	int index() const { return i; }
	
	QVectorCountableIterator &operator=(const QVector<T> &vector)
	{
		i = 0;
		size = vector.size();
		p = vector.constData();
	}
	
private:
	
	int i, size;
	const T *p;
};

template<typename T>
class MALACHITESHARED_EXPORT QVectorReverseCountableIterator
{
public:
	QVectorReverseCountableIterator(const QVector<T> &vector) : i(vector) { i.toBack(); }
	
	bool findNext(const T &value) { return i.findPrevious(value); }
	bool findPrevious(const T &value) { return i.findNext(value); }
	bool hasNext() const { return i.hasPrevious(); }
	bool hasPrevious() const { return i.hasNext(); }
	const T &next() { return i.previous(); }
	const T &peekNext() const { return i.peekPrevious(); }
	const T &previous() { return i.next(); }
	const T &peekPrevious() const { return i.peekNext(); }
	void toFront() { i.toBack(); }
	void toBack() { i.toFront(); }
	int index() const { return i.index(); }
	
	QVectorReverseCountableIterator &operator=(const QVector<T> &vector) { i = vector; i.toBack(); }
	
private:
	QVectorCountableIterator<T> i;
};


#endif // MLMISC_H
