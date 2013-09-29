#pragma once
#include "basicclasses.h"
#include "basicmacros.h"
#include <string.h>

#ifndef FLEXSIM_VALUE
#define FLEXSIM_VALUE
	class FlexSimValue
	{
	public:
		double asDouble;
		inline operator void*()const{return doubletoptr(asDouble);}
		inline operator TreeNode*()const{return (TreeNode*)doubletoptr(asDouble);}
		inline operator double()const{return asDouble;}
		inline operator __int64()const{return (__int64)asDouble;}
		inline operator int()const{return (int)asDouble;}
		inline operator short()const{return (short)asDouble;}
		inline operator char()const{return (char)asDouble;}
		inline operator unsigned __int64()const{return (unsigned __int64)asDouble;}
		inline operator unsigned int()const{return (unsigned int)asDouble;}
		inline operator unsigned short()const{return (unsigned short)asDouble;}
		inline operator unsigned char()const{return (unsigned char)asDouble;}
		inline operator unsigned char*()const{return (unsigned char*)doubletoptr(asDouble);}
		inline operator char*()const{return (char*)doubletoptr(asDouble);}
		inline FlexSimValue(void* x) : asDouble(ptrtodouble(x)) {}
		inline FlexSimValue(TreeNode* x) : asDouble(ptrtodouble(x)) {}
		inline FlexSimValue(double x) : asDouble(x) {}
		inline FlexSimValue(__int64 x) : asDouble((double)x) {}
		inline FlexSimValue(int x) : asDouble((double)x) {}
		inline FlexSimValue(short x) : asDouble((double)x) {}
		inline FlexSimValue(char x) : asDouble((double)x) {}
		inline FlexSimValue(unsigned __int64 x) : asDouble((double)x) {}
		inline FlexSimValue(unsigned int x) : asDouble((double)x) {}
		inline FlexSimValue(unsigned short x) : asDouble((double)x) {}
		inline FlexSimValue(unsigned char x) : asDouble((double)x) {}
		inline FlexSimValue(unsigned char* x) : asDouble((double)ptrtodouble(x)) {}
		inline FlexSimValue(char* x) : asDouble((double)ptrtodouble(x)) {}
		inline FlexSimValue(const char* x) : asDouble((double)ptrtodouble((char*)x)) {}
		inline FlexSimValue(const FlexSimValue& x) : asDouble(x.asDouble) {}
	};
#endif

#define COMPARE_NUMBER(op, numberType) \
	bool operator op (numberType& theNum)\
	{\
		if (type == Number) return numVal op theNum;\
		return false;\
	}\

#define COMPARE_NUMBER_TYPES(op)\
	COMPARE_NUMBER(op, float)\
	COMPARE_NUMBER(op, double)\
	COMPARE_NUMBER(op, char)\
	COMPARE_NUMBER(op, short)\
	COMPARE_NUMBER(op, int)\
	COMPARE_NUMBER(op, __int64)\
	COMPARE_NUMBER(op, unsigned char)\
	COMPARE_NUMBER(op, unsigned short)\
	COMPARE_NUMBER(op, unsigned int)\
	COMPARE_NUMBER(op, unsigned __int64)

struct SqlValue
{
	enum ValueType
	{
		Number = 1,
		String = 2,
		Null = 3
	} type;
	union {
		double numVal;
		char* strVal;
	};
	SqlValue(char* strVal) : type(String), strVal(strVal) {}
	SqlValue(double numVal) : type(Number), numVal(numVal) {}
	SqlValue(int numVal) : type(Number), numVal(numVal) {}
	SqlValue(ValueType type, double numVal) : type(type), numVal(numVal) {}
	operator bool() {return type == Number && numVal != 0;}
	operator double() {if (type == Number) return numVal; return 0;}
	bool operator < (SqlValue& other) 
	{
		if (type != other.type) return false; 
		if (type == Number) return numVal < other.numVal; 
		if (type == Null) return false;
		return strcmp(strVal, other.strVal) < 0;
	}
	bool operator <= (SqlValue& other) 
	{
		if (type != other.type) return false; 
		if (type == Number) return numVal <= other.numVal; 
		if (type == Null) return false;
		return strcmp(strVal, other.strVal) <= 0;
	}
	bool operator > (SqlValue& other) 
	{
		if (type != other.type) return false; 
		if (type == Number) return numVal > other.numVal; 
		if (type == Null) return false;
		return strcmp(strVal, other.strVal) > 0;
	}
	bool operator >= (SqlValue& other) 
	{
		if (type != other.type) return false; 
		if (type == Number) return numVal >= other.numVal; 
		if (type == Null) return false;
		return strcmp(strVal, other.strVal) >= 0;
	}
	bool operator == (SqlValue& other) 
	{
		if (type != other.type) return false; 
		if (type == Number) return numVal == other.numVal; 
		if (type == Null) return false;
		return strcmp(strVal, other.strVal) == 0;
	}
	bool operator != (SqlValue& other) 
	{
		if (type != other.type) return false; 
		if (type == Number) return numVal != other.numVal; 
		if (type == Null) return false;
		return strcmp(strVal, other.strVal) != 0;
	}
	COMPARE_NUMBER_TYPES(<);
	COMPARE_NUMBER_TYPES(>);
	COMPARE_NUMBER_TYPES(<=);
	COMPARE_NUMBER_TYPES(>=);
	COMPARE_NUMBER_TYPES(==);
};

