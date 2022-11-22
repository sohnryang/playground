package main

import (
	"context"
	"io"
	"os"

	"github.com/docker/docker/api/types"
	"github.com/docker/docker/api/types/container"
	"github.com/docker/docker/client"
	"github.com/docker/docker/pkg/stdcopy"
	"github.com/docker/go-connections/nat"
	log "github.com/sirupsen/logrus"
)

func main() {
	ctx := context.Background()
	cli, err := client.NewClientWithOpts(client.FromEnv, client.WithAPIVersionNegotiation())
	if err != nil {
		log.WithField("err", err).Fatal("Failed to get client")
	}
	defer cli.Close()

	r, err := cli.ImagePull(ctx, "docker.io/library/nginx", types.ImagePullOptions{})
	if err != nil {
		log.WithField("err", err).Fatal("Failed to pull image")
	}
	defer r.Close()
	io.Copy(os.Stdout, r)

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
		log.WithField("err", err).Fatal("Failed to create container")
	}

	if err := cli.ContainerStart(ctx, resp.ID, types.ContainerStartOptions{}); err != nil {
		log.WithField("err", err).Fatal("Failed to start container")
	}
	log.WithField("id", resp.ID).Info("Container started")

	logReader, err := cli.ContainerLogs(ctx, resp.ID, types.ContainerLogsOptions{
		ShowStdout: true,
		ShowStderr: true,
	})
	if err != nil {
		log.WithField("err", err).Fatal("Failed to get logs")
	}
	go func() {
		defer logReader.Close()
		stdcopy.StdCopy(os.Stdout, os.Stderr, logReader)
	}()

	statusCh, errCh := cli.ContainerWait(ctx, resp.ID, container.WaitConditionNotRunning)
	select {
	case err := <-errCh:
		if err != nil {
			log.WithField("err", err).Fatal("Error while waiting")
		}
	case <-statusCh:
	}
}
