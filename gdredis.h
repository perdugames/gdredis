// gdredis.h

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
