<p align="center">
   <img src="https://raw.githubusercontent.com/PerduGames/gdredis/master/cpp_redis/assets/images/godot-redis.jpg"/>
</p>

# GDRedis
GDRedis is a module for Godot 3 for connecting to the redis database.

## EXAMPLE
```extends Node

var gdredis = GDRedis.new()

func _ready():
	# Connect signal CONNECTED
	gdredis.connect("callback_GDRedis_connect", self, "_on_connect_redis")
	# Connect to redis-server in ip "127.0.0.1" and in port "6379"
	gdredis.GDRedis_connect("127.0.0.1", 6379)
	
	# Create a key named "num" with the value "3"
	gdredis.GDRedis_set("num", "3")
	
	# Look for a key called "num", returns "" if it does not exist, 
	# and returns the value if the key exists.
	var reply_get = gdredis.GDRedis_get("num")
	if reply_get == "":
		print("GDRedis_get: not exist")
	else:
		print("GDRedis_get: exist")
	
	# Dictionary that will be used to pass as parameter to GDRedis_hmset
	var xdict = { 
		"user1":"123",
		"user2":"123"
	}
	# First parameter receives a String that is the name of the hash, 
	# and the second parameter a dictionary with the keys and values.
	gdredis.GDRedis_hmset("users", xdict)
	gdredis.GDRedis_hmset("users-two", xdict)
	
	# Look for "users" in redis, and returns all fields and values of 
	# the hash stored at key in one Dictionary. If the key "users" does 
	# not exist, it returns an empty dictionary.
	var reply_hgetall = gdredis.GDRedis_hgetall("users77")
	if reply_hgetall.empty() == true:
		print("GDRedis_hgetall: not exist")
	else:
		print("GDRedis_hgetall: exist")
		print(reply_hgetall)
		
	# Arrays to pass as parameter to GDRedis_exists
	var a = ["users", "users-two"]
	var b = ["other-users"]
	# Look for the Array "a" and Array "b" keys and save 
	# the result to the "a" and "b" variables, remember to 
	#return 0 if the key does not exist, and +1 for each 
	#existing key. If you mention the same key twice in same 
	#Array, it counts twice.
	var reply_exists_a = gdredis.GDRedis_exists(a)
	var reply_exists_b = gdredis.GDRedis_exists(b)
	printt("GDRedis_exists(a): ", reply_exists_a)
	printt("GDRedis_exists(b): ", reply_exists_b)
	if reply_exists_b == 0:
		print("GDRedis_exists: 'other-users' not exist")
	else:
		print("GDRedis_exists: 'other-users' exist")

# Function that is executed when the signal connected to the redis is emitted.
func _on_connect_redis():
	print("REDIS CONNECTED")
   ```

## DOC

#### void GDRedis_connect(const String& host="127.0.0.1", int port=6379)
```# Method to connect to redis-server.```

#### void GDRedis_set(const String& key, const String& value)
```# Set String key to hold the String value. If key already holds a value, it is overwritten, regardless of its type. Any previous time to live associated with the key is discarded on successful SET operation.```

#### String GDRedis_get(const String& key)
```# Get the value of key. If the key does not exist the special value "" is returned, and returns the value if it exists. GET only handles string values.```

#### void GDRedis_hmset(const String& key, const Dictionary& pairs)
```# Passing a Dictionary, sets the specified fields to their respective values in the hash stored at String key. This command overwrites any specified fields already existing in the hash. If key does not exist, a new key holding a hash is created.```

#### Dictionary GDRedis_hgetall(const String& key)
```# Returns all fields and values of the hash stored at key in one Dictionary. If the key does not exist, it returns an empty dictionary.```

#### int GDRedis_exists(const Array& keys)
```# Returns if key exists. You must pass an Array with the keys you want to check as a parameter. Returns 0 if the key does not exist, and +1 for each key that exists. The user should be aware that if the same existing key is mentioned in the arguments multiple times, it will be counted multiple times.```

## API
For questions about redis methods, go to the link https://redis.io/commands/ and search for the command that is in doubt in the search field.

#### void GDRedis_connect(const String& host="127.0.0.1", int port=6379)
#### void GDRedis_set(const String& key, const String& value)
#### String GDRedis_get(const String& key)
#### void GDRedis_hmset(const String& key, const Dictionary& pairs)
#### Dictionary GDRedis_hgetall(const String& key)
#### int GDRedis_exists(const Array& keys)

## License
`gdredis` is under [MIT License](LICENSE).

## Special Thanks
Thanks to [@Cylix](https://github.com/Cylix/) for sharing the library  [cpp_redis](https://github.com/Cylix/cpp_redis) that was used in gdredis

## Author
[perdugames](https://github.com/PerduGames/)

## Note
The gdredis module still has few methods. I just put the ones I'm currently using. If you need other methods of redis, just ask in an issue that I will try to add it to gdredis, if you want to contribute also to contact by means of a issue.

