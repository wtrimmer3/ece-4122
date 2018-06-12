//
// Created by Brian Swenson on 1/29/18.
//

#pragma once
#include <iostream>

// William Trimmer
// ECE 4122
template<typename T>
class Vec3 {
public:

    Vec3() {
        x = 0.0;
        y = 0.0;
        z = 0.0;
    }

    Vec3(T newValue) {
        x = newValue;
        y = newValue;
        z = newValue;
    }

    Vec3(T newX, T newY, T newZ) {
        x = newX;
        y = newY;
        z = newZ;
    }

    // set/get x
    void setX(T newX) {
        x = newX;
    }
    T getX() const {
        return x;
    }

    // set/get y
    void setY(T newY) {
        y = newY;
    }
    T getY() const {
        return y;
    }

    // set/get z
    void setZ(T newZ) {
        z = newZ;
    }
    T getZ() const {
        return z;
    }

    double dot(const Vec3<T>& vecA) {
        return (this->x * vecA.x + this->y * vecA.y + this->z * vecA.z);
    }
    // + overload
    Vec3<T> operator+(const Vec3<T>& vecA) {
        return Vec3(x + vecA.x, y + vecA.y, z + vecA.z);
    }

    // += overload
    Vec3<T>& operator+=(const Vec3<T>& vecA) {
        x = x + vecA.x;
        y = y + vecA.y;
        z = z + vecA.z;
        return *this;
    }

    // - overload
    Vec3<T> operator-(const Vec3<T>& vecA) {
        return Vec3(x - vecA.x, y - vecA.y, z - vecA.z);
    }

    // -= overload
    Vec3<T>& operator-=(const Vec3<T>& vecA) {
        x -= vecA.x;
        y -= vecA.y;
        z -= vecA.z;
        return *this;
    }

    // / overload
    Vec3<T> operator/(int b) {
        return Vec3(x/b, y/b, z/b);
    }

    // * overload
    Vec3<T> operator*(int b) {
        return Vec3(x*b, y*b, z*b);
    }

    Vec3<T>& operator*=(int a) {
        x *= a;
        y *= a;
        z *= a;
        return *this;
    }

    Vec3<T>& operator/=(int a) {
        x /= a;
        y /= a;
        z /= a;
        return *this;
    }

    // ++ overload
    Vec3<T>& operator++() {
        Vec3 tempVec(this->getX(), this->getY(), this->getZ());
        this->x = tempVec.getZ();
        this->y = tempVec.getX();
        this->z = tempVec.getY();
        return *this;

    }

    Vec3<T> operator++(int) {
        Vec3 tempVec(this->getX(), this->getY(), this->getZ());
        x = tempVec.getZ();
        y = tempVec.getX();
        z = tempVec.getY();
        return tempVec;
    }

    // - operator
    Vec3<T>& operator--() {
        Vec3 tempVec(this->getX(), this->getY(), this->getZ());
        x = tempVec.getY();
        y = tempVec.getZ();
        z = tempVec.getX();
        return *this;
    }

    Vec3<T> operator--(int) {
        Vec3 tempVec(this->getX(), this->getY(), this->getZ());
        x = tempVec.getY();
        y = tempVec.getZ();
        z = tempVec.getX();
        return tempVec;
    }

    bool operator==(const Vec3<T>& vecA) {
        if(this->x == vecA.x) {
            if(this->y == vecA.y) {
                if(this->z == vecA.z) {
                    return true;
                }
            }
        }
        return false;
    }

    bool operator!=(const Vec3<T>& vecA) {
        if(this->x != vecA.x) {
            if(this->y != vecA.y) {
                if(this->z != vecA.z) {
                    return true;
                }
            }
        }
        return false;
    }


private:
    T x;
    T y;
    T z;
};

//for printing
template<typename T>
std::ostream& operator<<(std::ostream& stream, const Vec3<T>& vec) {
    stream << "X=" << vec.getX() << ", Y=" << vec.getY() << ", Z=" << vec.getZ();
    return stream;
}