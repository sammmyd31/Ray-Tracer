#ifndef VECTOR3_H
#define VECTOR3_H

class vector3 {
public:
    double e[3];

    vector3() : e{0, 0, 0} {}
    vector3(double e0, double e1, double e2) : e{e0, e1, e2} {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    vector3 operator-() const { return vector3(-e[0], -e[1], -e[2]); }
    double operator[](int i) const { return e[i]; }
    double& operator[](int i) { return e[i]; }

    vector3& operator+=(const vector3& v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vector3& operator*=(double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vector3& operator/=(double t) {
        return *this *= 1/t;
    }
    
    double length() const {
        return std::sqrt(length_squared());
    }

    double length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    bool near_zero() const {
        double s = 1e-8;
        return (std::fabs(e[0] < s) && std::fabs(e[1] < s) && std::fabs(e[2] < s));
    }

    static vector3 random() {
        return vector3(random_double(), random_double(), random_double());
    }

    static vector3 random(double min, double max) {
        return vector3(random_double(min, max), random_double(min, max), random_double(min, max));
    }
};

using point3 = vector3;

inline std::ostream& operator<<(std::ostream& out, const vector3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vector3 operator+(const vector3& u, const vector3& v) {
    return vector3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vector3 operator-(const vector3& u, const vector3& v) {
    return vector3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vector3 operator*(const vector3& u, const vector3& v) {
    return vector3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vector3 operator*(double t, const vector3& v) {
    return vector3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vector3 operator*(const vector3& v, double t) {
    return t * v;
}

inline vector3 operator/(const vector3& v, double t) {
    return (1/t) * v;
}

inline double dot(const vector3& u, const vector3& v) {
    return u.e[0] * v.e[0] +
           u.e[1] * v.e[1] +
           u.e[2] * v.e[2];
}

inline vector3 cross(const vector3& u, const vector3& v) {
    return vector3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vector3 unit_vector(const vector3& v) {
    return v / v.length();
}

inline vector3 random_unit_vector() {
    while (true) {
        vector3 p = vector3::random(-1, 1);
        double lensq = p.length_squared();
        if (1e-160 < lensq && lensq <= 1) {
            return p / sqrt(lensq);
        }
    }
}

inline vector3 reflect(const vector3& v, const vector3& n) {
    return v - 2*dot(v, n)*n;
}

inline vector3 refract(const vector3& uv, const vector3& n, double etai_over_etat) {
    double cos_theta = std::fmin(dot(-uv, n), 1.0);
    vector3 r_out_perp = etai_over_etat * (uv + cos_theta*n);
    vector3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

#endif