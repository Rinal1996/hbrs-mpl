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

#define BOOST_TEST_MODULE fn_inverse_hbrs_mpl_test
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include <hbrs/mpl/config.hpp>

#ifdef HBRS_MPL_ENABLE_ELEMENTAL
	#include <hbrs/mpl/dt/el_matrix.hpp>
	#include <hbrs/mpl/dt/el_dist_matrix.hpp>
	#include <hbrs/mpl/dt/el_vector.hpp>
	#include <hbrs/mpl/dt/el_dist_vector.hpp>
#endif

#include <hbrs/mpl/detail/test.hpp>
#include <hbrs/mpl/detail/gather.hpp>
#include <hbrs/mpl/detail/not_supported.hpp>

#include <hbrs/mpl/dt/ctsam.hpp>
#include <hbrs/mpl/dt/scv.hpp>
#include <hbrs/mpl/dt/storage_order.hpp>
#include <hbrs/mpl/dt/matrix_size.hpp>

#include <hbrs/mpl/fn/inverse.hpp>
#include <hbrs/mpl/fn/size.hpp>
#include <hbrs/mpl/fn/m.hpp>
#include <hbrs/mpl/fn/n.hpp>

#include <boost/hana/filter.hpp>
#include <boost/hana/zip.hpp>
#include <boost/hana/first.hpp>
#include <boost/hana/second.hpp>
#include <boost/hana/pair.hpp>
#include <boost/hana/at.hpp>
#include <boost/hana/plus.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/for_each.hpp>
#include <boost/hana/transform.hpp>
#include <boost/hana/cartesian_product.hpp>
#include <boost/hana/drop_back.hpp>
#include <boost/hana/drop_front.hpp>
#include <boost/hana/take_front.hpp>
#include <boost/hana/front.hpp>
#include <boost/hana/back.hpp>
#include <boost/hana/unpack.hpp>
#include <boost/hana/greater_equal.hpp>
#include <boost/hana/range.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/remove_at.hpp>

#include <array>

namespace utf = boost::unit_test;
namespace tt = boost::test_tools;

#define _TOL 0.000000001

BOOST_AUTO_TEST_SUITE(fn_inverse_hbrs_mpl_test)

using hbrs::mpl::detail::environment_fixture;
BOOST_TEST_GLOBAL_FIXTURE(environment_fixture);

