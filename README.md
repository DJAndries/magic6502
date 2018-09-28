# magic6502
#### Simple NMOS 6502 emulation library (without decimal mode)

## Building

Should build with gcc/make.
I used MinGW (32-bit) and MSYS to build this on Windows.

```
make
```

## API

### Initialization

```
magic6502_ctx* magic6502_init(void* app_ctx, unsigned char* (*ma)(void*, unsigned short));
```

Parameters:
- `app_ctx`: Pointer to an application context. Used in `ma` callback. Optional.
- `ma`: Callback for memory access. Parameters are the application context and memory address, respectively.
Should return pointer to the requested memory.

### Interrupts

```
void magic6502_interrupt(magic6502_ctx* ctx, char type);
```

Parameters:
- `ctx`: Pointer to the context returned from initialization.
- `type`: Type of interrupt to execute.
  - MAGIC6502_INT_BRK
  - MAGIC6502_INT_IRQ
  - MAGIC6502_INT_NMI
  - MAGIC6502_INT_RESET

### Execution

The library is designed to execute one instruction per `magic6502_exec` call.

```
unsigned char magic6502_exec(magic6502_ctx* ctx);
```

Parameters:
- `ctx`: Pointer to the context returned from initialization.

Returns amount of CPU "cycles" consumed during instruction execution. This is useful for timing.

### Memory access tracking

Basic memory access tracking is available via two variables in `magic6502_ctx`.
`address_accessed` will provide the accessed memory address from the last instruction, if any (0 if there was no memory access).
`is_last_instr_write` is a boolean which indicates whether the last instruction was a memory write.

### Cleanup

```
void magic6502_free(magic6502_ctx* ctx);
```

## Tests

### Test execution

Run `test` in the bin folder after building. It will execute all instructions in `functional_test.bin`.

Functional test is from https://github.com/Klaus2m5/6502_65C02_functional_tests
