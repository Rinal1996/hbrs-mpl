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

#ifndef HBRS_MPL_DT_GIVENS_RESULT_FWD_HPP
#define HBRS_MPL_DT_GIVENS_RESULT_FWD_HPP

#include <hbrs/mpl/config.hpp>
#include <boost/hana/fwd/core/make.hpp>
#include <boost/hana/fwd/core/to.hpp>

HBRS_MPL_NAMESPACE_BEGIN
namespace hana = boost::hana;

template<typename C, typename S>
struct givens_result;
struct givens_result_tag {};
constexpr auto make_givens_result = hana::make<givens_result_tag>;
constexpr auto to_givens_result = hana::to<givens_result_tag>;

HBRS_MPL_NAMESPACE_END

#endif // !HBRS_MPL_DT_GIVENS_RESULT_FWD_HPP
