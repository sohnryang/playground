package main

import (
	"context"
	"flag"
	"log"
	"os"
	"os/exec"
	"sync"
	"time"

	"github.com/firecracker-microvm/firecracker-go-sdk"
	"github.com/firecracker-microvm/firecracker-go-sdk/client/models"
	"github.com/google/uuid"
)

type metadata struct {
	Uuid string `json:"uuid"`
}

func startVm(ctx context.Context, wg *sync.WaitGroup, socketPath string, kernelImagePath string, rootfsImagePath string) {
	vmmCtx, vmmCancel := context.WithCancel(ctx)
	defer vmmCancel()

	fcBin, err := exec.LookPath("firecracker")
	if err != nil {
		log.Fatal(err)
	}
	machineOpts := []firecracker.Opt{}
	cmd := firecracker.VMCommandBuilder{}.
		WithBin(fcBin).
		WithSocketPath("/tmp/firecracker.socket").
		WithStdin(os.Stdin).
		WithStdout(os.Stdout).
		WithStderr(os.Stderr).
		Build(ctx)
	machineOpts = append(machineOpts, firecracker.WithProcessRunner(cmd))

	fcCfg := firecracker.Config{
		SocketPath:      "/tmp/firecracker.socket",
		KernelImagePath: kernelImagePath,
		KernelArgs:      "ro console=ttyS0 noapic reboot=k panic=1 pci=off nomodules",
		Drives: []models.Drive{{
			DriveID:      firecracker.String("1"),
			PathOnHost:   firecracker.String(rootfsImagePath),
			IsReadOnly:   firecracker.Bool(false),
			IsRootDevice: firecracker.Bool(true),
		}},
		MachineCfg: models.MachineConfiguration{
			VcpuCount:   firecracker.Int64(1),
			CPUTemplate: models.CPUTemplateC3,
			MemSizeMib:  firecracker.Int64(1024),
			Smt:         firecracker.Bool(true),
		},
		NetworkInterfaces: []firecracker.NetworkInterface{{
			CNIConfiguration: &firecracker.CNIConfiguration{
				NetworkName: "fcnet",
				IfName:      "veth0",
			},
		}},
	}
	m, err := firecracker.NewMachine(vmmCtx, fcCfg, machineOpts...)
	if err != nil {
		log.Fatal(err)
	}
	if err := m.Start(vmmCtx); err != nil {
		log.Fatal(err)
	}
	m.SetMetadata(vmmCtx, metadata{Uuid: uuid.New().String()})
	log.Println(fcCfg.NetworkInterfaces[0].StaticConfiguration.IPConfiguration.IPAddr.IP)
	defer m.StopVMM()
	defer wg.Done()
	<-ctx.Done()
}

func main() {
	var (
		socket, kernelImage, rootfsImage string
		timeout                          int
		wg                               sync.WaitGroup
	)
	flag.StringVar(&socket, "socket", "/tmp/firecracker.socket", "Path to firecracker socket")
	flag.StringVar(&kernelImage, "kernel", "vmlinux.bin", "Path to kernel image")
	flag.StringVar(&rootfsImage, "rootfs", "rootfs.ext4", "Path to rootfs image")
	flag.IntVar(&timeout, "timeout", 5, "VM termination timeout in seconds")
	flag.Parse()

	ctx, cancel := context.WithCancel(context.Background())
	log.Printf("Timer started: %d seconds", timeout)
	timer := time.NewTimer(time.Duration(timeout) * time.Second)

	log.Println("Starting a FC MVM...")
	wg.Add(1)
	go startVm(ctx, &wg, socket, kernelImage, rootfsImage)

	<-timer.C
	log.Println("Stopping MVM...")
	cancel()
	wg.Wait()
	os.Remove(socket)
}
