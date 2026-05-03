#pragma once
#include <string>
#include <sstream>
#include <iomanip>

namespace math {
	struct Matrix {
		float* operator[]( const int index ) { return matrix[index]; }
		const float* operator[]( const int index ) const { return matrix[index]; }

		float matrix[4][4];

		[[nodiscard]] std::string ToString() const {
			std::ostringstream oss;
			oss << std::fixed << std::setprecision(2);

			for ( const auto& row : matrix ) {
				for  (const float col : row ) {
					oss << std::setw(8) << col;
				}
				oss << "\n";
			}

			return oss.str();
		}
	};
}

typedef math::Matrix Matrix;