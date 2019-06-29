/**
 * @author Jacob Schloss <jacob.schloss@suburbanembedded.com>
 * @copyright Copyright (c) 2019 Suburban Embedded. All rights reserved.
 * @license Licensed under the 3-Clause BSD license. See LICENSE for details
*/

#pragma once

#include "libusb_dev_cpp/usb_core.hpp"

#include "libusb_dev_cpp/descriptor/Device_descriptor.hpp"
#include "libusb_dev_cpp/descriptor/Interface_descriptor.hpp"
#include "libusb_dev_cpp/descriptor/Endpoint_descriptor.hpp"
#include "libusb_dev_cpp/descriptor/Configuration_descriptor.hpp"

class CDC_usb : public USB_core
{
public:

	CDC_usb();
	~CDC_usb() override;

	bool fill_descriptors();

	USB_common::USB_RESP handle_std_device_request(Setup_packet* const req) override;
	USB_common::USB_RESP handle_std_iface_request(Setup_packet* const req) override;
	USB_common::USB_RESP handle_std_ep_request(Setup_packet* const req) override;

	bool set_configuration(const uint8_t bConfigurationValue) override;
	bool get_configuration(uint8_t* const bConfigurationValue) override;

protected:

	Device_descriptor::Device_descriptor_array dev_desc_array;
	Configuration_descriptor::Configuration_descriptor_array conf_desc_array;
	Interface_descriptor::Interface_descriptor_array iface_desc_array;

	Endpoint_descriptor::Endpoint_descriptor_array ep_in_desc_array;
	Endpoint_descriptor::Endpoint_descriptor_array ep_out_desc_array;
};
