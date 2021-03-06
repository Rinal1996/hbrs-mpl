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

#include "elemental.hpp"
#ifdef HBRS_MPL_ENABLE_ELEMENTAL

#include <hbrs/mpl/dt/matrix_index.hpp>

HBRS_MPL_NAMESPACE_BEGIN
namespace detail {

template decltype(auto) at_impl_el_matrix::operator()(el_matrix<float> &,      matrix_index<El::Int, El::Int> const&) const;
template decltype(auto) at_impl_el_matrix::operator()(el_matrix<float> const&, matrix_index<El::Int, El::Int> const&) const;
template decltype(auto) at_impl_el_matrix::operator()(el_matrix<float> &&,     matrix_index<El::Int, El::Int> const&) const;

template decltype(auto) at_impl_el_matrix::operator()(el_matrix<El::Complex<float>> &,      matrix_index<El::Int, El::Int> const&) const;
template decltype(auto) at_impl_el_matrix::operator()(el_matrix<El::Complex<float>> const&, matrix_index<El::Int, El::Int> const&) const;
template decltype(auto) at_impl_el_matrix::operator()(el_matrix<El::Complex<float>> &&,     matrix_index<El::Int, El::Int> const&) const;

template decltype(auto) at_impl_el_matrix::operator()(el_matrix<double> &,      matrix_index<El::Int, El::Int> const&) const;
template decltype(auto) at_impl_el_matrix::operator()(el_matrix<double> const&, matrix_index<El::Int, El::Int> const&) const;
template decltype(auto) at_impl_el_matrix::operator()(el_matrix<double> &&,     matrix_index<El::Int, El::Int> const&) const;

template decltype(auto) at_impl_el_matrix::operator()(el_matrix<El::Complex<double>> &,      matrix_index<El::Int, El::Int> const&) const;
template decltype(auto) at_impl_el_matrix::operator()(el_matrix<El::Complex<double>> const&, matrix_index<El::Int, El::Int> const&) const;
template decltype(auto) at_impl_el_matrix::operator()(el_matrix<El::Complex<double>> &&,     matrix_index<El::Int, El::Int> const&) const;

template decltype(auto) at_impl_el_matrix_smr::operator()(el_matrix<float> &,      El::Int) const;
template decltype(auto) at_impl_el_matrix_smr::operator()(el_matrix<float> const&, El::Int) const;
template decltype(auto) at_impl_el_matrix_smr::operator()(el_matrix<float> &&,     El::Int) const;

template decltype(auto) at_impl_el_matrix_smr::operator()(el_matrix<El::Complex<float>> &,      El::Int) const;
template decltype(auto) at_impl_el_matrix_smr::operator()(el_matrix<El::Complex<float>> const&, El::Int) const;
template decltype(auto) at_impl_el_matrix_smr::operator()(el_matrix<El::Complex<float>> &&,     El::Int) const;

template decltype(auto) at_impl_el_matrix_smr::operator()(el_matrix<double> &,      El::Int) const;
template decltype(auto) at_impl_el_matrix_smr::operator()(el_matrix<double> const&, El::Int) const;
template decltype(auto) at_impl_el_matrix_smr::operator()(el_matrix<double> &&,     El::Int) const;

template decltype(auto) at_impl_el_matrix_smr::operator()(el_matrix<El::Complex<double>> &,      El::Int) const;
template decltype(auto) at_impl_el_matrix_smr::operator()(el_matrix<El::Complex<double>> const&, El::Int) const;
template decltype(auto) at_impl_el_matrix_smr::operator()(el_matrix<El::Complex<double>> &&,     El::Int) const;

//TODO: Add row_vector and column_vector impls!

/* namespace detail */ }
HBRS_MPL_NAMESPACE_END

#endif // !HBRS_MPL_ENABLE_ELEMENTAL
