/* Copyright (c) 2016-2019 Jakob Meng, <jakobmeng@web.de>
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

#ifndef HBRS_MPL_DT_ML_VECTOR_IMPL_HPP
#define HBRS_MPL_DT_ML_VECTOR_IMPL_HPP

#include "fwd.hpp"
#ifdef HBRS_MPL_ENABLE_MATLAB

#include <boost/hana/core/make.hpp>
#include <boost/hana/core/to.hpp>
#include <hbrs/mpl/detail/matlab_cxn.hpp>
#include <hbrs/mpl/dt/scv.hpp>
#include <hbrs/mpl/dt/srv.hpp>
#include <hbrs/mpl/fn/at.hpp>
#include <boost/assert.hpp>
#include <array>
#include <algorithm>
#include <initializer_list>

#define _HBRS_MPL_DEF_ML_VEC1(vector_kind, base_type)                                                                  \
	HBRS_MPL_NAMESPACE_BEGIN                                                                                           \
                                                                                                                       \
	template<>                                                                                                         \
	struct HBRS_MPL_API ml_ ## vector_kind ## _vector<base_type> {                                                     \
		friend struct ml_column_vector<base_type>;                                                                     \
		friend struct ml_row_vector<base_type>;                                                                        \
		                                                                                                               \
		ml_ ## vector_kind ## _vector()                                                                                \
		: ptr_{nullptr, nullptr} {                                                                                     \
			emxArray_ ## base_type * emxArray{nullptr};                                                                \
			emxInitArray_ ## base_type(&emxArray, 1);                                                                  \
			ptr_ = {emxArray, emxDestroyArray_ ## base_type};                                                          \
		}                                                                                                              \
		                                                                                                               \
		explicit                                                                                                       \
		ml_ ## vector_kind ## _vector(int size)                                                                        \
		: ptr_{emxCreateND_ ## base_type(1, &size), emxDestroyArray_ ## base_type} {}                                  \
		                                                                                                               \
		/* TODO: Do we really want to allow construction of column vectors from row vectors and vice versa? */         \
		ml_ ## vector_kind ## _vector(ml_column_vector<base_type> const& rhs) : ml_ ## vector_kind ## _vector() {      \
			copy_from(rhs);                                                                                            \
		}                                                                                                              \
		                                                                                                               \
		/* TODO: Do we really want to allow construction of column vectors from row vectors and vice versa? */         \
		ml_ ## vector_kind ## _vector(ml_row_vector<base_type> const& rhs) : ml_ ## vector_kind ## _vector() {         \
			copy_from(rhs);                                                                                            \
		}                                                                                                              \
		                                                                                                               \
	private:                                                                                                           \
		template<typename T>                                                                                           \
		void copy_from(T const& rhs) {                                                                                 \
			if (rhs.ptr_ == nullptr) { return; }                                                                       \
			                                                                                                           \
			auto && v = (*rhs.ptr_);                                                                                   \
			auto && sz = rhs.ptr_->size[0];                                                                            \
			                                                                                                           \
			if (v.data != nullptr && sz > 0) {                                                                         \
				ptr_ = {                                                                                               \
					emxCreateND_ ## base_type(1, &sz),                                                                 \
					emxDestroyArray_ ## base_type                                                                      \
				};                                                                                                     \
                                                                                                                       \
				std::copy(v.data, v.data + sz, (*ptr_).data);                                                          \
			}                                                                                                          \
		}                                                                                                              \
		                                                                                                               \
	public:                                                                                                            \
		                                                                                                               \
		explicit                                                                                                       \
		ml_ ## vector_kind ## _vector(std::initializer_list<base_type> const& data)                                    \
		: ml_ ## vector_kind ## _vector(data.size()) {                                                                 \
			std::copy(data.begin(), data.end(), (*ptr_).data);                                                         \
		}                                                                                                              \
		                                                                                                               \
		ml_ ## vector_kind ## _vector(ml_ ## vector_kind ## _vector && rhs) : ml_ ## vector_kind ## _vector() {        \
			swap(*this, rhs);                                                                                          \
		}                                                                                                              \
		                                                                                                               \
		ml_ ## vector_kind ## _vector&                                                                                 \
		operator=(ml_ ## vector_kind ## _vector rhs) {                                                                 \
			swap(*this, rhs);                                                                                          \
			return *this;                                                                                              \
		}                                                                                                              \
		                                                                                                               \
		friend void swap(ml_ ## vector_kind ## _vector& lhs, ml_ ## vector_kind ## _vector& rhs) noexcept {            \
			using std::swap;                                                                                           \
			swap(lhs.ptr_, rhs.ptr_);                                                                                  \
		}                                                                                                              \
		                                                                                                               \
		int                                                                                                            \
		length() const {                                                                                               \
			return ptr_->size[0];                                                                                      \
		}                                                                                                              \
		                                                                                                               \
		base_type &                                                                                                    \
		at(int n) {                                                                                                    \
			using hbrs::mpl::at;                                                                                       \
			return (*at)(*ptr_, n);                                                                                    \
		}                                                                                                              \
                                                                                                                       \
		base_type const&                                                                                               \
		at(int n) const {                                                                                              \
			using hbrs::mpl::at;                                                                                       \
			return (*at)(*ptr_, n);                                                                                    \
		}                                                                                                              \
		                                                                                                               \
		base_type &                                                                                                    \
		operator[](int n) {                                                                                            \
			using hbrs::mpl::at;                                                                                       \
			return (*at)(*ptr_, n);                                                                                    \
		}                                                                                                              \
		                                                                                                               \
		base_type const&                                                                                               \
		operator[](int n) const {                                                                                      \
			using hbrs::mpl::at;                                                                                       \
			return (*at)(*ptr_, n);                                                                                    \
		}                                                                                                              \
		                                                                                                               \
		emxArray_ ## base_type &                                                                                       \
		data() {                                                                                                       \
			return *ptr_;                                                                                              \
		}                                                                                                              \
		                                                                                                               \
		emxArray_ ## base_type const&                                                                                  \
		data() const {                                                                                                 \
			return *ptr_;                                                                                              \
		}                                                                                                              \
		                                                                                                               \
	private:                                                                                                           \
		std::unique_ptr<                                                                                               \
			emxArray_ ## base_type,                                                                                    \
			void(*)(emxArray_ ## base_type*)                                                                           \
		> ptr_;                                                                                                        \
	};                                                                                                                 \
	                                                                                                                   \
	HBRS_MPL_NAMESPACE_END                                                                                             \
                                                                                                                       \
	namespace boost { namespace hana {                                                                                 \
                                                                                                                       \
	template <>                                                                                                        \
	struct tag_of< hbrs::mpl::ml_ ## vector_kind ## _vector<base_type> > {                                             \
		using type = hbrs::mpl::ml_ ## vector_kind ## _vector_tag;                                                     \
	};                                                                                                                 \
                                                                                                                       \
	/* namespace hana */ } /* namespace boost */ }

