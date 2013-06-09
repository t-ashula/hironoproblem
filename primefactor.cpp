#include <cstdint>
#include <iostream>

#include "primefactor.h"

namespace sencha
{

std::vector< natural > prime_factors( natural n )
{
	std::vector<natural> factors;

	natural val = n;
	for( natural i = 2; (i*i) <= n; ++i )
	{
		while( (val % i) == 0 )
		{
			factors.push_back( i );
			val /= i;
		}
	}
	if( val != 1 ) factors.push_back( val );
	return std::move( factors );
}

}	// namespace sencha
