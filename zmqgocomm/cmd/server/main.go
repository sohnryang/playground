package main

import (
	"log"
	"time"

	zmq "github.com/pebbe/zmq4"
)

func main() {
	zctx, _ := zmq.NewContext()
	s, _ := zctx.NewSocket(zmq.REP)
	s.Bind("tcp://*:5555")
	log.Println("Server started")

	for {
		msg, _ := s.Recv(0)
		log.Printf("Got: %s\n", msg)
		time.Sleep(1 * time.Second)
		s.Send("world", 0)
	}
}
