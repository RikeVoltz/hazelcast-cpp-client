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
#include <future>
#include <unordered_map>

#include "hazelcast/util/HazelcastDll.h"
#include "hazelcast/client/spi/DefaultObjectNamespace.h"

#if  defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#pragma warning(push)
#pragma warning(disable: 4251) //for dll export
#endif

namespace hazelcast {
    namespace client {
        class Address;

        namespace spi {
            class ClientContext;
            class ClientProxy;
            class ClientProxyFactory;

            class HAZELCAST_API ProxyManager {
            public:
                ProxyManager(ClientContext &context);

                std::shared_ptr<ClientProxy> getOrCreateProxy(const std::string &service,
                                                                const std::string &id,
                                                                spi::ClientProxyFactory &factory);

                /**
                 * Destroys the given proxy in a cluster-wide way.
                 * <p>
                 * Upon successful completion the proxy is unregistered in this proxy
                 * manager, all local resources associated with the proxy are released and
                 * a distributed object destruction operation is issued to the cluster.
                 * <p>
                 * If the given proxy instance is not registered in this proxy manager, the
                 * proxy instance is considered stale. In this case, this stale instance is
                 * a subject to a local-only destruction and its registered counterpart, if
                 * there is any, is a subject to a cluster-wide destruction.
                 *
                 * @param proxy the proxy to destroy.
                 */
                void destroyProxy(ClientProxy &proxy);

                void init();

                void destroy();

            private:
                void initializeWithRetry(const std::shared_ptr<ClientProxy> &clientProxy);

                std::shared_ptr<Address> findNextAddressToSendCreateRequest();

                void initialize(const std::shared_ptr<ClientProxy> &clientProxy);

                std::unordered_map<DefaultObjectNamespace, std::shared_future<std::shared_ptr<ClientProxy>>> proxies;
                std::mutex lock;
                std::chrono::steady_clock::duration invocationTimeout;
                std::chrono::steady_clock::duration invocationRetryPause;
                ClientContext &client;

                bool isRetryable(exception::IException &exception);

                void sleepForProxyInitRetry();
            };
        }
    }
}

#if  defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#pragma warning(pop)
#endif

