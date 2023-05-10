#ifndef _type_traits_hpp_
#define _type_traits_hpp_

#include <iostream>

namespace ft
{
	// ---- integral_constant ----
	// template <class T, T v>
	// struct integral_constant
	// {
	// 	static const T value = v;
	// 	typedef T value_type;
	// 	typedef integral_constant<T, v> type;
	// 	T const operator()(void) { return (this->value); }
	// };

	// ---- true_type and false_type ----
	typedef std::integral_constant<bool, true>	true_type;
	typedef std::integral_constant<bool, false>	false_type;

	// ---- enable_if ----
	template <bool, typename T = void>
	struct enable_if {};

	template <typename T>
	struct enable_if<true, T> { typedef T type; };

	// ---- is_integral ----
	template <typename T> struct is_integral 				: 	public false_type {};
	template <> struct is_integral<bool> 					: 	public true_type {};
	template <> struct is_integral<char> 					: 	public true_type {};
	template <> struct is_integral<char16_t> 				: 	public true_type {};
	template <> struct is_integral<char32_t>				: 	public true_type {};
	template <> struct is_integral<wchar_t> 				: 	public true_type {};
	template <> struct is_integral<signed char> 			: 	public true_type {};
	template <> struct is_integral<short int> 				: 	public true_type {};
	template <> struct is_integral<int> 					: 	public true_type {};
	template <> struct is_integral<long int>				: 	public true_type {};
	template <> struct is_integral<long long int>			: 	public true_type {};
	template <> struct is_integral<unsigned char>			: 	public true_type {};
	template <> struct is_integral<unsigned short int>		: 	public true_type {};
	template <> struct is_integral<unsigned int>			: 	public true_type {};
	template <> struct is_integral<unsigned long int>		: 	public true_type {};
	template <> struct is_integral<unsigned long long int>	: 	public true_type {};
}

#endif
