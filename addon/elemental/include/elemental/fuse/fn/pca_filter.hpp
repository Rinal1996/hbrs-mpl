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

#pragma once

#ifndef ELEMENTAL_FUSE_FN_PCA_FILTER_HPP
#define ELEMENTAL_FUSE_FN_PCA_FILTER_HPP

#include <elemental/config.hpp>
#include <hbrs/mpl/preprocessor/core.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <type_traits>

#include <hbrs/mpl/fn/pca.hpp>
#include <hbrs/mpl/fn/at.hpp>
#include <hbrs/mpl/fn/size.hpp>
#include <hbrs/mpl/fn/m.hpp>
#include <hbrs/mpl/fn/n.hpp>
#include <hbrs/mpl/fn/multiply.hpp>
#include <hbrs/mpl/fn/transpose.hpp>
#include <hbrs/mpl/fn/plus.hpp>
#include <hbrs/mpl/fn/equal.hpp>
#include <hbrs/mpl/fn/expand.hpp>

#include <hbrs/mpl/dt/matrix_index.hpp>
#include <hbrs/mpl/dt/pca_filter_result.hpp>
#include <El.hpp>
#include <vector>
#include <boost/assert.hpp>
#include <algorithm>

ELEMENTAL_NAMESPACE_BEGIN
namespace hana = boost::hana;
namespace mpl = hbrs::mpl;
namespace detail {

struct pca_filter_impl_Matrix {
	template <typename Ring>
	auto
	operator()(El::Matrix<Ring> const& a, std::vector<bool> const& keep) const {
		using namespace hbrs::mpl;
		
		auto a_sz = (*size)(a);
		auto a_m = (*m)(a_sz);
		auto a_n = (*n)(a_sz);
		
		auto rslt = (*pca)(a, true);
		
		auto && coeff =  (*at)(rslt, pca_coeff{});
		auto    score =  (*at)(rslt, pca_score{});
		auto && latent = (*at)(rslt, pca_latent{});
		auto && mean =   (*at)(rslt, pca_mean{});
		
		BOOST_ASSERT((*equal)(size(keep), std::min(a_m, a_n)));
		for (El::Int i = 0; i < score.Width(); ++i) {
			if (keep[i] == false) {
				auto column = score(El::ALL, i);
				El::Zero(column);
			}
		}
		
		auto centered = (*multiply)(score, transpose(coeff));
		BOOST_ASSERT((*equal)(a_sz, size(centered)));
		
		auto data = (*plus)(centered, expand(mean, size(centered)));
		
		return make_pca_filter_result(data, latent);
	}
};

/* namespace detail */ }
ELEMENTAL_NAMESPACE_END

#define ELEMENTAL_FUSE_FN_PCA_FILTER_IMPLS boost::hana::make_tuple(                                                    \
		elemental::detail::pca_filter_impl_Matrix{}                                                                    \
	)

#endif // !ELEMENTAL_FUSE_FN_PCA_FILTER_HPP