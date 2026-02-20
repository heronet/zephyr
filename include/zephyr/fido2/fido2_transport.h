/*
 * Copyright (c) 2026 Siratul Islam <email@sirat.me>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief FIDO2 transport abstraction API.
 */

#ifndef ZEPHYR_INCLUDE_FIDO2_FIDO2_TRANSPORT_H_
#define ZEPHYR_INCLUDE_FIDO2_FIDO2_TRANSPORT_H_

#include <zephyr/kernel.h>
#include <zephyr/sys/iterable_sections.h>
#include <stddef.h>
#include <stdint.h>

/**
 * @brief FIDO2 transport API
 * @ingroup fido2
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Transport driver API callbacks */
struct fido2_transport_api {
	/**
	 * Initialize the transport.
	 *
	 * @retval 0 on success
	 * @retval -ENODEV if hardware is not available
	 */
	int (*init)(void);
	/**
	 * Send response data to the host.
	 *
	 * @param data Response payload bytes
	 * @param len Length of data in bytes
	 * @retval 0 on success
	 * @retval -EIO on transport error
	 */
	int (*send)(const uint8_t *data, size_t len);
	/**
	 * Receive a request from the host.
	 *
	 * @param buf Buffer to store received data
	 * @param buf_size Maximum buffer capacity in bytes
	 * @param recv_len Output: actual number of bytes received
	 * @param timeout Maximum time to wait for data
	 * @retval 0 on success
	 * @retval -ETIMEDOUT if timeout expires
	 * @retval -ENOMEM if message exceeds buf_size
	 */
	int (*recv)(uint8_t *buf, size_t buf_size, size_t *recv_len, k_timeout_t timeout);
	/** Shut down the transport */
	void (*shutdown)(void);
};

/** @brief A registered FIDO2 transport */
struct fido2_transport {
	/** Transport name */
	const char *name;
	/** Transport API callbacks */
	const struct fido2_transport_api *api;
};

/**
 * @brief Register a FIDO2 transport.
 *
 * @param _name C identifier for the transport instance
 * @param _label Human-readable transport name string
 * @param _api Pointer to the transport API struct
 */
#define FIDO2_TRANSPORT_DEFINE(_name, _label, _api)                                                \
	STRUCT_SECTION_ITERABLE(fido2_transport, _name) = {                                        \
		.name = _label,                                                                    \
		.api = _api,                                                                       \
	}

/**
 * @brief Initialize all registered transports.
 * @retval 0 on success
 * @retval -errno if any transport fails to initialize
 */
int fido2_transport_init_all(void);

/**
 * @brief Shut down all registered transports.
 */
void fido2_transport_shutdown_all(void);

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* ZEPHYR_INCLUDE_FIDO2_FIDO2_TRANSPORT_H_ */