#undef COMPARE_NUMBER_TYPES
#undef COMPARE_NUMBER

template<class RefType>
class SafeRef {
protected:
	RefType* ref;
	unsigned int id;
	inline void init(RefType* x)
	{
		try{
			ref = x; 
			if(x)
				id = x->id;
			else id = 0;
		}catch(...){}
	}
public:
	SafeRef() : ref(0), id(0) {}
	SafeRef(RefType* x)
	{
		init(x);
	}
	inline SafeRef& operator=(RefType* x)
	{
		init(x);
		return *this;
	}
	// when VS supports it, this should be explicit operator bool() {} (it's a C++0x standard but not supported as of VS2012)
	operator bool() {return get() != 0;}
	bool operator !() {return get() == 0;}
	bool operator ==(RefType* other) {return get() == other;}
	bool operator !=(RefType* other) {return get() != other;}
	inline operator RefType*()
	{
		try {
			if(ref && ref->id == id)
				return ref;
		} catch (...) {;}
		return 0;
	}
	inline RefType* get() {return operator RefType*();}
	inline RefType* operator ->(){return operator RefType*();}
};


template<class ObjType>
class ObjRef : public SafeRef<TreeNode>
{
private:
	inline void init(ObjType* x)
	{
		if(x)
			SafeRef::init(x->holder);
		else SafeRef::init(0);
	}
public:
	ObjRef() : SafeRef() {}
	ObjRef(ObjType* x) : SafeRef(x ? x->holder : 0){}
	inline ObjRef& operator=(ObjType* x)
	{
		init(x);
		return *this;
	}
	// when VS supports it, this should be explicit operator bool() {} (it's a C++0x standard but not supported as of VS2012)
	operator bool() {return get() != 0;}
	const bool operator !() const {return get() == 0;}
	bool operator !() {return get() == 0;}
	const bool operator ==(ObjType* other) const {return get() == other;}
	bool operator ==(ObjType* other) {return get() == other;}
	const bool operator !=(ObjType* other) const {return get() != other;}
	bool operator !=(ObjType* other) {return get() != other;}
	const ObjType* operator->() const {return get();};
	ObjType* operator->() {return get();};
	inline operator ObjType*()
	{
		TreeNode* x = SafeRef::get();
		if(x)
			return &o(ObjType, x);
		else return 0;
	}
	inline ObjType* get() {return operator ObjType*();}
};


#define PP_IIF_0(t, f) f
#define PP_IIF_1(t, f) t
#define PP_IIF_I(bit, t, f) PP_IIF_II(PP_IIF_ ## bit(t, f))
#define PP_IIF_II(id) id
#define PP_IIF(bit, t, f) PP_IIF_I(bit, t, f)

#define PP_CAT_II(p, res) res
#define PP_CAT_I(a, b) PP_CAT_II(~, a ## b)
#define PP_CAT(a, b) PP_CAT_I(a, b)

#define PP_NOT_EQUAL_CHECK_PP_NIL 1

#define PP_NOT_EQUAL_CHECK_PP_NOT_EQUAL_0(c, y) 0
#define PP_NOT_EQUAL_CHECK_PP_NOT_EQUAL_1(c, y) 0
#define PP_NOT_EQUAL_CHECK_PP_NOT_EQUAL_2(c, y) 0
#define PP_NOT_EQUAL_CHECK_PP_NOT_EQUAL_3(c, y) 0
#define PP_NOT_EQUAL_CHECK_PP_NOT_EQUAL_4(c, y) 0
#define PP_NOT_EQUAL_CHECK_PP_NOT_EQUAL_5(c, y) 0
#define PP_NOT_EQUAL_CHECK_PP_NOT_EQUAL_6(c, y) 0
#define PP_NOT_EQUAL_CHECK_PP_NOT_EQUAL_7(c, y) 0
#define PP_NOT_EQUAL_CHECK_PP_NOT_EQUAL_8(c, y) 0
#define PP_NOT_EQUAL_CHECK_PP_NOT_EQUAL_9(c, y) 0
#define PP_NOT_EQUAL_CHECK_PP_NOT_EQUAL_10(c, y) 0


