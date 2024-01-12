// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.13;

import {Test, console2} from "forge-std/Test.sol";
import {Counter} from "../src/Counter.sol";

contract CounterTest is Test {
    Counter public counter;

    function setUp() public {
        counter = new Counter();
        counter.setNumber(0);
    }

    function test_Increment() public {
        counter.increment();
        assertEq(counter.number(), 1);
    }

    function test_IncrementAsNotOwner() public {
        vm.prank(address(0));
        counter.increment();
        assertEq(counter.number(), 1);
    }

    function test_Decrement() public {
        counter.setNumber(1);
        counter.derecrement();
        assertEq(counter.number(), 0);
    }

    function test_DecrementBelowZero() public {
        vm.expectRevert(Counter.NumberIsZero.selector);
        counter.derecrement();
        assertEq(counter.number(), 0);
    }

    function testFuzz_SetNumber(uint256 x) public {
        counter.setNumber(x);
        assertEq(counter.number(), x);
    }
}
