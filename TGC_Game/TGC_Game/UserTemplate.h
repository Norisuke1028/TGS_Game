#pragma once

// ��Βl��Ԃ�
template<typename T>
T Abs(T value)
{
	T result;

	if (value > 0)
	{
		result = value;
	}
	else
	{
		result = -value;
	}

	return result;
}

// �l���r���đ傫���l��Ԃ�
template <typename T>
T Max(T a, T b)
{
	T result;

	if (a < b)
	{
		result = b;
	}
	else
	{
		result = a;
	}

	return result;
}

// �l���r���ď������l��Ԃ�
template <typename T>
T Min(T a, T b)
{
	T result;

	if (a > b)
	{
		result = b;
	}
	else
	{
		result = a;
	}

	return result;
}