package main

import (
	"context"
	"fmt"
	"log"

	"github.com/go-redis/redis/v8"
)

func main() {
	ctx := context.Background()
	rdb := redis.NewClient(&redis.Options{
		Addr:     "localhost:6379",
		Password: "",
		DB:       0,
	})

	val, err := rdb.Do(ctx, "ping").Result()
	if err != nil {
		log.Fatal(err)
	}
	fmt.Printf("Ping Response: %v\n", val)

	err = rdb.Set(ctx, "key", "value", 0).Err()
	if err != nil {
		log.Fatal(err)
	}

	val, err = rdb.Get(ctx, "key").Result()
	if err != nil {
		log.Fatal(err)
	}
	fmt.Printf("Value for \"key\": %q\n", val)

	val, err = rdb.Del(ctx, "key").Result()
	if err != nil {
		log.Fatal(err)
	}
	fmt.Printf("Deleted %d keys\n", val.(int64))
}
