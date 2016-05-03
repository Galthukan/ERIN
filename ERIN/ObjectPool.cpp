#include "ObjectPool.h"

ObjectPool::ObjectPool()
{
	// Bullets
	firstAvailable = &bullets[0];

	for (int i = 0; i < this->b_poolSize - 1; i++)
	{
		bullets[i].setNext(&bullets[i + 1]);
	}

	bullets[this->b_poolSize - 1].setNext(NULL);

	// Enemies
	first = &enemies[0];

	for (int i = 0; i < this->e_poolSize - 1; i++)
	{
		enemies[i].setObjectID(100 + i);
		enemies[i].setObjectName("enemy" + i);

		/*enemies[i].setObjectPosX(0.0f);
		enemies[i].setObjectPosY(0.0f);
		enemies[i].setObjectPosZ(0.0f);*/

		// speed
		float LO = 0.07f, HI = 0.15f, lO = 0.0006f, hI = 0.0009f;
		float Random = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
		enemies[i].setMaxSpeed(Random);

		float Ran = lO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (hI - lO)));
		enemies[i].setAcceleration(Ran);

		enemies[i].setNext(&enemies[i + 1]);
	}

	enemies[this->e_poolSize - 1].setNext(NULL);
}

ObjectPool::~ObjectPool()
{
}

//void ObjectPool::animate()
//{
//
//	for (int i = 0; i < poolSize; i++)
//	{
//		if (bullets[i].getInUse())
//		{
//			bullets[i].setNext(firstAvailable);
//			firstAvailable = &bullets[i];
//		}
//	}
//}

/*void ObjectPool::createb(float x, float y, float z, int lifeTime, bool inUse)
{
	//assert(firstAvailable != NULL);

	for (int i = 0; i < poolSize; i++)
	{
		if (!bullets[i].getInUse())
		{
			bullets[i].iniBullet(x, y, z, lifeTime, inUse);
			bullets[i].inUse = true;
		}
	}
	
	/*Bullet* newBullet = firstAvailable;
	firstAvailable = newBullet->getNext();

	newBullet->iniBullet(x, y, z, lifeTime);*/
//}

void ObjectPool::fire()
{
	
	/*if (fbull.lastFire == 0)
	{
		Bullet* newBullet = firstAvailable;
		firstAvailable = newBullet->getNext();

		newBullet->iniBullet(0, 0, 0, fbull.timeLeft);
		fbull.lastFire = 100;
	}*/
	//if (fbull.canFire=true)
	//{
		for (int i = 0; i < this->b_poolSize; i++)
		{
			if (!bullets[i].getInUse())
			{
				bullets[i].iniBullet(fbull.state.alive.x, fbull.state.alive.y, fbull.state.alive.z, fbull.timeLeft);//(bullets[i].bulletPos->x, bullets[i].bulletPos->y, bullets[i].bulletPos->z, fbull.timeLeft);
				bullets[i].inUse = true;
				//fbull.canFire = false;
				//animate();
				//pfbull.lastFire = 200;
				return;
			}
		}
	//}
}

void ObjectPool::createEnemy(float x, float y, float z)
{
	for (int i = 0; i < e_poolSize; i++)
	{
		if (!enemies[i].getInUse())
		{
			enemies[i].setObjectPosX(x);
			enemies[i].setObjectPosY(y);
			enemies[i].setObjectPosZ(z);
			enemies[i].setInUse(true);
			return;
		}
	}
}
