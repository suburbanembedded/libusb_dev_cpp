/**
 * @author Jacob Schloss <jacob.schloss@suburbanembedded.com>
 * @copyright Copyright (c) 2019 Suburban Embedded. All rights reserved.
 * @license Licensed under the 3-Clause BSD license. See LICENSE for details
*/

#include "libusb_dev_cpp/core/Get_descriptor.hpp"

#include "common_util/Byte_util.hpp"

bool Get_descriptor::serialize(uint16_t* const out_wIndex)
{
	*out_wIndex = Byte_util::make_u16(static_cast<uint8_t>(type), idx);

	return true;
}
bool Get_descriptor::deserialize(const uint16_t wIndex)
{
	idx  = Byte_util::get_b0(wIndex);
	type = static_cast<DESCRIPTOR_TYPES>(Byte_util::get_b1(wIndex));

	return true;
}
