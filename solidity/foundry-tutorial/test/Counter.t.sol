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

    function test_ExpectEmit_Increment() public {
        vm.expectEmit(false, false, false, true);
        emit Counter.Incremented(1);
        counter.increment();
    }

    function test_ExpectEmit_Decrement() public {
        counter.setNumber(1);
        vm.expectEmit(false, false, false, true);
        emit Counter.Decremented(0);
        counter.derecrement();
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
