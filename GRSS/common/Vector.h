/*
 * [PROJECT NAME] General Relativity Simulation Software (GRSS)
 * [FILE NAME] Vector.h 
 * [DESCRIPTION] Class for Vectors and Vector mathmatics 
 * 
 * (c) 2026 Electro-Corp, All rights reserved. 
 *     Reproduction or distribution of this code without permission is prohibited.
 *     Code Source avaliable for educational and research purposes only. For commercial use, please contact Electro-Corp.
 *     Contributions to this project are welcome. Please refer to the CONTRIBUTING.md file for guidelines on how to contribute.
*/
#pragma once

class Vector3{
    public:
        double x, y, z;

        Vector3(double x, double y, double z) : x(x), y(y), z(z){}
        Vector3() : x(0), y(0), z(0){};

        Vector3 operator+(const Vector3& other){
            return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
        }

        Vector3 operator-(const Vector3& other){
            return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
        }
};

static Vector3 CrossProduct(const Vector3& a, const Vector3& b){
    return Vector3((a.y * b.z) - (a.z * b.y), (a.z * b.x) - (a.x * b.z), (a.x * b.y) - (a.y * b.x));
}

static double DotProduct(const Vector3& a, const Vector3& b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
}