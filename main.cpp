#include <cstdint>
#include <iostream>


// 5桁同士の積には十分な型ならいいのでより小さくできる。16bit環境は考慮していない
// ただしnの指定もこれなのでそこが問題になるのに注意
typedef unsigned long long natural;

natural f( natural n )
{
	natural val = 1;

	for( natural i = 1; i <= n; ++i )
	{
		if( (i % 10000000) == 0 )
		{
			std::cout << "calc now: " << i << std::endl;
		}
		natural mul = i;
		while( (mul % 10) == 0 ) mul /= 10;
		mul %= 1000000;

		val *= mul;

		while( (val % 10) == 0 ) val /= 10;
		val %= 1000000;	// オーバフロー対策に周回ごとに考慮の必要な下部5桁に絞る
	}

	return val % 100000;
}

int main(void)
{
	std::cout << f(99999) << std::endl;
/*
	std::cout << f(27) << std::endl;
	std::cout << f(1018) << std::endl;
	std::cout << f(4318285) << std::endl;

	std::cout << f(1000000000000) << std::endl;
	std::cout << f(5638029384213847) << std::endl;
*/

	return 0;
}
