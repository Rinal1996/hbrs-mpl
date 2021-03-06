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

#ifndef HBRS_MPL_FN_ITERATE_FWD_STD_HPP
#define HBRS_MPL_FN_ITERATE_FWD_STD_HPP

#include <boost/hana/tuple.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <type_traits>

HBRS_MPL_NAMESPACE_BEGIN
namespace hana = boost::hana;
namespace detail {

template<typename F>
struct iterate_impl_helper;

struct iterate_impl {
	template <typename F>
	constexpr iterate_impl_helper<F>
	operator()(F && f, std::size_t n) const;
	
	template <typename F, std::size_t n>
	constexpr decltype(auto)
	operator()(F && f, std::integral_constant<std::size_t, n>) const;
	
};

/* namespace detail */ }
HBRS_MPL_NAMESPACE_END

#define HBRS_MPL_FN_ITERATE_IMPLS_STD boost::hana::make_tuple(                                                    \
		hbrs::mpl::detail::iterate_impl{}                                                                              \
	)

#endif // !HBRS_MPL_FN_ITERATE_FWD_STD_HPP