#    define PP_NOT_EQUAL_0(c, y) PP_IIF(c, PP_NIL, y##(1, PP_NIL))
#    define PP_NOT_EQUAL_1(c, y) PP_IIF(c, PP_NIL, y##(1, PP_NIL))
#    define PP_NOT_EQUAL_2(c, y) PP_IIF(c, PP_NIL, y##(1, PP_NIL))
#    define PP_NOT_EQUAL_3(c, y) PP_IIF(c, PP_NIL, y##(1, PP_NIL))
#    define PP_NOT_EQUAL_4(c, y) PP_IIF(c, PP_NIL, y##(1, PP_NIL))
#    define PP_NOT_EQUAL_5(c, y) PP_IIF(c, PP_NIL, y##(1, PP_NIL))
#    define PP_NOT_EQUAL_6(c, y) PP_IIF(c, PP_NIL, y##(1, PP_NIL))
#    define PP_NOT_EQUAL_7(c, y) PP_IIF(c, PP_NIL, y##(1, PP_NIL))
#    define PP_NOT_EQUAL_8(c, y) PP_IIF(c, PP_NIL, y##(1, PP_NIL))
#    define PP_NOT_EQUAL_9(c, y) PP_IIF(c, PP_NIL, y##(1, PP_NIL))
#    define PP_NOT_EQUAL_10(c, y) PP_IIF(c, PP_NIL, y##(1, PP_NIL))

#pragma warning(disable : 4003)

#define PP_NOT_EQUAL_I(x, y) PP_CAT(PP_NOT_EQUAL_CHECK_, PP_NOT_EQUAL_ ## x(0, PP_NOT_EQUAL_ ## y))
#define PP_NOT_EQUAL(x, y) PP_NOT_EQUAL_I(x, y)

#define PP_COMPL_0 1
#define PP_COMPL_1 0
#define PP_COMPL_ID(id) id
#define PP_COMPL_I(x) PP_COMPL_ID(PP_COMPL_ ## x)
#define PP_COMPL(x) PP_COMPL_I(x)

#define PP_EQUAL(x, y) PP_COMPL(PP_NOT_EQUAL(x, y))

#define VA_NARGS_II(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, N, ...) N
#define VA_NARGS_I(paramsinparen) VA_NARGS_II paramsinparen
#define VA_NARGS(...) VA_NARGS_I((__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1))

#define VA_ARG_0(e0, ...) e0
#define VA_ARG_1(e0, e1, ...) e1
#define VA_ARG_2(e0, e1, e2, ...) e2
#define VA_ARG_3(e0, e1, e2, e3, ...) e3
#define VA_ARG_4(e0, e1, e2, e3, e4, ...) e4
#define VA_ARG_5(e0, e1, e2, e3, e4, e5, ...) e5
#define VA_ARG_6(e0, e1, e2, e3, e4, e5, e6, ...) e6
#define VA_ARG_7(e0, e1, e2, e3, e4, e5, e6, e7, ...) e7
#define VA_ARG_8(e0, e1, e2, e3, e4, e5, e6, e7, e8, ...) e8
#define VA_ARG_9(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, ...) e9
#define VA_ARG_10(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, ...) e10
#define VA_ARG(_i, ...) PP_CAT(PP_CAT(VA_ARG_, _i),(__VA_ARGS__))

// lambda's are only compatible with visual studio 2010+
#if _MSC_VER >= 1600

template<class Test, class Return>
FlexSimValue cpp_findmatch(int nr, Test test, Return returnFunc, bool reverse = false)
{
	int start, end, incr;
	if (reverse) {
		start = nr;
		end = 0;
		incr = -1;
	} else {
		start = 1;
		end = nr + 1;
		incr = 1;
	}
	for (int i = start; i != end; i+=incr)
		if (test(i))
			return returnFunc(i);
	return 0;
}

template<class Test>
int cpp_findmatch(int nr, Test test)
{
	for (int i = 1; i <= nr; i++)
		if (test(i))
			return i;
	return 0;
}

template<class Test, class Return>
FlexSimValue cpp_findmatchintree(treenode top, Test test, Return returnFunc)
{
	if (test(top))
		return returnFunc(top);
	forobjecttreeunder (top) {
		if (test(a))
			return returnFunc(a);
	}
	return 0;
}

template<class Test>
treenode cpp_findmatchintree(treenode top, Test test)
{
	if (test(top))
		return top;
	forobjecttreeunder (top) {
		if (test(a))
			return a;
	}
	return 0;
}



template<class ValueFunc, class ReturnFunc, class ValidityFunc>
FlexSimValue cpp_findmaxmin(int nr, ValueFunc test, ReturnFunc returnFunc, 
							ValidityFunc validityFunc, bool reverse = false, bool isMax = true)
{
	int start, end, incr;
	if (reverse) {
		start = nr;
		end = 0;
		incr = -1;
	} else {
		start = 1;
		end = nr + 1;
		incr = 1;
	}
	int bestIndex = 0;
	double best = -FLT_MAX;
	for (int i = start; i != end; i+=incr) {
		if(validityFunc(i)) {
			double temp = test(i);
			if (isMax ? temp > best : temp < best) {
				bestIndex = i;
				best = temp;
			}
		}
	}
	if (bestIndex == 0)
		return 0;
	else {
		FlexSimValue returnVal = returnFunc(bestIndex);
		if(returnVal.asDouble == -FLT_MAX)
			return best;
		else return returnVal;
	}
}

