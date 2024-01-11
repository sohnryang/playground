const hre = require("hardhat");

async function main() {
  const simpleStorage = await hre.ethers.deployContract("Storage", [0]);

  console.log(`Storage address: ${await simpleStorage.getAddress()}`);
}

main().catch((error) => {
  console.error(error);
  process.exitCode = 1;
});
