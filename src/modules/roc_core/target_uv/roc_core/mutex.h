/*
 * Copyright (c) 2015 Mikhail Baranov
 * Copyright (c) 2015 Victor Gaydov
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

//! @file roc_core/target_uv/roc_core/mutex.h
//! @brief Mutex.

#ifndef ROC_CORE_MUTEX_H_
#define ROC_CORE_MUTEX_H_

#include <uv.h>

#include "roc_core/noncopyable.h"
#include "roc_core/panic.h"
#include "roc_core/scoped_lock.h"

namespace roc {
namespace core {

class Cond;

//! Mutex.
class Mutex : public NonCopyable<> {
public:
    //! RAII lock.
    typedef ScopedLock<Mutex> Lock;

    Mutex() {
        if (int err = uv_mutex_init(&mutex_)) {
            roc_panic("mutex: uv_mutex_init(): [%s] %s", uv_err_name(err),
                      uv_strerror(err));
        }
    }

    ~Mutex() {
        uv_mutex_destroy(&mutex_);
    }

    //! Lock mutex.
    void lock() const {
        uv_mutex_lock(&mutex_);
    }

    //! Unlock mutex.
    void unlock() const {
        uv_mutex_unlock(&mutex_);
    }

private:
    friend class Cond;

    mutable uv_mutex_t mutex_;
};

} // namespace core
} // namespace roc

#endif // ROC_CORE_MUTEX_H_