template<class Value, class ReturnFunc, class ValidityFunc>
FlexSimValue cpp_findmax(int nr, Value test, ReturnFunc returnFunc, ValidityFunc validityFunc, bool reverse = false)
{
	return cpp_findmaxmin(nr, test, returnFunc, validityFunc, reverse, true);
}

template<class ValueFunc, class ReturnFunc>
double cpp_findmax(int nr, ValueFunc test, ReturnFunc returnFunc)
{
	return cpp_findmaxmin(nr, test, returnFunc, [](int count) -> bool {return true;}, false, true);
}

template<class ValueFunc>
double cpp_findmax(int nr, ValueFunc test)
{
	double best = -FLT_MAX;
	for (int i = 1; i <= nr; i++) {
		double temp = test(i);
		if (temp > best)
			best = temp;
	}
	return best;
}


template<class ValueFunc, class ReturnFunc, class ValidityFunc>
FlexSimValue cpp_findmin(int nr, ValueFunc test, ReturnFunc returnFunc, ValidityFunc validityFunc, bool reverse = false)
{
	return cpp_findmaxmin(nr, test, returnFunc, validityFunc, reverse, false);
}

template<class ValueFunc, class ReturnFunc>
double cpp_findmin(int nr, ValueFunc test, ReturnFunc returnFunc)
{
	return cpp_findmaxmin(nr, test, returnFunc, [](int count) -> bool {return true;}, false, false);
}

template<class Test>
double cpp_findmin(int nr, Test test)
{
	double best = FLT_MAX;
	for (int i = 1; i <= nr; i++) {
		double temp = test(i);
		if (temp < best)
			best = temp;
	}
	return best;
}

template<class Do>
void cpp_repeat(int nr, Do doIt) 
{
	for(int i = 1; i <= nr; i++)
		doIt(i);
}


#define findmatchintree(...) \
	PP_IIF(PP_EQUAL(2, VA_NARGS(__VA_ARGS__)), \
		cpp_findmatchintree(VA_ARG_0(__VA_ARGS__), [&](treenode a) -> bool {return VA_ARG_1(__VA_ARGS__);}), \
			cpp_findmatchtree(VA_ARG_0(__VA_ARGS__), [&](treenode a) -> bool {return VA_ARG_1(__VA_ARGS__);}, \
						[&](treenode a) -> FlexSimValue {return VA_ARG_2(__VA_ARGS__);}))

#define findmatch(...) \
	PP_IIF(PP_EQUAL(2, VA_NARGS(__VA_ARGS__)), \
		cpp_findmatch(VA_ARG_0(__VA_ARGS__), [&](int count) -> bool {return VA_ARG_1(__VA_ARGS__);}), \
		PP_IIF(PP_EQUAL(3, VA_NARGS(__VA_ARGS__)), \
			cpp_findmatch(VA_ARG_0(__VA_ARGS__), [&](int count) -> bool {return VA_ARG_1(__VA_ARGS__);}, \
						[&](int count) -> FlexSimValue {return VA_ARG_2(__VA_ARGS__);}), \
			cpp_findmatch(VA_ARG_0(__VA_ARGS__), [&](int count) -> bool {return VA_ARG_1(__VA_ARGS__);}, \
						[&](int count) -> FlexSimValue {return VA_ARG_2(__VA_ARGS__);}, VA_ARG_3(__VA_ARGS__))))


#define findmax(...) \
	PP_IIF(PP_EQUAL(2, VA_NARGS(__VA_ARGS__)), \
		cpp_findmax(VA_ARG_0(__VA_ARGS__), [&](int count) -> double {return VA_ARG_1(__VA_ARGS__);}), \
		PP_IIF(PP_EQUAL(3, VA_NARGS(__VA_ARGS__)), \
			cpp_findmax(VA_ARG_0(__VA_ARGS__), [&](int count) -> double {return VA_ARG_1(__VA_ARGS__);}, \
					[&](int count) -> FlexSimValue {return VA_ARG_2(__VA_ARGS__);}), \
			PP_IIF(PP_EQUAL(4, VA_NARGS(__VA_ARGS__)), \
				cpp_findmax(VA_ARG_0(__VA_ARGS__), [&](int count) -> double {return VA_ARG_1(__VA_ARGS__);}, \
						[&](int count) -> FlexSimValue {return VA_ARG_2(__VA_ARGS__);}, \
						[&](int count) -> bool {return VA_ARG_3(__VA_ARGS__);}), \
				cpp_findmax(VA_ARG_0(__VA_ARGS__), [&](int count) -> double {return VA_ARG_1(__VA_ARGS__);}, \
						[&](int count) -> FlexSimValue {return VA_ARG_2(__VA_ARGS__);}, \
						[&](int count) -> bool {return VA_ARG_3(__VA_ARGS__);}, VA_ARG_4(__VA_ARGS)))))

