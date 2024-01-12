// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.13;

contract Counter {
    uint256 public number;

    function setNumber(uint256 newNumber) public {
        number = newNumber;
    }

    event Incremented(uint256 newNumber);

    function increment() public {
        number++;
        emit Incremented(number);
    }

    error NumberIsZero();
    event Decremented(uint256 newNumber);

    function derecrement() public {
        if (number == 0) revert NumberIsZero();
        number--;
        emit Decremented(number);
    }
}
