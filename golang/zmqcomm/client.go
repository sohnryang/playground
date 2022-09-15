package main

import (
	"log"

	zmq "github.com/pebbe/zmq4"
)

func main() {
	zctx, _ := zmq.NewContext()

	log.Println("Connecting to server")
	s, _ := zctx.NewSocket(zmq.REP)
	s.Connect("tcp://*:5555")

	for i := 0; i < 10; i++ {
		log.Printf("Sending req id=%d\n", i)
		s.Send("Hell", 0)

		msg, _ := s.Recv(0)
		log.Printf("Got: %s\n", msg)
	}
}
