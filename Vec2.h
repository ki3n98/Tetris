#pragma once

template <typename T>
class Vec2 {
public:
	Vec2() = default;
	constexpr Vec2(T x, T y) //create object at compile time
		:
		x(x),
		y(y)
	{}

	constexpr T getX() const { return x; }
	constexpr T getY() const { return y; }
	constexpr void setX(T xIn) { x = xIn; }
	constexpr void setY(T yIn) { y = yIn; }

public:
	bool operator== (const Vec2& rhs) const
	{
		return (x == rhs.x && y == rhs.y);
	}
	constexpr Vec2 operator+ (const Vec2& rhs) const
	{
		return { x + rhs.x, y + rhs.y };
	}
	constexpr Vec2 operator+ (const int rhs) const
	{
		return { x + rhs, y + rhs };
	}
	constexpr Vec2& operator+=(const Vec2& rhs)
	{
		return *this = *this + rhs;
	}
	constexpr Vec2 operator- (const Vec2& rhs) const
	{
		return { x - rhs.x, y - rhs.y };
	}
	constexpr Vec2 operator- (const int rhs) const
	{
		return { x - rhs, y - rhs };
	}
	constexpr Vec2& operator-=(const Vec2& rhs)
	{
		return { x - rhs.x, y - rhs.y };
	}
	constexpr Vec2& operator* (const Vec2<T>& rhs) const
	{
		return { x * rhs.y, y * rhs.y };
	}
	constexpr Vec2& operator*=(const Vec2& rhs)
	{
		return *this = *this * rhs;
	}
	constexpr Vec2 operator* (const int rhs) const
	{
		return { x * rhs, y * rhs };
	}

private:
	T x;
	T y;

};
