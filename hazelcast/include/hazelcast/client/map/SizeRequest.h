//
// Created by sancar koyunlu on 6/11/13.
// Copyright (c) 2013 hazelcast. All rights reserved.


#ifndef HAZELCAST_MAP_SIZE_REQUEST
#define HAZELCAST_MAP_SIZE_REQUEST

#include "hazelcast/client/impl/ClientRequest.h"
#include <string>

namespace hazelcast {
    namespace client {
        namespace map {
            class HAZELCAST_API SizeRequest : public impl::ClientRequest{
            public:
                SizeRequest(const std::string& name);

                int getFactoryId() const;

                int getClassId() const;

                void write(serialization::PortableWriter& writer) const;

                bool isRetryable() const;
            private:
                std::string name;
            };
        }
    }
}


#endif //MAP_CLEAR_REQUEST

