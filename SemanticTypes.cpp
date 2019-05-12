// Semantic types
// Don't trust names of variables, trust types!

#include "pch.h"
#include <iostream>
#include <string>

template <int M, int K, int S>
struct MksUnit
{
	enum { metre = M, kilogram = K, second = S };
};

template <typename MksUnit>
class Value
{
private:
	long double magnitude{ 0.0 };
public:
	constexpr explicit Value(const long double magnitude) : magnitude(magnitude) {}
	long double getMagnitude() const {
		return magnitude;
	}

};

// Semantic Types
using DimensionlessQuantity = Value<MksUnit<0, 0, 0>>;
constexpr DimensionlessQuantity operator"" _(long double magnitude)
{
	return DimensionlessQuantity(magnitude);
}
using Length = Value<MksUnit<1, 0, 0>>;
constexpr Length operator"" _m(long double magnitude)
{
	return Length(magnitude);
}
using Area = Value<MksUnit<2, 0, 0>>;
constexpr Area operator"" _m2(long double magnitude)
{
	return Area(magnitude);
}
using Volume = Value<MksUnit<3, 0, 0>>;
constexpr Volume operator"" _m3(long double magnitude)
{
	return Volume(magnitude);
}
using Mass = Value<MksUnit<0, 1, 0>>;
constexpr Mass operator"" _kg(long double magnitude)
{
	return Mass(magnitude);
}
using Time = Value<MksUnit<0, 0, 1>>;
constexpr Time operator"" _s(long double magnitude)
{
	return Time(magnitude);
}
using Speed = Value < MksUnit < 1, 0, -1>>;
constexpr Speed operator"" _m_s(long double magnitude)
{
	return Speed(magnitude);
}
using Acceleration = Value<MksUnit<1, 0, -2>>;
constexpr Acceleration operator"" _m_s2(long double magnitude)
{
	return Acceleration(magnitude);
}
using Frequency = Value<MksUnit<0, 0, -1>>;
constexpr Frequency operator"" _Hz(long double magnitude)
{
	return Frequency(magnitude);
}
using Force = Value<MksUnit<1, 1, -2>>;
constexpr Force operator"" _N(long double magnitude)
{
	return Force(magnitude);
}
using Pressure = Value<MksUnit<-1, 1, -2>>;
constexpr Pressure operator"" _kg_ms2(long double magnitude)
{
	return Pressure(magnitude);
}
using Momentum = Value<MksUnit<1, 1, -1>>;
constexpr Momentum operator"" _Ns(long double magnitude)
{
	return Momentum(magnitude);
}

//Operator overloads to properly calculate units
template<int M, int K, int S>
constexpr Value<MksUnit<M, K, S>>operator+(const Value<MksUnit<M, K, S>>& lhs, Value<MksUnit<M, K, S>>& rhs)
{
	return Value<MksUnit<M, K, S>>(lhs.getMagnitude() + rhs.getMagnitude());
}

template<int M, int K, int S>
constexpr Value<MksUnit<M, K, S>>operator-(const Value<MksUnit<M, K, S>>& lhs, Value<MksUnit<M, K, S>>& rhs)
{
	return Value<MksUnit<M, K, S>>(lhs.getMagnitude() - rhs.getMagnitude());
}

template<int M1, int M2, int K1, int K2, int S1, int S2>
constexpr Value<MksUnit<M1 + M2, K1 + K2, S1 + S2>>operator*(const Value<MksUnit<M1, K1, S1>>& lhs, Value<MksUnit<M2, K2, S2>>& rhs)
{
	return Value<MksUnit<M1 + M2, K1 + K2, S1 + S2>>(lhs.getMagnitude() * rhs.getMagnitude());
}

template<int M1, int M2, int K1, int K2, int S1, int S2>
constexpr Value<MksUnit<M1 - M2, K1 - K2, S1 - S2>>operator/(const Value<MksUnit<M1, K1, S1>>& lhs, Value<MksUnit<M2, K2, S2>>& rhs)
{
	return Value<MksUnit<M1 - M2, K1 - K2, S1 - S2>>(lhs.getMagnitude() / rhs.getMagnitude());
}

//simple class to show how it works
class Spacecraft {
public:
	void applyMomentum(const Momentum& value)
	{
		std::cout << "Momentum: " << value.getMagnitude() << std::endl;
	}
};

int main()
{
	Spacecraft spacecraft;

		// it will compile and work
	Momentum momentum1 = 3.0_Ns;
	spacecraft.applyMomentum(momentum1);

		// it won't compile
	//Momentum momentum2 = 3.0;					// <- wrong units
	//spacecraft.applyMomentum(momentum2);

		// it also won't compile
	//Momentum momentum3 = 3.0_s;					// <- wrong units
	//spacecraft.applyMomentum(momentum3);

		// and it also won't compile
	//Momentum momentum4 = 3_Ns;					// <- wrong type it should be double, not integer
	//spacecraft.applyMomentum(momentum4);

		// but unfortunately it will compile and work...
	Momentum momentum5{ 10 };					// <- it doesn't matter if it's double or integer. it casting it to double
	spacecraft.applyMomentum(momentum5);

		// and this also
	Momentum momentum6(5);
	spacecraft.applyMomentum(momentum6);

		// but it is useful and works!
	auto momentum7 = 7.0_Ns;
	spacecraft.applyMomentum(momentum7);

		//another interesting and useful thing
	Force force = 30.0_N;
	Time time1 = 5.0_s;
	Momentum momentum8 = force * time1;
	std::cout << momentum8.getMagnitude() << std::endl;

	DimensionlessQuantity one = 1.0_;
	Time time2 = 5.0_s;
	Frequency frequency = one / time2;
	std::cout << frequency.getMagnitude() << std::endl;

}

// Output of this code is:

//Momentum: 3
//Momentum: 10
//Momentum: 5
//Momentum: 7
//150
//0.2
//

