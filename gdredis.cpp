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

/* gdredis.cpp */

#include "gdredis.h"

GDRedis::GDRedis() {
    //! Enable logging
    cpp_redis::active_logger = std::unique_ptr<cpp_redis::logger>(new cpp_redis::logger);
}

void GDRedis::GDRedis_connect(const String& host, int port) {

    //std::string stg_host = host.c_str();
    std::string stg_host = std::string(host.utf8().get_data());

    client.connect(stg_host, port, [this](const std::string& host, std::size_t port, cpp_redis::client::connect_state status) {
        if (status == cpp_redis::client::connect_state::dropped) {
            //std::cout << "client disconnected from " << host << ":" << port << std::endl;
            ERR_EXPLAIN("client disconnected!");
        }else if(status == cpp_redis::client::connect_state::ok){
            emit_signal("callback_GDRedis_connect");
        }
    });

 }

void GDRedis::GDRedis_set(const String& key, const String& value) {

    std::string stg_key = std::string(key.utf8().get_data());
    std::string stg_value = std::string(value.utf8().get_data());

    client.set(stg_key, stg_value, [](cpp_redis::reply& reply) {
        if (reply.is_error()){
            ERR_EXPLAIN("client.set error!");
        }
    });
    client.sync_commit();

 }

String GDRedis::GDRedis_get(const String& key) {

    String value;
    std::string stg_key = std::string(key.utf8().get_data());

    client.get(stg_key, [&value](cpp_redis::reply& reply) {
        if (reply.is_error()){
            ERR_EXPLAIN("client.get error!");
        }else{
            if (reply.is_string()){
                std::string s = reply.as_string();
                const char * stg = &s[0];
                value = stg;
            }
        }
    });
    client.sync_commit();
    return value;

 }

void GDRedis::GDRedis_hmset(const String& key, const Dictionary& pairs) {

    int reply_ok;
    int max = pairs.size();
    std::string stg_key = std::string(key.utf8().get_data());
    Array keys_pairs = pairs.keys();
    std::vector<std::pair<std::string, std::string>> pairs_vector(max);

    for(int i = 0; i < max; i++){
        std::string s_key = std::string(String(keys_pairs[i]).utf8().get_data());
        std::string s_value = std::string(String(pairs[keys_pairs[i]]).utf8().get_data());

        pairs_vector[i] = std::make_pair(s_key, s_value);
    }
    client.hmset(stg_key, pairs_vector, [](cpp_redis::reply& reply) {
        if (reply.is_error()){
            ERR_EXPLAIN("client.hmset error!");
        }
    });
    client.sync_commit();

}

Dictionary GDRedis::GDRedis_hgetall(const String& key) {

    Dictionary dict;
    std::string stg_key = std::string(key.utf8().get_data());

    client.hgetall(stg_key, [this,&dict](cpp_redis::reply& reply) {
        if (reply.is_error()){
            ERR_EXPLAIN("client.hgetall error!");
        }else{
            if (reply.is_array()){
                std::vector<std::pair<std::string, std::string>> data = redis_reply_to_vector(reply);
                int max = data.size();
                for(int i = 0; i < max; i++){
                    std::string s1 = data[i].first;
                    std::string s2 = data[i].second;
                    const char * stg1 = &s1[0];
                    const char * stg2 = &s2[0];
                    dict[stg1] = stg2;
                }
            }
        }
    });
    client.sync_commit();
    return dict;

}

std::vector<std::pair<std::string, std::string>> GDRedis::redis_reply_to_vector(cpp_redis::reply& reply) {

    int max = reply.as_array().size();
    std::vector<std::pair<std::string, std::string>> res(max*0.5);
    std::string key;
    std::string value;

    int i = 0;
    for (int j = 0; j < max; j+=2){
        key = reply.as_array()[j].as_string();
        value = reply.as_array()[j + 1].as_string();
        res[i] = std::make_pair(key, value);
        i++;
    }
    return res;

}

int GDRedis::GDRedis_exists(const Array& keys) {

    int res;
    int max = keys.size();
    std::vector<std::string> pairs_vector(max);

    for(int i = 0; i < max; i++){
        std::string s_key = std::string(String(keys[i]).utf8().get_data());
        pairs_vector[i] = s_key;
    }

    client.exists(pairs_vector, [&res](cpp_redis::reply& reply) {
        if (reply.is_error()){
            ERR_EXPLAIN("client.hmset error!");
        }else{
            if (reply.is_integer()){
                res = reply.as_integer();
            }
        }
    });
    client.sync_commit();
    return res;

}

 void GDRedis::_bind_methods() {
     ADD_SIGNAL(MethodInfo("callback_GDRedis_connect"));

     ClassDB::bind_method(D_METHOD("GDRedis_connect"),&GDRedis::GDRedis_connect);
     ClassDB::bind_method(D_METHOD("GDRedis_set"),&GDRedis::GDRedis_set);
     ClassDB::bind_method(D_METHOD("GDRedis_get"),&GDRedis::GDRedis_get);
     ClassDB::bind_method(D_METHOD("GDRedis_hmset"),&GDRedis::GDRedis_hmset);
     ClassDB::bind_method(D_METHOD("GDRedis_hgetall"),&GDRedis::GDRedis_hgetall);
     ClassDB::bind_method(D_METHOD("GDRedis_exists"),&GDRedis::GDRedis_exists);

 }
