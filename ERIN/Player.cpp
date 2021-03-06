#include "Player.h"

Player::Player()
	: name("noName"),
	x(0.0f), y(0.0f), z(0.0f)
{
}

Player::Player(string name, float x, float y, float z)
{
	this->name = name;
	this->x = x;
	this->y = y;
	this->z = z;

	this->maximumSpeed = 0.1f;
	this->currentSpeed = 0.0f;

	this->speed = 0.0f;
	this->acceleration = 0.0005f;

	this->input = new Input(GamePadIndex_One);

	//this->objectMatrix = new Matrix();
	this->shipMatrix = new Matrix();
	this->turretMatrix = new Matrix();
	this->shadowMatrix = new Matrix();

	this->shipPos = new Position{ this->x, this->y, this->z };
	this->turretPos = new Position{ this->x + 1.0f, this->y, this->z };

	// collision
	this->sphere = new TSphere();
	this->sphere->m_vecCenter = Vector3(this->x, this->y, this->z);
	this->sphere->m_fRadius = 0.5f;
}

Player::~Player()
{
	delete this->input;
	delete this->shipMatrix;
	delete this->turretMatrix;
	delete this->shipPos;
	delete this->turretPos;
	delete this->sphere;
	delete this->shadowMatrix;
}


void Player::playerInput()
{
	if (input->isConnected())
	{
		// ship thumbstick states
		this->thumbLeftX = input->State._left_thumbstick.x;
		this->thumbLeftY = input->State._left_thumbstick.y;

		// turret thumbstick states
		this->thumbRightX = input->State._right_thumbstick.x;
		this->thumbRightY = input->State._right_thumbstick.y;

		// ship accelerating or not
		if ((thumbLeftX && thumbLeftY) == 0)
		{
			this->accelerating = false;
		}
		else
		{
			this->accelerating = true;
		}
	}
}

void Player::update(double dt)
{
	this->shipPos->x = this->x;
	this->shipPos->y = this->y;
	this->shipPos->z = this->z;

	this->turretPos->x = this->x;
	this->turretPos->y = this->y;

	if (!accelerating)
	{
		// deacceleration
		if (this->thumbLeftX == 0)
		{
			velocityX *= 0.8f;
		}
		if (this->thumbLeftY == 0)
		{
			velocityY *= 0.8f;
		}
	}
	else
	{
		// Speed += ((MoveDirection * MaximumSpeed) - Speed) * AccelerationFactor
		velocityX += ((thumbLeftX * maximumSpeed) - velocityX) * abs(thumbLeftX);
		velocityY += ((thumbLeftY * maximumSpeed) - velocityY) * abs(thumbLeftY);
	}

	// ship heading
	if ((thumbLeftX && thumbLeftY) != 0)
	{
		plannedHeading = XMConvertToDegrees(atan2f(thumbLeftX, thumbLeftY));
	}

	// turret heading
	if ((thumbRightX && thumbRightY) != 0)
	{
		turret_plannedHeading = XMConvertToDegrees(atan2f(thumbRightX, thumbRightY));
	}

	x = x + velocityX;
	y = y + velocityY;

	// ship rotation
	r_x += dt * getVx();
	r_y += dt * getVy();
	if (heading != plannedHeading)
	{
		computeTurn(dt);
	}

	// turret rotation
	tr_x += dt * getTVx();
	tr_y += dt * getTVy();
	if (turrent_heading != turret_plannedHeading)
	{
		turretComputeTurn(dt);
	}

	this->sphere->m_vecCenter = Vector3(this->x, this->y, this->z);

	// turret matrix
	*this->turretMatrix =
		XMMatrixScaling(1.0f, 1.0f, 1.0f)
		* XMMatrixRotationZ(XMConvertToRadians((float)-turrent_heading))
		* XMMatrixTranslation(this->x, this->y, this->z);

	// ship matrix
	*this->shipMatrix = XMMatrixScaling(1.0f, 1.0f, 1.0f)
		* XMMatrixRotationZ(XMConvertToRadians((float)-heading))
		* XMMatrixTranslation(this->x, this->y, this->z);

	//shadow matrix
	*this->shadowMatrix = XMMatrixScaling(1.0f, 1.0f, 1.0f)
		* XMMatrixRotationZ(XMConvertToRadians((float)-heading))
			* XMMatrixTranslation(this->x * 1.03, this->y * 1.03, this->z + 0.45);

}

void Player::PlayerReset()
{
	this->SetX(0);
	this->SetY(0);
	this->SetZ(0);

	this->HP = 6;

	this->heading = 0;
	this->plannedHeading = 0;
}

void Player::NewFloorReset()
{
	this->SetX(0);
	this->SetY(0);
	this->SetZ(0);

	this->heading = 0;
	this->plannedHeading = 0;
}

void Player::computeTurn(double dt)
{
	double dh = plannedHeading - heading;
	if (dh < -180)
		dh += 360;
	if (dh > 180)
		dh -= 360;
	if (abs(dh) < turnRate * dt)
		heading = plannedHeading;
	else
	{
		int dir = 1;
		if (dh < 0)
			dir = -1;
		heading += turnRate * dt * dir;
	}
}

void Player::turretComputeTurn(double dt)
{
	double dh = turret_plannedHeading - turrent_heading;
	if (dh < -180)
		dh += 360;
	if (dh > 180)
		dh -= 360;
	if (abs(dh) < turret_turnRate * dt)
		turrent_heading = turret_plannedHeading;
	else
	{
		int dir = 1;
		if (dh < 0)
			dir = -1;
		turrent_heading += turret_turnRate * dt * dir;
	}
}

void Player::turnTo(double newHeading)
{
	plannedHeading = newHeading;
}

double Player::getVx()
{
	return r_speed * acos(heading * M_PI / 180);
}

double Player::getVy()
{
	return r_speed * asin(heading * M_PI / 180);
}

double Player::getTVx()
{
	return tr_speed * acos(heading * M_PI / 180);
}

double Player::getTVy()
{
	return tr_speed * asin(heading * M_PI / 180);
}

void Player::hpCooldown(double hpdt)
{
	if (hpcooldown <= hpcurrentTime)
	{
		hpcurrentTime = 0.0f;
		hpReady = true;
	}
	else
	{
		hpcurrentTime += hpdt;
	}
}