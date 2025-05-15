// ECVector.h
#ifndef ECVECTOR_H
#define ECVECTOR_H

#include <vector>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <algorithm>

template<typename T>
class ECVector {
private:
    std::vector<T> coordinates;
    int dimension;

public:
    // Construct from a std::vector of coordinates
    ECVector(const std::vector<T>& coords)
        : coordinates(coords), dimension(static_cast<int>(coords.size())) {}

    virtual ~ECVector() = default;

    // Copy constructor
    ECVector(const ECVector& other)
        : coordinates(other.coordinates), dimension(other.dimension) {}

    // Move constructor
    ECVector(ECVector&& other) noexcept
        : coordinates(std::move(other.coordinates)), dimension(other.dimension) {}

    // Copy assignment
    ECVector& operator=(const ECVector& other) {
        if (this != &other) {
            coordinates = other.coordinates;
            dimension = other.dimension;
        }
        return *this;
    }

    // Move assignment
    ECVector& operator=(ECVector&& other) noexcept {
        if (this != &other) {
            coordinates = std::move(other.coordinates);
            dimension = other.dimension;
        }
        return *this;
    }

    // Element access (read-only)
    const T& operator[](int index) const {
        return coordinates[index];
    }

    // Element access (modifiable)
    T& operator[](int index) {
        return coordinates[index];
    }

    // Number of dimensions
    const int& getDimension() const {
        return dimension;
    }

    // Euclidean magnitude
    double getMagnitude() const {
        double sum = 0.0;
        for (const auto& v : coordinates) {
            sum += static_cast<double>(v) * static_cast<double>(v);
        }
        return std::sqrt(sum);
    }

    // Return a unit‐vector copy
    ECVector normalized() const {
        double mag = getMagnitude();
        std::vector<T> result;
        result.reserve(dimension);
        for (const auto& v : coordinates) {
            result.push_back(static_cast<T>(v / mag));
        }
        return ECVector(result);
    }

    // Vector addition (handles unequal dimensions by treating missing coords as zero)
    ECVector operator+(const ECVector& other) const {
        int maxDim = std::max(dimension, other.dimension);
        std::vector<T> result(maxDim, T());
        for (int i = 0; i < maxDim; ++i) {
            T a = (i < dimension ? coordinates[i] : T());
            T b = (i < other.dimension ? other.coordinates[i] : T());
            result[i] = a + b;
        }
        return ECVector(result);
    }

    // Vector subtraction
    ECVector operator-(const ECVector& other) const {
        int maxDim = std::max(dimension, other.dimension);
        std::vector<T> result(maxDim, T());
        for (int i = 0; i < maxDim; ++i) {
            T a = (i < dimension ? coordinates[i] : T());
            T b = (i < other.dimension ? other.coordinates[i] : T());
            result[i] = a - b;
        }
        return ECVector(result);
    }

    // Dot product (requires same dimension)
    T operator*(const ECVector& other) const {
        if (dimension != other.dimension) {
            throw std::invalid_argument("Dot product requires vectors of same dimension");
        }
        T sum = T();
        for (int i = 0; i < dimension; ++i) {
            sum += coordinates[i] * other.coordinates[i];
        }
        return sum;
    }

    // Multiply by scalar (this * scalar)
    ECVector operator*(const T scalar) const {
        std::vector<T> result(dimension, T());
        for (int i = 0; i < dimension; ++i) {
            result[i] = coordinates[i] * scalar;
        }
        return ECVector(result);
    }

    // Divide by scalar (this / scalar)
    ECVector operator/(const T scalar) const {
        std::vector<T> result(dimension, T());
        for (int i = 0; i < dimension; ++i) {
            result[i] = coordinates[i] / scalar;
        }
        return ECVector(result);
    }

    // Print for debugging
    void display() const {
        std::cout << "{" << coordinates[0];
        for (int i = 1; i < dimension; ++i) {
            std::cout << "," << coordinates[i];
        }
        std::cout << "}" << std::endl;
    }

    // Scalar * vector
    friend ECVector operator*(const T scalar, const ECVector& vec) {
        return vec * scalar;
    }

    // Scalar / vector (yields coordinate-wise scalar/divide)
    friend ECVector operator/(const T scalar, const ECVector& vec) {
        std::vector<T> result(vec.dimension, T());
        for (int i = 0; i < vec.dimension; ++i) {
            result[i] = scalar / vec.coordinates[i];
        }
        return ECVector(result);
    }
};

#endif // ECVECTOR_H
