#ifndef VECTOR2_H
#define VECTOR2_H

template<typename T>
struct Vector2 {
	T X, Y;
	Vector2(T x, T y) : X(x), Y(y) {}

	Vector2<T> operator*(T m) {
		return Vector2<T>(X * m, Y * m);
	}

	Vector2<T> operator/(T m) {
		return Vector2<T>(X / m, Y / m);
	}

#ifdef SFML_GRAPHICS_HPP
	operator sf::Vector2<T>() const {
		return sf::Vector2<T>(X, Y);
	}
#endif

	template<typename T1>
	friend inline std::ostream& operator<<(std::ostream& os, const Vector2<T1>& o);
};

template<typename T1>
inline std::ostream& operator<<(std::ostream& os, const Vector2<T1>& o) {
    return os << "{ x: " << o.X << ", Y: " << o.Y << " }";
}

typedef Vector2<float> Vector2f;

#endif