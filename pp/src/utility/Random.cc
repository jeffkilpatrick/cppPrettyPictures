#include "pp/utility/Random.h"

pp::IRandom::result_type pp::RandomDevice::operator()()
{
    return m_rand();
}
