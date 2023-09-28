import pwn
import unicorn as uc
import unicorn.x86_const as uc86
from pwnlib.asm import asm

pwn.context.arch = "x86_64"

BASE = 0x400000
STACK_ADDR = 0x0
STACK_SIZE = 1024 * 1024


def hook(mu, addr, size, user_data):
    print(f"Tracing instruction @ {addr:#010x}, size {size}")


mu = uc.Uc(uc.UC_ARCH_X86, uc.UC_MODE_64)
mu.hook_add(uc.UC_HOOK_CODE, hook)
mu.mem_map(BASE, 1024 * 1024)
asm_code = """
    xorq rax, rax
    subq rax, 1
    cmpq rax, 2
    setl al
    movzbq rax, al
"""
compiled_code = asm(asm_code)
mu.mem_write(BASE, compiled_code)
mu.mem_map(STACK_ADDR, STACK_SIZE, uc.UC_PROT_ALL)
mu.reg_write(uc86.UC_X86_REG_RSP, STACK_ADDR + STACK_SIZE - 1)
mu.reg_write(uc86.UC_X86_REG_RIP, BASE)
mu.emu_start(BASE, BASE + len(compiled_code))

print(f"rax: {mu.reg_read(uc86.UC_X86_REG_RAX):#010x}")
print(f"rip: {mu.reg_read(uc86.UC_X86_REG_RIP):#010x}")
