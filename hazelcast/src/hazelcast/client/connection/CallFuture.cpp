/*
 * Copyright (c) 2008-2017, Hazelcast, Inc. All Rights Reserved.
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
// Created by sancar koyunlu on 21/08/14.
//

#include "hazelcast/util/IOUtil.h"
#include "hazelcast/client/serialization/pimpl/Data.h"
#include "hazelcast/client/connection/CallFuture.h"
#include "hazelcast/client/connection/CallPromise.h"
#include "hazelcast/client/connection/Connection.h"
#include "hazelcast/client/spi/InvocationService.h"
#include "hazelcast/client/exception/ProtocolExceptions.h"
#include <climits>
#include <ctime>
#include <algorithm>
#include <cstdlib>

namespace hazelcast {
    namespace client {
        namespace connection {
            CallFuture::CallFuture()
            : invocationService(NULL)
            , heartBeatTimeout(0) {

            }

            CallFuture::CallFuture(boost::shared_ptr<CallPromise> promise, boost::shared_ptr<Connection> connection, int heartBeatTimeout, spi::InvocationService *invocationService)
            : promise(promise)
            , connection(connection)
            , invocationService(invocationService)
            , heartBeatTimeout(heartBeatTimeout) {

            }

            CallFuture::CallFuture(const CallFuture &rhs) : promise(rhs.promise), connection(rhs.connection),
                                                            invocationService(rhs.invocationService),
                                                            heartBeatTimeout(rhs.heartBeatTimeout) {
            }

            CallFuture &CallFuture::operator=(const CallFuture &rhs) {
                promise = rhs.promise;
                connection = rhs.connection;
                invocationService = rhs.invocationService;
                heartBeatTimeout = rhs.heartBeatTimeout;
                return *this;
            }

            std::auto_ptr<protocol::ClientMessage> CallFuture::get() {
                // no need to check for the return value
                waitFor(INT64_MAX);

                return promise->getFuture().get();
            }

            bool CallFuture::waitFor(int64_t timeoutInMilliseconds) {
                bool resultReady = false;
				while (timeoutInMilliseconds > 0 && !resultReady) {
                    int64_t beg = util::currentTimeMillis();
                    using namespace std;
                    int64_t waitMillis = (int64_t) min(timeoutInMilliseconds, (int64_t) heartBeatTimeout * 1000);
                    resultReady = promise->getFuture().waitFor(waitMillis);

                    int64_t elapsed = util::currentTimeMillis() - beg;
                    timeoutInMilliseconds -= elapsed;
                }

                return resultReady;
            }

            int64_t CallFuture::getCallId() const {
                int64_t callId = -1;
                protocol::ClientMessage *req = promise->getRequest();
                if (req) {
                    callId = req->getCorrelationId();
                }
                return callId;
            }

            const Connection &CallFuture::getConnection() const {
                return *connection;
            }

        }
    }
}

