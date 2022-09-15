package main

import (
	"context"
	"log"
	"net"

	"github.com/go-redis/redis/v8"
)

func main() {
	rdb := redis.NewClient(&redis.Options{
		Addr:     net.JoinHostPort("localhost", "6379"),
		Password: "",
		DB:       0,
	})
	ctx := context.Background()

	pubsub := rdb.Subscribe(ctx, "testchan")
	defer pubsub.Close()

	ch := pubsub.Channel()
	for msg := range ch {
		log.Printf("[%v] %v", msg.Channel, msg.Payload)
	}
}