#define findmin(...) \
	PP_IIF(PP_EQUAL(2, VA_NARGS(__VA_ARGS__)), \
		cpp_findmin(VA_ARG_0(__VA_ARGS__), [&](int count) -> double {return VA_ARG_1(__VA_ARGS__);}), \
		PP_IIF(PP_EQUAL(3, VA_NARGS(__VA_ARGS__)), \
			cpp_findmin(VA_ARG_0(__VA_ARGS__), [&](int count) -> double {return VA_ARG_1(__VA_ARGS__);}, \
					[&](int count) -> FlexSimValue {return VA_ARG_2(__VA_ARGS__);}), \
			PP_IIF(PP_EQUAL(4, VA_NARGS(__VA_ARGS__)), \
				cpp_findmin(VA_ARG_0(__VA_ARGS__), [&](int count) -> double {return VA_ARG_1(__VA_ARGS__);}, \
						[&](int count) -> FlexSimValue {return VA_ARG_2(__VA_ARGS__);}, \
						[&](int count) -> bool {return VA_ARG_3(__VA_ARGS__);}), \
				cpp_findmin(VA_ARG_0(__VA_ARGS__), [&](int count) -> double {return VA_ARG_1(__VA_ARGS__);}, \
						[&](int count) -> FlexSimValue {return VA_ARG_2(__VA_ARGS__);}, \
						[&](int count) -> bool {return VA_ARG_3(__VA_ARGS__);}, VA_ARG_4(__VA_ARGS)))))

#define repeat(nr, doIt) cpp_repeat(nr, [&](int count) -> {doIt;});

#ifndef FLEXSIM_ENGINE_COMPILE
#define query(...) \
	PP_IIF(PP_EQUAL(1, VA_NARGS(__VA_ARGS__)), \
		cpp_query(VA_ARG_0(__VA_ARGS__)), \
	PP_IIF(PP_EQUAL(2, VA_NARGS(__VA_ARGS__)), \
		cpp_query(VA_ARG_0(__VA_ARGS__), \
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_1(__VA_ARGS__));})),\
	PP_IIF(PP_EQUAL(3, VA_NARGS(__VA_ARGS__)), \
		cpp_query(VA_ARG_0(__VA_ARGS__),  \
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_1(__VA_ARGS__));}),\
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_2(__VA_ARGS__));})),\
	PP_IIF(PP_EQUAL(4, VA_NARGS(__VA_ARGS__)), \
		cpp_query(VA_ARG_0(__VA_ARGS__), \
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_1(__VA_ARGS__));}),\
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_2(__VA_ARGS__));}),\
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_3(__VA_ARGS__));})),\
	PP_IIF(PP_EQUAL(5, VA_NARGS(__VA_ARGS__)), \
		cpp_query(VA_ARG_0(__VA_ARGS__), \
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_1(__VA_ARGS__));}),\
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_2(__VA_ARGS__));}),\
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_3(__VA_ARGS__));}),\
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_4(__VA_ARGS__));})),\
	PP_IIF(PP_EQUAL(6, VA_NARGS(__VA_ARGS__)), \
		cpp_query(VA_ARG_0(__VA_ARGS__), \
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_1(__VA_ARGS__));}),\
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_2(__VA_ARGS__));}),\
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_3(__VA_ARGS__));}),\
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_4(__VA_ARGS__));}),\
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_5(__VA_ARGS__));})),\
	PP_IIF(PP_EQUAL(7, VA_NARGS(__VA_ARGS__)), \
		cpp_query(VA_ARG_0(__VA_ARGS__), \
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_1(__VA_ARGS__));}),\
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_2(__VA_ARGS__));}),\
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_3(__VA_ARGS__));}),\
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_4(__VA_ARGS__));}),\
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_5(__VA_ARGS__));}),\
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_6(__VA_ARGS__));})),\
	PP_IIF(PP_EQUAL(8, VA_NARGS(__VA_ARGS__)), \
		cpp_query(VA_ARG_0(__VA_ARGS__), \
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_1(__VA_ARGS__));}),\
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_2(__VA_ARGS__));}),\
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_3(__VA_ARGS__));}),\
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_4(__VA_ARGS__));}),\
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_5(__VA_ARGS__));}),\
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_6(__VA_ARGS__));}),\
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_7(__VA_ARGS__));})),\
	PP_IIF(PP_EQUAL(9, VA_NARGS(__VA_ARGS__)), \
		cpp_query(VA_ARG_0(__VA_ARGS__), \
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_1(__VA_ARGS__));}),\
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_2(__VA_ARGS__));}),\
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_3(__VA_ARGS__));}),\
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_4(__VA_ARGS__));}),\
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_5(__VA_ARGS__));}),\
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_6(__VA_ARGS__));}),\
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_7(__VA_ARGS__));}),\
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_8(__VA_ARGS__));})),\
		cpp_query(VA_ARG_0(__VA_ARGS__), \
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_1(__VA_ARGS__));}),\
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_2(__VA_ARGS__));}),\
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_3(__VA_ARGS__));}),\
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_4(__VA_ARGS__));}),\
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_5(__VA_ARGS__));}),\
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_6(__VA_ARGS__));}),\
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_7(__VA_ARGS__));}),\
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_8(__VA_ARGS__));}),\
		                    QueryCallback([&]() -> double {return FlexSimValue(VA_ARG_9(__VA_ARGS__));}))\
	)))))))))
