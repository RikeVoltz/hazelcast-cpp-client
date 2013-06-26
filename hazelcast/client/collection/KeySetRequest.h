//
// Created by sancar koyunlu on 6/25/13.
// Copyright (c) 2013 hazelcast. All rights reserved.



#ifndef HAZELCAST_KeySetRequest
#define HAZELCAST_KeySetRequest

#include "CollectionProxyId.h"
#include "CollectionRequest.h"

namespace hazelcast {
    namespace client {
        namespace collection {
            class KeySetRequest : public CollectionRequest {
            public:
                KeySetRequest(const CollectionProxyId& id)
                : CollectionRequest(id) {

                };

                int getClassId() const {
                    return CollectionPortableHook::KEY_SET;
                };

                template<typename HzWriter>
                void writePortable(HzWriter& writer) const {
                    CollectionRequest::writePortable(writer);
                };

                template<typename HzReader>
                void readPortable(HzReader& reader) {
                    CollectionRequest::readPortable(reader);
                };
            };
        }
    }
}
#endif //HAZELCAST_KeySetRequest