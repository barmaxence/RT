#pragma once

#include <vector>

class MPerlinNoise
{
public:
    MPerlinNoise(void);
    MPerlinNoise(const MPerlinNoise& src);
    MPerlinNoise(MPerlinNoise&& src);
    MPerlinNoise(unsigned int seed);
    ~MPerlinNoise(void);
    MPerlinNoise& operator=(const MPerlinNoise& rhs);
    MPerlinNoise& operator=(MPerlinNoise&& rhs);
    double noise(double x, double y, double z);
private:
    double fade(double t);
    double lerp(double t, double a, double b);
    double grad(int hash, double x, double y, double z);
    std::vector<int> p;
};