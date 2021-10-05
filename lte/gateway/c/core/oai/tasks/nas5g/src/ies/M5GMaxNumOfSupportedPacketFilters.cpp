/*
Copyright 2020 The Magma Authors.
This source code is licensed under the BSD-style license found in the
LICENSE file in the root directory of this source tree.
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <iostream>
#include <sstream>
#include <cstdint>
#include <cstring>
#include "M5GCommonDefs.h"
#include "M5GMaxNumOfSupportedPacketFilters.h"

namespace magma5g {
M5GMaxNumOfSupportedPacketFilters::M5GMaxNumOfSupportedPacketFilters() {}
M5GMaxNumOfSupportedPacketFilters::~M5GMaxNumOfSupportedPacketFilters() {}

int M5GMaxNumOfSupportedPacketFilters::EncodeMaxNumOfSupportedPacketFilters(
    M5GMaxNumOfSupportedPacketFilters* maxNumOfSuppPktFilters, uint8_t iei,
    uint8_t* buffer, uint32_t len) {
  int encoded = 0;
  if (maxNumOfSuppPktFilters->iei) {
    *(buffer + encoded) = maxNumOfSuppPktFilters->iei;
    encoded++;
    *(buffer + encoded) =
        (uint8_t)(maxNumOfSuppPktFilters->maxNumOfSuppPktFilters & 0xFF);
    encoded++;
    *(buffer + encoded) =
        (uint8_t)((maxNumOfSuppPktFilters->maxNumOfSuppPktFilters & 0xE0));
    encoded++;
  }

  return encoded;
}

int M5GMaxNumOfSupportedPacketFilters::DecodeMaxNumOfSupportedPacketFilters(
    M5GMaxNumOfSupportedPacketFilters* maxNumOfSuppPktFilters, uint8_t iei,
    uint8_t* buffer, uint32_t len) {
  int decoded = 0;

  if (iei > 0) {
    maxNumOfSuppPktFilters->iei = *buffer;
    MLOG(MDEBUG) << "maxNumOfSuppPktFilters: iei = " << std::hex
                 << int(maxNumOfSuppPktFilters->iei);
    decoded++;

    maxNumOfSuppPktFilters->maxNumOfSuppPktFilters = (*(buffer + decoded) << 8);
    decoded++;
    maxNumOfSuppPktFilters->maxNumOfSuppPktFilters |=
        (*(buffer + decoded) & 0xE0);
    MLOG(MDEBUG) << "In DecodeMaxNumOfSuppPktFilters: maxNumOfSuppPktFilters = "
                 << std::hex
                 << int(maxNumOfSuppPktFilters->maxNumOfSuppPktFilters);
    decoded++;
  }

  return decoded;
}
}  // namespace magma5g
