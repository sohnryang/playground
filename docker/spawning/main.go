package main

import (
	"context"
	"io"
	"log"
	"os"

	"github.com/docker/docker/api/types"
	"github.com/docker/docker/api/types/container"
	"github.com/docker/docker/client"
	"github.com/docker/go-connections/nat"
)

func main() {
	ctx := context.Background()
	cli, err := client.NewClientWithOpts(client.FromEnv, client.WithAPIVersionNegotiation())
	if err != nil {
		log.Fatal(err)
	}
	defer cli.Close()

	reader, err := cli.ImagePull(ctx, "docker.io/library/nginx", types.ImagePullOptions{})
	if err != nil {
		log.Fatal(err)
	}
	defer reader.Close()
	io.Copy(os.Stdout, reader)

	resp, err := cli.ContainerCreate(ctx, &container.Config{
		Image:        "nginx",
		Tty:          false,
		AttachStdout: true,
	}, &container.HostConfig{
		PortBindings: nat.PortMap{
			"80/tcp": []nat.PortBinding{{
				HostPort: "8080",
			}},
		},
	}, nil, nil, "nginx-server")
	if err != nil {
		log.Fatal(err)
	}

	if err := cli.ContainerStart(ctx, resp.ID, types.ContainerStartOptions{}); err != nil {
		log.Fatal(err)
	}
	log.Println(resp.ID)
}
