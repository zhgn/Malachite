#include "private/agg_math.h"
#include "mlcurvesubdivision.h"

namespace agg
{

//-------------------------------------------------------------curve4_div
class curve4_div
{
public:
    curve4_div() : 
        m_approximation_scale(1.0),
        m_angle_tolerance(0.0),
        m_cusp_limit(0.0)
    {}

    curve4_div(const MLVec2D &p1,
               const MLVec2D &p2,
               const MLVec2D &p3,
               const MLVec2D &p4) :
        m_approximation_scale(1.0),
        m_angle_tolerance(0.0),
        m_cusp_limit(0.0)
    { 
        init(p1, p2, p3, p4);
    }

    void reset() { m_points.clear(); }
    void init(const MLVec2D &p1,
			  const MLVec2D &p2,
              const MLVec2D &p3,
              const MLVec2D &p4);

    void approximation_scale(double s) { m_approximation_scale = s; }
    double approximation_scale() const { return m_approximation_scale;  }

    void angle_tolerance(double a) { m_angle_tolerance = a; }
    double angle_tolerance() const { return m_angle_tolerance;  }

    void cusp_limit(double v) 
    { 
        m_cusp_limit = (v == 0.0) ? 0.0 : pi - v; 
    }

    double cusp_limit() const 
    { 
        return (m_cusp_limit == 0.0) ? 0.0 : pi - m_cusp_limit; 
    }

	MLPolygon polygon() const { return m_points; }
	
	int size() const
	{
		return m_points.size();
	}

private:
    void bezier(const MLVec2D &p1,
				const MLVec2D &p2,
                const MLVec2D &p3,
                const MLVec2D &p4);

    void recursive_bezier(const MLVec2D &p1,
						  const MLVec2D &p2,
			              const MLVec2D &p3,
			              const MLVec2D &p4,
                          unsigned level);

