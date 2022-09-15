package main

import (
	"fmt"
	"log"

	"gopkg.in/yaml.v3"
)

type Account struct {
	Username     string `yaml:"username"`
	PasswordHash string `yaml:"password_hash"`
	Email        string `yaml:"email"`
}

var data = `
username: Alice
password_hash: 6b3a55e0261b0304143f805a24924d0c1c44524821305f31d9277843b8a10f4e
email: alice@bobcorp.com
`

func main() {
	john := Account{
		Username:     "JohnDoe",
		PasswordHash: "6b3a55e0261b0304143f805a24924d0c1c44524821305f31d9277843b8a10f4e",
		Email:        "john@example.com",
	}

	d, err := yaml.Marshal(&john)
	if err != nil {
		log.Fatal(err)
	}
	fmt.Printf("YAML dump:\n---\n%s---\n\n", string(d))

	alice := Account{}
	if err := yaml.Unmarshal([]byte(data), &alice); err != nil {
		log.Fatal(err)
	}
	fmt.Printf("Unmarshaled struct:\n---\n%v\n---\n", alice)
}
