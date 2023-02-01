package main

import (
	"context"
	"encoding/json"
	"flag"
	"log"

	"github.com/aws/aws-sdk-go-v2/aws"
	"github.com/aws/aws-sdk-go-v2/config"
	"github.com/aws/aws-sdk-go-v2/service/sqs"
)

type Data struct {
	BoolData bool   `json:"bool"`
	IntData  int    `json:"int"`
	StrData  string `json:"str"`
}

func must(err error) {
	if err != nil {
		log.Fatal(err)
	}
}

func main() {
	endpointFlag := flag.String("endpoint", "", "AWS endpoint URL")
	flag.Parse()
	ctx := context.TODO()
	cfg, err := config.LoadDefaultConfig(ctx,
		config.WithEndpointResolver(
			aws.EndpointResolverFunc(
				func(service, region string) (aws.Endpoint, error) {
					if *endpointFlag != "" {
						return aws.Endpoint{
							URL:         *endpointFlag,
							PartitionID: "aws",
						}, nil
					}
					return aws.Endpoint{}, &aws.EndpointNotFoundError{}
				})),
	)
	must(err)
	log.Println(cfg)
	svc := sqs.NewFromConfig(cfg)
	log.Println(svc)

	listResult, err := svc.ListQueues(ctx, nil)
	must(err)
	log.Println("ListQueues result:")
	log.Println(listResult)

	createResult, err := svc.CreateQueue(ctx, &sqs.CreateQueueInput{
		QueueName: aws.String("testqueue"),
	})
	must(err)
	log.Println("CreateQueue result:")
	log.Println(createResult)
	u := createResult.QueueUrl

	sendResult, err := svc.SendMessage(ctx, &sqs.SendMessageInput{
		MessageBody: aws.String("hell world!"),
		QueueUrl:    u,
	})
	must(err)
	log.Println("SendMessage result:")
	log.Println(sendResult)

	d := Data{
		BoolData: true,
		IntData:  42,
		StrData:  "hell world!",
	}
	b, err := json.Marshal(d)
	must(err)
	sendResult, err = svc.SendMessage(ctx, &sqs.SendMessageInput{
		MessageBody: aws.String(string(b)),
		QueueUrl:    u,
	})
	must(err)
	log.Println("SendMessage result:")
	log.Println(sendResult)

	recvResult, err := svc.ReceiveMessage(ctx, &sqs.ReceiveMessageInput{
		QueueUrl: u,
	})
	must(err)
	log.Println("ReceiveMessage result:")
	log.Println(recvResult)

	recvResult, err = svc.ReceiveMessage(ctx, &sqs.ReceiveMessageInput{
		QueueUrl: u,
	})
	must(err)
	log.Println("ReceiveMessage result:")
	log.Println(recvResult)
}
