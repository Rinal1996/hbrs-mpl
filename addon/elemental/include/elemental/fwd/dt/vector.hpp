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

#ifndef ELEMENTAL_FWD_DT_VECTOR_HPP
#define ELEMENTAL_FWD_DT_VECTOR_HPP

#include <elemental/config.hpp>
#include <boost/hana/fwd/core/make.hpp>
#include <boost/hana/fwd/core/to.hpp>

ELEMENTAL_NAMESPACE_BEGIN
namespace hana = boost::hana;

template<typename Ring>
struct column_vector;
struct column_vector_tag;
constexpr auto make_column_vector = hana::make<column_vector_tag>;
constexpr auto to_column_vector = hana::to<column_vector_tag>;

template<typename Ring>
struct row_vector;
struct row_vector_tag;
constexpr auto make_row_vector = hana::make<row_vector_tag>;
constexpr auto to_row_vector = hana::to<row_vector_tag>;

ELEMENTAL_NAMESPACE_END

#endif // !ELEMENTAL_FWD_DT_VECTOR_HPP