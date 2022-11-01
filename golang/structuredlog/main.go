package main

import (
	"bufio"
	"fmt"
	"net/url"
	"os"

	log "github.com/sirupsen/logrus"
)

func main() {
	log.Trace("Tracing")
	log.Info("Info")
	log.Warn("Warn")
	log.Error("Error")

	log.WithField("world", "hell").Info("Hell world")
	log.WithFields(log.Fields{"bool": true, "num": 42}).Info("Info with fields")

	fmt.Print("Input URL: ")
	scanner := bufio.NewScanner(os.Stdin)
	var urlStr string
	for scanner.Scan() {
		urlStr = scanner.Text()
		break
	}
	u, err := url.Parse(urlStr)
	if err != nil {
		log.WithField("err", err).Fatal("URL parse failed")
	}
	log.WithField("url", u).Info("URL parsed")
}
