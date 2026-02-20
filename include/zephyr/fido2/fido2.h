/*
 * Copyright (c) 2026 Siratul Islam <email@sirat.me>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief FIDO2 authenticator public API.
 */

#ifndef ZEPHYR_INCLUDE_FIDO2_FIDO2_H_
#define ZEPHYR_INCLUDE_FIDO2_FIDO2_H_

#include <zephyr/fido2/fido2_types.h>

/**
 * @brief FIDO2 authenticator subsystem
 * @defgroup fido2 FIDO2
 * @since 4.4
 * @version 0.1.0
 * @ingroup os_services
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize the FIDO2 subsystem.
 *
 * Sets up credential storage, crypto, and registered transports.
 *
 * @retval 0 on success
 * @retval -errno on failure
 */
int fido2_init(void);

/**
 * @brief Start the FIDO2 authenticator.
 *
 * Begins listening for CTAP2 commands on all enabled transports.
 *
 * @retval 0 on success
 * @retval -errno on failure
 */
int fido2_start(void);

/**
 * @brief Stop the FIDO2 authenticator.
 *
 * Stops all transports and the processing thread.
 *
 * @retval 0 on success
 * @retval -errno on failure
 */
int fido2_stop(void);

/**
 * @brief Get authenticator device info.
 *
 * Populates the info structure with supported versions, extensions,
 * AAGUID, and current configuration state.
 *
 * @param info Pointer to device info structure to populate
 * @retval 0 on success
 * @retval -EINVAL if info is NULL
 */
int fido2_get_info(struct fido2_device_info *info);

/**
 * @brief Perform a factory reset.
 *
 * Wipes all stored credentials, PIN state, and resets the authenticator.
 * This requires user presence confirmation.
 *
 * @retval 0 on success
 * @retval -errno on failure
 */
int fido2_reset(void);

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* ZEPHYR_INCLUDE_FIDO2_FIDO2_H_ */
