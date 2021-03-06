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

#ifndef HBRS_MPL_DT_RTSAM_IMPL_HPP
#define HBRS_MPL_DT_RTSAM_IMPL_HPP

#include "fwd.hpp"

#include <hbrs/mpl/core/preprocessor.hpp>
#include <hbrs/mpl/dt/matrix_index.hpp>
#include <hbrs/mpl/dt/matrix_size.hpp>
#include <hbrs/mpl/dt/smr.hpp>
#include <hbrs/mpl/dt/rtsacv.hpp>
#include <hbrs/mpl/dt/rtsarv.hpp>
#include <hbrs/mpl/dt/sm.hpp>
#include <hbrs/mpl/dt/ctsav.hpp>
#include <hbrs/mpl/dt/submatrix.hpp>
#include <hbrs/mpl/dt/range.hpp>
#include <hbrs/mpl/dt/storage_order.hpp>
#include <hbrs/mpl/dt/givens_rotation.hpp>
#include <hbrs/mpl/fn/m.hpp>
#include <hbrs/mpl/fn/n.hpp>
#include <hbrs/mpl/fn/size.hpp>
#include <hbrs/mpl/fn/not_equal.hpp>
#include <hbrs/mpl/detail/translate_index.hpp>
#include <hbrs/mpl/detail/copy_matrix.hpp>
#include <hbrs/mpl/dt/exception.hpp>

#include <boost/hana/core/make.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/type.hpp>
#include <boost/assert.hpp>
#include <vector>
#include <type_traits>

HBRS_MPL_NAMESPACE_BEGIN

template<
	typename /* type of matrix entries */ Ring,
	storage_order Order
>
struct rtsam {
	rtsam(matrix_size<std::size_t, std::size_t> sz) : rtsam(sz.m(), sz.n()) {}
	
	rtsam(std::vector<Ring> data, matrix_size<std::size_t, std::size_t> sz) : data_{data}, size_{sz} {
		if (sz.m() * sz.n() != data.size()) {
			BOOST_THROW_EXCEPTION(
				incompatible_matrix_sequence_exception{}
				<< errinfo_matrix_size{sz}
				<< errinfo_sequence_size{data.size()}
			);
		}
	}
	
	rtsam(std::size_t m, std::size_t n) : data_(m * n, Ring{0}), size_{m,n} {}
	
	rtsam(rtsam const&) = default;
	rtsam(rtsam &&) = default;
	
	rtsam&
	operator=(rtsam const&) = default;
	rtsam&
	operator=(rtsam &&) = default;
	
	//TODO: Move to new implementation of assign() function
	template<
		storage_order Order_ = Order,
		typename std::enable_if_t<
			Order != Order_
		>* = nullptr
	>
	rtsam&
	operator=(rtsam<Ring, Order_> const& m_) {
		using hbrs::mpl::size;
		if ((*not_equal)(size_, size(m_))) {
			BOOST_THROW_EXCEPTION((
				incompatible_matrices_exception{} << errinfo_matrix_sizes{{size_, (*size)(m_)}}
			));
		}
		
		for (std::size_t i = 0; i < (*m)(size_); ++i) {
			for (std::size_t j = 0; j < (*n)(size_); ++j) {
				at(make_matrix_index(i,j)) = m_.at(make_matrix_index(i,j));
			}
		}
		
		return *this;
	}
	
	//TODO: Move to new implementation of assign() function
	/*
	 * Chapter 5.1.9 (Applying Givens Rotations) on page 241
	 * A = G(i,k,theta)^T * A
	 *              --     --T
	 *              |       |
	 *              |  c s  |
	 * A([i,k],:) = |       | * A([i,k],:)
	 *              | -s c  |
	 *              |       |
	 *              --     --
	 *
	 * Apply the Givens roation on A and return A.
	 */
	template<
		typename Ring_ = Ring,
		typename std::enable_if_t<
			std::is_same_v<Ring_, Ring> && !std::is_const_v<std::remove_reference_t<Ring_>>
		>* = nullptr
	>
	rtsam&
	operator=(
		detail::givens_rotation_expression<
			givens_rotation<Ring_> const&,
			rtsam<Ring_,Order> const&
		> const& e
	) {
		if (&(e.rhs()) != this) {
			*this = e.rhs();
		}

		decltype(auto) i     = e.lhs().i();
		decltype(auto) k     = e.lhs().k();
		decltype(auto) theta = e.lhs().theta();

		BOOST_ASSERT(i < (*m)(size_));
		BOOST_ASSERT(k < (*m)(size_));

		for (std::size_t j = 0; j <= (*n)(size_) - 1; ++j) {
			auto tau1 = at(make_matrix_index(i, j));
			auto tau2 = at(make_matrix_index(k, j));
			at(make_matrix_index(i, j)) = theta.c() * tau1 - theta.s() * tau2;
			at(make_matrix_index(k, j)) = theta.s() * tau1 + theta.c() * tau2;
		}
		
		return *this;
	}
	
