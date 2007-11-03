/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 8 -*- */
/***************************************************************************
 *
 * polkit-error.h : error reporting from PolicyKit
 *
 * Copyright (C) 2007 David Zeuthen, <david@fubar.dk>
 *
 * Licensed under the Academic Free License version 2.1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 **************************************************************************/

#if !defined (POLKIT_COMPILATION) && !defined(_POLKIT_INSIDE_POLKIT_H)
#error "Only <polkit/polkit.h> can be included directly, this file may disappear or change contents."
#endif

#ifndef POLKIT_ERROR_H
#define POLKIT_ERROR_H

#include <polkit/polkit-types.h>

POLKIT_BEGIN_DECLS

/**
 * PolKitErrorCode:
 * @POLKIT_ERROR_OUT_OF_MEMORY: Out of memory
 * @POLKIT_ERROR_POLICY_FILE_INVALID: There was an error parsing the given policy file
 * @POLKIT_ERROR_GENERAL_ERROR: A general error code typically
 * indicating problems with the installation of PolicyKit,
 * e.g. helpers missing or wrong owner / permission.
 * @POLKIT_ERROR_NOT_AUTHORIZED_TO_READ_AUTHORIZATIONS_FOR_OTHER_USERS:
 * An attempt was made to read authorizations for other users and the
 * calling process is not authorized.
 * @POLKIT_ERROR_NOT_AUTHORIZED_TO_REVOKE_AUTHORIZATIONS_FROM_OTHER_USERS:
 * An attempt was made to revoke authorizations for other users and the
 * calling process is not authorized.
 * @POLKIT_ERROR_NOT_AUTHORIZED_TO_GRANT_AUTHORIZATION: An attempt was
 * made to grant an authorization and the calling process is not
 * authorized.
 * @POLKIT_ERROR_AUTHORIZATION_ALREADY_EXISTS: Subject already has an
 * similar authorization already (modulo time of grant and who granted).
 * @POLKIT_ERROR_NOT_SUPPORTED: The operation is not supported by the
 * authorization database backend
 * @POLKIT_ERROR_NUM_ERROR_CODES: Number of error codes. This may change
 * from version to version; do not rely on it.
 *
 * Errors returned by PolicyKit
 */
typedef enum
{      
        POLKIT_ERROR_OUT_OF_MEMORY,
        POLKIT_ERROR_POLICY_FILE_INVALID,
        POLKIT_ERROR_GENERAL_ERROR,
        POLKIT_ERROR_NOT_AUTHORIZED_TO_READ_AUTHORIZATIONS_FOR_OTHER_USERS,
        POLKIT_ERROR_NOT_AUTHORIZED_TO_REVOKE_AUTHORIZATIONS_FROM_OTHER_USERS,
        POLKIT_ERROR_NOT_AUTHORIZED_TO_GRANT_AUTHORIZATION,
        POLKIT_ERROR_AUTHORIZATION_ALREADY_EXISTS,
        POLKIT_ERROR_NOT_SUPPORTED,

        POLKIT_ERROR_NUM_ERROR_CODES
} PolKitErrorCode;

struct _PolKitError;
typedef struct _PolKitError PolKitError;

polkit_bool_t    polkit_error_is_set (PolKitError *error);
const char      *polkit_error_get_error_name (PolKitError *error);
PolKitErrorCode  polkit_error_get_error_code (PolKitError *error);
const char      *polkit_error_get_error_message (PolKitError *error);
void             polkit_error_free (PolKitError *error);
polkit_bool_t    polkit_error_set_error (PolKitError **error, PolKitErrorCode error_code, const char *format, ...) __attribute__((__format__ (__printf__, 3, 4)));

POLKIT_END_DECLS

#endif /* POLKIT_ERROR_H */
