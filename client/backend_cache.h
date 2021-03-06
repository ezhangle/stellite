// Copyright 2016 LINE Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef STELLITE_CLIENT_BACKEND_CACHE_H_
#define STELLITE_CLIENT_BACKEND_CACHE_H_

#include <memory>

#include "base/memory/weak_ptr.h"
#include "stellite/include/stellite_export.h"
#include "net/base/completion_callback.h"
#include "net/log/net_log.h"

namespace disk_cache {
class Backend;
} // namespace disk_cache

namespace net {
class BackendFactory;

class STELLITE_EXPORT BackendCache {
 public:
  BackendCache(NetLog* netlog, BackendFactory* factory);
  virtual ~BackendCache();

  int GetBackend(disk_cache::Backend** backend,
                 const CompletionCallback& callback);

  void Close();

 private:
  void OnBackendCreated(disk_cache::Backend** backend,
                        const CompletionCallback& callback, int rv);

  int CreateBackend(disk_cache::Backend** backend,
                    const CompletionCallback& callback);

  NetLog* net_log_;

  BackendFactory* backend_factory_; // not owned

  std::unique_ptr<disk_cache::Backend> disk_cache_;

  base::WeakPtrFactory<BackendCache> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(BackendCache);
};

} // namespace net

#endif  // STELLITE_CLIENT_BACKEND_CACHE_H_
