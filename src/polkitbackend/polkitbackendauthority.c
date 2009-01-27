/*
 * Copyright (C) 2008 Red Hat, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * Author: David Zeuthen <davidz@redhat.com>
 */

#include "config.h"
#include <errno.h>
#include <pwd.h>
#include <string.h>
#include <polkit/polkit.h>
#include "polkitbackendauthority.h"

enum
{
  CHANGED_SIGNAL,
  LAST_SIGNAL,
};

static guint signals[LAST_SIGNAL] = {0};

G_DEFINE_ABSTRACT_TYPE (PolkitBackendAuthority, polkit_backend_authority, G_TYPE_OBJECT);

static void
polkit_backend_authority_init (PolkitBackendAuthority *local_authority)
{
}

static void
polkit_backend_authority_class_init (PolkitBackendAuthorityClass *klass)
{
  /**
   * PolkitBackendAuthority::changed:
   * @authority: A #PolkitBackendAuthority.
   *
   * Emitted when actions and/or authorizations change
   */
  signals[CHANGED_SIGNAL] = g_signal_new ("changed",
                                          POLKIT_BACKEND_TYPE_AUTHORITY,
                                          G_SIGNAL_RUN_LAST,
                                          0,                      /* class offset     */
                                          NULL,                   /* accumulator      */
                                          NULL,                   /* accumulator data */
                                          g_cclosure_marshal_VOID__VOID,
                                          G_TYPE_NONE,
                                          0);
}

void
polkit_backend_authority_system_bus_name_owner_changed (PolkitBackendAuthority   *authority,
                                                        const gchar              *name,
                                                        const gchar              *old_owner,
                                                        const gchar              *new_owner)
{
  PolkitBackendAuthorityClass *klass;

  klass = POLKIT_BACKEND_AUTHORITY_GET_CLASS (authority);

  klass->system_bus_name_owner_changed (authority, name, old_owner, new_owner);
}

void
polkit_backend_authority_enumerate_actions (PolkitBackendAuthority   *authority,
                                            const gchar              *locale,
                                            PolkitBackendPendingCall *pending_call)
{
  PolkitBackendAuthorityClass *klass;

  klass = POLKIT_BACKEND_AUTHORITY_GET_CLASS (authority);

  klass->enumerate_actions (authority, locale, pending_call);
}

void
polkit_backend_authority_enumerate_users (PolkitBackendAuthority   *authority,
                                          PolkitBackendPendingCall *pending_call)
{
  PolkitBackendAuthorityClass *klass;

  klass = POLKIT_BACKEND_AUTHORITY_GET_CLASS (authority);

  klass->enumerate_users (authority, pending_call);
}

void
polkit_backend_authority_enumerate_groups (PolkitBackendAuthority   *authority,
                                           PolkitBackendPendingCall *pending_call)
{
  PolkitBackendAuthorityClass *klass;

  klass = POLKIT_BACKEND_AUTHORITY_GET_CLASS (authority);

  klass->enumerate_groups (authority, pending_call);
}

void
polkit_backend_authority_check_authorization (PolkitBackendAuthority        *authority,
                                              PolkitSubject                 *subject,
                                              const gchar                   *action_id,
                                              PolkitCheckAuthorizationFlags  flags,
                                              PolkitBackendPendingCall      *pending_call)
{
  PolkitBackendAuthorityClass *klass;

  klass = POLKIT_BACKEND_AUTHORITY_GET_CLASS (authority);

  klass->check_authorization (authority, subject, action_id, flags, pending_call);
}

void
polkit_backend_authority_enumerate_authorizations  (PolkitBackendAuthority    *authority,
                                                    PolkitIdentity            *identity,
                                                    PolkitBackendPendingCall  *pending_call)
{
  PolkitBackendAuthorityClass *klass;

  klass = POLKIT_BACKEND_AUTHORITY_GET_CLASS (authority);

  klass->enumerate_authorizations (authority, identity, pending_call);
}

void
polkit_backend_authority_add_authorization  (PolkitBackendAuthority    *authority,
                                             PolkitIdentity            *identity,
                                             PolkitAuthorization       *authorization,
                                             PolkitBackendPendingCall  *pending_call)
{
  PolkitBackendAuthorityClass *klass;

  klass = POLKIT_BACKEND_AUTHORITY_GET_CLASS (authority);

  klass->add_authorization (authority, identity, authorization, pending_call);
}

void
polkit_backend_authority_remove_authorization  (PolkitBackendAuthority    *authority,
                                                PolkitIdentity            *identity,
                                                PolkitAuthorization       *authorization,
                                                PolkitBackendPendingCall  *pending_call)
{
  PolkitBackendAuthorityClass *klass;

  klass = POLKIT_BACKEND_AUTHORITY_GET_CLASS (authority);

  klass->remove_authorization (authority, identity, authorization, pending_call);
}

void
polkit_backend_authority_register_authentication_agent (PolkitBackendAuthority    *authority,
                                                        const gchar               *object_path,
                                                        PolkitBackendPendingCall  *pending_call)
{
  PolkitBackendAuthorityClass *klass;

  klass = POLKIT_BACKEND_AUTHORITY_GET_CLASS (authority);

  klass->register_authentication_agent (authority, object_path, pending_call);
}

void
polkit_backend_authority_unregister_authentication_agent (PolkitBackendAuthority    *authority,
                                                          const gchar               *object_path,
                                                          PolkitBackendPendingCall  *pending_call)
{
  PolkitBackendAuthorityClass *klass;

  klass = POLKIT_BACKEND_AUTHORITY_GET_CLASS (authority);

  klass->unregister_authentication_agent (authority, object_path, pending_call);
}

void
polkit_backend_authority_authentication_agent_response (PolkitBackendAuthority    *authority,
                                                        const gchar               *cookie,
                                                        PolkitIdentity            *identity,
                                                        PolkitBackendPendingCall  *pending_call)
{
  PolkitBackendAuthorityClass *klass;

  klass = POLKIT_BACKEND_AUTHORITY_GET_CLASS (authority);

  klass->authentication_agent_response (authority, cookie, identity, pending_call);
}
