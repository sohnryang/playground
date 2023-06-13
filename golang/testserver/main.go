package main

import (
	"log"
	"net/http"
	"net/http/httptest"
)

func main() {
	mux := http.NewServeMux()
	mux.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		log.Printf("Connection from %v\n", r.RemoteAddr)
		w.Header().Add("Content-Type", "text/plain")
		w.Write([]byte("hell world!"))
	})
	ts := httptest.NewServer(mux)
	log.Printf("Server started on %v\n", ts.URL)
	for {
	}
}
