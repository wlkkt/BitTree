#pragma once
#include<assert.h>

namespace bit
{
	template<size_t N>
	class bitset
	{
	public:
	//����һ����С�ܹ����������޷�������״̬λͼ���������飬��ʼʱ����Ԫ�ؾ�Ϊ0 => ����bitλ��Ϊ0
	bitset()
	{
		//�޷������ͺ����Ͷ����ĸ��ֽڴ�С
		_bits.resize(N / 32 + 1, 0);
		//һ������ = 4 ���ֽ�
		//һ�ֽ� = 8 ������λ
		// һ������ = 4 * 8 ������λ
		//N���޷�������������Ҫ32 * N ������λ
		//+1����ȡ������ֹ����
	}

	// ��xӳ���λ��ǳ�1
	void set(size_t x)
	{
		assert(x <= N);//xӦ��С�ڵ���N����ֹ�޷�ӳ��ɹ�

		size_t i = x / 32;//�����޷�������xӳ���ڵ�i�����͵�32������λ��
		size_t j = x % 32;//�������Ӧ�÷��ڵ�jλ����λ��

		_bits[i] |= (1 << j);//��1�ƶ���Ŀ��λ�ã�Ȼ������ԭ���͵�32������λ��������
	}

	// ��xӳ���λ��ǳ�0
	void reset(size_t x)
	{
		assert(x <= N);//xӦ��С�ڵ���N����ֹ�޷�ӳ��ɹ�

		size_t i = x / 32;//�����޷�������xӳ���ڵ�i�����͵�32������λ��
		size_t j = x % 32;//�������Ӧ�÷��ڵ�jλ����λ��

		_bits[i] &= ~(1 << j);//��1�ƶ���Ŀ��λ�ò�ȡ����Ȼ������ԭ���͵�32������λ��������
	}

	//����Ƿ����
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

	//���Ժ���
	void test_bitset()
	{
		//ʵ����һ��100
		bitset<100> bs1;
		bs1.set(50);
		bs1.set(30);
		bs1.set(90);

		for (size_t i = 0; i < 100; i++)
		{
			if (bs1.test(i))
			{
				cout << i << "->" << "��" << endl;
			}
			else
			{
				cout << i << "->" << "����" << endl;
			}
		}
		bs1.reset(90);
		bs1.set(91);

		cout << endl << endl;

		for (size_t i = 0; i < 100; i++)
		{
			if (bs1.test(i))
			{
				cout << i << "->" << "��" << endl;
			}
			else
			{
				cout << i << "->" << "����" << endl;
			}
		}

		//�������ֶ����Ա�ʾ��ʮ�ڸ�λͼ
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
		//		return 2; // 2�μ�����
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
