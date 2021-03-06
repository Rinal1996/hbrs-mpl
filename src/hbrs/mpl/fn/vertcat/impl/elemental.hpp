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

#ifndef HBRS_MPL_FN_VERTCAT_IMPL_ELEMENTAL_HPP
#define HBRS_MPL_FN_VERTCAT_IMPL_ELEMENTAL_HPP

#include "../fwd/elemental.hpp"
#ifdef HBRS_MPL_ENABLE_ELEMENTAL

#include <hbrs/mpl/core/preprocessor.hpp>

#include <hbrs/mpl/dt/el_matrix.hpp>
#include <hbrs/mpl/dt/exception.hpp>
#include <hbrs/mpl/dt/matrix_index.hpp>
#include <hbrs/mpl/dt/smr.hpp>

#include <hbrs/mpl/fn/size.hpp>
#include <hbrs/mpl/fn/m.hpp>
#include <hbrs/mpl/fn/n.hpp>
#include <hbrs/mpl/fn/at.hpp>

HBRS_MPL_NAMESPACE_BEGIN
namespace hana = boost::hana;
namespace detail {

template<
	typename MatrixA,
	typename MatrixB,
	typename std::enable_if_t< 
		std::is_same< hana::tag_of_t<MatrixA>, el_matrix_tag >::value && 
		std::is_same< hana::tag_of_t<MatrixB>, el_matrix_tag >::value && 
		std::is_same< std::decay_t<MatrixA>, std::decay_t<MatrixB> >::value
	>*
>
auto
vertcat_impl_smr_el_matrix_smr_el_matrix::operator()(
	smr<MatrixA, El::Int> const& a, 
	smr<MatrixB, El::Int> const& b
) const {
	auto a_sz = (*size)(a);
	auto b_sz = (*size)(b);
	
	if (a_sz != b_sz) {
		BOOST_THROW_EXCEPTION((
			incompatible_vectors_exception{} 
			<< errinfo_el_vector_sizes{ {a_sz, b_sz} }
		));
	}
	
	std::decay_t<MatrixA> c{2, a_sz};
	
	for(El::Int i = 0; i < a_sz; ++i) {
		(*at)(c, make_matrix_index(0, i)) = (*at)(a, i);
	}
	
	for(El::Int i = 0; i < a_sz; ++i) {
		(*at)(c, make_matrix_index(1, i)) = (*at)(b, i);
	}
	
	return c;
}

template<
	typename MatrixA,
	typename MatrixB,
	typename std::enable_if_t< 
		std::is_same< hana::tag_of_t<MatrixA>, el_matrix_tag >::value && 
		std::is_same< hana::tag_of_t<MatrixB>, el_matrix_tag >::value && 
		std::is_same< std::decay_t<MatrixA>, std::decay_t<MatrixB> >::value
	>*
>
auto
vertcat_impl_el_matrix_smr_el_matrix::operator()(
	MatrixA const& a,
	smr<MatrixB, El::Int> const& b
) const {
	auto a_sz = (*size)(a);
	auto a_m = (*m)(a_sz);
	auto a_n = (*n)(a_sz);
	auto b_sz = (*size)(b);
	
	if (a_n != b_sz) {
		BOOST_THROW_EXCEPTION((
			incompatible_matrix_vector_exception{}
			<< errinfo_el_matrix_size{a_sz}
			<< errinfo_el_vector_size{b_sz}
		));
	}
	
	std::decay_t<MatrixA> c{a_m+1, a_n};
	
	for(El::Int i = 0; i < a_m; ++i) {
		for(El::Int j = 0; j < a_n; ++j) {
			(*at)(c, make_matrix_index(i, j)) = (*at)(a, make_matrix_index(i, j));
		}
	}
	
	for(El::Int i = 0; i < a_n; ++i) {
		(*at)(c, make_matrix_index(a_m, i)) = (*at)(b, i);
	}
	
	return c;
}

template<typename Ring>
auto
vertcat_impl_el_matrix_el_matrix::operator()(
	el_matrix<Ring> const& a,
	el_matrix<Ring> const& b
) const {
	auto a_sz = (*size)(a);
	auto a_m = (*m)(a_sz);
	auto a_n = (*n)(a_sz);
	auto b_sz = (*size)(b);
	auto b_m = (*m)(b_sz);
	auto b_n = (*n)(b_sz);
	
	if (a_n != b_n) {
		BOOST_THROW_EXCEPTION((
			incompatible_matrices_exception{}
			<< errinfo_el_matrix_sizes{a_sz, b_sz}
		));
	}
	
	El::Matrix<Ring> c{a_m+b_m, a_n};
	
	for(El::Int i = 0; i < a_m; ++i) {
		for(El::Int j = 0; j < a_n; ++j) {
			(*at)(c, make_matrix_index(i, j)) = (*at)(a, make_matrix_index(i, j));
		}
	}
	
	for(El::Int i = 0; i < b_m; ++i) {
		for(El::Int j = 0; j < b_n; ++j) {
			(*at)(c, make_matrix_index(a_m+i, j)) = (*at)(b, make_matrix_index(i, j));
		}
	}
	
	return make_el_matrix(std::move(c));
}


/* namespace detail */ }
HBRS_MPL_NAMESPACE_END

#endif // !HBRS_MPL_ENABLE_ELEMENTAL
#endif // !HBRS_MPL_FN_VERTCAT_IMPL_ELEMENTAL_HPP
