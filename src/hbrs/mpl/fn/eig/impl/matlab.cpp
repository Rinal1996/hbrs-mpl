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

#include "matlab.hpp"
#ifdef HBRS_MPL_ENABLE_MATLAB

#include <hbrs/mpl/dt/ml_matrix.hpp>
#include <hbrs/mpl/dt/ml_vector.hpp>
#include <hbrs/mpl/dt/eig_control.hpp>
#include <hbrs/mpl/dt/eig_result.hpp>

extern "C" {
	#include <hbrs/mpl/detail/matlab_cxn/impl/eig_level0.h>
}
#undef I /* I is defined by MATLAB Coder, but also used within Boost Unit Test Framework as a template parameter. */

HBRS_MPL_NAMESPACE_BEGIN
namespace detail {

#define _DEF_EIG(lvl)                                                                                                  \
	HBRS_MPL_API                                                                                                       \
	eig_result<                                                                                                        \
		ml_column_vector<creal_T> /* eigenvalues */,                                                                   \
		ml_matrix<creal_T>        /* eigenvectors */                                                                   \
	>                                                                                                                  \
	eig_impl_level ## lvl ## _ml_matrix::operator()(                                                                   \
		ml_matrix<real_T> const& a,                                                                                    \
		eig_control<> const& ctrl                                                                                      \
	) const {                                                                                                          \
		ml_column_vector<creal_T> eigenvalues;                                                                         \
		ml_matrix<creal_T> eigenvectors;                                                                               \
		                                                                                                               \
		eig_level ## lvl(                                                                                              \
			&a.data(),                                                                                                 \
			&eigenvalues.data(),                                                                                       \
			&eigenvectors.data()                                                                                       \
		);                                                                                                             \
		                                                                                                               \
		return { eigenvalues, eigenvectors };                                                                          \
	}

_DEF_EIG(0)
#undef _DEF_EIG

/* namespace detail */ }
HBRS_MPL_NAMESPACE_END

#endif // !HBRS_MPL_ENABLE_MATLAB