	//TODO: Move to new implementation of assign() function
	/*
	 * Chapter 5.1.9 (Applying Givens Rotations) on page 241
	 * A = A * G(i,k,theta)
	 *                           --     --
	 *                           |       |
	 *                           |  c s  |
	 * A(:,[i,k]) = A(:,[i,k]) * |       |
	 *                           | -s c  |
	 *                           |       |
	 *                           --     --
	 *
	 * Apply the Givens roation on A and return A.
	 */
	template<
		typename Ring_ = Ring,
		typename std::enable_if_t<
			std::is_same_v<Ring_, Ring> && !std::is_const_v<std::remove_reference_t<Ring_>>
		>* = nullptr
	>
	rtsam&
	operator=(
		detail::givens_rotation_expression<
			rtsam<Ring_,Order> const&,
			givens_rotation<Ring_> const&
		> const& e
	) {
		if (&(e.lhs()) != this) {
			*this = e.lhs();
		}

		decltype(auto) i     = e.rhs().i();
		decltype(auto) k     = e.rhs().k();
		decltype(auto) theta = e.rhs().theta();

		BOOST_ASSERT(i < (*n)(size_));
		BOOST_ASSERT(k < (*n)(size_));

		for (std::size_t j = 0; j <= (*m)(size_) - 1; ++j) {
			auto tau1 = at(make_matrix_index(j, i));
			auto tau2 = at(make_matrix_index(j, k));
			at(make_matrix_index(j, i)) = theta.c() * tau1 - theta.s() * tau2;
			at(make_matrix_index(j, k)) = theta.s() * tau1 + theta.c() * tau2;
		}
		
		return *this;
	}

	auto const&
	size() const { return size_; };
	
	decltype(auto)
	order() const { return storage_order_c<Order>; }
	
	decltype(auto)
	at(matrix_index<std::size_t, std::size_t> const& i) {
		return data_.at(
			detail::translate_index(size_, i, storage_order_c<Order>)
		);
	}
	
	decltype(auto)
	at(matrix_index<std::size_t, std::size_t> const& i) const {
		return data_.at(
			detail::translate_index(size_, i, storage_order_c<Order>)
		);
	}
	
	auto
	operator[](std::size_t i) & { return smr<rtsam &, std::size_t>{*this, i}; }
	
	auto
	operator[](std::size_t i) const& { return smr<rtsam const&, std::size_t>{*this, i}; }
	
	auto
	operator[](std::size_t i) && { return make_smr(std::move(*this), i); }
private:
	std::vector<Ring> data_;
	matrix_size<std::size_t, std::size_t> size_;
};

HBRS_MPL_NAMESPACE_END

namespace boost { namespace hana {

template <
	typename Ring,
	hbrs::mpl::storage_order Order
>
struct tag_of< hbrs::mpl::rtsam<Ring, Order> > {
	using type = hbrs::mpl::rtsam_tag;
};

template <>
struct make_impl<hbrs::mpl::rtsam_tag> {
	template <
		typename Ring,
		hbrs::mpl::storage_order Order
	>
	static hbrs::mpl::rtsam<Ring, Order>
	apply(hana::basic_type<Ring>, hbrs::mpl::matrix_size<std::size_t, std::size_t> sz, hbrs::mpl::storage_order_<Order>) {
		return {sz};
	}
	
	template <
		typename Ring,
		hbrs::mpl::storage_order Order
	>
	static hbrs::mpl::rtsam<std::remove_const_t<Ring>, Order>
	apply(std::vector<Ring> data, hbrs::mpl::matrix_size<std::size_t, std::size_t> sz, hbrs::mpl::storage_order_<Order>) {
		return {data, sz};
	}
	
	template <
		typename Ring,
		std::size_t Length,
		typename M,
		typename N,
		hbrs::mpl::storage_order Order,
		typename std::enable_if_t<
			std::is_convertible_v<M,std::size_t> && std::is_convertible_v<N,std::size_t>
		>* = nullptr
	>
	static constexpr auto
	apply(
		hbrs::mpl::sm<hbrs::mpl::ctsav<Ring, Length>, hbrs::mpl::matrix_size<M, N>, Order> const& x
	) {
		using namespace hbrs::mpl;
		typedef std::remove_cv_t<Ring> _Ring_;
		matrix_size<std::size_t, std::size_t> sz = {x.size()};
		rtsam<_Ring_, Order> y = {sz.m(), sz.n()};
		return hbrs::mpl::detail::copy_matrix(x, y);
	}
};

/* namespace hana */ } /* namespace boost */ }

#endif // !HBRS_MPL_DT_RTSAM_IMPL_HPP
