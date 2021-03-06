/* Copyright (c) 2019 Jakob Meng, <jakobmeng@web.de>
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

#ifndef HBRS_MPL_DETAIL_IS_INF_IMPL_HPP
#define HBRS_MPL_DETAIL_IS_INF_IMPL_HPP

#include "fwd.hpp"

#include <hbrs/mpl/config.hpp>
#include <hbrs/mpl/core/preprocessor.hpp>
#include <cmath>

HBRS_MPL_NAMESPACE_BEGIN
namespace hana = boost::hana;
namespace detail {

//TODO: Move code to dedicated global function
struct is_inf_t {
	template<typename T>
	decltype(auto)
	operator()(T && t) const {
		return std::isinf(HBRS_MPL_FWD(t));
	}
};

constexpr is_inf_t is_inf{};

/* namespace detail */ }
HBRS_MPL_NAMESPACE_END

#endif // !HBRS_MPL_DETAIL_IS_INF_IMPL_HPP
