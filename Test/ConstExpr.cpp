#if !defined __GNUC__
// relative include path contains '..', specific to this file
#pragma warning( disable: 4464 )

#else
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

// For testing - intrinsics can never be constexpr
#undef SAFEINT_USE_INTRINSICS
#define SAFEINT_USE_INTRINSICS 0

#include "../SafeInt.hpp"

namespace TestConstExpr
{
	template <typename T, typename U>
	_CONSTEXPR11 bool LessThanTest()
	{
		return
			(U)2 < SafeInt<T>(3) &&
			SafeInt<T>(4) < (U)5 &&
			SafeInt<T>(6) < SafeInt<U>(7);
	}

	template <typename T, typename U>
	_CONSTEXPR11 bool GreaterThanTest()
	{
		return
			(U)2 > SafeInt<T>(3) &&
			SafeInt<T>(4) > (U)5 &&
			SafeInt<T>(6) > SafeInt<U>(7);
	}

	template <typename T, typename U>
	_CONSTEXPR11 bool LessThanEqualTest()
	{
		return
			(U)2 <= SafeInt<T>(3) &&
			SafeInt<T>(4) <= (U)5 &&
			SafeInt<T>(6) <= SafeInt<U>(7);
	}

	template <typename T, typename U>
	_CONSTEXPR11 bool GreaterThanEqualTest()
	{
		return
			(U)2 >= SafeInt<T>(3) &&
			SafeInt<T>(4) >= (U)5 &&
			SafeInt<T>(6) >= SafeInt<U>(7);
	}

	template <typename T, typename U>
	_CONSTEXPR11 bool EqualTest()
	{
		return
			(U)2 == SafeInt<T>(3) &&
			SafeInt<T>(4) == (U)5 &&
			SafeInt<T>(6) == SafeInt<U>(7) &&
			true == SafeInt<T>(1) &&
			false == SafeInt<T>(0);
	}

	template <typename T, typename U>
	_CONSTEXPR11 bool NotEqualTest()
	{
		return
			(U)2 != SafeInt<T>(3) &&
			SafeInt<T>(4) != (U)5 &&
			SafeInt<T>(6) != SafeInt<U>(7) &&
			true != SafeInt<T>(1) &&
			false != SafeInt<T>(0);
	}

	template <typename T, typename U>
	void ComparisonTestTU()
	{
		static bool b1 = LessThanTest<T, U>();
		static bool b2 = LessThanEqualTest<T, U>();
		static bool b3 = GreaterThanTest<T, U>();
		static bool b4 = GreaterThanEqualTest<T, U>();
		static bool b5 = EqualTest<T, U>();
		static bool b6 = NotEqualTest<T, U>();
	}

	template <typename T> void ComparisonTestT()
	{
		ComparisonTestTU<T, char>();
		ComparisonTestTU<T, signed char>();
		ComparisonTestTU<T, unsigned char>();
		ComparisonTestTU<T, signed short>();
		ComparisonTestTU<T, unsigned short>();
		ComparisonTestTU<T, signed int>();
		ComparisonTestTU<T, unsigned int>();
		ComparisonTestTU<T, signed long>();
		ComparisonTestTU<T, unsigned long>();
		ComparisonTestTU<T, signed long long>();
		ComparisonTestTU<T, unsigned long long>();
	}

	template <typename T>
	_CONSTEXPR11 T ConstConstructor()
	{
		// Constructors, also add in the useless unary + operator
		return SafeInt<T>() + SafeInt<T>(1) + SafeInt<T>(false) + (+SafeInt<T>(3));
	}

	template <typename T>
	_CONSTEXPR11 bool ConstBool()
	{
		return (bool)SafeInt<T>(2) && !SafeInt<T>(0);
	}

	template <typename T>
	void ConstTestT()
	{
		static const T t = ConstConstructor<T>();
		static const bool b = ConstBool<T>();
	}

	template <typename T>
	_CONSTEXPR11 SafeInt<T> ConstSafeInt()
	{
		return SafeInt<T>(1);
	}

	template <typename T>
	void ConstCastTestT()
	{
		static const bool b = ConstSafeInt<T>();
		static const wchar_t w = ConstSafeInt<T>();
		static const char c = ConstSafeInt<T>();
		static const signed char sc = ConstSafeInt<T>();
		static const unsigned char uc = ConstSafeInt<T>();
		static const signed short s = ConstSafeInt<T>();
		static const unsigned short us = ConstSafeInt<T>();
		static const signed int i = ConstSafeInt<T>();
		static const unsigned int ui = ConstSafeInt<T>();
		static const signed long l = ConstSafeInt<T>();
		static const unsigned long ul = ConstSafeInt<T>();
		static const signed long long ll = ConstSafeInt<T>();
		static const unsigned long long ull = ConstSafeInt<T>();
		static const size_t st = ConstSafeInt<T>();
		static const ptrdiff_t pt = ConstSafeInt<T>();

		// Also catch the useless unary + operator
		static const int pl = +ConstSafeInt<T>();
	}

#if CPLUSPLUS_STD == CPLUSPLUS_14

