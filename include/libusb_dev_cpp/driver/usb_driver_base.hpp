/**
 * @brief usb_driver_base
 * @author Jacob Schloss <jacob@schloss.io>
 * @copyright Copyright (c) 2019 Jacob Schloss. All rights reserved.
 * @license Licensed under the 3-Clause BSD license. See LICENSE for details
*/

#pragma once

#include "libusb_dev_cpp/usb_common.hpp"

#include <cstdint>
#include <cstddef>

class usb_driver_base
{
public:

	enum class USB_STATE
	{
		IDLE,
		RXDATA,
		TXDATA,
		TX_ZLP,
		LASTDATA,
		STATUS_IN,
		STATUS_OUT
	};

	struct usb_driver_status
	{
		size_t   ep0_size;
		uint8_t  active_device_cfg;
		// uint8_t  device_state;
		USB_STATE  control_state;
	};

	usb_driver_base();
	virtual ~usb_driver_base() = default;

	virtual bool initialize() = 0;

	virtual void get_info() = 0;

	virtual bool enable() = 0;
	virtual bool disable() = 0;

	virtual bool connect() = 0;
	virtual bool disconnect() = 0;

	virtual bool set_address(const uint8_t addr) = 0;

	virtual bool ep_setup(const uint8_t ep) = 0;
	virtual bool ep_config(const uint8_t ep) = 0;
	virtual void ep_unconfig(const uint8_t ep) = 0;

	virtual bool ep_is_stalled(const uint8_t ep) = 0;
	virtual void ep_stall(const uint8_t ep) = 0;
	virtual void ep_unstall(const uint8_t ep) = 0;

	virtual size_t ep_write(const uint8_t ep, const uint8_t* buf, const uint16_t len) = 0;
	virtual size_t ep_read(const uint8_t ep, uint8_t* const buf, const uint16_t max_len) = 0;

	virtual uint16_t get_frame_number() = 0;
	virtual size_t get_serial_number(uint8_t* const buf, const size_t maxlen) = 0;

	bool set_ep_rx_callback(const uint8_t ep, const USB_common::Event_callback& func);
	bool set_ep_tx_callback(const uint8_t ep, const USB_common::Event_callback& func);
	bool set_ep_setup_callback(const uint8_t ep, const USB_common::Event_callback& func);

	usb_driver_status& get_status()
	{
		return m_status;
	}

	const usb_driver_status& get_status() const
	{
		return m_status;
	}

	const USB_common::Event_callback& get_event_callback(const uint8_t ep) const
	{
		return m_event_callbacks[ep];
	}

	const USB_common::Event_callback& get_ep_rx_callback(const uint8_t ep) const
	{
		return m_ep_tx_callbacks[ep];
	}

	const USB_common::Event_callback& get_ep_tx_callback(const uint8_t ep) const
	{
		return m_ep_tx_callbacks[ep & 0x7F];
	}

	const USB_common::Event_callback& get_ep_setup_callback(const uint8_t ep) const
	{
		return m_ep_setup_callbacks[ep];
	}

	virtual void poll(const USB_common::Event_callback& func) = 0;

protected:

	std::array<USB_common::Event_callback, USB_common::USB_EVENTS_MAX> m_event_callbacks;
	std::array<USB_common::Event_callback, 8>                          m_ep_rx_callbacks;
	std::array<USB_common::Event_callback, 8>                          m_ep_tx_callbacks;
	std::array<USB_common::Event_callback, 8>                          m_ep_setup_callbacks;

	usb_driver_status m_status;
};