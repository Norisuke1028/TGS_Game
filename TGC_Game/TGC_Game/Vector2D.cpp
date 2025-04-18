#include "Vector2D.h"
#include "UserTemplate.h"

// �R���X�g���N�^
Vector2D::Vector2D() : x(0.0f), y(0.0f)
{
}
Vector2D::Vector2D(float scalar) : x(scalar), y(scalar)
{
}
Vector2D::Vector2D(float mx, float my) : x(mx), y(my)
{
}

// �f�X�g���N�^
Vector2D::~Vector2D()
{
}

// x�Ay��location����
Vector2D& Vector2D::operator=(const Vector2D& location)
{
	this->x = location.x;
	this->y = location.y;

	return *this;
}

// x�Ay��location�����Z�����l��Ԃ�
const Vector2D Vector2D::operator+(const Vector2D& location) const
{
	Vector2D result = Vector2D(0.0f);

	result.x = this->x + location.x;
	result.y = this->y + location.y;

	return result;
}

// x�Ay��location�����Z���
Vector2D& Vector2D::operator+=(const Vector2D& location)
{
	this->x += location.x;
	this->y += location.y;

	return *this;
}

// x�Ay����location�����Z�����l��Ԃ�
const Vector2D Vector2D::operator-(const Vector2D& location) const
{
	Vector2D result = Vector2D(0.0f);

	result.x = this->x - location.x;
	result.y = this->y - location.y;

	return result;
}

// x�Ay����location�����Z���
Vector2D& Vector2D::operator-=(const Vector2D& location)
{
	this->x -= location.x;
	this->y -= location.y;

	return *this;
}

// x�Ay��scalar�{�ɂ����l��Ԃ�
const Vector2D Vector2D::operator*(const float& scalar) const
{
	Vector2D result = Vector2D(0.0f);

	result.x = this->x * scalar;
	result.y = this->y * scalar;

	return result;
}

// x�Ay��location���|�����l��Ԃ�
const Vector2D Vector2D::operator*(const Vector2D& location) const
{
	Vector2D result = Vector2D(0.0f);

	result.x = this->x * location.x;
	result.y = this->y * location.y;

	return result;
}

// x�Ay��scalar�{�ɂ���
Vector2D& Vector2D::operator*=(const float& scalar)
{
	this->x *= scalar;
	this->y *= scalar;

	return *this;
}

// x�Ay��location���|����
Vector2D& Vector2D::operator*=(const Vector2D& location)
{
	this->x *= location.x;
	this->y *= location.y;

	return *this;
}

// x�Ay��scalar�Ŋ������l��Ԃ�
const Vector2D Vector2D::operator/(const float& scalar) const
{
	// 1e-6f�E�E�E�������l
	if (Abs(scalar) < 1e-6f)
	{
		return Vector2D(0.0f);
	}

	return Vector2D(this->x / scalar, this->y / scalar);
}

// x�Ay��location�Ŋ������l��Ԃ�
const Vector2D Vector2D::operator/(const Vector2D& location) const
{
	// 1e-6f�E�E�E�������l
	if ((Abs(location.x) < 1e-6f) || (Abs(location.y) < 1e-6f))
	{
		return Vector2D(0.0f);
	}

	return Vector2D(this->x / location.x, this->y / location.y);
}

// x�Ay��scalar�Ŋ���
Vector2D& Vector2D::operator/=(const float& scalar)
{
	if (Abs(scalar) < 1e-6f)
	{
		this->x = 0.0f;
		this->y = 0.0f;
	}
	else
	{
		this->x /= scalar;
		this->y /= scalar;
	}
	return *this;
}

// x�Ay��location�Ŋ���
Vector2D& Vector2D::operator/=(const Vector2D& location)
{
	if ((Abs(location.x) < 1e-6f) || (Abs(location.y) < 1e-6f))
	{
		this->x = 0.0f;
		this->y = 0.0f;
	}
	else
	{
		this->x /= location.x;
		this->y /= location.y;
	}
	return *this;
}

// int�^�ɕϊ�
void Vector2D::ToInt(int* x, int* y)
{
	*x = static_cast<int>(this->x);
	*y = static_cast<int>(this->y);
}
