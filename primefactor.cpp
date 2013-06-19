#include <vector>

#include "primefactor.h"

namespace sencha
{

std::vector< natural > prime_factors( natural n )
{
	std::vector<natural> factors;

	if( n <= 1 ) return std::move( factors );

	for( natural i = 2; n != 1; ++i )
	{
		while( (n % i) == 0 )
		{
			factors.push_back( i );
			n /= i;
		}
	}
	return std::move( factors );
}

}	// namespace sencha

