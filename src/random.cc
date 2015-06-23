// Copyright (C) 2015 the Massachusetts Institute of Technology
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not
// use this file except in compliance with the License.  You may obtain a copy
// of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
// License for the specific language governing permissions and limitations under
// the License.

#include "random.h"

#include <cstddef>
#include <limits>

#include <openssl/rand.h>
extern "C" {
#include <urweb/urweb_cpp.h>
}

static_assert(sizeof(char) == 1, "char is not a single byte");
static_assert(sizeof(unsigned char) == 1, "unsigned char is not a single byte");

namespace {

// Asserts a condition without crashing or releasing information about where the
// error occurred.  This function is essential for web programming, where an
// attacker should not be able to bring down the app by causing an assertion
// failure.
void Assert(uw_context* const context, const bool condition,
            const failure_kind action, const char* const message) {
  if (!condition) {
    uw_error(context, action, message);
  }
}

void Assert(uw_context* const context,
            const bool condition, const char* const message) {
  Assert(context, condition, FATAL, message);
}

char* RandomBytes(struct uw_context* const context, const int n_bytes) {
  Assert(context, 0 <= n_bytes,
         "cannot produce a negative number of random bytes");
  // Allocate for the result.  Ensure that no precision gets lost when casting
  // from int to std::size_t.
  static_assert(std::numeric_limits<int>::max()
                <= std::numeric_limits<std::size_t>::max(),
                "int is larger than expected");
  unsigned char* const result_bytes =
    static_cast<unsigned char*>(uw_malloc(context,
                                          static_cast<std::size_t>(n_bytes)));
  // Fill it with random data.
  Assert(context, RAND_bytes(result_bytes, n_bytes) == 1, BOUNDED_RETRY,
         "cannot generate random data");
  return reinterpret_cast<char*>(result_bytes);
}

}  // namespace

uw_Basis_int uw_Random_int(struct uw_context* const context) {
  return *reinterpret_cast<uw_Basis_int*>(RandomBytes(context,
                                                      sizeof(uw_Basis_int)));
}

uw_Basis_blob uw_Random_bytes(struct uw_context* const context,
                              const uw_Basis_int ur_n_bytes) {
  // We need to use ur_n_bytes as a number of different types in this function.
  // The smallest one, however, is almost certainly int.  Ensure that that's the
  // case.
  static_assert(std::numeric_limits<int>::max()
                <= std::numeric_limits<std::size_t>::max(),
                "int is larger than expected");
  static_assert(std::numeric_limits<int>::max()
                <= std::numeric_limits<uw_Basis_int>::max(),
                "int is larger than expected");
  // Ensure that we don't lose precision when converting ur_n_bytes to int, and
  // do so.
  Assert(context, 0 <= ur_n_bytes,
         "cannot produce a negative number of random bytes");
  Assert(context, ur_n_bytes < std::numeric_limits<int>::max(),
         "requested number of bytes is larger than supported");
  const int n_bytes = static_cast<int>(ur_n_bytes);
  // Generate random data.
  return uw_Basis_blob{static_cast<std::size_t>(n_bytes),
                       RandomBytes(context, n_bytes)};
}