	template <typename T, typename U>
	void StaticAssertTU()
	{
		// Constructors
		static_assert(SafeInt<T>(SafeInt<U>(1)), "SafeInt U constr");
		static_assert(SafeInt<T>((U)1), "U constr");

		// Assignment operators
		static_assert((SafeInt<T>() = (U)1), "Assignment U");
		static_assert((SafeInt<T>() = (T)1), "Assignment T");
		static_assert((SafeInt<T>() = SafeInt<U>(1)), "Assignment SafeInt U");
		// Next one happens when T == U, so already included
		// static_assert((SafeInt<T>() = SafeInt<T>(1)), "Assignment SafeInt T");

		// Test the casting operators
		static_assert((U)(SafeInt<T>((T)1)), "Casting");

		// Modulus
		static_assert(SafeInt<T>((T)3) % (U)2, "Modulus");
		static_assert(SafeInt<T>((T)3) % SafeInt<T>(2), "Modulus");
		static_assert((SafeInt<T>((T)3) %= (U)2), "Modulus");
		static_assert((SafeInt<T>((T)3) %= SafeInt<U>(2)), "Modulus");
		static_assert((U)3 % SafeInt<T>(2), "Modulus");
		static_assert((T)3 % SafeInt<U>(2), "Modulus");

		// Multiplication
		static_assert(SafeInt<T>((T)3) * (U)2, "Multiplication");
		static_assert(SafeInt<T>((T)3) * SafeInt<T>(2), "Multiplication");
		static_assert((SafeInt<T>((T)3) *= (U)2), "Multiplication");
		static_assert((SafeInt<T>((T)3) *= SafeInt<U>(2)), "Multiplication");
		static_assert((U)3 * SafeInt<T>(2), "Multiplication");
		static_assert((T)3 * SafeInt<U>(2), "Multiplication");

	}

	template <typename T, typename U>
	void StaticAssertMultiplyTU()
	{

	}

	template <typename T>
	void StaticAssertTest()
	{
		static_assert(SafeInt<T>() == 0, "Default constr");
		static_assert(SafeInt<T>((T)1), "T constr");
		static_assert(SafeInt<T>(true), "bool constr");
		// Floating point will not work due to presence of fpclassify
		// static_assert(SafeInt<T>((float)1.0), "float constr");

		StaticAssertTU<T, char>();
		StaticAssertTU<T, signed char>();
		StaticAssertTU<T, unsigned char>();
		StaticAssertTU<T, signed short>();
		StaticAssertTU<T, unsigned short>();
		StaticAssertTU<T, signed int>();
		StaticAssertTU<T, unsigned int>();
		StaticAssertTU<T, signed long>();
		StaticAssertTU<T, unsigned long>();
		StaticAssertTU<T, signed long long>();
		StaticAssertTU<T, unsigned long long>();

		// Special case casting
		static_assert((bool)(SafeInt<T>((T)1)), "Casting");
		static_assert((wchar_t)(SafeInt<T>((T)1)), "Casting");
		static_assert((float)(SafeInt<T>((T)1)), "Casting");
		static_assert((double)(SafeInt<T>((T)1)), "Casting");
		static_assert((long double)(SafeInt<T>((T)1)), "Casting");

		// Unary operations
		static_assert(!SafeInt<T>((T)0), "operator !");
		static_assert(++SafeInt<T>((T)1), "operator ++");
		static_assert(SafeInt<T>((T)1)++, "operator ++");
		static_assert(--SafeInt<T>((T)2), "operator --");
		static_assert(SafeInt<T>((T)2)--, "operator --");
		static_assert(~SafeInt<T>((T)0), "operator ~");


	}

	template <typename T, typename U>
	_CONSTEXPR14 T ConstMultiplyTU()
	{
		return (SafeInt<T>(2) * (U)1) + (U(4) * SafeInt<T>(3)) + (SafeInt<T>(6) * SafeInt<T>(5));
	}

	template <typename T>
	void ConstMultiplyT()
	{
		static const T c = ConstMultiplyTU< T, char >();
		static const T sc = ConstMultiplyTU< T, signed char >();
		static const T uc = ConstMultiplyTU< T, unsigned char >();
		static const T ss = ConstMultiplyTU< T, signed short >();
		static const T us = ConstMultiplyTU< T, unsigned short >();
		static const T si = ConstMultiplyTU< T, signed int >();
		static const T ui = ConstMultiplyTU< T, unsigned int >();
		static const T sl = ConstMultiplyTU< T, signed long >();
		static const T ul = ConstMultiplyTU< T, unsigned long >();
		static const T sll = ConstMultiplyTU< T, signed long long >();
		static const T ull = ConstMultiplyTU< T, unsigned long long >();
	}

