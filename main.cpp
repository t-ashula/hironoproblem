#include <cstdint>
#include <iostream>


// 5桁同士の積には十分な型ならいいのでより小さくできうるが
// ただしnの指定もこれなのでそこが問題になるのでもう大きな型でいいかな。という妥協
typedef std::uint64_t natural;

// 対象にする桁数
static const natural digit = 100000ll;

natural cut( natural val )
{
	// 下位の0になっている桁は全て演算にも答えにも寄与しないのでカットしてよい
	while( (val % 10) == 0 ) val /= 10;

	// 10進数で考えるので5*2とか5*4とか5*8といったものがあり
	// 桁間の和分で流れる可能性が結局ある。
	// そのため上位桁を考慮分と同等だけ残す
	// 直感的にそれ以上は考慮しなくて良いはず……(未証明)
	// 2進数であれば0が最下位桁に来ないinvariantが効いてくるのになー。
	static const natural need_think_digit = digit*digit;
	val %= need_think_digit;

	return val;
}

natural f( natural n )
{
	natural val = 1;
	for( natural i = 1; i <= n; ++i )
	{
		val *= cut( i );
		val = cut( val );
	}

	// 対象桁数までカット
	return val % digit;
}

int main(void)
{
	std::cout << "f(99999) = " << f(99999ll) << std::endl;
	std::cout << "f(27) = " << f(27ll) << std::endl;
	std::cout << "f(1018) = " << f(1018ll) << std::endl;
	std::cout << "f(4318285) = " << f(4318285ll) << std::endl;

	// これだけではhardは計算が終わりません
	// おそらく積の結合性を使うと解けるようになりますが、とりあえずここまで。
	/*
	std::cout << "f(1000000000000) = " << f(1000000000000ll) << std::endl;
	std::cout << "f(5638029384213847) = " << f(5638029384213847ll) << std::endl;
	*/

	return 0;
}
