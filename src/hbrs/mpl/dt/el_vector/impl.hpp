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

#ifndef HBRS_MPL_DT_EL_VECTOR_IMPL_HPP
#define HBRS_MPL_DT_EL_VECTOR_IMPL_HPP

#include "fwd.hpp"
#ifdef HBRS_MPL_ENABLE_ELEMENTAL

#include <boost/hana/core/make.hpp>
#include <boost/hana/core/to.hpp>

#include <hbrs/mpl/dt/matrix_index.hpp>
#include <hbrs/mpl/dt/scv.hpp>
#include <hbrs/mpl/dt/srv.hpp>
#include <hbrs/mpl/fn/at.hpp>
#include <hbrs/mpl/fn/size.hpp>

#include <boost/numeric/conversion/cast.hpp>
#include <boost/hana/type.hpp>
#include <boost/assert.hpp>
#include <array>
#include <El.hpp>
#include <type_traits>

#define _HBRS_MPL_DEF_EL_VECTOR(vector_kind)                                                                           \
	HBRS_MPL_NAMESPACE_BEGIN                                                                                           \
                                                                                                                       \
	template<typename Ring>                                                                                            \
	struct el_ ## vector_kind ## _vector {                                                                             \
		template<                                                                                                      \
			typename Ring_ = Ring,                                                                                     \
			typename std::enable_if_t<                                                                                 \
				std::is_same_v<std::remove_const_t<Ring>, Ring_>                                                       \
			>* = nullptr                                                                                               \
		>                                                                                                              \
		el_ ## vector_kind ## _vector(El::Matrix<Ring_> data);                                                         \
		el_ ## vector_kind ## _vector(El::Int sz);                                                                     \
		                                                                                                               \
		el_ ## vector_kind ## _vector(Ring const* data, El::Int sz)                                                    \
		: el_ ## vector_kind ## _vector{sz} {                                                                          \
			for(El::Int i = 0; i < sz; ++i) {                                                                          \
				at(i) = data[i];                                                                                       \
			}                                                                                                          \
		}                                                                                                              \
		                                                                                                               \
		el_ ## vector_kind ## _vector(el_ ## vector_kind ## _vector const&) = default;                                 \
		el_ ## vector_kind ## _vector(el_ ## vector_kind ## _vector &&) = default;                                     \
		                                                                                                               \
		el_ ## vector_kind ## _vector&                                                                                 \
		operator=(el_ ## vector_kind ## _vector const&) = default;                                                     \
		el_ ## vector_kind ## _vector&                                                                                 \
		operator=(el_ ## vector_kind ## _vector &&) = default;                                                         \
		                                                                                                               \
		decltype(auto)                                                                                                 \
		length() const;                                                                                                \
		                                                                                                               \
		decltype(auto)                                                                                                 \
		at(El::Int i);                                                                                                 \
                                                                                                                       \
		decltype(auto)                                                                                                 \
		at(El::Int i) const;                                                                                           \
		                                                                                                               \
		decltype(auto)                                                                                                 \
		operator[](El::Int i) {                                                                                        \
			return at(i);                                                                                              \
		}                                                                                                              \
		                                                                                                               \
		decltype(auto)                                                                                                 \
		operator[](El::Int i) const {                                                                                  \
			return at(i);                                                                                              \
		}                                                                                                              \
		                                                                                                               \
		constexpr decltype(auto)                                                                                       \
		data() & { return (data_); };                                                                                  \
		                                                                                                               \
		constexpr decltype(auto)                                                                                       \
		data() const& { return (data_); };                                                                             \
		                                                                                                               \
		constexpr decltype(auto)                                                                                       \
		data() && { return HBRS_MPL_FWD(data_); };                                                                     \
		                                                                                                               \
	private:                                                                                                           \
		template<typename Matrix>                                                                                      \
		decltype(auto)                                                                                                 \
		static at_(Matrix && m, matrix_index<El::Int, El::Int> const& i) {                                             \
			BOOST_ASSERT(i.m() >= 0 && i.m() < HBRS_MPL_FWD(m).Height());                                              \
			BOOST_ASSERT(i.n() >= 0 && i.n() < HBRS_MPL_FWD(m).Width());                                               \
			                                                                                                           \
			if constexpr(std::is_const_v<Ring> || std::is_const_v<std::remove_reference_t<Matrix>>) {                  \
				return *HBRS_MPL_FWD(m).LockedBuffer(i.m(), i.n());                                                    \
			} else {                                                                                                   \
				return *HBRS_MPL_FWD(m).Buffer(i.m(), i.n());                                                          \
			}                                                                                                          \
		}                                                                                                              \
		                                                                                                               \
		El::Matrix<std::remove_const_t<Ring>> data_;                                                                   \
	};                                                                                                                 \
	                                                                                                                   \
	HBRS_MPL_NAMESPACE_END                                                                                             \
                                                                                                                       \
	namespace boost { namespace hana {                                                                                 \
                                                                                                                       \
	template <typename Ring>                                                                                           \
	struct tag_of< hbrs::mpl::el_ ## vector_kind ## _vector<Ring> > {                                                  \
		using type = hbrs::mpl::el_ ## vector_kind ## _vector_tag;                                                     \
	};                                                                                                                 \
                                                                                                                       \
	/* namespace hana */ } /* namespace boost */ }

