/**
 * @brief Configuration_descriptor
 * @author Jacob Schloss <jacob@schloss.io>
 * @copyright Copyright (c) 2019 Jacob Schloss. All rights reserved.
 * @license Licensed under the 3-Clause BSD license. See LICENSE for details
*/

#include "libusb_dev_cpp/descriptor/Configuration_descriptor.hpp"

#include "common_util/Byte_util.hpp"

bool Configuration_descriptor::serialize(Configuration_descriptor_array* const out_array)
{
	(*out_array)[0] = bLength;
	(*out_array)[1] = bDescriptorType;
	(*out_array)[2] = Byte_util::get_b0(wTotalLength);
	(*out_array)[3] = Byte_util::get_b1(wTotalLength);
	(*out_array)[4] = bNumInterfaces;
	(*out_array)[5] = bConfigurationValue;
	(*out_array)[6] = iConfiguration;
	(*out_array)[7] = bmAttributes;
	(*out_array)[8] = bMaxPower;

	return true;
}
bool Configuration_descriptor::deserialize(const Configuration_descriptor_array& array)
{
	if(bLength != array[0])
	{
		return false;
	}
	if(bDescriptorType != array[1])
	{
		return false;
	}

	wTotalLength        = Byte_util::make_u16(array[3], array[2]);
	bNumInterfaces      = array[4];
	bConfigurationValue = array[5];
	iConfiguration      = array[6];
	bmAttributes        = array[7];
	bMaxPower           = array[8];

	return true;
}
