/*
 * Copyright (c) 2026 Siratul Islam <email@sirat.me>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief FIDO2 credential storage API.
 */

#ifndef ZEPHYR_INCLUDE_FIDO2_FIDO2_STORAGE_H_
#define ZEPHYR_INCLUDE_FIDO2_FIDO2_STORAGE_H_

#include <zephyr/fido2/fido2_types.h>
#include <stddef.h>

/**
 * @brief FIDO2 credential storage
 * @ingroup fido2
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Storage backend API */
struct fido2_storage_api {
	/** Initialize the storage backend */
	int (*init)(void);
	/** Store a credential */
	int (*store)(const struct fido2_credential *cred);
	/** Load a credential by ID */
	int (*load)(const uint8_t *cred_id, size_t cred_id_len, struct fido2_credential *cred);
	/** Remove a credential by ID */
	int (*remove)(const uint8_t *cred_id, size_t cred_id_len);
	/** Find credentials by relying party ID hash */
	int (*find_by_rp)(const uint8_t rp_id_hash[FIDO2_SHA256_SIZE],
			  struct fido2_credential *creds, size_t max_creds, size_t *count);
	/** Get the signature counter for a credential */
	int (*get_sign_count)(const uint8_t *cred_id, size_t cred_id_len, uint32_t *count);
	/** Increment the signature counter for a credential */
	int (*increment_sign_count)(const uint8_t *cred_id, size_t cred_id_len);
	/** Wipe all stored data */
	int (*wipe_all)(void);
};

/**
 * @brief Initialize credential storage.
 * @retval 0 on success
 * @retval -errno on failure
 */
int fido2_storage_init(void);

/**
 * @brief Store a credential.
 * @param cred Credential to store
 * @retval 0 on success
 * @retval -ENOSPC if storage is full
 */
int fido2_storage_store(const struct fido2_credential *cred);

/**
 * @brief Load a credential by ID.
 * @param cred_id Credential ID bytes
 * @param cred_id_len Length of credential ID
 * @param cred Output credential structure
 * @retval 0 on success
 * @retval -ENOENT if not found
 */
int fido2_storage_load(const uint8_t *cred_id, size_t cred_id_len, struct fido2_credential *cred);

/**
 * @brief Delete a credential.
 * @param cred_id Credential ID bytes
 * @param cred_id_len Length of credential ID
 * @retval 0 on success
 * @retval -ENOENT if not found
 */
int fido2_storage_delete(const uint8_t *cred_id, size_t cred_id_len);

/**
 * @brief Find all credentials for a relying party.
 * @param rp_id_hash SHA-256 of the relying party ID
 * @param creds Output array
 * @param max_creds Array capacity
 * @param count Number of credentials found
 * @retval 0 on success
 */
int fido2_storage_find_by_rp(const uint8_t rp_id_hash[FIDO2_SHA256_SIZE],
			     struct fido2_credential *creds, size_t max_creds, size_t *count);

/** @brief Get sign counter for a credential */
int fido2_storage_get_sign_count(const uint8_t *cred_id, size_t cred_id_len, uint32_t *count);

/** @brief Increment sign counter for a credential */
int fido2_storage_increment_sign_count(const uint8_t *cred_id, size_t cred_id_len);

/** @brief Wipe all stored credentials and state */
int fido2_storage_wipe_all(void);

/* PIN storage */

/** @brief Store PIN hash */
int fido2_storage_pin_set(const uint8_t pin_hash[FIDO2_PIN_HASH_SIZE]);

/** @brief Load stored PIN hash */
int fido2_storage_pin_get(uint8_t pin_hash[FIDO2_PIN_HASH_SIZE]);

/** @brief Get remaining PIN retries */
int fido2_storage_pin_retries_get(uint8_t *retries);

/** @brief Decrement PIN retry counter */
int fido2_storage_pin_retries_decrement(void);

/** @brief Reset PIN retry counter to max */
int fido2_storage_pin_retries_reset(void);

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* ZEPHYR_INCLUDE_FIDO2_FIDO2_STORAGE_H_ */
