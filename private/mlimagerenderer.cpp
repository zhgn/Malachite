
#include "mlimagerenderer.h"

unsigned QPainterPath_vs::vertex(double *x, double *y)
{
	forever
	{
		if (_subdIndex)
		{
			if (_subdIndex == _subdPolygon.size())
			{
				_subdIndex = 0;
				continue;
			}
			
			const MLVec2D p = _subdPolygon.at(_subdIndex);
			*x = p.x;
			*y = p.y;
			_subdIndex++;
			
			return agg::path_cmd_line_to;
		}
		
		if (_index == _path.elementCount())	// path終わり
			return agg::path_cmd_stop;
		
		const QPainterPath::Element element = _path.elementAt(_index);
		
		if (element.type == QPainterPath::CurveToElement)
		{
			QPainterPath::Element e1, e2, e3, e4;
			e1 = _path.elementAt(_index - 1);
			e2 = _path.elementAt(_index);
			e3 = _path.elementAt(_index + 1);
			e4 = _path.elementAt(_index + 2);
			
			_subdPolygon = MLCurveSubdivision(MLVec2D(e1.x, e1.y), MLVec2D(e2.x, e2.y), MLVec2D(e3.x, e3.y), MLVec2D(e4.x, e4.y)).polygon();
			_subdIndex = 1;
			_index += 3;
			continue;
		}
		
		_index++;
		*x = element.x;
		*y = element.y;
		
		switch (element.type)
		{
		case QPainterPath::MoveToElement:
			return agg::path_cmd_move_to;
		case QPainterPath::LineToElement:
			return agg::path_cmd_line_to;
		default:
			return agg::path_cmd_line_to;
		}
	}
}
