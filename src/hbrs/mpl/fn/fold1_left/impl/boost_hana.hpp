/* Copyright (c) 2018 Jakob Meng, <jakobmeng@web.de>
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

#ifndef HBRS_MPL_FN_FOLD1_LEFT_IMPL_BOOST_HANA_HPP
#define HBRS_MPL_FN_FOLD1_LEFT_IMPL_BOOST_HANA_HPP

#include "../fwd/boost_hana.hpp"

HBRS_MPL_NAMESPACE_BEGIN
namespace hana = boost::hana;
namespace detail {

template <
	typename Sequence,
	typename F,
	typename std::enable_if_t< 
		is_tag_and_is_invokable_trait<detail::fold1_left_t, Sequence &&, hana::tuple_tag, F&& >::value
	>*
>
constexpr decltype(auto)
fold1_left_impl_hana::operator()(Sequence && s, F && f) const {
	return detail::fold1_left(s, HBRS_MPL_FWD(f));
}

/* namespace detail */ }
HBRS_MPL_NAMESPACE_END

#endif // !HBRS_MPL_FN_FOLD1_LEFT_IMPL_BOOST_HANA_HPP
