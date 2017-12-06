// gdredis.h

#ifndef GD_REDIS
#define GD_REDIS

#include "reference.h"
#include "ustring.h"

class GDRedis : public Reference {

    GDCLASS(GDRedis,Reference);

protected:
    static void _bind_methods();

public:
    GDRedis();

    // Error GDRedis_connect(const String& host, int port);
    // Error GDRedis::GDRedis_set(const String& key, const String& value);
    // Error GDRedis::GDRedis_get(const String& key);
    // Error GDRedis::GDRedis_hmset();
    // Error GDRedis::GDRedis_hgetall();
    // Error GDRedis::GDRedis_exists();

private:
    cpp_redis::client _client;


};

#endif
