#ifndef STRUCTS_H
#define STRUCTS_H

struct Position
{
	float x, y, z;
	float xPos[1];
	float yPos[1];
};

struct TriangleVertex
{
	float x, y, z;
	float r, g, b;
};

struct AABBBox
{
	XMFLOAT3 points[8];
	XMFLOAT3 min;
	XMFLOAT3 max;
};

struct AABBVertex
{
	XMFLOAT3 points[24];
};

struct TSphere
{
	Vector3		m_vecCenter;
	float       m_fRadius;
};

#endif // !STRUCTS_H
