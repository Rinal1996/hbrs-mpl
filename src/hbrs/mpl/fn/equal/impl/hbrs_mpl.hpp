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

#ifndef HBRS_MPL_FUSE_HBRS_MPL_FN_EQUAL_HPP
#define HBRS_MPL_FUSE_HBRS_MPL_FN_EQUAL_HPP

#include <hbrs/mpl/config.hpp>
#include <hbrs/mpl/fn/equal/fwd.hpp>
#include <hbrs/mpl/detail/function_object.hpp>
#include <hbrs/mpl/fwd/dt/matrix_size.hpp>
#include <hbrs/mpl/fwd/dt/matrix_index.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/tuple.hpp>
#include <type_traits>

HBRS_MPL_NAMESPACE_BEGIN
namespace hana = boost::hana;
namespace detail {

HBRS_MPL_DEF_FO_TRY_OPERATOR(equal_impl_matrix_size, matrix_size_tag, HBRS_MPL_OPERATOR_EQUAL, equal)
HBRS_MPL_DEF_FO_TRY_OPERATOR(equal_impl_matrix_index, matrix_index_tag, HBRS_MPL_OPERATOR_EQUAL, equal)

/* namespace detail */ }
HBRS_MPL_NAMESPACE_END

#define HBRS_MPL_FUSE_HBRS_MPL_FN_EQUAL_IMPLS boost::hana::make_tuple(                                                 \
		hbrs::mpl::detail::equal_impl_matrix_size{},                                                                   \
		hbrs::mpl::detail::equal_impl_matrix_index{}                                                                   \
	)

#endif // !HBRS_MPL_FUSE_HBRS_MPL_FN_EQUAL_HPP
