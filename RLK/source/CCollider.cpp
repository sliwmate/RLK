#include "CCollider.h"

CCollider::CCollider()
{
	//object = NULL;
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
		al_draw_ellipse(position.x - offset.x, position.y - offset.y, points[0].x * 2, points[0].y * 2, al_map_rgba_f(0, 1, 1, 1), 1);
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