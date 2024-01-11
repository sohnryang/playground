const { expect } = require("chai");

describe("Storage", function () {
  it("Should return the new value once it's changed", async function () {
    const storage = await ethers.deployContract("Storage", [0]);
    await storage.set(42);
    const storedData = await storage.get();
    expect(storedData).to.equal(42);
  });
});
