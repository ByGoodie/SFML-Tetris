#include "Vector.h"

Goodie::Vector::Vector(int vec_size) : Goodie::Matrix(vec_size, 1, false) {}

Goodie::Vector::Vector(sf::Vector2i vec) : Goodie::Matrix(2, 1, true, vec.x, vec.y) {}

Goodie::Vector::Vector(sf::Vector3i vec) : Goodie::Matrix(3, 1, true, vec.x, vec.y, vec.z) {}

sf::Vector2i Goodie::Vector::convertToSFMLVector2() {
	if (this->line_count != 2)
		throw std::runtime_error("Vectors size don't suit each other.");

	sf::Vector2i convert_vec;
	convert_vec.x = (*this)[0][0];
	convert_vec.y = (*this)[1][0];
	return convert_vec;
}

sf::Vector3i Goodie::Vector::convertToSFMLVector3() {
	if (this->line_count != 3)
		throw std::runtime_error("Vectors size don't suit each other.");

	sf::Vector3i convert_vec;	
	convert_vec.x = (*this)[0][0];
	convert_vec.y = (*this)[1][0];
	convert_vec.z = (*this)[2][0];
	return convert_vec;
}
 
Goodie::Vector& Goodie::Vector::operator = (sf::Vector2i &&vec_r) {
	if (this->line_count != 2)
		return *this;

	(*this)[0][0] = vec_r.x;
	(*this)[1][0] = vec_r.y;
	return *this;
}

Goodie::Vector& Goodie::Vector::operator = (sf::Vector3i &&vec_r) {
	if (this->line_count != 3)
		return *this;

	(*this)[0][0] = vec_r.x;
	(*this)[1][0] = vec_r.y;
	(*this)[2][0] = vec_r.z;
	return *this;
}
