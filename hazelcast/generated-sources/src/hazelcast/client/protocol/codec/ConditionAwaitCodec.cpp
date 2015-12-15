/*
 * Copyright (c) 2008-2015, Hazelcast, Inc. All Rights Reserved.
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



#include "hazelcast/client/protocol/codec/ConditionAwaitCodec.h"
#include "hazelcast/client/exception/UnexpectedMessageTypeException.h"

namespace hazelcast {
    namespace client {
        namespace protocol {
            namespace codec {
                const ConditionMessageType ConditionAwaitCodec::RequestParameters::TYPE = HZ_CONDITION_AWAIT;
                const bool ConditionAwaitCodec::RequestParameters::RETRYABLE = false;
                const int32_t ConditionAwaitCodec::ResponseParameters::TYPE = 101;
                std::auto_ptr<ClientMessage> ConditionAwaitCodec::RequestParameters::encode(
                        const std::string &name, 
                        int64_t threadId, 
                        int64_t timeout, 
                        const std::string &lockName) {
                    int32_t requiredDataSize = calculateDataSize(name, threadId, timeout, lockName);
                    std::auto_ptr<ClientMessage> clientMessage = ClientMessage::createForEncode(requiredDataSize);
                    clientMessage->setMessageType((uint16_t)ConditionAwaitCodec::RequestParameters::TYPE);
                    clientMessage->setRetryable(RETRYABLE);
                    clientMessage->set(name);
                    clientMessage->set(threadId);
                    clientMessage->set(timeout);
                    clientMessage->set(lockName);
                    clientMessage->updateFrameLength();
                    return clientMessage;
                }

                int32_t ConditionAwaitCodec::RequestParameters::calculateDataSize(
                        const std::string &name, 
                        int64_t threadId, 
                        int64_t timeout, 
                        const std::string &lockName) {
                    int32_t dataSize = ClientMessage::HEADER_SIZE;
                    dataSize += ClientMessage::calculateDataSize(name);
                    dataSize += ClientMessage::calculateDataSize(threadId);
                    dataSize += ClientMessage::calculateDataSize(timeout);
                    dataSize += ClientMessage::calculateDataSize(lockName);
                    return dataSize;
                }

                ConditionAwaitCodec::ResponseParameters::ResponseParameters(ClientMessage &clientMessage) {
                    if (TYPE != clientMessage.getMessageType()) {
                        throw exception::UnexpectedMessageTypeException("ConditionAwaitCodec::ResponseParameters::decode", clientMessage.getMessageType(), TYPE);
                    }

                    response = clientMessage.get<bool >();
                }

                ConditionAwaitCodec::ResponseParameters ConditionAwaitCodec::ResponseParameters::decode(ClientMessage &clientMessage) {
                    return ConditionAwaitCodec::ResponseParameters(clientMessage);
                }

                ConditionAwaitCodec::ResponseParameters::ResponseParameters(const ConditionAwaitCodec::ResponseParameters &rhs) {
                        response = rhs.response;
                }
                //************************ EVENTS END **************************************************************************//

            }
        }
    }
}
