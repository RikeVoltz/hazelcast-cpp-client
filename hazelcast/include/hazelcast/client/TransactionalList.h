//
// Created by sancar koyunlu on 8/6/13.
// Copyright (c) 2013 hazelcast. All rights reserved.




#ifndef HAZELCAST_TransactionalList
#define HAZELCAST_TransactionalList

#include "hazelcast/client/serialization/Data.h"
#include "hazelcast/client/collection/TxnListAddRequest.h"
#include "hazelcast/client/txn/TransactionProxy.h"
#include "hazelcast/client/collection/TxnListRemoveRequest.h"
#include "hazelcast/client/collection/TxnListSizeRequest.h"
#include "hazelcast/client/proxy/TransactionalObject.h"

namespace hazelcast {
    namespace client {
        template <typename E>
        class HAZELCAST_API TransactionalList : public proxy::TransactionalObject {
            friend class TransactionContext;

        public:
            bool add(const E &e) {
                serialization::Data data = toData(e);
                collection::TxnListAddRequest *request = new collection::TxnListAddRequest(getName(), &data);
                boost::shared_ptr<bool> success = invoke<bool>(request);
                return success;
            }

            bool remove(const E &e) {
                serialization::Data data = toData(e);
                collection::TxnListRemoveRequest *request = new collection::TxnListRemoveRequest(getName(), &data);
                boost::shared_ptr<bool> success = invoke<bool>(request);
                return *success;
            }

            int size() {
                collection::TxnListSizeRequest *request = new collection::TxnListSizeRequest(getName());
                boost::shared_ptr<int> s = invoke<int>(request);
                return *s;
            }

            void onDestroy() {
            }

        private:
            TransactionalList(const std::string &instanceName, txn::TransactionProxy *context)
            :TransactionalObject("hz:impl:listService", instanceName, context) {

            }

        };

    }
}

#endif //HAZELCAST_TransactionalList