BOOST_AUTO_TEST_CASE(inverse_diagonal, * utf::tolerance(_TOL)) {
	using namespace hbrs::mpl;
	using hbrs::mpl::select;
	
	static constexpr auto datasets = hana::make_tuple(
		hana::make_tuple(
			make_ctsam(
				std::array<double, 4*4>{
					1., 0., 0., 0.,
					0., 2., 0., 0.,
					0., 0., 3., 0.,
					0., 0., 0., 4.,
				},
				make_matrix_size(hana::size_c<4>, hana::size_c<4>),
				row_major_c
			),
			make_ctsam(
				std::array<double, 4*4>{
					1./1., 0., 0., 0.,
					0., 1./2., 0., 0.,
					0., 0., 1./3., 0.,
					0., 0., 0., 1./4.,
				},
				make_matrix_size(hana::size_c<4>, hana::size_c<4>),
				row_major_c
			)
		)
	);
	
	static constexpr auto dimensions = hana::make_tuple(
		hana::to_tuple(hana::make_range(hana::size_c<0>, hana::length(datasets)))
	);
	
	static constexpr auto factories = hana::drop_back(hana::make_tuple(
		#ifdef HBRS_MPL_ENABLE_ELEMENTAL
		[](auto && dataset) {
			auto A = hana::at(dataset, hana::size_c<0>);
			auto inv_A = hana::at(dataset, hana::size_c<1>);
			
			auto el_A = make_el_matrix(std::move(A));
			auto el_inv_A = make_el_matrix(std::move(inv_A));
			
			return hana::make_tuple(
				detail::inverse_impl_el_matrix{},
				detail::diagonal_matrix_without_zeros_on_main_diagonal<decltype(el_A)>{el_A},
				el_A,
				el_inv_A
			);
		},
		[](auto && dataset) {
			static El::Grid grid{}; // grid is static because reference to grid is required by El::DistMatrix<...>
			auto A = hana::at(dataset, hana::size_c<0>);
			auto inv_A = hana::at(dataset, hana::size_c<1>);
			
			auto el_A = make_el_dist_matrix(grid, make_el_matrix(std::move(A)));
			auto el_inv_A = make_el_dist_matrix(grid, make_el_matrix(std::move(inv_A)));
			
			return hana::make_tuple(
				detail::inverse_impl_el_dist_matrix{},
				detail::diagonal_matrix_without_zeros_on_main_diagonal<decltype(el_A)>{el_A},
				el_A,
				el_inv_A
			);
		},
		#endif
		"SEQUENCE_TERMINATOR___REMOVED_BY_DROP_BACK"
	));
	
	hana::for_each(hana::cartesian_product(dimensions), [](auto const& cfg) {
		auto const& dataset_nr = hana::at_c<0>(cfg);
		BOOST_TEST_MESSAGE("dataset_nr=" << dataset_nr);
		auto const& dataset = hana::at(datasets, dataset_nr);
		
		auto testcases = hana::transform(
			factories,
			[&](auto factory) { return factory(dataset); }
		);
		
		auto supported_indices = hana::transform(
			hana::filter(
				hana::zip(
					hana::transform(testcases, detail::is_supported), // tuple of hana::true_ and hana::false_
					hana::to_tuple(hana::make_range(hana::size_c<0>,hana::length(testcases))) // indices of testcases
				),
				hana::front
			),
			hana::back
		);
		
		auto results = hana::transform(
			supported_indices,
			[&](auto i) {
				BOOST_TEST_MESSAGE("Running impl nr " << i);
				auto testcase = hana::at(testcases, i);
				return hana::unpack(
					hana::take_front(hana::drop_front(testcase), hana::size_c<1>),
					hana::front(testcase)
				);
			}
		);
		
		auto results_indices = hana::to_tuple(hana::make_range(
			hana::size_c<0>,
			hana::length(results)
		));
		
		BOOST_TEST_MESSAGE("All runs finished.");
		
		BOOST_TEST_PASSPOINT();
		
		if constexpr(hana::length(results) >= 2u) {
			auto compare = [&](auto i) {
				auto j = i+hana::ushort_c<1>;
				auto impl_idx_i = hana::at(supported_indices, i);
				auto impl_idx_j = hana::at(supported_indices, j);
				
				auto const& result_i = hana::at(results, i);
				auto const& result_j = hana::at(results, j);
				
				BOOST_TEST_PASSPOINT();
				
				BOOST_TEST_MESSAGE("comparing results of impl nr " << impl_idx_i << " and " << impl_idx_j);
				
				HBRS_MPL_TEST_MMEQ(result_i, result_j, false);
				
				BOOST_TEST_MESSAGE("comparing impl nr " << impl_idx_i << " and " << impl_idx_j << " done.");
				
				BOOST_TEST_PASSPOINT();
			};
			
			hana::for_each(hana::drop_back(results_indices), compare);
		}
		
		BOOST_TEST_PASSPOINT();
		
		hana::for_each(
			results_indices,
			[&](auto i) {
				auto impl_idx = hana::at(supported_indices, i);
				BOOST_TEST_MESSAGE("Comparing correct inv(A) and results computed by impl nr " << impl_idx);
				
				auto testcase = hana::at(testcases, impl_idx);
				
				auto inv_A = hana::at(testcase, hana::size_c<3>);
				auto cmp_inv_A = hana::at(results, i);
				
				HBRS_MPL_TEST_MMEQ(inv_A, cmp_inv_A, false);
			}
		);
		BOOST_TEST_MESSAGE("Comparing of correct inv(A) and computed results done.");
	});
}

BOOST_AUTO_TEST_SUITE_END()
