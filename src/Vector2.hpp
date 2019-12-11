#ifndef AG_VECTOR2_H
#define AG_VECTOR2_H

#include <Box2D/Box2D.h>

template<typename T>
struct Vector2 {
	T X, Y;
	Vector2() : X(0), Y(0) {}
	Vector2(T x, T y) : X(x), Y(y) {}
	Vector2(const b2Vec2 vec) : X(vec.x), Y(vec.y) {}
	template<typename T2>
	Vector2(const Vector2<T2> vec) : X((T)vec.X), Y((T)vec.Y) {}

	Vector2<T> operator*(const T m) const {
		return Vector2<T>(X * m, Y * m);
	}

	Vector2<T> operator*(const Vector2<T> m) const {
		return Vector2<T>(X * m.X, Y * m.Y);
	}

	Vector2<T> operator/(const T m) const {
		return Vector2<T>(X / m, Y / m);
	}

	operator b2Vec2() const {
		return b2Vec2(X, Y);
	}

#ifdef SFML_GRAPHICS_HPP
	operator sf::Vector2<T>() const {
		return sf::Vector2<T>(X, Y);
	}
	template<typename T2>
	operator sf::Vector2<T2>() const {
		return sf::Vector2<T2>(X, Y);
	}
	Vector2(const sf::Vector2<T>& vec) : X(vec.x), Y(vec.y) {}
#endif

	template<typename T1>
	friend inline std::ostream& operator<<(std::ostream& os, const Vector2<T1>& o);
};

template<typename T1>
inline std::ostream& operator<<(std::ostream& os, const Vector2<T1>& o) {
    return os << "{ x: " << o.X << ", Y: " << o.Y << " }";
}
typedef Vector2<uint> Vector2u;
typedef Vector2<float> Vector2f;

#endif