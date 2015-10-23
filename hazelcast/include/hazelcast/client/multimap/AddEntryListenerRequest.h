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
//
// Created by sancar koyunlu on 6/25/13.




#ifndef HAZELCAST_AddEntryListenerRequest
#define HAZELCAST_AddEntryListenerRequest

#include "hazelcast/client/serialization/pimpl/Data.h"
#include "hazelcast/client/impl/ClientRequest.h"
#include <vector>

namespace hazelcast {
    namespace client {
        namespace multimap {
            class AddEntryListenerRequest : public impl::ClientRequest {
            public:
                AddEntryListenerRequest(const std::string &name, const serialization::pimpl::Data &key, bool includeValue);

                AddEntryListenerRequest(const std::string &name, bool includeValue);

                int getFactoryId() const;

                int getClassId() const;

                void write(serialization::PortableWriter &writer) const;

                bool isRetryable() const;

            private:
                std::string name;
                serialization::pimpl::Data key;
                bool hasKey;
                bool includeValue;
            };

        }
    }
}


#endif //HAZELCAST_AddEntryListenerRequest

