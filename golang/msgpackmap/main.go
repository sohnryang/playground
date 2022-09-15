package main

import (
	"fmt"
	"os"

	"github.com/vmihailenco/msgpack/v5"
)

func main() {
	m := make(map[interface{}]interface{})
	m["arr"] = []int{2, 3, 5, 7}
	m["int"] = 42
	m["bool"] = true
	m["str"] = "hell world!"
	m2 := make(map[interface{}]interface{})
	m2["int"] = 256
	m2["bool"] = false
	m["map"] = m2
	fmt.Println(m)

	b, err := msgpack.Marshal(m)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	fmt.Println("serialized data\n----")
	fmt.Println(b)
	fmt.Println("----")
}
