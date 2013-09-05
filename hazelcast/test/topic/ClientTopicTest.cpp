#include "ClientTopicTest.h"
#include "HazelcastInstanceFactory.h"
#include "HazelcastClient.h"
#include "CountDownLatch.h"


namespace hazelcast {
    namespace client {

        class HazelcastClient;

        namespace test {
            using namespace iTest;

            ClientTopicTest::ClientTopicTest(HazelcastInstanceFactory& hazelcastInstanceFactory)
            :hazelcastInstanceFactory(hazelcastInstanceFactory)
            , instance(hazelcastInstanceFactory.newHazelcastInstance())
            , client(new HazelcastClient(clientConfig.addAddress(Address("localhost", 5701))))
            , topic(new ITopic<std::string>(client->getTopic<std::string>("ClientTopicTest"))) {
            };


            void ClientTopicTest::addTests() {
                addTest(&ClientTopicTest::testListener, "testListener");
            };

            void ClientTopicTest::beforeClass() {
            };

            void ClientTopicTest::afterClass() {
            };

            void ClientTopicTest::beforeTest() {
            };

            void ClientTopicTest::afterTest() {
            };

            class MyMessageListener {
            public:
                MyMessageListener(util::CountDownLatch& latch)
                :latch(latch) {

                };

                void onMessage(topic::Message<std::string> message) {
                    std::cout << message.getMessageObject() << std::endl;
                    std::cout << message.getSource() << std::endl;
                    latch.countDown();
                }

            private:
                util::CountDownLatch& latch;
            };

            void ClientTopicTest::testListener() {

                util::CountDownLatch latch(10);
                MyMessageListener listener(latch);
                topic->addMessageListener(listener);

                for (int i = 0; i < 10; i++) {
                    topic->publish(std::string("naber") + util::to_string(i));
                }
                assertTrue(latch.await(20 * 1000));

            }
        }
    }
}