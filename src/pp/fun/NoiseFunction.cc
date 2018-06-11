#include "pp/fun/NoiseFunction.h"

#include <array>
#include <cmath>

using pp::ColorNoiseFunction;
using pp::GrayscaleNoiseFunction;

// Minimally adapted from https://mrl.nyu.edu/~perlin/noise/

// JAVA REFERENCE IMPLEMENTATION OF IMPROVED NOISE - COPYRIGHT 2002 KEN PERLIN.

std::array<int, 512> MakePermutations()
{
    std::array<int, 512> p{};
    std::array<int, 512> permutation{ { 151,160,137,91,90,15,
    131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
    190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
    88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
    77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
    102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
    135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
    5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
    223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
    129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
    251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
    49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
    138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
    } };

    for (int i=0; i < 256 ; i++) p[256+i] = p[i] = permutation[i];
    return p;
}

const std::array<int, 512>& permutations()
{
    static std::array<int, 512> s_p = MakePermutations();

    return s_p;
}

static double fade(double t) { return t * t * t * (t * (t * 6 - 15) + 10); }

static double lerp(double t, double a, double b) { return a + t * (b - a); }

static double grad(int hash, double x, double y, double z) {
  int h = hash & 15;                      // CONVERT LO 4 BITS OF HASH CODE
  double u = h<8 ? x : y,                 // INTO 12 GRADIENT DIRECTIONS.
         v = h<4 ? y : h==12||h==14 ? x : z;
  return ((h&1) == 0 ? u : -u) + ((h&2) == 0 ? v : -v);
}
static double noise(double x, double y, double z) {
  const auto& p = permutations();
  int X = (int)std::floor(x) & 255,                  // FIND UNIT CUBE THAT
      Y = (int)std::floor(y) & 255,                  // CONTAINS POINT.
      Z = (int)std::floor(z) & 255;
  x -= std::floor(x);                                // FIND RELATIVE X,Y,Z
  y -= std::floor(y);                                // OF POINT IN CUBE.
  z -= std::floor(z);
  double u = fade(x),                                // COMPUTE FADE CURVES
         v = fade(y),                                // FOR EACH OF X,Y,Z.
         w = fade(z);
  int A = p[X  ]+Y, AA = p[A]+Z, AB = p[A+1]+Z,      // HASH COORDINATES OF
      B = p[X+1]+Y, BA = p[B]+Z, BB = p[B+1]+Z;      // THE 8 CUBE CORNERS,

  return lerp(w, lerp(v, lerp(u, grad(p[AA  ], x  , y  , z   ),  // AND ADD
                                 grad(p[BA  ], x-1, y  , z   )), // BLENDED
                         lerp(u, grad(p[AB  ], x  , y-1, z   ),  // RESULTS
                                 grad(p[BB  ], x-1, y-1, z   ))),// FROM  8
                 lerp(v, lerp(u, grad(p[AA+1], x  , y  , z-1 ),  // CORNERS
                                 grad(p[BA+1], x-1, y  , z-1 )), // OF CUBE
                         lerp(u, grad(p[AB+1], x  , y-1, z-1 ),
                                 grad(p[BB+1], x-1, y-1, z-1 ))));
}

ColorNoiseFunction::ColorNoiseFunction(IFunctionPtr arg)
    : IUnaryFunction(std::move(arg))
{ }

float ColorNoiseFunction::EvalSingle(float x, float y, float a) const
{
    return noise(x, y, a);
}

const std::string& ColorNoiseFunction::GetName() const
{
    return ColorNoiseFunctionGenerator{}.GetName();
}

pp::IFunctionPtr pp::ColorNoiseFunctionGenerator::Make(IFunctionPtr arg)
{
    return std::make_unique<ColorNoiseFunction>(std::move(arg));
}

const std::string& pp::ColorNoiseFunctionGenerator::GetName() const
{
    static std::string name = "color-noise";
    return name;
}

// ------------------------------------------------------

GrayscaleNoiseFunction::GrayscaleNoiseFunction(IFunctionPtr arg)
    : IFunction(std::move(arg))
{ }

pp::Color GrayscaleNoiseFunction::Eval(float x, float y) const
{
    auto c = GetArgs().at(0)->Eval(x, y);
    auto gray = (c.C1 + c.C2 + c.C3) / 3.f;
    return Color{ static_cast<float>(noise(x, y, gray)) };
}

void GrayscaleNoiseFunction::EvalRow(const std::vector<float>& xs, float y, pp::Color* out) const
{
    auto& buf = m_buffers.at(0);
    buf.resize(xs.size(), Color{0.f});

    GetArgs().at(0)->EvalRow(xs, y, buf.data());

    for (size_t i = 0; i < xs.size(); ++i)
    {
        auto z = (buf[i].C1 + buf[i].C2 + buf[i].C3) / 3.f;
        *out = Color{ static_cast<float>(noise(xs[i], y, z)) };
        ++out;
    }
}

const std::string& GrayscaleNoiseFunction::GetName() const
{
    return GrayscaleNoiseFunctionGenerator{}.GetName();
}

pp::IFunctionPtr pp::GrayscaleNoiseFunctionGenerator::Make(IFunctionPtr arg)
{
    return std::make_unique<GrayscaleNoiseFunction>(std::move(arg));
}

const std::string& pp::GrayscaleNoiseFunctionGenerator::GetName() const
{
    static std::string name = "grayscale-noise";
    return name;
}
