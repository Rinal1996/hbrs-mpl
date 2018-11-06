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

#pragma once

#ifndef ELEMENTAL_FUSE_FN_COLUMNS_HPP
#define ELEMENTAL_FUSE_FN_COLUMNS_HPP

#include <elemental/config.hpp>
#include <elemental/dt/matrix.hpp>
// #include <elemental/dt/vector.hpp>
// #include <hbrs/mpl/fn/size.hpp>
// #include <hbrs/mpl/fn/m.hpp>
// #include <hbrs/mpl/fn/n.hpp>
#include <hbrs/mpl/dt/smcs.hpp>
#include <El.hpp>
#include <boost/hana/tuple.hpp>
#include <type_traits>
#include <vector>

ELEMENTAL_NAMESPACE_BEGIN
namespace mpl = hbrs::mpl;
namespace detail {

struct columns_impl_Matrix {
// 	template <typename Ring>
// 	constexpr auto
// 	operator()(El::Matrix<Ring> const& a) const {
// 		using namespace hbrs::mpl;
// 		
// 		typedef std::decay_t<Ring> _Ring_;
// 		auto a_sz = (*size)(a);
// 		auto a_m = (*m)(a_sz);
// 		auto a_n = (*n)(a_sz);
// 		
// 		std::vector<row_vector<_Ring_>> v;
// 		v.reserve(a_n);
// 		for(El::Int i = 0; i < a_n; ++i) {
// 			v.emplace_back( a(El::ALL, i) );
// 		}
// 		return v;
// 		
// 		return mpl::smcs<Matrix>{HBRS_MPL_FWD(a)};
// 	}
	
	template <
		typename Matrix,
		typename std::enable_if_t< 
			std::is_same< hana::tag_of_t<Matrix>, hana::ext::El::Matrix_tag >::value
		>* = nullptr
	>
	constexpr auto
	operator()(Matrix && a) const {
		return mpl::smcs<Matrix>{HBRS_MPL_FWD(a)};
	}
};

/* namespace detail */ }
ELEMENTAL_NAMESPACE_END

#define ELEMENTAL_FUSE_FN_COLUMNS_IMPLS boost::hana::make_tuple(                                                       \
		elemental::detail::columns_impl_Matrix{}                                                                       \
	)

#endif // !ELEMENTAL_FUSE_FN_COLUMNS_HPP