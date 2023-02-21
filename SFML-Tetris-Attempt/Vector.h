#ifndef VECTOR_H
#define VECTOR_H

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include "Matrix.h"

namespace Goodie {
	class Vector : public Matrix {
	public:
		Vector(int vec_size);
		Vector(sf::Vector2i vec); 
		Vector(sf::Vector3i vec);

		sf::Vector2i convertToSFMLVector2();
		sf::Vector3i convertToSFMLVector3();
		
		Vector& operator = (sf::Vector2i &&vec_r);
		Vector& operator = (sf::Vector3i &&vec_r);
	};
}

#endif
