// gdredis.cpp

#include "gdredis.h"

GDRedis::GDRedis() {
    //! Enable logging
    //cpp_redis::active_logger = std::unique_ptr<cpp_redis::logger>(new cpp_redis::logger);
}

// Error GDRedis::GDRedis_connect(const String& host, int port) {
//
//     //std::string stg_host = host.c_str();
//     std::string stg_host = std::string(host.utf8().get_data());
//
//     _client.connect(stg_host, port, [this](const std::string& host, std::size_t port, cpp_redis::client::connect_state status) {
//         if (status == cpp_redis::client::connect_state::dropped) {
//             //std::cout << "client disconnected from " << host << ":" << port << std::endl;
//             ERR_EXPLAIN("client disconnected!");
//             return FAILED;
//         }else{
//             emit_signal("callback_GDRedis_connect");
//         }
//     });
//     return OK;
//
//  }

// Error GDRedis::GDRedis_set(const String& key, const String& value) {
//
//     client.set("hello", "42", [](cpp_redis::reply& reply) {
//         //std::cout << "set hello 42: " << reply << std::endl;
//         if (reply.is_error()){
//             ERR_EXPLAIN("client.set error!");
//             return FAILED;
//         }else{
//             emit_signal("callback_GDRedis_set");
//         }
//     });
//     client.commit();
//     return OK;
//
//  }
//
// Error GDRedis::GDRedis_get(const String& key) {
//
//     client.get(key, [](cpp_redis::reply& reply) {
//         //std::cout << "get hello: " << reply << std::endl;
//         if (reply.is_error()){
//             ERR_EXPLAIN("client.get error!");
//             return FAILED;
//         }else{
//             emit_signal("callback_GDRedis_get");
//         }
//     });
//     client.commit();
//     return OK;
//
//  }

// Error GDRedis::GDRedis_hmset(const String& key, ) {
//     client.hmset (key, const std::vector <std::pair <std::string, std::string>> & field_val, [](cpp_redis::reply& reply) {
//         if (reply.is_error()){
//             ERR_EXPLAIN("client.get error!");
//             return FAILED;
//         }else{
//             emit_signal("callback_GDRedis_hmset");
//         }
//     }
// }

 void GDRedis::_bind_methods() {
    //  ADD_SIGNAL(MethodInfo("callback_GDRedis_connect"));
    //  ADD_SIGNAL(MethodInfo("callback_GDRedis_set"));
    //  ADD_SIGNAL(MethodInfo("callback_GDRedis_get"));
     //
    //  ClassDB::bind_method(D_METHOD("GDRedis_connect"),&GDRedis::GDRedis_connect);
    //  ClassDB::bind_method(D_METHOD("GDRedis_set"),&GDRedis::GDRedis_set);
    //  ClassDB::bind_method(D_METHOD("GDRedis_get"),&GDRedis::GDRedis_get);

 }