_HBRS_MPL_DEF_ML_VEC1(column, real_T)
_HBRS_MPL_DEF_ML_VEC1(column, creal_T)
_HBRS_MPL_DEF_ML_VEC1(column, boolean_T)
_HBRS_MPL_DEF_ML_VEC1(row, real_T)
_HBRS_MPL_DEF_ML_VEC1(row, creal_T)
_HBRS_MPL_DEF_ML_VEC1(row, boolean_T)

#undef _HBRS_MPL_DEF_ML_VEC1

namespace boost { namespace hana {

template <>
struct make_impl<hbrs::mpl::ml_column_vector_tag> {
	template<typename T, std::size_t N>
	static auto
	apply(hbrs::mpl::scv<std::array<T, N>> const& a) {
		using namespace hbrs::mpl;
		
		ml_column_vector<T> b((int)N);
		BOOST_ASSERT(b.length() == N);
		for(std::size_t i = 0; i < N; ++i) {
			b.at((int)i) = a.at(i);
		}
		return b;
	}
};

template <>
struct make_impl<hbrs::mpl::ml_row_vector_tag> {
	template<typename T, std::size_t N>
	static auto
	apply(hbrs::mpl::srv<std::array<T, N>> const& a) {
		using namespace hbrs::mpl;
		
		ml_row_vector<T> b((int)N);
		BOOST_ASSERT(b.length() == N);
		for(std::size_t i = 0; i < N; ++i) {
			b.at((int)i) = a.at(i);
		}
		return b;
	}
};

/* namespace hana */ } /* namespace boost */ }

#endif // !HBRS_MPL_ENABLE_MATLAB
#endif // !HBRS_MPL_DT_ML_VECTOR_IMPL_HPP
