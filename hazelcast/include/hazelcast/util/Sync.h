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
//
// Created by ihsan demir on Nov 12, 2015.
//
#pragma once
#include <ostream>
#include <mutex>

#if  defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#pragma warning(push)
#pragma warning(disable: 4251) //for dll export
#endif

namespace hazelcast {
    namespace util {
        template<typename T>
        class Sync {
        public:
            Sync() {}

            Sync(const T &v) : v(v) {
            }

            virtual ~Sync() {
            }

            T operator--(int) {
                std::lock_guard<std::mutex> lockGuard(mutex);
                return v--;
            }

            T operator-=(const T &delta) {
                std::lock_guard<std::mutex> lockGuard(mutex);
                v -= delta;
                return v;
            }

            T operator++(int) {
                std::lock_guard<std::mutex> lockGuard(mutex);
                return v++;
            }

            T operator++() {
                std::lock_guard<std::mutex> lockGuard(mutex);
                return ++v;
            }

            T operator+=(const T &delta) {
                std::lock_guard<std::mutex> lockGuard(mutex);
                v += delta;
                return v;
            }

            void operator=(const T &i) {
                std::lock_guard<std::mutex> lockGuard(mutex);
                v = i;
            }

            void set(const T &i) {
                std::lock_guard<std::mutex> lockGuard(mutex);
                v = i;
            }

            operator T() {
                return get();
            }

            T get() {
                std::lock_guard<std::mutex> lockGuard(mutex);
                return v;
            }

            T operator--() {
                std::lock_guard<std::mutex> lockGuard(mutex);
                return --v;
            }

            bool operator<=(const T &i) {
                std::lock_guard<std::mutex> lockGuard(mutex);
                return v <= i;
            }

            bool operator==(const T &i) {
                std::lock_guard<std::mutex> lockGuard(mutex);
                return i == v;
            }

            bool operator!=(const T &i) {
                std::lock_guard<std::mutex> lockGuard(mutex);
                return i != v;
            }

            bool compareAndSet(const T &compareValue, const T &setValue) {
                std::lock_guard<std::mutex> lockGuard(mutex);
                if(compareValue == v){
                    v = setValue;
                    return true;
                }
                return false;
            }

        protected:

            std::mutex mutex;
            T v;
        };
    }
}

#if  defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#pragma warning(pop)
#endif


