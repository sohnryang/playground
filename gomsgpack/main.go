package main

import (
	"fmt"
	"os"
	"reflect"
	"time"

	"github.com/vmihailenco/msgpack/v5"
)

type Account struct {
	Username     string    `msgpack:"username"`
	PasswordHash string    `msgpack:"password_hash"`
	Email        string    `msgpack:"email"`
	Timestamp    time.Time `msgpack:"timestamp"`
}

func main() {
	alice := Account{
		Username:     "Alice",
		PasswordHash: "2aaec9f2c5195fd325826cb6b666901030b96749",
		Email:        "alice@bob.com",
		Timestamp:    time.Unix(0, 0),
	}
	b, err := msgpack.Marshal(alice)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	fmt.Printf("serialized: %v\n", b)

	user := Account{}
	if err := msgpack.Unmarshal(b, &user); err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	fmt.Printf("deserialized: %v\n", user)
	if reflect.DeepEqual(alice, user) {
		fmt.Println("success")
	} else {
		fmt.Println("fail")
		os.Exit(1)
	}
}
