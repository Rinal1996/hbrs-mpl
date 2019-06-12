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

#include <hbrs/mpl/fn/vertcat.hpp>

ELEMENTAL_NAMESPACE_BEGIN
namespace detail {

template auto vertcat_impl_smr_smr::operator()(
	mpl::smr<matrix<float>, El::Int> const&,
	mpl::smr<matrix<float>, El::Int> const&
) const;

template auto vertcat_impl_smr_smr::operator()(
	mpl::smr<matrix<El::Complex<float>>, El::Int> const&,
	mpl::smr<matrix<El::Complex<float>>, El::Int> const&
) const;

template auto vertcat_impl_smr_smr::operator()(
	mpl::smr<matrix<double>, El::Int> const&,
	mpl::smr<matrix<double>, El::Int> const&
) const;

template auto vertcat_impl_smr_smr::operator()(
	mpl::smr<matrix<El::Complex<double>>, El::Int> const&,
	mpl::smr<matrix<El::Complex<double>>, El::Int> const&
) const;

template auto vertcat_impl_matrix_smr::operator()(
	matrix<float> const&,
	mpl::smr<matrix<float>, El::Int> const&
) const;

template auto vertcat_impl_matrix_smr::operator()(
	matrix<El::Complex<float>> const&,
	mpl::smr<matrix<El::Complex<float>>, El::Int> const&
) const;

template auto vertcat_impl_matrix_smr::operator()(
	matrix<double> const&,
	mpl::smr<matrix<double>, El::Int> const&
) const;

template auto vertcat_impl_matrix_smr::operator()(
	matrix<El::Complex<double>> const&,
	mpl::smr<matrix<El::Complex<double>>, El::Int> const&
) const;

/* namespace detail */ }
ELEMENTAL_NAMESPACE_END