	template <typename T, typename U>
	_CONSTEXPR14 T ConstSubtractTU()
	{
		return (SafeInt<T>(2) - (U)1) + (U(4) - SafeInt<T>(3)) + (SafeInt<T>(6) - SafeInt<T>(5));
	}

	template <typename T>
	void ConstSubtractT()
	{
		static const T c = ConstSubtractTU< T, char >();
		static const T sc = ConstSubtractTU< T, signed char >();
		static const T uc = ConstSubtractTU< T, unsigned char >();
		static const T ss = ConstSubtractTU< T, signed short >();
		static const T us = ConstSubtractTU< T, unsigned short >();
		static const T si = ConstSubtractTU< T, signed int >();
		static const T ui = ConstSubtractTU< T, unsigned int >();
		static const T sl = ConstSubtractTU< T, signed long >();
		static const T ul = ConstSubtractTU< T, unsigned long >();
		static const T sll = ConstSubtractTU< T, signed long long >();
		static const T ull = ConstSubtractTU< T, unsigned long long >();
	}

	template <typename T, typename U>
	_CONSTEXPR14 T ConstAddTU()
	{
		return (SafeInt<T>(1) + (U)2) + (U(3) + SafeInt<T>(4)) + (SafeInt<T>(5) + SafeInt<T>(6));
	}

	template <typename T>
	void ConstAddT()
	{
		static const T c   = ConstAddTU< T, char >();
		static const T sc  = ConstAddTU< T, signed char >();
		static const T uc  = ConstAddTU< T, unsigned char >();
		static const T ss  = ConstAddTU< T, signed short >();
		static const T us  = ConstAddTU< T, unsigned short >();
		static const T si  = ConstAddTU< T, signed int >();
		static const T ui  = ConstAddTU< T, unsigned int >();
		static const T sl  = ConstAddTU< T, signed long >();
		static const T ul  = ConstAddTU< T, unsigned long >();
		static const T sll = ConstAddTU< T, signed long long >();
		static const T ull = ConstAddTU< T, unsigned long long >();
	}

	template <typename T>
	_CONSTEXPR14 T PrefixInc(T i)
	{
		return ++SafeInt<T>(i);
	}

	template <typename T>
	_CONSTEXPR14 T PostfixInc(T i)
	{
		return SafeInt<T>(i)++;
	}

	template <typename T>
	_CONSTEXPR14 T PrePostTest()
	{
		static const T t1 = PrefixInc<T>((T)1);
		static const T t2 = PostfixInc<T>((T)2);
		static_assert(t1 + t2 == 4, "Failed");

		return (T)(t1 + t2);
	}

	template <typename T>
	_CONSTEXPR14 void SignedOnly()
	{
		static_assert(-SafeInt<T>((T)1), "operator -");
	}

	void TestSignedOnly()
	{
		SignedOnly<signed char>();
		SignedOnly<signed short>();
		SignedOnly<signed int>();
		SignedOnly<signed long>();
		SignedOnly<signed long long>();
	}

#endif // CPLUSPLUS_14

	template <typename T>
	void ConstExprTestT()
	{
		ConstTestT<T>();
		ComparisonTestT<T>();
		ConstCastTestT<T>();

#if CPLUSPLUS_STD == CPLUSPLUS_14
		StaticAssertTest<T>();
		TestSignedOnly();

		ConstAddT<T>();
		ConstSubtractT<T>();
		ConstMultiplyT<T>();
		PrePostTest<T>();
#endif
	}

	void ConstExprTest()
	{
		ConstExprTestT<char>();
		ConstExprTestT<signed char>();
		ConstExprTestT<unsigned char>();
		ConstExprTestT<signed short>();
		ConstExprTestT<unsigned short>();
		ConstExprTestT<signed int>();
		ConstExprTestT<unsigned int>();
		ConstExprTestT<signed long>();
		ConstExprTestT<unsigned long>();
		ConstExprTestT<signed long long>();
		ConstExprTestT<unsigned long long>();

		// Catch the SafePtrDiff function, since it is marked. Can't think of a scenario for this being constexpr, though.
		const char* p1 = (char*)1;
		const char* p2 = nullptr;

		static const SafeInt<ptrdiff_t> pt = SafePtrDiff(p1, p2);
	}

}

void ConstExpr()
{
	TestConstExpr::ConstExprTest();
}