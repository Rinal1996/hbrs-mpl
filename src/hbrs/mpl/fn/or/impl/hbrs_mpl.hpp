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

#ifndef HBRS_MPL_FN_OR_IMPL_HBRS_MPL_HPP
#define HBRS_MPL_FN_OR_IMPL_HBRS_MPL_HPP

#include "../fwd/hbrs_mpl.hpp"
#include <boost/hana/if.hpp>

HBRS_MPL_NAMESPACE_BEGIN
namespace hana = boost::hana;
namespace detail {

template<
	typename L,
	typename R,
	typename std::enable_if_t<
		(
			std::is_same<
				hana::tag_of_t<
					decltype(evaluate(std::declval<L&&>()))
				>,
				hana::integral_constant_tag<bool>
			>::value ||
			std::is_same<
				hana::tag_of_t<
					decltype(evaluate(std::declval<L&&>()))
				>,
				hana::ext::std::integral_constant_tag<bool>
			>::value 
		) &&
		(
			std::is_same<
				hana::tag_of_t<
					decltype(evaluate(std::declval<R&&>()))
				>,
				hana::integral_constant_tag<bool>
			>::value ||
			std::is_same<
				hana::tag_of_t<
					decltype(evaluate(std::declval<R&&>()))
				>,
				hana::ext::std::integral_constant_tag<bool>
			>::value ||
			std::is_same<
				hana::tag_of_t<
					decltype(evaluate(std::declval<R&&>()))
				>,
				bool
			>::value
		)
	>*
>
constexpr decltype(auto)
or__impl_ic::operator()(L && l, R && r) const {
	return evaluate(
		hana::if_(
			!evaluate(HBRS_MPL_FWD(l)),
			hana::false_c,
			HBRS_MPL_FWD(r)
		)
	);
}

template<
	typename L,
	typename R,
	typename std::enable_if_t<
		std::is_convertible<
			decltype(evaluate(std::declval<L&&>())),
			bool
		>::value &&
		std::is_convertible<
			decltype(evaluate(std::declval<R&&>())),
			bool
		>::value
	>*
>
constexpr decltype(auto)
or__impl_i::operator()(L && l, R && r) const {
	return evaluate(HBRS_MPL_FWD(l)) || evaluate(HBRS_MPL_FWD(r));
}

/* namespace detail */ }
HBRS_MPL_NAMESPACE_END

#endif // !HBRS_MPL_FN_OR_IMPL_HBRS_MPL_HPP
