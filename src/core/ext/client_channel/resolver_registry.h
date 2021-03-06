/*
 *
 * Copyright 2015, Google Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef GRPC_CORE_EXT_CLIENT_CHANNEL_RESOLVER_REGISTRY_H
#define GRPC_CORE_EXT_CLIENT_CHANNEL_RESOLVER_REGISTRY_H

#include "src/core/ext/client_channel/resolver_factory.h"

void grpc_resolver_registry_init();
void grpc_resolver_registry_shutdown(void);

/** Set the default URI prefix to \a default_prefix. */
void grpc_resolver_registry_set_default_prefix(const char *default_prefix);

/** Register a resolver type.
    URI's of \a scheme will be resolved with the given resolver.
    If \a priority is greater than zero, then the resolver will be eligible
    to resolve names that are passed in with no scheme. Higher priority
    resolvers will be tried before lower priority schemes. */
void grpc_register_resolver_type(grpc_resolver_factory *factory);

/** Create a resolver given \a target.
    First tries to parse \a target as a URI. If this succeeds, tries
    to locate a registered resolver factory based on the URI scheme.
    If parsing or location fails, prefixes default_prefix from
    grpc_resolver_registry_init to target, and tries again (if default_prefix
    was not NULL).
    If a resolver factory was found, use it to instantiate a resolver and
    return it.
    If a resolver factory was not found, return NULL.
    \a args is a set of channel arguments to be included in the result
    (typically the set of arguments passed in from the client API). */
grpc_resolver *grpc_resolver_create(const char *target,
                                    const grpc_channel_args *args);

/** Find a resolver factory given a name and return an (owned-by-the-caller)
 *  reference to it */
grpc_resolver_factory *grpc_resolver_factory_lookup(const char *name);

/** Given a target, return a (freshly allocated with gpr_malloc) string
    representing the default authority to pass from a client. */
char *grpc_get_default_authority(const char *target);

/** Returns a newly allocated string containing \a target, adding the
    default prefix if needed. */
char *grpc_resolver_factory_add_default_prefix_if_needed(const char *target);

#endif /* GRPC_CORE_EXT_CLIENT_CHANNEL_RESOLVER_REGISTRY_H */
