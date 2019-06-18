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

#ifndef HBRS_MPL_FN_MINUS_FWD_BOOST_HANA_HPP
#define HBRS_MPL_FN_MINUS_FWD_BOOST_HANA_HPP

#include <hbrs/mpl/config.hpp>
#include <hbrs/mpl/detail/operators/fwd/boost_hana.hpp>
#include <boost/hana/tuple.hpp>

#define HBRS_MPL_FN_MINUS_IMPLS_BOOST_HANA boost::hana::make_tuple(                                                    \
		hbrs::mpl::detail::minus_impl_hana_ic{}                                                                        \
	)

#endif // !HBRS_MPL_FN_MINUS_FWD_BOOST_HANA_HPP