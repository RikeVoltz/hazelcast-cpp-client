//
// Created by sancar koyunlu on 8/15/13.
// Copyright (c) 2013 hazelcast. All rights reserved.




#ifndef HAZELCAST_IsShutDownRequest
#define HAZELCAST_IsShutDownRequest

#include "hazelcast/client/impl/IdentifiedDataSerializableRequest.h"
#include "hazelcast/client/impl/RetryableRequest.h"
#include <string>

namespace hazelcast {
    namespace client {
        namespace executor {
            class IsShutdownRequest : public impl::IdentifiedDataSerializableRequest, public RetryableRequest {
            public:
                IsShutdownRequest(const std::string& instanceName);

                int getFactoryId() const;

                int getClassId() const;

                void writeData(serialization::ObjectDataOutput& writer) const;

            private:
                const std::string& instanceName;

            };
        }
    }
}

#endif //HAZELCAST_IsShutDownRequest
