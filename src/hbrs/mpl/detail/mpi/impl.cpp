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

#include "impl.hpp"

#include <hbrs/mpl/core/preprocessor.hpp>
#include <hbrs/mpl/dt/exception.hpp>
#include <boost/throw_exception.hpp>
#include <boost/assert.hpp>
#include <mpi.h>

HBRS_MPL_NAMESPACE_BEGIN
namespace detail {
namespace mpi {

static void
safe(int ec) {
	if (ec != MPI_SUCCESS) {
		BOOST_THROW_EXCEPTION((
			mpi_exception{} 
			<< errinfo_mpi_error_info{mpi_error_info{ec}}
		));
	}
}

HBRS_MPL_API
MPI_Datatype
datatype(hana::basic_type<double>) {
	return MPI_DOUBLE;
}

HBRS_MPL_API
MPI_Datatype
datatype(hana::basic_type<int>) {
	return MPI_INT;
}

HBRS_MPL_API
MPI_Datatype
datatype(hana::basic_type<unsigned long>) {
	return MPI_UNSIGNED_LONG;
}

HBRS_MPL_API
MPI_Datatype
datatype(hana::basic_type<unsigned long long>) {
	return MPI_UNSIGNED_LONG_LONG;
}

HBRS_MPL_API
MPI_Datatype
datatype(hana::basic_type<pair<int,int>>) {
	return MPI_2INT;
}

HBRS_MPL_API
MPI_Datatype
datatype(hana::basic_type<pair<short,int>>) {
	return MPI_SHORT_INT;
}

HBRS_MPL_API
MPI_Datatype
datatype(hana::basic_type<pair<long,int>>) {
	return MPI_LONG_INT;
}

HBRS_MPL_API
MPI_Datatype
datatype(hana::basic_type<pair<float,int>>) {
	return MPI_FLOAT_INT;
}

HBRS_MPL_API
MPI_Datatype
datatype(hana::basic_type<pair<double,int>>) {
	return MPI_DOUBLE_INT;
}

HBRS_MPL_API
bool
initialized() {
	int flag;
	safe(MPI_Initialized(&flag));
	return flag;
}

HBRS_MPL_API
bool
finalized() {
	int flag;
	safe(MPI_Finalized(&flag));
	return flag;
}

HBRS_MPL_API
int
comm_rank(MPI_Comm comm) {
	BOOST_ASSERT(initialized());
	int rank;
	safe(MPI_Comm_rank(comm, &rank));
	return rank;
}

HBRS_MPL_API
int
comm_size(MPI_Comm comm) {
	BOOST_ASSERT(initialized());
	int size;
	safe(MPI_Comm_size(comm, &size));
	return size;
}

HBRS_MPL_API
void
barrier(MPI_Comm comm) {
	BOOST_ASSERT(initialized());
	safe(MPI_Barrier(comm));
}

HBRS_MPL_API
void
abort(MPI_Comm comm, int errorcode) {
	BOOST_ASSERT(initialized());
	safe(MPI_Abort(comm, errorcode));
}

HBRS_MPL_API
MPI_Request
ibcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm) {
	BOOST_ASSERT(initialized());
	MPI_Request request;
	safe(MPI_Ibcast(buffer, count, datatype, root, comm, &request));
	return request;
}

HBRS_MPL_API
MPI_Status
wait(MPI_Request & request) {
	BOOST_ASSERT(initialized());
	MPI_Status status;
	safe(MPI_Wait(&request, &status));
	return status;
}

HBRS_MPL_API
MPI_Status
probe(int source, int tag, MPI_Comm comm) {
	BOOST_ASSERT(initialized());
	MPI_Status status;
	safe(MPI_Probe(source, tag, comm, &status));
	return status;
}

HBRS_MPL_API
int
get_count(MPI_Status const& status, MPI_Datatype datatype) {
	BOOST_ASSERT(initialized());
	int count;
	safe(MPI_Get_count(&status, datatype, &count));
	return count;
}

HBRS_MPL_API
MPI_Request
isend(void const *buffer, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm) {
	BOOST_ASSERT(initialized());
	MPI_Request request;
	safe(MPI_Isend(buffer, count, datatype, dest, tag, comm, &request));
	return request;
}

HBRS_MPL_API
MPI_Request
irecv(void *buffer, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm) {
	BOOST_ASSERT(initialized());
	MPI_Request request;
	safe(MPI_Irecv(buffer, count, datatype, source, tag, comm, &request));
	return request;
}

HBRS_MPL_API
void
allreduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm) {
	BOOST_ASSERT(initialized());
	safe(MPI_Allreduce(sendbuf, recvbuf, count, datatype, op, comm));
}

HBRS_MPL_API
MPI_Request
iallreduce(void const *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm) {
	BOOST_ASSERT(initialized());
	MPI_Request request;
	safe(MPI_Iallreduce(sendbuf, recvbuf, count, datatype, op, comm, &request));
	return request;
}

HBRS_MPL_API
void
allgather(void const* sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm) {
	BOOST_ASSERT(initialized());
	safe(MPI_Allgather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm));
}

HBRS_MPL_API
MPI_Request
iallgather(void const* sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm) {
	BOOST_ASSERT(initialized());
	MPI_Request request;
	safe(MPI_Iallgather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, &request));
	return request;
}

/* namespace mpi */ }
/* namespace detail */ }
HBRS_MPL_NAMESPACE_END
