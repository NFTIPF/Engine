#include "HitBoxCollider.hpp"


HitBoxCollider::HitBoxCollider()
{
    knockback = 1;
}


HitBoxCollider::~HitBoxCollider()
{
}


sf::Vector2f HitBoxCollider::getNewPosition(HitBox* boxA, sf::Vector2f velA, HitBox* boxB, sf::Vector2f velB)
{
    sf::Vector2f corVel(0,0);
    if (checkCollision(boxA, boxB))
    {
        double magsqA = velA.x * velA.x + velA.y + velA.y;
        double magsqB = velB.x * velB.x + velB.y + velB.y;

        if (fabs(magsqA) < .001)
        {

        }
        else if (fabs(magsqB) < .001)
        {

        }

    }


    return corVel;

}

bool HitBoxCollider::checkCollision(HitBox* boxA, HitBox* boxB)
{
	bool collided;

	if ((boxA->getType() == HitBox::AABB) && (boxB->getType() == HitBox::AABB))
	{
		collided = collideDoubleAABB(downcastAABB(boxA), downcastAABB(boxB));
	}
	else if ((boxA->getType() == HitBox::CIRC) && (boxB->getType() == HitBox::AABB))
	{
		//collided = collideAABBCirc(downcastAABB(boxB), downcastCirc(boxA));
	}
	else if ((boxA->getType() == HitBox::AABB) && (boxB->getType() == HitBox::CIRC))
	{
		//collided = collideAABBCirc(downcastAABB(boxA), downcastCirc(boxB));
	}
	else if ((boxA->getType() == HitBox::CIRC) && (boxB->getType() == HitBox::CIRC))
	{
		//collided = collideDoubleCirc(downcastCirc(boxA), downcastCirc(boxB));
	}

	return collided;
}

//private

bool HitBoxCollider::collideDoubleAABB(AAHitbox* boxA, AAHitbox* boxB)
{
	enum boundpos { Top = 0, Right, Bot, Left, BOUND_SIZE};

	double boundsA[BOUND_SIZE];

	boundsA[Top] = boxA->getCorners().first.y;
	boundsA[Right] = boxA->getCorners().second.x;
	boundsA[Bot] = boxA->getCorners().second.y;
	boundsA[Left] = boxA->getCorners().first.x;

	double boundsB[BOUND_SIZE];

	boundsB[Top] = boxB->getCorners().first.y;
	boundsB[Right] = boxB->getCorners().second.x;
	boundsB[Bot] = boxB->getCorners().second.y;
	boundsB[Left] = boxB->getCorners().first.x;

	bool collided = true;

	if ((boundsA[Top] > boundsB[Bot]) || (boundsA[Bot] < boundsB[Top]) || (boundsA[Right] < boundsB[Left]) || (boundsA[Left] > boundsB[Right]))
	{
		collided = false;
	}

	return collided;

}

//bool HitBoxCollider::collideAABBCirc(AAHitbox* boxA, CircularHitbox* boxB)
//{
//
//	enum cornerNames {TL = 0, TR, BR, BL, CORNER_SIZE};
//
//	bool boxTest = false;
//	bool circPointTest = false;
//	bool rectPointTest = false;
//	bool positionTest = false;
//
//
//	AAHitbox testor;
//	const sf::Vector2f circpos = boxB->getPosition();
//	const double rad = boxB->getRadius();
//	testor.setPosition(circpos);
//	testor.setSize(sf::Vector2f(2 * rad, 2 * rad));
//
//	boxTest = collideDoubleAABB(boxA, &testor);
//
//
//
//
//	if (boxTest)
//	{
//		positionTest = boxB->isPointInside(boxB->getPosition()) || boxA->isPointInside(boxA->getPosition());
//		if (!positionTest)
//		{
//			sf::Vector2f corners[CORNER_SIZE];
//			corners[TL] = boxA->getCorners().first;
//			corners[TR] = sf::Vector2f(boxA->getCorners().second.x, boxA->getCorners().first.y);
//			corners[BR] = boxA->getCorners().second;
//			corners[BL] = sf::Vector2f(boxA->getCorners().first.x, boxA->getCorners().second.y);
//
//
//			for (unsigned int i = 0; i < CORNER_SIZE; i++)
//			{
//				if (boxB->isPointInside(corners[i]))
//				{
//					circPointTest = true;
//					break;
//				}
//			}
//
//			if (!circPointTest)
//			{
//				for (unsigned int i = 0; i < CORNER_SIZE; i++)
//				{
//					if (testor.isPointInside(corners[i]))
//					{
//						rectPointTest = true;
//						break;
//					}
//				}
//
//			}
//		}
//
//	}
//
//
//	bool retVal = boxTest;
//	if (boxTest)
//	{
//		if (positionTest)
//		{
//			retVal = positionTest;
//		}
//		else
//		{
//			if (circPointTest)
//			{
//				retVal = true;
//			}
//			else
//			{
//				retVal = !rectPointTest;
//			}
//		}
//
//	}
//
//	return retVal;
//
//
//
//
//}

