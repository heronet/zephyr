/*
 * Copyright (c) 2026 Siratul Islam <email@sirat.me>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief FIDO2 user verification abstraction API.
 */

#ifndef ZEPHYR_INCLUDE_FIDO2_FIDO2_UV_H_
#define ZEPHYR_INCLUDE_FIDO2_FIDO2_UV_H_

#include <zephyr/kernel.h>
#include <zephyr/sys/iterable_sections.h>
#include <stdbool.h>

/**
 * @brief FIDO2 user verification
 * @ingroup fido2
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/** @brief User verification method types */
enum fido2_uv_type {
	FIDO2_UV_NONE,      /**< No verification */
	FIDO2_UV_PIN,       /**< Client PIN */
	FIDO2_UV_BIOMETRIC, /**< Biometric sensor */
};

/** @brief User verification API callbacks */
struct fido2_uv_api {
	/** Check if this UV method is configured and ready */
	bool (*is_configured)(void);
	/** Perform user verification */
	int (*verify)(k_timeout_t timeout);
};

/** @brief A registered UV method */
struct fido2_uv {
	/** Verification type */
	enum fido2_uv_type type;
	/** UV API callbacks */
	const struct fido2_uv_api *api;
};

/**
 * @brief Register a user verification method.
 *
 * @param _name C identifier for the UV instance
 * @param _type UV type enum value
 * @param _api Pointer to the UV API struct
 */
#define FIDO2_UV_DEFINE(_name, _type, _api)                                                        \
	STRUCT_SECTION_ITERABLE(fido2_uv, _name) = {                                               \
		.type = _type,                                                                     \
		.api = _api,                                                                       \
	}

/**
 * @brief Check for user presence (e.g. button press).
 *
 * @param timeout Maximum time to wait for user interaction
 * @retval 0 User presence confirmed
 * @retval -ETIMEDOUT if timeout expired
 */
int fido2_up_check(k_timeout_t timeout);

/**
 * @brief Perform user verification.
 *
 * Iterates registered UV methods and attempts verification.
 *
 * @param timeout Maximum time to wait
 * @retval 0 on success
 * @retval -ENOTSUP if no UV method is configured
 * @retval -EACCES if verification failed
 */
int fido2_uv_perform(k_timeout_t timeout);

/**
 * @brief Check if any UV method is configured.
 * @retval true if at least one UV method is available
 */
bool fido2_uv_is_configured(void);

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* ZEPHYR_INCLUDE_FIDO2_FIDO2_UV_H_ */
