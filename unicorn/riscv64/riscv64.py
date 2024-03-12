import pwnlib.context
import unicorn as uc
import unicorn.riscv_const as ucrv
from pwnlib.asm import asm, context

context.update(arch="riscv64")

BASE = 0x400000


def hook(mu, addr, size, user_data):
    print(f"Tracing instruction @ {addr:#010x}, size {size}")


mu = uc.Uc(uc.UC_ARCH_RISCV, uc.UC_MODE_RISCV64)
mu.hook_add(uc.UC_HOOK_CODE, hook)
mu.mem_map(BASE, 1024 * 1024)
asm_code = """
    lui x10, 74565
    addi x10, x10, 1656
"""
compiled_code = asm(asm_code)
mu.mem_write(BASE, compiled_code)
mu.reg_write(ucrv.UC_RISCV_REG_PC, BASE)
mu.emu_start(BASE, BASE + len(compiled_code))

print(f"x10: {mu.reg_read(ucrv.UC_RISCV_REG_X10):#010x}")
