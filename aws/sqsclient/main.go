package main

import (
	"encoding/json"
	"log"

	"github.com/aws/aws-sdk-go/aws"
	"github.com/aws/aws-sdk-go/aws/session"
	"github.com/aws/aws-sdk-go/service/sqs"
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
	sess := session.Must(session.NewSession(&aws.Config{
		Endpoint: aws.String("http://localhost:4566"), // localstack endpoint
	}))
	svc := sqs.New(sess)

	listResult, err := svc.ListQueues(nil)
	must(err)
	log.Println("ListQueues result:")
	log.Println(listResult)

	createResult, err := svc.CreateQueue(&sqs.CreateQueueInput{
		QueueName: aws.String("testqueue"),
	})
	must(err)
	log.Println("CreateQueue result:")
	log.Println(createResult)
	u := createResult.QueueUrl

	sendResult, err := svc.SendMessage(&sqs.SendMessageInput{
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
	sendResult, err = svc.SendMessage(&sqs.SendMessageInput{
		MessageBody: aws.String(string(b)),
		QueueUrl:    u,
	})
	must(err)
	log.Println("SendMessage result:")
	log.Println(sendResult)

	recvResult, err := svc.ReceiveMessage(&sqs.ReceiveMessageInput{
		QueueUrl: u,
	})
	must(err)
	log.Println("ReceiveMessage result:")
	log.Println(recvResult)

	recvResult, err = svc.ReceiveMessage(&sqs.ReceiveMessageInput{
		QueueUrl: u,
	})
	must(err)
	log.Println("ReceiveMessage result:")
	log.Println(recvResult)

	deleteResult, err := svc.DeleteQueue(&sqs.DeleteQueueInput{
		QueueUrl: u,
	})
	must(err)
	log.Println("DeleteQueue result:")
	log.Println(deleteResult)
}
