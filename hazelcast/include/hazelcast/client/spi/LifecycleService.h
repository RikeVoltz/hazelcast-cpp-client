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
//
// Created by sancar koyunlu on 6/17/13.

#pragma once
#include <mutex>
#include <boost/thread/latch.hpp>

#include "hazelcast/util/HazelcastDll.h"
#include "hazelcast/util/AtomicBoolean.h"

#include <set>

#if  defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#pragma warning(push)
#pragma warning(disable: 4251) //for dll export
#endif

namespace hazelcast {
    namespace client {
        class LifecycleListener;

        class LifecycleEvent;

        class ClientConfig;

        class LoadBalancer;

        class Cluster;

        namespace spi {

            class ClientContext;

            class HAZELCAST_API LifecycleService {
            public:

                LifecycleService(ClientContext &clientContext, const std::set<LifecycleListener *> &lifecycleListeners,
                                 LoadBalancer *const loadBalancer, Cluster &cluster);

                virtual ~LifecycleService();

                bool start();

                void fireLifecycleEvent(const LifecycleEvent &lifecycleEvent);

                void shutdown();

                void addLifecycleListener(LifecycleListener *lifecycleListener);

                bool removeLifecycleListener(LifecycleListener *lifecycleListener);

                bool isRunning();

            private:
                ClientContext &clientContext;
                std::set<LifecycleListener *> listeners;
                std::mutex listenerLock;
                util::AtomicBoolean active;
                LoadBalancer *loadBalancer;
                Cluster &cluster;
                boost::latch shutdownCompletedLatch;
            };
        }
    }
}

#if  defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#pragma warning(pop)
#endif


