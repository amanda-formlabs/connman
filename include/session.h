/*
 *
 *  Connection Manager
 *
 *  Copyright (C) 2012  BMW Car IT GbmH. All rights reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifndef __CONNMAN_SESSION_H
#define __CONNMAN_SESSION_H

#include <connman/service.h>
#include <connman/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CONNMAN_SESSION_POLICY_PRIORITY_LOW      -100
#define CONNMAN_SESSION_POLICY_PRIORITY_DEFAULT     0
#define CONNMAN_SESSION_POLICY_PRIORITY_HIGH      100

enum connman_session_roaming_policy {
	CONNMAN_SESSION_ROAMING_POLICY_UNKNOWN		= 0,
	CONNMAN_SESSION_ROAMING_POLICY_DEFAULT		= 1,
	CONNMAN_SESSION_ROAMING_POLICY_ALWAYS		= 2,
	CONNMAN_SESSION_ROAMING_POLICY_FORBIDDEN	= 3,
	CONNMAN_SESSION_ROAMING_POLICY_NATIONAL		= 4,
	CONNMAN_SESSION_ROAMING_POLICY_INTERNATIONAL	= 5,
};

enum connman_session_type {
	CONNMAN_SESSION_TYPE_UNKNOWN  = 0,
	CONNMAN_SESSION_TYPE_ANY      = 1,
	CONNMAN_SESSION_TYPE_LOCAL    = 2,
	CONNMAN_SESSION_TYPE_INTERNET = 3,
};

struct connman_session;

struct connman_session_bearer {
	connman_bool_t match_all;
	enum connman_service_type service_type;
};

struct connman_session_config {
	connman_bool_t priority;
	enum connman_session_roaming_policy roaming_policy;
	enum connman_session_type type;
	connman_bool_t ecall;
	GSList *allowed_bearers;
};

typedef void (* connman_session_config_cb) (struct connman_session *session,
					struct connman_session_config *config,
					void *user_data, int err);

struct connman_session_policy {
	const char *name;
	int priority;
	int (*create)(struct connman_session *session,
			connman_session_config_cb callback,
			void *user_data);
	void (*destroy)(struct connman_session *session);
};

int connman_session_policy_register(struct connman_session_policy *config);
void connman_session_policy_unregister(struct connman_session_policy *config);

GSList *connman_session_allowed_bearers_any(void);
void connman_session_free_bearers(GSList *bearers);

struct connman_session_config *connman_session_create_default_config(void);

#ifdef __cplusplus
}
#endif

#endif /* __CONNMAN_SESSION_H */
