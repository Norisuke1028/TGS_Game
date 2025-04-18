#pragma once

// 2�����x�N�g���N���X
class Vector2D
{
public:
	float x;				// x���W
	float y;				// y���W

public:
	// �R���X�g���N�^
	Vector2D();
	Vector2D(float scalar);
	Vector2D(float mx, float my);

	// �f�X�g���N�^
	~Vector2D();

public:
	// ���
	Vector2D& operator = (const Vector2D& location);

	// ���Z
	const Vector2D operator + (const Vector2D& location) const;
	// ���Z���
	Vector2D& operator += (const Vector2D& location);

	// ���Z
	const Vector2D operator - (const Vector2D& location) const;
	// ���Z���
	Vector2D& operator -= (const Vector2D& location);

	// ��Z
	const Vector2D operator * (const float& scalar) const;
	const Vector2D operator * (const Vector2D& location) const;
	// ��Z���
	Vector2D& operator *= (const float& scalar);
	Vector2D& operator *= (const Vector2D& location);

	// ���Z
	const Vector2D operator / (const float& scalar) const;
	const Vector2D operator / (const Vector2D& location) const;
	// ���Z���
	Vector2D& operator /= (const float& scalar);
	Vector2D& operator /= (const Vector2D& location);

public:
	// int�^�ɕϊ�
	void ToInt(int* x, int* y);
};
