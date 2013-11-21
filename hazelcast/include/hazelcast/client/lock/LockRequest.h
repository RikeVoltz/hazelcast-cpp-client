//
// Created by sancar koyunlu on 6/25/13.
// Copyright (c) 2013 hazelcast. All rights reserved.

#ifndef HAZELCAST_Lock_LockRequest
#define HAZELCAST_Lock_LockRequest

#include "hazelcast/client/impl/PortableRequest.h"
#include <string>

namespace hazelcast {
    namespace client {
        namespace serialization {
            class Data;
        }
        namespace lock {
            class LockRequest : public impl::PortableRequest {
            public:
                LockRequest(serialization::Data& key, int threadId);

                LockRequest(serialization::Data& key, int threadId, long ttl, long timeout);

                int getClassId() const;

                int getFactoryId() const;

                void writePortable(serialization::PortableWriter& writer) const;

            private:
                serialization::Data& key;
                int threadId;
                long ttl;
                long timeout;
            };
        }
    }
}


#endif //HAZELCAST_LockRequest
