const hre = require("hardhat");

async function main() {
  const contractAddr = process.env.CONTRACT_ADDR;
  const simpleStorage = await hre.ethers.getContractAt("Storage", contractAddr);
  const storedValue = await simpleStorage.get();

  console.log(`Stored value (before increment): ${storedValue}`);
  await simpleStorage.set(storedValue + 1n);
  console.log(`Stored value (after increment): ${await simpleStorage.get()}`);
}

main().catch((error) => {
  console.error(error);
  process.exitCode = 1;
});