#endif

#endif

/// <summary> The NodeListArray class is 
/// meant to allow you, in c++, to treat a list of nodes with coupling data just
/// like a regular 0-based c++ array. So, instead of every time you have to do 
/// something like NetworkNode* nn = &o(NetworkNode, ownerobject(tonode(get(rank(node_v_myNetNodes, i)))));
/// you can just add the correct NodeListArray to your class, and do myNetNodes[i],
/// and bam, it handles all the rest.</summary>
/// 
/// <remarks> There are different ways that a list of coupling nodes may be set up, so
/// there are also several different types I've defined to represent these different
/// types of node list arrays. For example, you may have a list of just one-way 
/// pointers directly to the objects themselves. Or you may have a list of coupling nodes
/// where the other side of the coupling is created in the "stored" attribute
/// of the associated object, and so on. 
/// 
/// So, below are the basic defined ones that you can use out of the box. See the documeation of 
/// each on for more information
/// NodeListArray<YourClass>::ObjPtrType
/// NodeListArray<YourClass>::CouplingSdtPtrType
/// NodeListArray<YourClass>::ObjStoredAttCouplingType
/// NodeListArray<YourClass, YourAdder>::ObjCouplingType
/// NodeListArray<YourClass>::SdtSubNodeType
/// NodeListArray<YourClass>::SdtSubNodeBindingType
/// NodeListArray<YourClass>::CouplingSdtSubNodeType
/// NodeListArray<YourClass>::CouplingSdtSubNodeBindingType
/// NodeListArray<>::NodePtrType
/// NodeListArray<>::StoredAttCouplingType
/// NodeListArray<>::SubNodeCouplingType
/// NodeListArray<YourClass>::SdtSubNodeCouplingType
/// 
/// 
/// Also, usually you are going to initialize a NodeListArray in your bind()
/// or bindVariables() method, depending on if you're an odt or an sdt. </remarks>
template<class T = TreeNode, void (*Adder)(treenode x, T* obj) = 0, T* (*Getter)(treenode x) = 0>
class NodeListArray
{
	treenode parent;

public:
	NodeListArray() : parent(0) {}
	NodeListArray(treenode parent) : parent(parent) {}
	void init(treenode parent) {this->parent = parent;}
	
	int size() {return content(parent);}

	T* operator[](int index)
	{
		_ASSERTE(index >= 0 && index < size());
		treenode subNode = rank(parent, index + 1);
		return Getter(subNode);
	}
	T* operator[](const char* name)
	{
		treenode x = node(name, parent);
		if(objectexists(x))
			return operator[](getrank(x) - 1);
		return NULL;
	}
	T* back()
	{
		if (size() == 0)
			return 0;
		treenode subNode = last(parent);
		return Getter(subNode);
	}
	T* add(T* obj)
	{
		_ASSERTE(obj != 0);
		treenode tmp = nodeadddata(nodeinsertinto(parent), DATA_POINTERCOUPLING);
		Adder(tmp, obj);
		return obj;
	}
	void remove(int index)
	{
		_ASSERTE(index >= 0 && index < size());
		destroynode(rank(parent, index + 1));
	}
	void clear(){clearcontents(parent);}
	void swap(int index1, int index2){swapnoderanks(parent, index2 + 1, index1 + 1);}
	void setRank(int fromIndex, int toIndex){setrank(rank(parent, fromIndex + 1), toIndex + 1);}
	int find(T* x)
	{
		int tmpSize = size();
		for(int i = 0; i < tmpSize; i++) 
			if(operator[](i) == x) 
				return i;
		return -1;
	}

	static TreeNode* NodePtrGetter(treenode x) {return tonode(get(x));}
	static void NodePtrAdder (treenode x, TreeNode* obj) {nodepoint(x, obj);}

	static TreeNode* StoredAttCouplingGetter (treenode x) 
	{
		treenode partner = x->dataascoupling ? x->dataascoupling->partner() : 0; 
		if (partner)
			return ownerobject(partner);
		return 0;
	}
	static void StoredAttCouplingAdder (treenode x, TreeNode* obj) {nodejoin(x, nodeadddata(nodeinsertinto(assertattribute(obj, "stored", 0)), DATA_POINTERCOUPLING));}

