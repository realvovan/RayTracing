#ifndef VEC3_H
#define VEC3_H

#include "cmath"
#include "iostream"

class Vector3 {
    double e[3];

    public:
        Vector3() : e{0,0,0} {}
        Vector3(double e0, double e1, double e2) : e{e0, e1, e2} {}

        double x() const {return e[0];}
        double y() const {return e[1];}
        double z() const {return e[2];}

        double length() const {
            return std::sqrt(
                this->e[0] * this->e[0]
                +this->e[1] * this->e[1]
                +this->e[2] * this->e[2]
            );
        }
        double dot(const Vector3& v) {
            return this->e[0] * v.e[0]
                +this->e[1] * v.e[1]
                +this->e[2] * v.e[2];
        }
        Vector3 cross(const Vector3& v) {
            return Vector3(
                this->e[1] * v.e[2] - this->e[2] * v.e[1],
                this->e[2] * v.e[0] - this->e[0] * v.e[2],
                this->e[0] * v.e[1] - this->e[1] * v.e[0]
            );
        }
        Vector3 unit() const {return (*this)/this->length();}
        Vector3 operator-() const {
            return Vector3(-e[0], -e[1], -e[2]);
        }
        double operator[](int i) const {return e[i];}
        double& operator[](int i) {return e[i];}
        Vector3 operator+(const Vector3& v) const {
            return Vector3(this->e[0]+v.e[0],this->e[1]+v.e[1],this->e[2]+v.e[2]);
        }
        Vector3 operator-(const Vector3& v) const {
            return Vector3(this->e[0]-v.e[0],this->e[1]-v.e[1],this->e[2]-v.e[2]);
        }
        Vector3 operator*(const Vector3& v) const {
            return Vector3(this->e[0]*v.e[0],this->e[1]*v.e[1],this->e[2]*v.e[2]);
        }
        Vector3 operator*(double other) const {
            return Vector3(this->e[0]*other,this->e[1]*other,this->e[2]*other);
        }
        Vector3 operator/(double other) const {
            return (*this) * (1/other);
        }
        Vector3& operator+=(const Vector3& other) {
            this->e[0] += other.e[0];
            this->e[1] += other.e[1];
            this->e[2] += other.e[2];
            return *this;
        }
        Vector3& operator*=(double other) {
            this->e[0] *= other;
            this->e[1] *= other;
            this->e[2] *= other;
            return *this;
        }
        Vector3& operator/=(double other) {
            return *this *= 1/other;
        }
};


inline std::ostream& operator<<(std::ostream& out, const Vector3& v) {
    return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

using Point3 = Vector3;

#endif