package main

import (
	"context"
	"encoding/base64"
	"encoding/json"
	"io"
	"log"
	"os"

	"github.com/docker/docker/api/types"
	"github.com/docker/docker/client"
)

func must(err error) {
	if err != nil {
		log.Fatalln(err)
	}
}

func main() {
	cli, err := client.NewClientWithOpts()
	must(err)
	ctx, cancel := context.WithCancel(context.Background())
	defer cancel()

	token := os.Getenv("CR_PAT")
	authCfg := types.AuthConfig{
		Username:      "sohnryang",
		Password:      token,
		ServerAddress: "ghcr.io",
	}
	res, err := cli.RegistryLogin(ctx, authCfg)
	must(err)
	log.Printf("Token: %q\n", res.IdentityToken)
	log.Printf("Status: %s\n", res.Status)

	credJson, err := json.Marshal(authCfg)
	must(err)
	cred := base64.StdEncoding.EncodeToString(credJson)
	r, err := cli.ImagePull(ctx, "ghcr.io/sohnryang/simpleserver", types.ImagePullOptions{
		RegistryAuth: cred,
	})
	must(err)
	defer r.Close()
	io.Copy(os.Stdout, r)
}
