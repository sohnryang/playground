import { expect } from "chai";
import hre from "hardhat";

describe("Coin", function () {
  it("Coins should be given to the minter after minting", async function () {
    const [minter] = await hre.ethers.getSigners();
    const coin = await hre.ethers.deployContract("Coin");

    await coin.mint(minter.address, 100);

    const minterBalance = await coin.balances(minter.address);
    expect(minterBalance).to.equal(100);
  });

  it("Coins should be given to the receiver after being sent", async function () {
    const [minter, receiver] = await hre.ethers.getSigners();
    const coin = await hre.ethers.deployContract("Coin");

    await coin.mint(minter.address, 100);
    await coin.send(receiver.address, 50);

    expect(await coin.balances(minter.address)).to.equal(50);
    expect(await coin.balances(receiver.address)).to.equal(50);
  });

  it("Sending more coins than you have should fail", async function () {
    const [minter, receiver] = await hre.ethers.getSigners();
    const coin = await hre.ethers.deployContract("Coin");

    await coin.mint(minter.address, 100);
    await expect(
      coin.send(receiver.address, 150)
    ).to.be.revertedWithCustomError(coin, "InsufficientBalance");
  });

  it("Sending coins should emit a Sent event", async function () {
    const [minter, receiver] = await hre.ethers.getSigners();
    const coin = await hre.ethers.deployContract("Coin");

    await coin.mint(minter.address, 100);
    await expect(coin.send(receiver.address, 50))
      .to.emit(coin, "Sent")
      .withArgs(minter.address, receiver.address, 50);
  });

  it("Only the minter should be able to mint coins", async function () {
    const [_, nonMinter] = await hre.ethers.getSigners();
    const coin = await hre.ethers.deployContract("Coin");

    await expect(
      coin.connect(nonMinter).mint(nonMinter.address, 100)
    ).to.be.revertedWith("only minter can mint coins");
  });
});
