/*
 * Copyright (c) 2008-2020, Hazelcast, Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#include <string>
#include "hazelcast/client/protocol/ClientMessage.h"
#include "hazelcast/client/spi/EventHandler.h"

namespace hazelcast {
    namespace client {
        namespace spi {
            namespace impl {
                class ListenerMessageCodec;
            }
            /**
             * Client service to add/remove remote listeners.
             *
             * For smart client, it registers local  listeners to all nodes in cluster.
             * For dummy client, it registers global listener to one node.
             */
            class ClientListenerService {
            public:
                virtual std::string
                registerListener(const std::shared_ptr<impl::ListenerMessageCodec> listenerMessageCodec,
                                 const std::shared_ptr<EventHandler<protocol::ClientMessage>> handler) = 0;

                virtual bool deregisterListener(const std::string registrationId) = 0;
            };
        }
    }
}


