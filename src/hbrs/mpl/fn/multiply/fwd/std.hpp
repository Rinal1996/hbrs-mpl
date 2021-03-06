/* Copyright (c) 2016-2018 Jakob Meng, <jakobmeng@web.de>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef HBRS_MPL_FN_MULTIPLY_FWD_STD_HPP
#define HBRS_MPL_FN_MULTIPLY_FWD_STD_HPP

#include <hbrs/mpl/config.hpp>
#include <hbrs/mpl/detail/operators/fwd/std.hpp>
#include <boost/hana/tuple.hpp>

HBRS_MPL_NAMESPACE_BEGIN
namespace detail {
HBRS_MPL_DECLARE_STD_INTEGRAL_CONSTANT_OPERATOR_IMPL_ARITY2(multiply, HBRS_MPL_OPERATOR_MULTIPLY)
HBRS_MPL_DECLARE_STD_ARITHMETIC_ENUM_OPERATOR_IMPL_ARITY2(multiply, HBRS_MPL_OPERATOR_MULTIPLY)
HBRS_MPL_DECLARE_FREEFUN_OPERATOR_IMPL_ARITY2(multiply, HBRS_MPL_OPERATOR_MULTIPLY)
/* namespace detail */ }
HBRS_MPL_NAMESPACE_END

#define HBRS_MPL_FN_MULTIPLY_IMPLS_STD boost::hana::make_tuple(                                                        \
		hbrs::mpl::detail::multiply_impl_std_ic{},                                                                     \
		hbrs::mpl::detail::multiply_impl_std_op{},                                                                     \
		hbrs::mpl::detail::multiply_impl_lhs_is_braces_constructible{},                                                \
		hbrs::mpl::detail::multiply_impl_rhs_is_braces_constructible{},                                                \
		hbrs::mpl::detail::multiply_impl_numeric_cast{},                                                               \
		hbrs::mpl::detail::multiply_impl_op{}                                                                          \
	)

#endif // !HBRS_MPL_FN_MULTIPLY_FWD_STD_HPP
