/* Copyright (c) 2019 Abdullah Güntepe, <abdullah@guentepe.com>
 * Copyright (c) 2019 Jakob Meng, <jakobmeng@web.de>
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

#ifndef HBRS_MPL_FN_MULTIPLY_FWD_HBRS_MPL_HPP
#define HBRS_MPL_FN_MULTIPLY_FWD_HBRS_MPL_HPP

#include <hbrs/mpl/config.hpp>
#include <hbrs/mpl/core/preprocessor.hpp>
#include <hbrs/mpl/dt/rtsacv/fwd.hpp>
#include <hbrs/mpl/dt/rtsarv/fwd.hpp>
#include <hbrs/mpl/dt/rtsam/fwd.hpp>
#include <hbrs/mpl/dt/submatrix/fwd.hpp>
#include <hbrs/mpl/dt/givens_rotation/fwd.hpp>

HBRS_MPL_NAMESPACE_BEGIN
namespace hana = boost::hana;
namespace detail {

struct multiply_impl_rtsacv_scalar {
	template<typename Ring>
	auto
	operator()(rtsacv<Ring> lhs, Ring const& rhs) const;
};

struct multiply_impl_scalar_rtsacv {
	template<typename Ring>
	auto
	operator()(Ring const& lhs, rtsacv<Ring> rhs) const;
};

struct multiply_impl_rtsarv_rtsacv {
	template<typename Ring>
	decltype(auto)
	operator()(rtsarv<Ring> const& v1, rtsacv<Ring> const& v2) const;
};

struct multiply_impl_rtsacv_rtsarv {
	template<typename Ring>
	decltype(auto)
	operator()(rtsacv<Ring> const& v1, rtsarv<Ring> const& v2) const;
};

struct multiply_impl_rtsam_rtsam {
	template<
		typename Ring,
		storage_order Order1,
		storage_order Order2
	>
	decltype(auto)
	operator()(rtsam<Ring,Order1> const& M1, rtsam<Ring,Order2> const& M2) const;

	template<
		typename Ring,
		storage_order Order,
		typename Offset,
		typename Size
	>
	decltype(auto)
	operator()(submatrix<rtsam<Ring,Order>&, Offset,Size> const& M1, submatrix<rtsam<Ring,Order>&, Offset,Size> const& M2) const;

	template<
		typename Ring,
		storage_order Order1,
		storage_order Order2,
		typename Offset,
		typename Size
	>
	decltype(auto)
	operator()(rtsam<Ring,Order1> const& M1, submatrix<rtsam<Ring,Order2>&, Offset,Size> const& M2) const;

	template<
		typename Ring,
		storage_order Order,
		typename Offset,
		typename Size
	>
	decltype(auto)
	operator()(submatrix<rtsam<Ring,Order>&, Offset,Size> const& M1, rtsam<Ring,Order> const& M2) const;
};

struct multiply_impl_rtsarv_rtsam {
	template<
		typename Ring,
		storage_order Order
	>
	decltype(auto)
	operator()(rtsarv<Ring> const& v, rtsam<Ring,Order> const& M) const;

	template<
		typename Ring,
		storage_order Order,
		typename Offset,
		typename Size
	>
	decltype(auto)
	operator()(rtsarv<Ring> const& v, submatrix<rtsam<Ring,Order>&, Offset,Size> const& M) const;
};

struct multiply_impl_rtsam_rtsacv {
	template<
		typename Ring,
		storage_order Order
	>
	decltype(auto)
	operator()(rtsam<Ring,Order> const& M, rtsacv<Ring> const& v) const;

	template<
		typename Ring,
		storage_order Order,
		typename Offset,
		typename Size
	>
	decltype(auto)
	operator()(submatrix<rtsam<Ring,Order>&, Offset,Size> const& M, rtsacv<Ring> const& v) const;
};

struct multiply_impl_rtsam_scalar {
	template<
		typename Ring,
		storage_order Order
	>
	auto
	operator()(rtsam<Ring,Order> lhs, Ring const& rhs) const;
};

struct multiply_impl_scalar_rtsam {
	template<
		typename Ring,
		storage_order Order
	>
	auto
	operator()(Ring const& lhs, rtsam<Ring,Order> rhs) const;
};

struct multiply_impl_givens_rotation_rtsam {
	template<
		typename Ring,
		storage_order Order
	>
	auto
	operator()(givens_rotation<Ring> const& G, rtsam<Ring,Order> const& A) const;

	template<
		typename Ring,
		storage_order Order,
		typename Offset,
		typename Size
	>
	auto
	operator()(givens_rotation<Ring> const& G, submatrix<rtsam<Ring,Order>&, Offset, Size> const& A) const;
};

struct multiply_impl_rtsam_givens_rotation {
	template<
		typename Ring,
		storage_order Order
	>
	auto
	operator()(rtsam<Ring,Order> const& A, givens_rotation<Ring> const& G) const;

	template<
		typename Ring,
		storage_order Order,
		typename Offset,
		typename Size
	>
	auto
	operator()(submatrix<rtsam<Ring,Order>&, Offset, Size> const& A, givens_rotation<Ring> const& G) const;
};

/* namespace detail */ }
HBRS_MPL_NAMESPACE_END

#define HBRS_MPL_FN_MULTIPLY_IMPLS_HBRS_MPL boost::hana::make_tuple(                                                   \
		hbrs::mpl::detail::multiply_impl_rtsacv_scalar{},                                                              \
		hbrs::mpl::detail::multiply_impl_scalar_rtsacv{},                                                              \
		hbrs::mpl::detail::multiply_impl_rtsarv_rtsacv{},                                                              \
		hbrs::mpl::detail::multiply_impl_rtsacv_rtsarv{},                                                              \
		hbrs::mpl::detail::multiply_impl_rtsam_rtsam{},                                                                \
		hbrs::mpl::detail::multiply_impl_rtsarv_rtsam{},                                                               \
		hbrs::mpl::detail::multiply_impl_rtsam_rtsacv{},                                                               \
		hbrs::mpl::detail::multiply_impl_rtsam_scalar{},                                                               \
		hbrs::mpl::detail::multiply_impl_scalar_rtsam{},                                                               \
		hbrs::mpl::detail::multiply_impl_givens_rotation_rtsam{},                                                      \
		hbrs::mpl::detail::multiply_impl_rtsam_givens_rotation{}                                                       \
	)

#endif // !HBRS_MPL_FN_MULTIPLY_FWD_HBRS_MPL_HPP
