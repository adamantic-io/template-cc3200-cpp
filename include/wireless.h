/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                     `..--::::::--.``                                    *
 *                 `-:/++:--.`      ``....``                               *
 *               .://+:.        ``..``    .-.`                             *
 *             `://+/`      .-//-.       .yss                              *
 *            `://+:      .://`         `so`y+                             *
 *            -///+      -//+           +y. :y:                            *
 *           `:////     `://:          :y:   +y.                           *
 *            :///+     `////         .yo    `ss                           *
 *            -///+.     -//+.        sy+/////oy+                          *
 *            `////+`     -//+-      +y-......./y:                         *
 *             `/////`     .///:`   -y/         +y.                        *
 *              `/////-      -///:.`++          `+/                        *
 *                -////:.      .:///-.`                     `              *
 *                 `:////:.       `-:/+/-..``     `..`     .               *
 *                   .://///-`         .--:::::---.       .-               *
 *                     `-/////:-.                       `::                *
 *                        `-/+////:-.``              `.:/.                 *
 *                            .-:/+/////::--------::+/:.                   *
 *                                 .--::////////::-.`                      *
 *                            ADAMANTIC SOLUTIONS                          *
 *                      Copyright (C) 2017 ADAMANTIC srl                   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Project : TI-CC3200 C++ Template                                        *
 * Author  : Domenico Barra <dom@adamantic.io>                             *
 * This    : Wireless Interface Support - header file                      *
 * License : LGPL v.3, see the LICENSE file shipped with this distribution *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef ADM_NET_WIRELESS_H
#define ADM_NET_WIRELESS_H

#include <functional>


namespace adm { namespace net {

class WirelessConnection {
public:
	enum SecType {
		OPEN,
		WEP,
		WPA_WPA2
	};
	using ConnectionUpListener   = typename std::function<void ()>;
	using ConnectionFailListener = ConnectionUpListener;
	using ConnectionDownListener = typename std::function<void (bool)> ;
	using IpAcquiredListener     = typename std::function<void(const std::string&)>;

	static void wlan_connect(const std::string& ssid, const std::string& key, SecType sec_type);
	static void wlan_disconnect();
	static bool is_connected();
	static bool is_ip_acquired();

	/**
	 * Registers a listener to be called when the connection
	 * is established. The listener is called from the
	 * network watchdog thread, so it's important not to sleep
	 * or wait on any condition in the listener.
	 *
	 * @param lst the listener to be called.
	 */
	static void on_connection_up(ConnectionUpListener);

	/**
	 * Registers a listener to be called when the connection
	 * goes down for any reason. The listener is called from the
	 * network watchdog thread, so it's important not to sleep
	 * or wait on any condition in the listener.
	 *
	 * @param lst the listener to be called. It accept a `bool`
	 *            parameter which is valued as `true` if the
	 *            disconnection has been intentional (i.e. `disconnect()`
	 *            has been called), `false` otherwise (e.g. transport lost,
	 *            connection reset by peer, ...).
	 */
	static void on_connection_down(ConnectionDownListener);

	/**
	 * Registers a listener to be called when the connection
	 * fails for any reason. The listener is called from the
	 * network watchdog thread, so it's important not to sleep
	 * or wait on any condition in the listener.
	 *
	 * @param lst the listener to be called. 
	 */
	static void on_connection_fail(ConnectionFailListener);

	/**
	 * Registers a listener to be called when the connection
	 * fails for any reason. The listener is called from the
	 * network watchdog thread, so it's important not to sleep
	 * or wait on any condition in the listener.
	 *
	 * @param lst the listener to be called. It accepts a string
	 *            (reference) parameter carrying the IP address.
	 */
	static void on_ip_acquired(IpAcquiredListener);

};

}}

#endif