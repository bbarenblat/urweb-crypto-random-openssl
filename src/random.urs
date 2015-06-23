(* Copyright 2015 the Massachusetts Institute of Technology

Licensed under the Apache License, Version 2.0 (the "License"); you may not use
this file except in compliance with the License.  You may obtain a copy of the
License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied.  See the License for the
specific language governing permissions and limitations under the License. *)

(* Generates a random int, chosen uniformly using a cryptographically secure
entropy pool. *)
val int : transaction int

(* Returns a blob containing the specified number of cryptographically secure
pseudorandom bytes.  You must specify a nonnegative number equal or less than
INT_MAX as defined by your platform. *)
val bytes : int -> transaction blob
