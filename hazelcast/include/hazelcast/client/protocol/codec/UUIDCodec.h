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
#include "hazelcast/util/UUID.h"
#include "hazelcast/util/Bits.h"

namespace hazelcast {
    namespace client {
        namespace protocol {
            class ClientMessage;

            namespace codec {
                class UUIDCodec {
                public:
                    static util::UUID decode(ClientMessage &clientMessage);

                    static void encode(const util::UUID &address, ClientMessage &clientMessage);

                    static int calculateDataSize(const util::UUID &address);

                private:
                    static const int UUID_LONG_FIELD_COUNT = 2;
                    static const int UUID_DATA_SIZE = UUID_LONG_FIELD_COUNT * util::Bits::LONG_SIZE_IN_BYTES;
                };
            }
        }
    }
}


