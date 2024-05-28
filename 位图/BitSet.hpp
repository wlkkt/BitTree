#pragma once
#include<assert.h>

namespace bit
{
	template<size_t N>
	class bitset
	{
	public:
	//构造一个大小能够放下所有无符号整数状态位图的整型数组，初始时所有元素均为0 => 所有bit位均为0
	bitset()
	{
		//无符号整型和整型都是四个字节大小
		_bits.resize(N / 32 + 1, 0);
		//一个整型 = 4 个字节
		//一字节 = 8 个比特位
		// 一个整型 = 4 * 8 个比特位
		//N个无符号整型数，需要32 * N 个比特位
		//+1向上取整，防止不够
	}

	// 把x映射的位标记成1
	void set(size_t x)
	{
		assert(x <= N);//x应该小于等于N，防止无法映射成功

		size_t i = x / 32;//计算无符号整数x映射在第i个整型的32个比特位上
		size_t j = x % 32;//计算具体应该放在第j位比特位上

		_bits[i] |= (1 << j);//将1移动到目标位置，然后在与原整型的32个比特位做或运算
	}

	// 把x映射的位标记成0
	void reset(size_t x)
	{
		assert(x <= N);//x应该小于等于N，防止无法映射成功

		size_t i = x / 32;//计算无符号整数x映射在第i个整型的32个比特位上
		size_t j = x % 32;//计算具体应该放在第j位比特位上

		_bits[i] &= ~(1 << j);//将1移动到目标位置并取反，然后在与原整型的32个比特位做与运算
	}

	//检查是否存在
	bool test(size_t x)
	{
		assert(x <= N);

		size_t i = x / 32;
		size_t j = x % 32;

		return _bits[i] & (1 << j);
	}

	private:
		vector<int> _bits;
	};

	//测试函数
	void test_bitset()
	{
		//实例化一个100
		bitset<100> bs1;
		bs1.set(50);
		bs1.set(30);
		bs1.set(90);

		for (size_t i = 0; i < 100; i++)
		{
			if (bs1.test(i))
			{
				cout << i << "->" << "在" << endl;
			}
			else
			{
				cout << i << "->" << "不在" << endl;
			}
		}
		bs1.reset(90);
		bs1.set(91);

		cout << endl << endl;

		for (size_t i = 0; i < 100; i++)
		{
			if (bs1.test(i))
			{
				cout << i << "->" << "在" << endl;
			}
			else
			{
				cout << i << "->" << "不在" << endl;
			}
		}

		//以下三种都可以表示四十亿个位图
	/*	bitset<-1> bs2;
		bitset<UINT_MAX> bs3;
		bitset<0xffffffff> bs4;*/
	}

	template<size_t N>
	class two_bit_set
	{
	public:
		void set(size_t x)
		{
			// 00 -> 01
			if (_bs1.test(x) == false
				&& _bs2.test(x) == false)
			{
				_bs2.set(x);
			}
			else if (_bs1.test(x) == false
				&& _bs2.test(x) == true)
			{
				// 01 -> 10
				_bs1.set(x);
				_bs2.reset(x);
			}
		}

		//int test(size_t x)
		//{
		//	if (_bs1.test(x) == false
		//		&& _bs2.test(x) == false)
		//	{
		//		return 0;
		//	}
		//	else if (_bs1.test(x) == false
		//		&& _bs2.test(x) == true)
		//	{
		//		return 1;
		//	}
		//	else
		//	{
		//		return 2; // 2次及以上
		//	}
		//}
		bool test(size_t x)
		{
			if (_bs1.test(x) == false
				&& _bs2.test(x) == true)
			{
				return true;
			}

			return false;
		}
	private:
		bitset<N> _bs1;
		bitset<N> _bs2;
	};

	void test_bitset2()
	{
		int a[] = { 5,7,9,2,5,99,5,5,7,5,3,9,2,55,1,5,6 };
		two_bit_set<100> bs;
		for (auto e : a)
		{
			bs.set(e);
		}

		for (size_t i = 0; i < 100; i++)
		{
			//cout << i << "->" << bs.test(i) << endl;
			if (bs.test(i))
			{
				cout << i << endl;
			}
		}
	}

	void test_bitset3()
	{
		int a1[] = { 5,7,9,2,5,99,5,5,7,5,3,9,2,55,1,5,6 };
		int a2[] = { 5,3,5,99,6,99,33,66 };

		bitset<100> bs1;
		bitset<100> bs2;

		for (auto e : a1)
		{
			bs1.set(e);
		}

		for (auto e : a2)
		{
			bs2.set(e);
		}

		for (size_t i = 0; i < 100; i++)
		{
			if (bs1.test(i) && bs2.test(i))
			{
				cout << i << endl;
			}
		}
	}
}
