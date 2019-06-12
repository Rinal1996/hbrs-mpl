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

#ifndef MATLAB_FUSE_FN_MEAN_HPP
#define MATLAB_FUSE_FN_MEAN_HPP

#include <hbrs/mpl/preprocessor/core.hpp>
#include <matlab/fwd/dt/matrix.hpp>
#include <hbrs/mpl/dt/smc.hpp>
#include <hbrs/mpl/dt/smcs.hpp>
#include <hbrs/mpl/dt/smr.hpp>
#include <hbrs/mpl/dt/smrs.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <type_traits>

MATLAB_NAMESPACE_BEGIN
namespace hana = boost::hana;
namespace mpl = hbrs::mpl;

namespace detail {
struct mean_impl_matrix {
	mpl::smc<matlab::matrix<real_T>, int>
	operator()(mpl::smrs<matlab::matrix<real_T>> const& a) const;
	
	mpl::smr<matlab::matrix<real_T>, int>
	operator()(mpl::smcs<matlab::matrix<real_T>> const& a) const;
};

/* namespace detail */ }
MATLAB_NAMESPACE_END

#define MATLAB_FUSE_FN_MEAN_IMPLS boost::hana::make_tuple(                                                             \
		matlab::detail::mean_impl_matrix{}                                                                             \
	)

#endif // !MATLAB_FUSE_FN_MEAN_HPP