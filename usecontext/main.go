package main

import (
	"context"
	"fmt"
	"time"
)

func main() {
	gen := func(ctx context.Context) <-chan int { // return type is write only
		dst := make(chan int)
		n := 1
		go func() {
			for {
				select {
				case <-ctx.Done():
					return
				case dst <- n:
					n++
				}
			}
		}()
		return dst
	}

	ctx, cancel := context.WithCancel(context.Background())
	for n := range gen(ctx) {
		fmt.Println(n)
		if n == 10 {
			break
		}
	}
	cancel()

	tick := func(ctx context.Context) int {
		tickCount := 0
		ticker := time.NewTicker(100 * time.Millisecond)
		defer ticker.Stop()
		for {
			select {
			case <-ticker.C:
				fmt.Println("tick")
				tickCount++
			case <-ctx.Done():
				return tickCount
			}
		}
	}

	duration := 5 * time.Second
	ctx, cancel = context.WithTimeout(context.Background(), duration)
	count := tick(ctx)
	fmt.Printf("tick count: %v\n", count)
	cancel()
}
