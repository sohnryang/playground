const hre = require("hardhat");

async function main() {
  const contractAddr = process.env.CONTRACT_ADDR;
  const simpleStorage = await hre.ethers.getContractAt("Storage", contractAddr);

  console.log(`Stored value: ${await simpleStorage.get()}`);
}

main().catch((error) => {
  console.error(error);
  process.exitCode = 1;
});
