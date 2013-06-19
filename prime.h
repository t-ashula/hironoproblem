#pragma once

#include <vector>
#include <cstdint>
#include <cstddef>

namespace sencha
{


//! 素数・素数でない数を判定して保存するテーブル
class PrimeTable
{
public:
	//! コンストラクタ
	//! 素数判定のため巨大な計算(1～5分程度)が走るので注意が必要です
	//! @param n この数以下の素数を列挙します
	PrimeTable( uint32_t n );

	bool isPrime(uint32_t n) const;
	bool isComposite(uint32_t n) const;
private:

	//! 数のテーブル。ある数が素数であるか否かを記録します。
	//! ビットベクトルとして扱っています
	//! std::vector<bool>はむしろややこしくなるので使っていません
	//! 操作にはメンバメソッドのturnOn, turnOff, isPrime, isCompositeを使ってください。
	std::vector< uint32_t > mPrimeTable;

	size_t N;	//!< 対象にする数の範囲。Nは含まれます
	size_t SQRT_N;	//!< 対象にする数の二乗根。

	//! テーブル内のすべての数を素数の候補であるとしてクリアします
	void clear();

	//! 対象の数が素数であることをテーブルに記録します
	//! @param n 素数
	void turnOn(uint32_t n);

	//! 対象の数が素数ではない(合成数であるか、トリビアルに素数でない数である)ことをテーブルに記録します
	//! @param n 合成数、あるいはトリビアルに素数でない数
	void turnOff(uint32_t n);

	//! トリビアルに素数でない数をテーブル内で記録します
	//! 具体的には0と1について記録します。
	//! この2つは合成数でもないですが、素数でも無いので特別扱いです。
	//! このことを指してトリビアル(定義から明らか)というのもおかしな話ですが
	//! いい名前が思いつかないのでこの名称
	void turnOffTrivialNonPrimeNumber();

	//! N以下の数について全ての素数と素数以外を判定しテーブルを更新します
	void calculate();
};


class PrimeSequence
{
public:
	//! コンストラクタ
	//! 巨大な計算(1～5分程度)が走るので注意
	//! @param n この数以下の素数を全列挙します
	PrimeSequence( uint32_t n );

	//! n以下のi番目の素数を取得する
	uint32_t getPrime( size_t i ) const;

	//! コンストラクタに指定されたn以下の素数の個数を取得する
	size_t size( ) const;

private:
	//! 素数リスト
	//! 前のほうから順番に素数の番号を保存したリスト
	std::vector< uint32_t > mPrimes;
};

}	// namespace sencha


