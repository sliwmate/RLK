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
				position.x + points[i].x, position.y + points[i].y,
				position.x + points[i + 1].x, position.y + points[i + 1].y,
				al_map_rgba_f(0, 1, 1, 1), 1);
		}
		al_draw_line(
			position.x + points[0].x, position.y + points[0].y,
			position.x + points[points.size() - 1].x, position.y + points[points.size() - 1].y,
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

CVector2<float> CCollider::getContactPoint(CCollider c1, CCollider c2)
{
	if (c1.type == Type::ELLIPSE)
	{
		if (c2.type == Type::ELLIPSE)
		{
			CVector2<float> v = c1.position - c2.position;
			float d = v.abs();
			if (d <= c1.points[0].x + c2.points[0].x)
			{
				return CVector2<float>(c1.position.x - v.x / 2, c1.position.y - v.y / 2);
			}
		}
	}
	return CVector2<float>(0, 0);
}
