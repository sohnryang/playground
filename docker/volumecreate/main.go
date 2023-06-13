package main

import (
	"context"
	"log"

	"github.com/docker/docker/api/types/volume"
	"github.com/docker/docker/client"
)

func must(err error) {
	if err != nil {
		log.Fatal(err)
	}
}

func main() {
	cli, err := client.NewClientWithOpts(client.FromEnv, client.WithAPIVersionNegotiation())
	must(err)
	ctx, cancel := context.WithCancel(context.Background())
	defer cancel()
	cli.VolumeCreate(ctx, volume.CreateOptions{
		ClusterVolumeSpec: &volume.ClusterVolumeSpec{},
		Name:              "testvolume",
	})
}
