#pragma once

#include <cstdint>
#include <vector>

namespace sencha
{

typedef std::uint64_t natural;

std::vector< natural > prime_factors( natural n );

}	// namespace sencha