_HBRS_MPL_DEF_EL_VECTOR(column)
_HBRS_MPL_DEF_EL_VECTOR(row)

#undef _HBRS_MPL_DEF_EL_VECTOR

HBRS_MPL_NAMESPACE_BEGIN

template<typename Ring>
template<
	typename Ring_ /* = Ring */,
	typename std::enable_if_t<
		std::is_same_v<std::remove_const_t<Ring>, Ring_>
	>* /* = nullptr */
>
el_column_vector<Ring>::el_column_vector(El::Matrix<Ring_> data) : data_{std::move(data)} {
	BOOST_ASSERT(!std::is_const_v<Ring> ? !data_.Locked() : true);
	BOOST_ASSERT(data_.Width() == 1);
}

template<typename Ring>
template<
	typename Ring_ /* = Ring */,
	typename std::enable_if_t<
		std::is_same_v<std::remove_const_t<Ring>, Ring_>
	>* /* = nullptr */
>
el_row_vector<Ring>::el_row_vector(El::Matrix<Ring_> data) : data_{std::move(data)} {
	BOOST_ASSERT(!std::is_const_v<Ring> ? !data_.Locked() : true);
	BOOST_ASSERT(data_.Height() == 1);
}

template<typename Ring>
el_column_vector<Ring>::el_column_vector(El::Int sz) : data_{sz,1} {
	El::Zero(data_);
}

template<typename Ring>
el_row_vector<Ring>::el_row_vector(El::Int sz) : data_{1,sz} {
	El::Zero(data_);
}

template<typename Ring>
decltype(auto)
el_column_vector<Ring>::length() const {
	return data_.Height();
}

template<typename Ring>
decltype(auto)
el_row_vector<Ring>::length() const {
	return data_.Width();
}

template<typename Ring>
decltype(auto)
el_column_vector<Ring>::at(El::Int i) {
	return at_(data_, make_matrix_index(i, 0));
}

template<typename Ring>
decltype(auto)
el_column_vector<Ring>::at(El::Int i) const {
	return at_(data_, make_matrix_index(i, 0));
}

template<typename Ring>
decltype(auto)
el_row_vector<Ring>::at(El::Int i) {
	return at_(data_, make_matrix_index(0, i));
}

template<typename Ring>
decltype(auto)
el_row_vector<Ring>::at(El::Int i) const {
	return at_(data_, make_matrix_index(0, i));
}

HBRS_MPL_NAMESPACE_END

namespace boost { namespace hana {

#define _HBRS_MPL_DEF_EL_VECTOR(vector_kind)                                                                           \
	template <typename Ring>                                                                                           \
	static hbrs::mpl::el_ ## vector_kind ## _vector<Ring>                                                              \
	apply(basic_type<Ring>, El::Int sz) {                                                                              \
		return {sz};                                                                                                   \
	}                                                                                                                  \
	                                                                                                                   \
	template <typename Ring>                                                                                           \
	static hbrs::mpl::el_ ## vector_kind ## _vector<std::decay_t<Ring>>                                                \
	apply(El::Matrix<Ring> data) {                                                                                     \
		return {data};                                                                                                 \
	}                                                                                                                  \
	                                                                                                                   \
	template <typename Ring>                                                                                           \
	static hbrs::mpl::el_ ## vector_kind ## _vector<std::decay_t<Ring>>                                                \
	apply(Ring const* data, El::Int sz) {                                                                              \
		return {data, sz};                                                                                             \
	}                                                                                                                  \
	                                                                                                                   \
	template <typename Ring>                                                                                           \
	static hbrs::mpl::el_ ## vector_kind ## _vector<std::decay_t<Ring>>                                                \
	apply(std::initializer_list<Ring> data) {                                                                          \
		return { data.begin(), boost::numeric_cast<El::Int>(data.size()) };                                            \
	}                                                                                                                  \

template <>
struct make_impl<hbrs::mpl::el_column_vector_tag> {
	_HBRS_MPL_DEF_EL_VECTOR(column)
	
	template<typename T, std::size_t N>
	static auto
	apply(hbrs::mpl::scv<std::array<T, N>> const& a) {
		using namespace hbrs::mpl;
		
		el_column_vector<T> b = {(El::Int)N};
		for(std::size_t i = 0; i < N; ++i) {
			b.at((El::Int)i) = a.at(i);
		}
		return b;
	}
};

template <>
struct make_impl<hbrs::mpl::el_row_vector_tag> {
	_HBRS_MPL_DEF_EL_VECTOR(row)
	
	template<typename T, std::size_t N>
	static auto
	apply(hbrs::mpl::srv<std::array<T, N>> const& a) {
		using namespace hbrs::mpl;
		
		el_row_vector<T> b = {(El::Int)N};
		for(std::size_t i = 0; i < N; ++i) {
			b.at((El::Int)i) = a.at(i);
		}
		return b;
	}
};

#undef _HBRS_MPL_DEF_EL_VECTOR

/* namespace hana */ } /* namespace boost */ }

#endif // !HBRS_MPL_ENABLE_ELEMENTAL
#endif // !HBRS_MPL_DT_EL_VECTOR_IMPL_HPP
