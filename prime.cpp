#include <vector>
#include <limits>
#include <cmath>
#include <cstdint>

#include "prime.h"

using namespace std;

namespace sencha
{

PrimeTable::PrimeTable( uint32_t n )
	: N( n )
	, SQRT_N( std::ceil( std::sqrt( n ) ) )
{
	mPrimeTable.resize( N >> 3 );

	clear();
	calculate();
}

bool PrimeTable::isPrime(uint32_t n) const
{
	return (mPrimeTable[n >> 5] >> (n & 31)) & 0x01;
}

bool PrimeTable::isComposite(uint32_t n) const
{
	return !isPrime( n );
}

void PrimeTable::turnOn(uint32_t n)
{
	mPrimeTable[n >> 5] |= (0x1 << (n & 31));
}

void PrimeTable::turnOff(uint32_t n)
{
	mPrimeTable[n >> 5] &= ~(0x1 << (n & 31));
}

void PrimeTable::clear()
{
	for( size_t i = 0; i <= mPrimeTable.size(); ++i )
	{
		mPrimeTable[i] = std::numeric_limits<uint32_t>::max();
	}
}

void PrimeTable::turnOffTrivialNonPrimeNumber()
{
	turnOff(0);   // 0は素数ではない
	turnOff(1);   // 1は素数ではない
}

void PrimeTable::calculate()
{
	// トリビアルなものについてとりあえず考える
	// 0と1が対象だが、この後エラトステネスの篩を掛けるので重要。
	turnOffTrivialNonPrimeNumber();

	// 残りをエラトステネスの篩に掛ける
	for( uint32_t p = 2; p <= SQRT_N; ++p)
	{
		if( !isPrime(p) ) continue;

		for( uint64_t i = 2*p; i <= N; i += p)
		{
			turnOff(i);
		}
	}
}




PrimeSequence::PrimeSequence( uint32_t n )
{
	PrimeTable table( n );
	for( size_t i = 0; i <= n ; ++i )
	{
		if( table.isPrime( i ) )
		{
			mPrimes.push_back( i );
		}
	}
}

uint32_t PrimeSequence::getPrime( size_t i ) const
{
	return mPrimes[ i ];
}

size_t PrimeSequence::size( ) const
{
	return mPrimes.size();
}

}	// namespace sencha