//bool HitBoxCollider::collideDoubleCirc(CircularHitbox* boxA, CircularHitbox* boxB)
//{
//	const double distX = boxA->getPosition().x - boxB->getPosition().x;
//	const double distY = boxA->getPosition().y - boxB->getPosition().y;
//	const double radsum = boxA->getRadius() + boxB->getRadius();
//
//	return (distX * distX + distY * distY  < radsum * radsum);
//}

bool HitBoxCollider::collideDoublePolygon(const polygon& hb1, const polygon& hb2)
{
	double maxX = hb2[0].x;

	bool colliding = false;




	std::pair<sf::Vector2f, sf::Vector2f> bb1 = getBoundingBoxCorners(hb1);
	std::pair<sf::Vector2f, sf::Vector2f> bb2 = getBoundingBoxCorners(hb2);

	AAHitbox aabb1;
	aabb1.setCorners(bb1.first, bb1.second);

	AAHitbox aabb2;
	aabb2.setCorners(bb2.first, bb2.second);

	colliding = collideDoubleAABB(&aabb1, &aabb2);





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
				std::pair<sf::Vector2f, bool> poi = getLinePoi(hb1[i], hb1[i + 1], hb2[k], hb2[k + 1]);
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
				std::pair<sf::Vector2f, bool> poi = getLinePoi(hb1[0], sf::Vector2f(maxX, hb1[0].y), hb2[k], hb2[k + 1]);
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


AAHitbox* HitBoxCollider::downcastAABB(HitBox* box)
{
	if (box->getType() == HitBox::AABB)
	{
		return (AAHitbox*)(box);
	}
}

CircularHitbox* HitBoxCollider::downcastCirc(HitBox* box)
{
	if (box->getType() == HitBox::CIRC)
	{
		return (CircularHitbox*)(box);
	}
}


//sf::Vector2f HitBoxCollider::getCorVelDoubleAABB( sf::Vector2f vel, AAHitbox* boxA, AAHitbox* boxB)
//{
//
//	//first, we get all of the corners of the moving box
//	enum cornerNames {TL = 0, TR, BR, BL, CORNER_SIZE};
//
//	sf::Vector2f cornersA[CORNER_SIZE];
//
//	cornersA[TL] = boxA->getCorners().first;
//	cornersA[TR] = sf::Vector2f(boxA->getCorners().second.x, boxA->getCorners().first.y);
//	cornersA[BR] = boxA->getCorners().second;
//	cornersA[BL] = sf::Vector2f(boxA->getCorners().first.x, boxA->getCorners().second.y);
//
//
//
//	//then we get all of the corners of the stationary box.
//
//	sf::Vector2f cornersB[CORNER_SIZE];
//
//	cornersB[TL] = boxB->getCorners().first;
//	cornersB[TR] = sf::Vector2f(boxB->getCorners().second.x, boxB->getCorners().first.y);
//	cornersB[BR] = boxB->getCorners().second;
//	cornersB[BL] = sf::Vector2f(boxB->getCorners().first.x, boxB->getCorners().second.y);
//
//
//
//	unsigned int cornerIndex;	// the corner of the moving box that collides first
//
//	sf::Vector2f firstPoi;		// the forst point of intersection
//
//	bool foundFirst = false;	//if a point of intersection has been found or not;
//
//	double minDistSq = 0;		//the minimum distance found -- because first point of intersection means closest one to its corresponding corner.
//
//	for (unsigned int i = 0; i < CORNER_SIZE; i++)
//	{
//		//for each moving corner
//		const sf::Vector2f oldCornerA = cornersA[i] - vel;	//what the corner was before it was moved
//
//		for (unsigned int k = 0; k < CORNER_SIZE; k++)
//		{
//			// for each stationary corner
//			
//			std::pair<sf::Vector2f, bool> poi = getLinePoi(oldCornerA, cornersA[i], cornersB[k], cornersB[(k + 1) % CORNER_SIZE]);
//			//where the point of intersection was and if we should care about it
//
//			if (poi.second)
//			{
//				//if we care about it -- find out if its smaller than the rest
//				double tmpDistSq = distSq(oldCornerA, poi.first);
//				if (tmpDistSq <= minDistSq || !foundFirst)
//				{
//					foundFirst = true;
//					minDistSq = tmpDistSq;
//					firstPoi = poi.first;
//					cornerIndex = i;
//
//					//if so, record it and continue
//				}
//			}
//		}
//	}
//
//	
//	sf::Vector2f correctiveDistance = firstPoi - cornersA[cornerIndex]; //the exact distance overshot
//	
//	const double corMag = sqrt(magSq(correctiveDistance));	//magnitude of the corrective distance
//
//	correctiveDistance.x += correctiveDistance.x / corMag * knockback;	// add on the knockback
//	correctiveDistance.y += correctiveDistance.y / corMag * knockback;	
//
//	return correctiveDistance;	//return the corrective distance
//
//
//}
//
//sf::Vector2f HitBoxCollider::getCorVelCircAABB(sf::Vector2f vel, CircularHitbox* circA, AAHitbox* boxB)
//{
//
//}

//sf::Vector2f HitBoxCollider::getCorVelAABBCirc(sf::Vector2f vel, AAHitbox* boxA, CircularHitbox* circA)
//{
//
//	//first, we get all of the corners of the moving box
//	enum cornerNames {TL = 0, TR, BR, BL, CORNER_SIZE};
//
//	sf::Vector2f cornersA[CORNER_SIZE];
//
//	cornersA[TL] = boxA->getCorners().first;
//	cornersA[TR] = sf::Vector2f(boxA->getCorners().second.x, boxA->getCorners().first.y);
//	cornersA[BR] = boxA->getCorners().second;
//	cornersA[BL] = sf::Vector2f(boxA->getCorners().first.x, boxA->getCorners().second.y);
//
//
//
//
//}
//sf::Vector2f HitBoxCollider::getCorVelDoubleCirc(sf::Vector2f vel, CircularHitbox* circA, CircularHitbox* circB)
//{
//
//}

double HitBoxCollider::magSq(const sf::Vector2f& vec)
{
	return ((double)(vec.x * vec.x + vec.y * vec.y));
}


double HitBoxCollider::distSq(const sf::Vector2f& veca, const sf::Vector2f& vecb)
{
	return ((double)((veca.x - vecb.x) * (veca.x - vecb.x) + (veca.y - vecb.y) * (veca.y - vecb.y)));
}

//
//
//double HitBoxCollider::distanceSqToAALine(const sf::Vector2f& point, const sf::Vector2f& c1, const sf::Vector2f& c2)
//{
//
//	double distsq = 0;
//	bool cornDist = false;
//	if (c1.x == c2.x)
//	{
//		if ((c1.x > point.x && c2.x < point.x) || (c1.x < point.x && c2.x > point.x))
//		{
//			distsq = (c1.x - point.x) *  (c1.x - point.x);
//		}
//		else
//		{
//			cornDist = true;
//		}
//			
//	}
//	else if (c1.y == c2.y)
//	{
//			
//		if ((c1.y > point.y && c2.y < point.y) || (c1.y < point.y && c2.y > point.y))
//		{
//			distsq = (c1.y - point.y) *  (c1.y - point.y);
//		}
//		else
//		{
//			cornDist = true;
//		}
//	}
//	else
//	{
//		cornDist = true;
//	}
//
//	if (cornDist)
//	{
//		distsq = util::dmin(distSq(point, c1), distSq(point, c2));
//	}
//
//	return distsq;
//}



std::pair<sf::Vector2f, bool> HitBoxCollider::getLinePoi(const sf::Vector2f& u, const sf::Vector2f& v, const sf::Vector2f& a, const sf::Vector2f& b)
{
	bool legit = true;
	sf::Vector2f poi = sf::Vector2f (0,0);

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



//std::pair<std::pair<sf::Vector2f, bool>, std::pair<sf::Vector2f, bool>> HitBoxCollider::getLineCirclePois(const sf::Vector2f& u, const sf::Vector2f& v, const sf::Vector2f& c, const double& rad)
//{
//	if (u.x == v.x)
//	{ 
//		
//	}
//}



bool HitBoxCollider::checkPointOnLine(const sf::Vector2f& point, const sf::Vector2f& pa, const sf::Vector2f& pb)
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






std::pair<sf::Vector2f, sf::Vector2f> HitBoxCollider::getBoundingBoxCorners(const std::vector<sf::Vector2f>& points)
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




std::pair<sf::Vector2f, sf::Vector2f> HitBoxCollider::getKineticResponseDoublePolygon(const sf::Vector2f& vel, const polygon& polyA, const polygon& polyB)
{
	unsigned int sizb = polyB.size();

	bool foundFirst = false;
	double minDistSq = 1;
	unsigned int critLine1;
	unsigned int critLine2;
	unsigned int critCorner;

	sf::Vector2f firstPoi;

	for (unsigned int i = 0; i < polyA.size(); i++)
	{
		const sf::Vector2f oldPoint = polyA[i] - vel;
		for (unsigned int k = 0; k < polyB.size(); k++)
		{
			std::pair<sf::Vector2f, bool> poi = getLinePoi(oldPoint, polyA[i], polyB[k], polyB[(k + 1) % sizb]);
			if (poi.second)
			{
				double tmpDistSq = distSq(oldPoint, poi.first);
				if ((tmpDistSq < minDistSq) || (!foundFirst))
				{
					foundFirst = true;
					critLine1 = k;
					critLine2 = (k + 1) % sizb;
					critCorner = i;
					minDistSq = tmpDistSq;
					firstPoi = poi.first;
				}
			}
		}
	}

	sf::Vector2f corDisp = firstPoi - polyA[critCorner];

	const double corMag = sqrt(magSq(corDisp));	

	corDisp.x += corDisp.x / corMag * knockback;
	corDisp.y += corDisp.y / corMag * knockback;	


	sf::Vector2f critLineVec = polyB[critLine1] - polyB[critLine2]; //move line to origin
	

	//rotate by 90 degrees
	double tmpx = critLineVec.x;

	critLineVec.x = critLineVec.y;
	critLineVec.y = -tmpx;

	//normalize that vector
	sf::Vector2f normCLVec;
	normCLVec.x = critLineVec.x / sqrt(magSq(critLineVec));
	normCLVec.y = critLineVec.y / sqrt(magSq(critLineVec));

	//find dot product
	const double dotProduct = normCLVec.x * vel.x + normCLVec.y * vel.y;

	//find projection vector
	const sf::Vector2f projVec(dotProduct * normCLVec.x, dotProduct * normCLVec.y);

	//find other component (rejection vector)
	sf::Vector2f newVelocity = vel - projVec;

	return std::make_pair(corDisp, newVelocity);
	
}


