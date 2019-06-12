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

#ifndef HBRS_MPL_FUSE_BOOST_HANA_FN_CONTAINS_HPP
#define HBRS_MPL_FUSE_BOOST_HANA_FN_CONTAINS_HPP

#include <hbrs/mpl/preprocessor/core.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/contains.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/concept/comparable.hpp>
#include <type_traits>

HBRS_MPL_NAMESPACE_BEGIN
namespace hana = boost::hana;
namespace detail {
	
struct contains_impl_hana_tuple {
	template<
		typename S, 
		typename E, 
		typename std::enable_if_t< 
			std::is_same< hana::tag_of_t<S>, hana::tuple_tag >::value &&
			hana::Comparable<E&&>::value
		>* = nullptr
	>
	constexpr decltype(auto)
	operator()(S && s, E && e) const {
		return hana::contains(HBRS_MPL_FWD(s), HBRS_MPL_FWD(e));
	}
};

/* namespace detail */ }
HBRS_MPL_NAMESPACE_END

#define HBRS_MPL_FUSE_BOOST_HANA_FN_CONTAINS_IMPLS boost::hana::make_tuple(                                            \
		hbrs::mpl::detail::contains_impl_hana_tuple{}                                                                  \
	)

#endif // !HBRS_MPL_FUSE_BOOST_HANA_FN_CONTAINS_HPP