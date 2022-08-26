package main

import (
	"fmt"
	"time"
)

func main() {
	now := time.Now()
	nano := now.UnixNano()
	fmt.Printf("Time in nanoseconds: %d\n", nano)
}
