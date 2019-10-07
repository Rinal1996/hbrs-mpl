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

//TODO: Add impls!

template decltype(auto) dmd_impl_el_matrix::operator()(
	el_matrix<float> const&,
	el_matrix<float> const&,
	dmd_control<El::Int> const&) const;

// template decltype(auto) dmd_impl_el_matrix::operator()(
// 	el_matrix<El::Complex<float>> const&,
// 	el_matrix<El::Complex<float>> const&,
// 	dmd_control<El::Int> const&) const;

template decltype(auto) dmd_impl_el_matrix::operator()(
	el_matrix<double> const&,
	el_matrix<double> const&,
	dmd_control<El::Int> const&) const;

// template decltype(auto) dmd_impl_el_matrix::operator()(
// 	el_matrix<El::Complex<double>> const&,
// 	el_matrix<El::Complex<double>> const&,
// 	dmd_control<El::Int> const&) const;

template decltype(auto) dmd_impl_el_dist_matrix::operator()(
	el_dist_matrix<float> const&,
	el_dist_matrix<float> const&,
	dmd_control<El::Int> const&) const;

// template decltype(auto) dmd_impl_el_dist_matrix::operator()(
// 	el_dist_matrix<El::Complex<float>> const&,
// 	el_dist_matrix<El::Complex<float>> const&,
// 	dmd_control<El::Int> const&) const;

template decltype(auto) dmd_impl_el_dist_matrix::operator()(
	el_dist_matrix<double> const&,
	el_dist_matrix<double> const&,
	dmd_control<El::Int> const&) const;

// template decltype(auto) dmd_impl_el_dist_matrix::operator()(
// 	el_dist_matrix<El::Complex<double>> const&,
// 	el_dist_matrix<El::Complex<double>> const&,
// 	dmd_control<El::Int> const&) const;

/* namespace detail */ }
HBRS_MPL_NAMESPACE_END

#endif // !HBRS_MPL_ENABLE_ELEMENTAL
