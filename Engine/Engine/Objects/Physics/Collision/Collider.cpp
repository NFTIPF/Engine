#include "Collider.hpp"

Collider::Collider(){}
Collider::~Collider(){}

CollisionData Collider::collide(boost::shared_ptr<Collidable>& o1, boost::shared_ptr<Collidable>& o2)
{
	return collide(*(o1->getHitBox()), *(o2->getHitBox()));
}

CollisionData Collider::collide(boost::shared_ptr<Collidable>& o1, std::vector<boost::shared_ptr<Collidable> >& oVec)
{
	CollisionData data;
	for (unsigned int i = 0; i < oVec.size(); i++)
	{
		data = collide(*(o1->getHitBox()), *(oVec[i]->getHitBox()));
		if (data.collided())
		{
			return data;
		}
	}

	data = CollisionData(false, *oVec.back()->getHitBox());
	return data;

}

CollisionData Collider::collide(HitBox& b1, HitBox& b2)
{

	CollisionData ret = CollisionData(isCollide(b1.get(), b2.get()), b2);

	return ret;
}

CollisionData Collider::collide(HitBox& b1, std::vector<HitBox*>& b2)
{
	CollisionData data;
	for (unsigned int i = 0; i < b2.size(); i++)
	{
		data = CollisionData(isCollide(b1.get(), b2[i]->get()), *b2[i]);
		//data.setFeathered(b2[i]->isFeather());
		if (data.collided())
		{

			return data;
		}
	}

	data = CollisionData(false, *b2.back());
	return data;
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

	if (fabs(u.x - v.x) < .001)
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
	else if (fabs(a.x - b.x) < .001)
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
			double na = a.y - slopeb * a.x;
			double nu = u.y - slopea * u.x;
			poi.x = (na - nu) / (slopea - slopeb);
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

	if (fabs(vec.x) < .001)
	{
		good = (fabs(point.x - pa.x) < .01);

	}
	else
	{
		double slope = vec.y / vec.x;
		good = ((fabs(slope * (point.x - pa.x) + pa.y - point.y) < .01));
	}

	bool xtest = (((pb.x <= point.x && pa.x >= point.x) || (pb.x >= point.x && pa.x <= point.x)) || ((fabs(pa.x - point.x) < .01) || (fabs(pb.x - point.x) < .01)));
	bool ytest = (((pb.y <= point.y && pa.y >= point.y) || (pb.y >= point.y && pa.y <= point.y)) || ((fabs(pa.y - point.y) < .01) || (fabs(pb.y - point.y) < .01)));
	good = (good && xtest && ytest);

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
			maxY = points[i].y;
		}

		if (points[i].y < minY)
		{
			minY = points[i].y;
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





double Collider::magSq(const sf::Vector2f& vec)
{
	return ((double)(vec.x * vec.x + vec.y * vec.y));
}


double Collider::distSq(const sf::Vector2f& veca, const sf::Vector2f& vecb)
{
	return ((double)((veca.x - vecb.x) * (veca.x - vecb.x) + (veca.y - vecb.y) * (veca.y - vecb.y)));
}

std::tuple<sf::Vector2f, sf::Vector2f, unsigned int> Collider::getKineticResponseDoublePolygon(sf::Vector2f vel, const polygon& polyA, const polygon& polyB, const bool& hollow)
{
	if (fabs(vel.y) > 20)
	{
		std::cout << "why?" << std::endl;
	}
	double signMultiplier = 1;

	unsigned int sizb = polyB.size();

	bool foundFirst = false;
	double minDistSq = 1;
	sf::Vector2f critLine1(0, 0);
	sf::Vector2f critLine2(0, 0);
	sf::Vector2f critCorner(0, 0);
	const double knockback = .1;

	sf::Vector2f firstPoi;

	for (unsigned int i = 0; i < polyA.size(); i++)
	{
		
		const sf::Vector2f oldPoint = polyA[i] - vel;
		for (unsigned int k = 0; k < polyB.size(); k++)
		{
			std::pair<sf::Vector2f, bool> poi = getLinePoint(oldPoint, polyA[i], polyB[k], polyB[(k + 1) % sizb]);
			if (poi.second)
			{
				double tmpDistSq = distSq(oldPoint, poi.first);
				if ((tmpDistSq < minDistSq) || (!foundFirst))
				{
					foundFirst = true;
					critLine1 = polyB[k];
					critLine2 = polyB[(k + 1) % sizb];
					critCorner = polyA[i];
					minDistSq = tmpDistSq;
					firstPoi = poi.first;
				}
			}
		}
	}

	if (!foundFirst)
	{
		vel = -vel;
		signMultiplier = -1;
		unsigned int siza = polyA.size();
		for (unsigned int i = 0; i < polyB.size(); i++)
		{
			const sf::Vector2f oldPoint = polyB[i] - vel;
			for (unsigned int k = 0; k < polyA.size(); k++)
			{
				std::pair<sf::Vector2f, bool> poi = getLinePoint(oldPoint, polyB[i], polyA[k], polyA[(k + 1) % siza]);
				if (poi.second)
				{
					double tmpDistSq = distSq(oldPoint, poi.first);
					if ((tmpDistSq < minDistSq) || (!foundFirst))
					{
						
						foundFirst = true;
						critLine1 = polyA[k];
						critLine2 = polyA[(k + 1) % siza];
						critCorner = polyB[i];
						minDistSq = tmpDistSq;
						firstPoi = poi.first;
					}
				}
			}
		}
	}

	if (!foundFirst)
	{
		return std::make_tuple(sf::Vector2f(0,0), sf::Vector2f(0,0), 0);
	}
	sf::Vector2f corDisp = firstPoi - critCorner;


	const sf::Vector2f critLineVec = critLine2 - critLine1; //move line to origin
	

	
	if (hollow && critLineVec.x != 0)
	{
		double critSlope = critLineVec.y / critLineVec.x;
		if ((fabs(critSlope) < 1) && (signMultiplier * (critCorner.y - vel.y) > signMultiplier * (firstPoi.y)))
		{
			return std::make_tuple(sf::Vector2f(0,0), sf::Vector2f(0,0), 2);
		}
	}


	const sf::Vector2f groundVel = -corDisp;

	const double critMagSq = magSq(critLineVec);

	//find dot product
	const double dotProd = dotProduct(critLineVec, groundVel);

	//find projection vector
	const sf::Vector2f projVec(dotProd / critMagSq * critLineVec.x, dotProd / critMagSq * critLineVec.y);

	//find other component (rejection vector)
	sf::Vector2f normalVelocity =  projVec - groundVel;



	sf::Vector2f knockbackVec;


	sf::Vector3f outwardNormalTmp = crossProduct(sf::Vector3f(critLineVec.x, critLineVec.y, 0), sf::Vector3f(0, 0, 1));
	sf::Vector2f outwardNormal(outwardNormalTmp.x, outwardNormalTmp.y);
	const double normalMag = sqrt(magSq(outwardNormal));

	knockbackVec.x = outwardNormal.x / normalMag * knockback;
	knockbackVec.y = outwardNormal.y / normalMag * knockback;



	normalVelocity += knockbackVec;

	corDisp += knockbackVec;






	bool jumpable = false;
	if (critLineVec.x != 0)
	{
		double critSlope = critLineVec.y / critLineVec.x;
		jumpable = ((fabs(critSlope) <= 1) && (signMultiplier * (critCorner.y - vel.y) < signMultiplier * (firstPoi.y)));
	}

	corDisp.x *= signMultiplier;
	corDisp.y *= signMultiplier;
	normalVelocity.x *= signMultiplier;
	normalVelocity.y *= signMultiplier;


	if ((normalVelocity.x != normalVelocity.x) || (normalVelocity.y != normalVelocity.y))
	{
		std::cout << "why?" << std::endl;
	}
	if (normalVelocity.x > 10)
	{
		std::cout << "is this an error?" << std::endl;
		std::pair<sf::Vector2f, bool> poi = getLinePoint(critCorner - vel, critCorner, critLine1, critLine2);
	}


	return std::make_tuple(corDisp, normalVelocity, jumpable);
	//return std::make_pair(corDisp, normalVelocity);

}



sf::Vector3f Collider::crossProductZN(const sf::Vector2f& v, const sf::Vector2f& u)
{
	return crossProduct(sf::Vector3f(v.x, v.y, 0), sf::Vector3f(u.x, u.y, 0));
}
sf::Vector3f Collider::crossProduct(const sf::Vector3f& v, const sf::Vector3f& u)
{
	return sf::Vector3f(v.y *u.z - v.z * u.y, v.z * u.x - v.x * u.z, v.x * u.y - v.y * v.x);
}

double Collider::dotProduct(const sf::Vector2f& v, const sf::Vector2f& u)
{
	return v.x * u.x + v.y * u.y;
}