	static TreeNode* SubNodeCouplingGetter (treenode x)
	{
		treenode partner = x->datatype == DATA_POINTERCOUPLING ? x->dataascoupling->partner() : 0;  
		if (partner)
			return up(partner);
		return 0;
	}
	static void SubNodeCouplingAdder (treenode x, TreeNode* obj) {nodejoin(x, nodeadddata(nodeinsertinto(obj), DATA_POINTERCOUPLING));}
	static T* SdtSubNodeCouplingGetter (treenode x)
	{
		treenode partner = x->datatype == DATA_POINTERCOUPLING ? x->dataascoupling->partner() : 0;  
		if (partner)
			return &o(T, up(partner));
		return 0;
	}
	static void SdtSubNodeCouplingAdder (treenode x, T* obj) 
	{
		_ASSERTE(obj->holder != 0);
		nodejoin(x, nodeadddata(nodeinsertinto(obj->holder), DATA_POINTERCOUPLING));
	}

	static T* SdtSubNodeGetter (treenode x) {return &o(T, x);}
	static void SdtSubNodeAdder (treenode x, T* obj) {nodeaddsimpledata(x, obj, 0);}
	static void SdtSubNodeBindingAdder (treenode x, T* obj) {nodeaddsimpledata(x, obj, 1);}
	static void CouplingSdtSubNodeAdder (treenode x, T* obj) {nodeaddcouplingdata(x, obj, 0);}
	static void CouplingSdtSubNodeBindingAdder (treenode x, T* obj) {nodeaddcouplingdata(x, obj, 1);}
	static void ObjSubNodeAdder (treenode x, T* obj) {transfernode(obj->holder, up(x)); destroyobject(x);}

	static T* ObjPtrGetter(treenode x)
	{
		treenode partner = x->datatype == DATA_POINTERCOUPLING ? x->dataascoupling->partner() : 0;   
		if (partner)
			return &o(T, partner);
		return 0;
	}
	static void ObjPtrAdder (treenode x, T* obj) 
	{
		_ASSERTE(obj->holder != 0);
		nodepoint(x, obj->holder);
	}
	static void CouplingSdtPtrAdder (treenode x, T* obj) 
	{
		_ASSERTE(obj->holder != 0);
		nodejoin(x, obj->holder);
	}