    double               m_approximation_scale;
    double               m_distance_tolerance_square;
    double               m_angle_tolerance;
    double               m_cusp_limit;
    MLPolygon m_points;
};

//------------------------------------------------------------------------
const double curve_distance_epsilon                  = 1e-30;
const double curve_collinearity_epsilon              = 1e-30;
const double curve_angle_tolerance_epsilon           = 0.01;
enum curve_recursion_limit_e { curve_recursion_limit = 32 };

//------------------------------------------------------------------------
void curve4_div::init(const MLVec2D &p1, const MLVec2D &p2, 
                      const MLVec2D &p3, const MLVec2D &p4)
{
    m_points.clear();
    m_distance_tolerance_square = 0.5 / m_approximation_scale;
    m_distance_tolerance_square *= m_distance_tolerance_square;
    bezier(p1, p2, p3, p4);
}

//------------------------------------------------------------------------
void curve4_div::recursive_bezier(const MLVec2D &p1, const MLVec2D &p2, 
                                  const MLVec2D &p3, const MLVec2D &p4, 
                                  unsigned level)
{
    if(level > curve_recursion_limit) 
    {
        return;
    }

    // Calculate all the mid-points of the line segments
    //----------------------
	
	MLVec2D p12 = (p1 + p2) * 0.5;
	MLVec2D p23 = (p2 + p3) * 0.5;
	MLVec2D p34 = (p3 + p4) * 0.5;
	MLVec2D p123 = (p12 + p23) * 0.5;
	MLVec2D p234 = (p23 + p34) * 0.5;
	MLVec2D p1234 = (p123 + p234) * 0.5;

    // Try to approximate the full cubic curve by a single straight line
    //------------------
	MLVec2D d = p4 - p1;
	
	MLVec2D d42 = p2 - p4;
	MLVec2D d43 = p3 - p4;
	
	MLVec2D d2d3 = MLVec2D(d42.x, d43.x) * d.y - MLVec2D(d42.y, d43.y) * d.x;
	double d2 = fabs(d2d3.x);
	double d3 = fabs(d2d3.x);
	
	MLVec2D da;
    double k;

    switch((int(d2 > curve_collinearity_epsilon) << 1) +
            int(d3 > curve_collinearity_epsilon))
    {
    case 0:
        // All collinear OR p1==p4
        //----------------------
        k = mlSqLength(d);
        if(k == 0)
        {
			d2 = mlSqLength(p2 - p1);
			d3 = mlSqLength(p3 - p4);
        }
        else
        {
            k   = 1 / k;
			da = p2 - p1;
			d2 = k * mlDot(da, d);
			da = p3 - p1;
			d3 = k * mlDot(da, d);
            if(d2 > 0 && d2 < 1 && d3 > 0 && d3 < 1)
            {
                // Simple collinear case, 1---2---3---4
                // We can leave just two endpoints
                return;
            }
                 if(d2 <= 0) d2 = mlSqLength(p1 - p2);
            else if(d2 >= 1) d2 = mlSqLength(p4 - p2);
            else             d2 = mlSqLength(p1 + d2 * d - p2);

                 if(d3 <= 0) d3 = mlSqLength(p1 - p3);
            else if(d3 >= 1) d3 = mlSqLength(p4 - p3);
            else             d3 = mlSqLength(p1 + d3 * d - p3);
        }
        if(d2 > d3)
        {
            if(d2 < m_distance_tolerance_square)
            {
                m_points << p2;
                return;
            }
        }
        else
        {
            if(d3 < m_distance_tolerance_square)
            {
                m_points << p3;
                return;
            }
        }
        break;

    case 1:
        // p1,p2,p4 are collinear, p3 is significant
        //----------------------
        if(d3 * d3 <= m_distance_tolerance_square * mlSqLength(d))
        {
            if(m_angle_tolerance < curve_angle_tolerance_epsilon)
            {
                m_points << p23;
                return;
            }

            // Angle Condition
            //----------------------
			
			MLVec2D d34 = p4 - p3;
			MLVec2D d23 = p3 - p2;
			da.x = fabs(atan2(d34.y, d34.x) - atan2(d23.y, d23.x));
			
            if(da.x >= pi) da.x = 2*pi - da.x;

            if(da.x < m_angle_tolerance)
            {
                m_points << p2;
                m_points << p3;
                return;
            }

            if(m_cusp_limit != 0.0)
            {
                if(da.x > m_cusp_limit)
                {
                    m_points << p3;
                    return;
                }
            }
        }
        break;

    case 2:
        // p1,p3,p4 are collinear, p2 is significant
        //----------------------
        if(d2 * d2 <= m_distance_tolerance_square * mlSqLength(d))
        {
            if(m_angle_tolerance < curve_angle_tolerance_epsilon)
            {
                m_points << p23;
                return;
            }

            // Angle Condition
            //----------------------
			
			MLVec2D d23 = p3 - p2;
			MLVec2D d12 = p2 - p1;
			da.x = fabs(atan2(d23.y, d23.x) - atan2(d12.y, d12.x));
            if(da.x >= pi) da.x = 2*pi - da.x;

            if(da.x < m_angle_tolerance)
            {
                m_points << p2;
                m_points << p3;
                return;
            }

            if(m_cusp_limit != 0.0)
            {
                if(da.x > m_cusp_limit)
                {
                    m_points << p2;
                    return;
                }
            }
        }
        break;

    case 3: 
        // Regular case
        //-----------------
        if((d2 + d3)*(d2 + d3) <= m_distance_tolerance_square * mlSqLength(d))
        {
            // If the curvature doesn't exceed the distance_tolerance value
            // we tend to finish subdivisions.
            //----------------------
            if(m_angle_tolerance < curve_angle_tolerance_epsilon)
            {
                m_points << p23;
                return;
            }

            // Angle & Cusp Condition
            //----------------------
			
			MLVec2D d34 = p4 - p3;
			MLVec2D d23 = p3 - p2;
			MLVec2D d12 = p2 - p1;
			
			
            k   = atan2(d23.y, d23.x);
            da.x = fabs(k - atan2(d12.y, d12.x));
            da.y = fabs(atan2(d34.y, d34.x) - k);
            if(da.x >= pi) da.x = 2*pi - da.x;
            if(da.y >= pi) da.y = 2*pi - da.y;

            if(da.x + da.y < m_angle_tolerance)
            {
                // Finally we can stop the recursion
                //----------------------
                m_points << p23;
                return;
            }

            if(m_cusp_limit != 0.0)
            {
                if(da.x > m_cusp_limit)
                {
                    m_points << p2;
                    return;
                }

                if(da.y > m_cusp_limit)
                {
                    m_points << p3;
                    return;
                }
            }
        }
        break;
    }

    // Continue subdivision
    //----------------------
	recursive_bezier(p1, p12, p123, p1234, level + 1);
	recursive_bezier(p1234, p234, p34, p4, level + 1);
}

//------------------------------------------------------------------------
void curve4_div::bezier(const MLVec2D &p1,
						const MLVec2D &p2,
		                const MLVec2D &p3,
		                const MLVec2D &p4)
{
    m_points << p1;
    recursive_bezier(p1, p2, p3, p4, 0);
    m_points << p4;
}

}

MLCurveSubdivision::MLCurveSubdivision(const MLCurve4 &curve)
{
	agg::curve4_div curveSub(curve.start, curve.control1, curve.control2, curve.end);
	_polygon = curveSub.polygon();
}

MLCurveSubdivision::MLCurveSubdivision(const MLVec2D &start, const MLVec2D &control1, const MLVec2D &control2, const MLVec2D &end)
{
	agg::curve4_div curveSub(start, control1, control2, end);
	_polygon = curveSub.polygon();
}
