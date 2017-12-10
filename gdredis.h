// MIT License
// 
// Copyright (c) 2017 PerduGames
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

/* gdredis.h */

#ifndef GD_REDIS
#define GD_REDIS

#include <cpp_redis/cpp_redis>
#include <iostream>
#include <memory>

#include "reference.h"
#include "ustring.h"

class GDRedis : public Reference {

    GDCLASS(GDRedis,Reference);

protected:
    static void _bind_methods();

public:
    GDRedis();

    void GDRedis_connect(const String& host="127.0.0.1", int port=6379);
    void GDRedis_set(const String& key, const String& value);
    String GDRedis_get(const String& key);
    void GDRedis_hmset(const String& key, const Dictionary& pairs);
    Dictionary GDRedis_hgetall(const String& key);
    int GDRedis_exists(const Array& keys);

private:
    cpp_redis::client client;
    std::vector<std::pair<std::string, std::string>> redis_reply_to_vector(cpp_redis::reply& records);


};

#endif