	static T* ObjCouplingGetter (treenode x)
	{
		treenode partner = x->datatype == DATA_POINTERCOUPLING ? x->dataascoupling->partner() : 0;  
		if (partner)
			return &o(T, ownerobject(partner));
		return 0;
	}
	static void ObjCouplingAdder(treenode x, T* obj) 
	{
		_ASSERTE(obj->holder != 0);
		nodejoin(x, nodeadddata(nodeinsertinto(assertattribute(obj->holder, "stored", 0)), DATA_POINTERCOUPLING));
	}


/*********************************************************************
OK, Here are the list of classes that this header file sets up for you.
**********************************************************************/

/*********************************************************************
NodeListArray<TheClass>::ObjPtrType
This one represents a list of direct one-way pointers to odt or sdt objects,
For example, you may do:
NodeListArray<NetworkNode>::ObjPtrType myNetNodes;
Then dereferencing myNetNodes[arrayIndex] will get you back a NetworkNode*
**********************************************************************/
	typedef NodeListArray<T, ObjPtrAdder, ObjPtrGetter> ObjPtrType;
	
/*********************************************************************
NodeListArray<TheClass>::CouplingSdtPtrType
This one represents a list of two-way pointers to coupling sdt objects. It is like
ObjPtrType in that each item in the list is a coupling node that points to an
object, but it also assumes the other side of the reference is a coupling sdt, so
when adding, it will join the nodes together with a two-way pointer instead of just
a one-way pointer to the object. This is useful when you have coupling nodes where 
one side of the coupling is your custom coupling class (you would use the 
CouplingSdtSubNodeType for that side), and the other is just a vanilla coupling node 
bound to that class. On the vanilla side, you would use CouplingSdtPtrType. Note that when
using this and adding connections to the list, you should add the 
CouplingSdtSubNodeType first, then add the CouplingSdtPtrType (the vanilla side) 
last to properly establish the connection.
**********************************************************************/
	typedef NodeListArray<T, CouplingSdtPtrAdder, ObjPtrGetter> CouplingSdtPtrType;

/*********************************************************************
NodeListArray<TheClass>::ObjStoredAttCouplingType
This one represents a list of two-way couplings to odt objects. The other side of the 
coupling will be stored in the "stored" attribute of each object.
NodeListArray<NetworkNode>::ObjStoredAttCouplingType myNetNodes;
myNetNodes[arrayIndex] will then retrieve a NetworkNode*
**********************************************************************/
	typedef NodeListArray<T, ObjCouplingAdder, ObjCouplingGetter> ObjStoredAttCouplingType;

/*********************************************************************
NodeListArray<TheClass, YourAdder>::ObjCouplingType
This one represents a list of two-way couplings to odt objects. It's like 
ObjStoredAttCouplingType except the other side of the 
coupling is stored where you want it to be stored, so you have to add the adder yourself

NodeListArray<NetworkNode, myAddToNetNodesVar>::ObjCouplingType myNetNodes;
myNetNodes[arrayIndex] will then retrieve a NetworkNode*. Note you have to define 
the function myAddToNetNodesVar, which in this example should look like this:
void myAddToNetNodesVar(treenode x, NetworkNode* y) {
	nodejoin(x, nodeadddata(nodeinsertinto(y->node_v_backpointer), DATATYPE_COUPLING);
}
**********************************************************************/
	typedef NodeListArray<T, Adder, ObjCouplingGetter> ObjCouplingType;

/*********************************************************************
NodeListArray<TheClass>::SdtSubNodeType
This one represents a straight list of sdt's.

NodeListArray<MySdt>::SdtSubNodeType mySdts;
myNetNodes[arrayIndex] will then retrieve the MySdt* stored directly in the given sub-node.
**********************************************************************/
typedef NodeListArray<T, SdtSubNodeAdder, SdtSubNodeGetter> SdtSubNodeType;
typedef NodeListArray<T, SdtSubNodeBindingAdder, SdtSubNodeGetter> SdtSubNodeBindingType;

/*********************************************************************
NodeListArray<TheClass>::CouplingSdtSubNodeType
This one represents a straight list of coupling sdt's. It's just like SdtSubNodeType, except
the adder will use nodeaddcouplingdata() instead of nodeaddsimpledata().

NodeListArray<MySdt>::CouplingSdtSubNodeType mySdts;
myNetNodes[arrayIndex] will then retrieve the MySdt* stored directly in the given sub-node.
**********************************************************************/
	typedef NodeListArray<T, CouplingSdtSubNodeAdder, SdtSubNodeGetter> CouplingSdtSubNodeType;
	typedef NodeListArray<T, CouplingSdtSubNodeBindingAdder, SdtSubNodeGetter> CouplingSdtSubNodeBindingType;

/*********************************************************************
NodeListArray<TheClass>::ObjSubNodeType
This one represents a straight list of odt's.

NodeListArray<MyObj>::ObjSubNodeType myObjs;
myObjs[arrayIndex] will then retrieve the MyObj* stored directly in the given sub-node.
to add, you do myObjs.add(&o(MyObj, createinstance(theClass, model())));
**********************************************************************/
typedef NodeListArray<T, ObjSubNodeAdder, SdtSubNodeGetter> ObjSubNodeType;

/*********************************************************************
NodeListArray::NodePtrType:
This one represents a list of one-way pointers to nodes. This is just like the 
NodeListArray::ObjPtrType, except it returns a TreeNode*, i.e. the node itself instead of the odt/sdt.
This can be used if you're pointing to nodes that don't necessarily have object data.
NodeListArray::NodePtrType myNetNodes;
myNetNodes[arrayIndex] will then get back a treenode that is the network node.
**********************************************************************/
	typedef NodeListArray<TreeNode, NodePtrAdder, NodePtrGetter> NodePtrType;

/*********************************************************************
NodeListArray::StoredAttCouplingType:
This one represents a list of two-way couplings to objects. This is just like the 
NodeListArray::ObjStoredAttCouplingType, except it returns a TreeNode*, i.e. the node itself instead of the odt/sdt.
Like ObjListArray, the other side of the coupling will be stored in the "stored" attribute
of the object.
NodeListArray::StoredAttCouplingType myNetNodes;
myNetNodes[arrayIndex] will then get back a treenode that is the network node.
**********************************************************************/
	typedef NodeListArray<TreeNode, StoredAttCouplingAdder, StoredAttCouplingGetter> StoredAttCouplingType;

/*********************************************************************
NodeListArray::SubNodeCouplingType:
This one represents a list of two-way couplings to nodes. This will store the other side of the 
coupling as a sub-node of the node referenced, and when dereferenced it will return the node that
contains the coupling sub-node.
**********************************************************************/
	typedef NodeListArray<TreeNode, SubNodeCouplingAdder, SubNodeCouplingGetter> SubNodeCouplingType;

/*********************************************************************
NodeListArray<MyObj>::SdtSubNodeCouplingType:
This one represents a list of two-way couplings to objects. This will store the other side of the 
coupling as a sub-node of the object referenced, and when dereferenced it will return the object 
whose holder node contains the coupling sub-node. It's just like SubNodeCouplingType, except it returns
an object reference instead of a node reference.
**********************************************************************/
	typedef NodeListArray<T, SdtSubNodeCouplingAdder, SdtSubNodeCouplingGetter> SdtSubNodeCouplingType;
};


