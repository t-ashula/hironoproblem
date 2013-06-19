#include <cstdint>
#include <iostream>
#include <cmath>

#include "prime.h"
#include "primefactor.h"

using namespace sencha;

// 対象にする桁モジュロマスク
static const natural digit = 100000ll;

//! nの階乗を素因数分解した時、素数pの指数は何になるか
//! 小さな数での実験は行なっているが
//! 未証明の推論が含まれているので正しさに注意を払うこと！
//! @param n 自然数
//! @param p 素数
natural fact_factor( natural n, natural p )
{
	// このコードは2つの予想に基づいたもので、正しい保証がない
	// 正しさを確かめたければ以下の2つの予想を証明すること。
	// 予想I) n以下に素数pのp**i(i=1,2,3...)の倍数が含まれる回数はfloor(n/p**i)
	// 予想II) したがってfact_factor(n,p) = sum of floor(n/p**i) (i=1,2,3,...)
	// 予想IIがまさにこのコードに等しい

	natural v = p;
	natural factor = 0;
	while( v <= n )
	{
		factor += n / v;
		v *= p;
	}
	return factor;
}

natural power( natural p, natural fact )
{
	natural val = 1;
	p %= digit;
	for( natural i = 0; i < fact; ++i )
	{
		val *= p;
		val %= digit;
	}
	return val;
}

natural f( natural n )
{
	sencha::PrimeSequence seq( n );

	// 5までは特別扱い。つまりi=0,1,2は先行して計算
	const natural factor2 = fact_factor( n, 2 );
	const natural factor3 = fact_factor( n, 3 );
	const natural factor5 = fact_factor( n, 5 );

	// 繰り上がりを打ち消し
	const natural factor2_ = factor2 - factor5;

	natural val = 1;
	val *= power(2, factor2_) % digit;
	val %= digit;
	val *= power(3, factor3) % digit;
	val %= digit;

	// それ以後は順当に計算
	for( size_t i = 3; i < seq.size(); ++i )
	{
		const natural p = seq.getPrime( i );
		const natural factor = fact_factor( n, p );
		const natural s = power( p, factor);
		val *= (s % digit);
		val %= digit;
	}
	return val;
}

int main(void)
{
	std::cout << "f(27) = " << f(27ll) << std::endl;
	std::cout << "f(1018) = " << f(1018ll) << std::endl;
	std::cout << "f(4318285) = " << f(4318285ll) << std::endl;
	/*
	std::cout << "f(1000000000000) = " << f(1000000000000ll) << std::endl;
	std::cout << "f(5638029384213847) = " << f(5638029384213847ll) << std::endl;
	*/
	return 0;
}


