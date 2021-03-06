/* Copyright (c) 2019 Abdullah Güntepe, <abdullah@guentepe.com>
 * Copyright (c) 2019 Jakob Meng, <jakobmeng@web.de>
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

#ifndef HBRS_MPL_FN_DIVIDE_IMPL_HBRS_MPL_HPP
#define HBRS_MPL_FN_DIVIDE_IMPL_HBRS_MPL_HPP

#include "../fwd/hbrs_mpl.hpp"

#include <hbrs/mpl/dt/rtsacv.hpp>
#include <hbrs/mpl/fn/multiply.hpp>
#include <hbrs/mpl/fn/divide.hpp>
#include <type_traits>

HBRS_MPL_NAMESPACE_BEGIN
namespace detail {

template<typename Ring>
decltype(auto)
divide_impl_rtsacv_scalar::operator()(rtsacv<Ring> const& v, Ring const& d) const {
	typedef std::decay_t<Ring> _Ring_;
	return multiply(divide(_Ring_(1), d), v);
}

/* namespace detail */ }
HBRS_MPL_NAMESPACE_END

#endif // !HBRS_MPL_FN_DIVIDE_IMPL_HBRS_MPL_HPP
