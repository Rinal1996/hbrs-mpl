/* Copyright (c) 2018-2019 Jakob Meng, <jakobmeng@web.de>
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

#ifndef HBRS_MPL_FN_PCA_FWD_ELEMENTAL_HPP
#define HBRS_MPL_FN_PCA_FWD_ELEMENTAL_HPP

#include <hbrs/mpl/config.hpp>

#ifdef HBRS_MPL_ENABLE_ELEMENTAL
	#include <hbrs/mpl/dt/pca_control/fwd.hpp>
	#include <hbrs/mpl/dt/el_matrix/fwd.hpp>
	#include <hbrs/mpl/dt/el_dist_matrix/fwd.hpp>
#endif
#include <boost/hana/tuple.hpp>

HBRS_MPL_NAMESPACE_BEGIN
namespace hana = boost::hana;
namespace detail {

#ifdef HBRS_MPL_ENABLE_ELEMENTAL

struct pca_impl_el_matrix {
	template <typename Ring>
	auto
	operator()(
		el_matrix<Ring> const& a,
		pca_control<bool,bool> const& ctrl
	) const;
};

//TODO: Join with pca_impl_el_matrix!
struct pca_impl_el_dist_matrix {
	template<typename Ring, El::Dist Columnwise, El::Dist Rowwise, El::DistWrap Wrapping>
	auto
	operator()(
		el_dist_matrix<Ring, Columnwise, Rowwise, Wrapping> const& a,
		pca_control<bool,bool> const& ctrl
	) const;
};

#else
struct pca_impl_el_matrix {};
struct pca_impl_el_dist_matrix {};
#endif

/* namespace detail */ }
HBRS_MPL_NAMESPACE_END

#define HBRS_MPL_FN_PCA_IMPLS_ELEMENTAL boost::hana::make_tuple(                                                       \
		hbrs::mpl::detail::pca_impl_el_matrix{},                                                                       \
		hbrs::mpl::detail::pca_impl_el_dist_matrix{}                                                                   \
	)

#endif // !HBRS_MPL_FN_PCA_FWD_ELEMENTAL_HPP
