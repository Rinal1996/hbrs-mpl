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

#include "elemental.hpp"
#ifdef HBRS_MPL_ENABLE_ELEMENTAL

HBRS_MPL_NAMESPACE_BEGIN
namespace detail {

//TODO: Implement El::Complex<> overloads
template auto rdivide_impl_scalar_el_vector::operator()(float  const&, el_row_vector<float>              ) const;
// template auto rdivide_impl_scalar_el_vector::operator()(float  const&, el_row_vector<El::Complex<float>> ) const;
template auto rdivide_impl_scalar_el_vector::operator()(double const&, el_row_vector<double>             ) const;
// template auto rdivide_impl_scalar_el_vector::operator()(double const&, el_row_vector<El::Complex<double>>) const;

template auto rdivide_impl_scalar_el_dist_vector::operator()(float const& b, el_dist_column_vector<float> &&) const;
// template auto rdivide_impl_scalar_el_dist_vector::operator()(float const& b, el_dist_column_vector<El::Complex<float>> &&) const;
template auto rdivide_impl_scalar_el_dist_vector::operator()(double const& b, el_dist_column_vector<double> &&) const;
// template auto rdivide_impl_scalar_el_dist_vector::operator()(double const& b, el_dist_column_vector<El::Complex<double>> &&) const;
	
/* namespace detail */ }
HBRS_MPL_NAMESPACE_END

#endif // !HBRS_MPL_ENABLE_ELEMENTAL
