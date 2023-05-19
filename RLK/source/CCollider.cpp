#include "CCollider.h"

CCollider::CCollider()
{
	//object = NULL;
	type = 0;
}

CCollider::~CCollider()
{
	points.clear();
}

void CCollider::render(CVector2<float> offset)
{
	if (points.size() > 2)
	{
		for (int i = 0; i < points.size() - 1; i++)
		{
			al_draw_line(
				position.x + points[i].x - offset.x, position.y + points[i].y - offset.y,
				position.x + points[i + 1].x - offset.x, position.y + points[i + 1].y - offset.y,
				al_map_rgba_f(0, 1, 1, 1), 1);
		}
		al_draw_line(
			position.x + points[0].x - offset.x, position.y + points[0].y - offset.y,
			position.x + points[points.size() - 1].x - offset.x, position.y + points[points.size() - 1].y - offset.y,
			al_map_rgba_f(0, 1, 1, 1), 1);
	}
	else if (points.size() == 1)
	{
		al_draw_ellipse(position.x - offset.x, position.y - offset.y, points[0].x, points[0].y, al_map_rgba_f(0, 1, 1, 1), 1);
	}
	else if (points.size() == 2)
	{
		al_draw_line(
			position.x + points[0].x, position.y + points[0].y,
			position.x + points[1].x, position.y + points[1].y,
			al_map_rgba_f(0, 1, 1, 1), 1);
		al_draw_ellipse(position.x + points[0].x, position.y + points[0].y,
			5, 5, al_map_rgba_f(0, 1, 1, 1), 1);
	}
}

void CCollider::update(CVector2<float> pos, float angle)
{
	position.x = pos.x;
	position.y = pos.y;
}

void CCollider::addPoint(float x, float y)
{
	points.push_back(CVector2<float>(x, y));
}

bool CCollider::pointCircle(CVector2<float> p, CVector2<float> c, float r)
{
	return (p - c).abs() <= r;
}

bool CCollider::circleCircle(CVector2<float> c1, float r1, CVector2<float> c2, float r2, CVector2<float>* out)
{
	CVector2<float> dist = c2 - c1;
	if (dist.abs() <= r1 + r2)
	{
		*out = c1 + (r1 / (r1 + r2)) * (c2 - c1);
		return true;
	}
	return false;
}

bool CCollider::linePoint(CVector2<float> a1, CVector2<float> a2, CVector2<float> p)
{
	float d1 = (a1 - p).abs();
	float d2 = (a2 - p).abs();
	float len = (a2 - a1).abs();
	float buffer = 0.1f;
	return d1 + d2 >= len - buffer && d1 + d2 <= len + buffer;
}

bool CCollider::lineCircle(CVector2<float> a1, CVector2<float> a2, CVector2<float> c, float r, CVector2<float>* out)
{
	bool inside1 = pointCircle(a1, c, r);
	bool inside2 = pointCircle(a2, c, r);
	if (inside1 || inside2) return true;
	CVector2<float> dist = a2 - a1;
	float len = dist.abs();
	float dot = (((c.x - a1.x) * (a2.x - a1.x)) + ((c.y - a1.y) * (a2.y - a1.y))) / (len * len);
	CVector2<float> closest(a1.x + (dot * (a2.x - a1.x)), a1.y + (dot * (a2.y - a1.y)));
	bool onSegment = linePoint(a1, a2, closest);
	if (!onSegment) return false;
	*out = closest;
	return pointCircle(closest, c, r);
	return false;
}
