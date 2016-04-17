#include "Collider.hpp"

Collider::Collider(){}
Collider::~Collider(){}

CollisionData Collider::collide(Collidable& o1, Collidable& o2)
{
	return collide(o1.getHitBox(), o2.getHitBox());
}

CollisionData Collider::collide(Collidable& o1, std::vector<Collidable*>& oVec)
{
	CollisionData data;
	for (unsigned int i = 0; i < oVec.size(); i++)
	{
		data = collide(o1.getHitBox(), oVec[i]->getHitBox());
		if (data.collided())
		{
			return data;
		}
	}
}

CollisionData Collider::collide(HitBox& b1, HitBox& b2)
{
	return CollisionData(isCollide(b1.get(), b2.get()), b2);
}

CollisionData Collider::collide(HitBox& b1, std::vector<HitBox*>& b2)
{
	CollisionData data;
	for (unsigned int i = 0; i < b2.size(); i++)
	{
		data = CollisionData(isCollide(b1.get(), b2[i]->get()), *b2[i]);
		if (data.collided())
		{
			return data;
		}
	}
}

bool Collider::checkBoundingBoxCollision(const sf::Vector2f& tla, const sf::Vector2f& bra, const sf::Vector2f& tlb, const sf::Vector2f& brb)
{
	enum boundpos { Top = 0, Right, Bot, Left, BOUND_SIZE };

	double boundsA[BOUND_SIZE];

	boundsA[Top] = tla.y;
	boundsA[Right] = bra.x;
	boundsA[Bot] = bra.y;
	boundsA[Left] = tla.x;

	double boundsB[BOUND_SIZE];

	boundsB[Top] = tlb.y;
	boundsB[Right] = brb.x;
	boundsB[Bot] = brb.y;
	boundsB[Left] = tlb.x;

	bool collided = true;

	if ((boundsA[Top] > boundsB[Bot]) || (boundsA[Bot] < boundsB[Top]) || (boundsA[Right] < boundsB[Left]) || (boundsA[Left] > boundsB[Right]))
	{
		collided = false;
	}

	return collided;


}



std::pair<sf::Vector2f, bool> Collider::getLinePoint(const sf::Vector2f& u, const sf::Vector2f& v, const sf::Vector2f& a, const sf::Vector2f& b)
{
	bool legit = true;
	sf::Vector2f poi = sf::Vector2f(0, 0);

	if (u.x == v.x)
	{
		if (a.x == b.x)
		{
			legit = false;
		}
		else
		{
			double slopeb = (a.y - b.y) / (a.x - b.x);
			poi = sf::Vector2f(u.x, slopeb * (u.x - a.x) + a.y);
		}
	}
	else if (a.x == b.x)
	{
		double slopea = (u.y - v.y) / (u.x - v.x);
		poi = sf::Vector2f(a.x, slopea * (a.x - u.x) + u.y);
	}
	else
	{
		double slopea = (u.y - v.y) / (u.x - v.x);
		double slopeb = (a.y - b.y) / (a.x - b.x);

		if (slopea == slopeb)
		{
			legit = false;
		}
		else
		{
			poi.x = (slopeb * a.x - slopea * u.x + u.y - a.y) / (slopeb - slopea);
			poi.y = slopea * (poi.x - u.x) + u.y;
		}

	}


	if (legit)
	{
		legit = (checkPointOnLine(poi, u, v) && checkPointOnLine(poi, a, b));
	}


	return std::make_pair(poi, legit);

}




bool Collider::checkPointOnLine(const sf::Vector2f& point, const sf::Vector2f& pa, const sf::Vector2f& pb)
{
	const sf::Vector2f vec = (pb - pa);

	bool good = false;

	if (vec.x == 0)
	{
		good = (fabs(point.x - pa.x) < .001);

	}
	else
	{
		double slope = vec.y / vec.x;
		good = ((fabs(slope * (point.x - pa.x) + pa.y - point.y) < .001));
	}

	good = (good && (pb.x <= point.x && pa.x >= point.x || pb.x >= point.x && pa.x <= point.x));
	good = (good && (pb.y <= point.y && pa.y >= point.y || pb.y >= point.y && pa.y <= point.y));

	return good;


}

std::pair<sf::Vector2f, sf::Vector2f> Collider::getBoundingBoxCorners(const std::vector<sf::Vector2f>& points)
{
	double maxX = points[0].x;
	double minX = points[0].x;
	double maxY = points[0].y;
	double minY = points[0].y;



	for (unsigned int i = 0; i < points.size(); i++)
	{
		if (points[i].x > maxX)
		{
			maxX = points[i].x;
		}

		if (points[i].x < minX)
		{
			minX = points[i].x;
		}

		if (points[i].y > maxY)
		{
			maxY = points[i].x;
		}

		if (points[i].x > minY)
		{
			minY = points[i].x;
		}
	}

	return std::make_pair(sf::Vector2f(minX, minY), sf::Vector2f(maxX, maxY));

}



bool Collider::isCollide(const std::vector<sf::Vector2f>& hb1, const std::vector<sf::Vector2f>& hb2)
{
	double maxX = hb2[0].x;

	bool colliding = false;


	std::pair<sf::Vector2f, sf::Vector2f> bb1 = getBoundingBoxCorners(hb1);
	std::pair<sf::Vector2f, sf::Vector2f> bb2 = getBoundingBoxCorners(hb2);

	colliding = checkBoundingBoxCollision(bb1.first, bb1.second, bb2.first, bb2.second);


	if (colliding)
	{
		for (unsigned int i = 0; i < hb1.size() - 1 && colliding == false; i++)
		{
			for (unsigned int k = 0; k < hb2.size() - 1 && colliding == false; k++)
			{
				if (hb2[k].x > maxX)
				{
					maxX = hb2[k].x;
				}
				std::pair<sf::Vector2f, bool> poi = getLinePoint(hb1[i], hb1[i + 1], hb2[k], hb2[k + 1]);
				colliding = poi.second;
			}
		}

		if (!colliding)
		{
			unsigned int poiCounter = 0;
			maxX += 10;

			for (unsigned int k = 0; k < hb2.size() - 1 && colliding == false; k++)
			{
				colliding = checkPointOnLine(hb1[0], hb2[k], hb2[k + 1]);
				std::pair<sf::Vector2f, bool> poi = getLinePoint(hb1[0], sf::Vector2f(maxX, hb1[0].y), hb2[k], hb2[k + 1]);
				poiCounter += poi.second;
			}

			if (!colliding)
			{
				colliding = (poiCounter & 1);
			}

		}
	}


	return colliding;
}
