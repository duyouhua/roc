/*
 * Copyright (c) 2017 Mikhail Baranov
 * Copyright (c) 2017 Victor Gaydov
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

//! @file roc_core/target_posix/roc_core/singleton.h
//! @brief Singleton.

#ifndef ROC_CORE_SINGLETON_H_
#define ROC_CORE_SINGLETON_H_

#include <pthread.h>

#include "roc_core/alignment.h"
#include "roc_core/errno_to_str.h"
#include "roc_core/noncopyable.h"
#include "roc_core/panic.h"

namespace roc {
namespace core {

//! Singleton.
template <class T> class Singleton : public core::NonCopyable<> {
public:
    //! Get singleton instance.
    static T& instance() {
        if (int err = pthread_once(&once_, create_)) {
            roc_panic("singleton: pthread_once: %s", errno_to_str(err).c_str());
        }
        return *instance_;
    }

private:
    union Storage {
        MaxAlign align;
        char mem[sizeof(T)];
    };

    static void create_() {
        instance_ = new (storage_.mem) T();
    }

    static pthread_once_t once_;
    static Storage storage_;
    static T* instance_;
};

template <class T> pthread_once_t Singleton<T>::once_ = PTHREAD_ONCE_INIT;
template <class T> typename Singleton<T>::Storage Singleton<T>::storage_;
template <class T> T* Singleton<T>::instance_;

} // namespace core
} // namespace roc

#endif // ROC_CORE_SINGLETON_H_
