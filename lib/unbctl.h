/*
 * Copyright (c) 2008, 2009, 2011 Nicira, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef UNBCTL_H
#define UNBCTL_H 1

#ifdef  __cplusplus
extern "C" {
#endif

/* Server for Unix domain socket control connection. */
struct unbctl_server;
int unbctl_server_create(const char *path, struct unbctl_server **);
void unbctl_server_run(struct unbctl_server *);
void unbctl_server_wait(struct unbctl_server *);
void unbctl_server_destroy(struct unbctl_server *);

const char *unbctl_server_get_path(const struct unbctl_server *);

/* Client for Unix domain socket control connection. */
struct jsonrpc;
int unbctl_client_create(const char *path, struct jsonrpc **client);
int unbctl_client_transact(struct jsonrpc *client,
                            const char *command,
                            int argc, char *argv[],
                            char **result, char **error);

/* Command registration. */
struct unbctl_conn;
typedef void unbctl_cb_func(struct unbctl_conn *,
                             int argc, const char *argv[], void *aux);
void unbctl_command_register(const char *name, const char *usage,
                              int min_args, int max_args,
                              unbctl_cb_func *cb, void *aux);
void unbctl_command_reply_error(struct unbctl_conn *, const char *error);
void unbctl_command_reply(struct unbctl_conn *, const char *body);

#ifdef  __cplusplus
}
#endif

#endif /* unbctl.h */
