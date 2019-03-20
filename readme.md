HW03
===
This is the hw03 sample. Please follow the steps below.

# Build the Sample Program

1. Fork this repo to your own github account.

2. Clone the repo that you just forked.

3. Under the hw03 dir, use:

	* `make` to build.

	* `make clean` to clean the ouput files.

4. Extract `gnu-mcu-eclipse-qemu.zip` into hw03 dir. Under the path of hw03, start emulation with `make qemu`.

	See [Lecture 02 ─ Emulation with QEMU] for more details.

5. The sample is a minimal program for ARM Cortex-M4 devices, which enters `while(1);` after reset. Use gdb to get more details.

	See [ESEmbedded_HW02_Example] for knowing how to do the observation and how to use markdown for taking notes.

# Build Your Own Program

1. Edit main.c.

2. Make and run like the steps above.

3. Please avoid using hardware dependent C Standard library functions like `printf`, `malloc`, etc.

# HW03 Requirements

1. How do C functions pass and return parameters? Please describe the related standard used by the Application Binary Interface (ABI) for the ARM architecture.
~
2. Modify main.c to observe what you found.

3. You have to state how you designed the observation (code), and how you performed it.

	Just like how you did in HW02.

3. If there are any official data that define the rules, you can also use them as references.

4. Push your repo to your github. (Use .gitignore to exclude the output files like object files or executable files and the qemu bin folder)

[Lecture 02 ─ Emulation with QEMU]: http://www.nc.es.ncku.edu.tw/course/embedded/02/#Emulation-with-QEMU
[ESEmbedded_HW02_Example]: https://github.com/vwxyzjimmy/ESEmbedded_HW02_Example

--------------------

- [ ] **If you volunteer to give the presentation next week, check this.**

--------------------

**★★★ Please take your note here ★★★**

將設計完的main.c檔執行make，make完觀察反組譯後結果為`arm-none-eabi-objdump -D main.elf`，並參考 [Procedure Call Standard for the ARM Architecture](http://infocenter.arm.com/help/topic/com.arm.doc.ihi0042f/IHI0042F_aapcs.pdf) 知道核心暫存器與
參數的傳遞的規則。

```main.c

int add(int a,int b,int c,int d)
{
	return a+b+c+d;
}

void reset_handler(void)
{
	int sum=0;
	sum=add(5,10,15,20);
	while (1)
	;
}
```

```assembly
00000030 <reset_handler>:
  30:	b580      	push	{r7, lr}       -> r7 儲存sp的位址、lr 保護以免破壞之前的數據
  32:	b082      	sub	sp, #8
  34:	af00      	add	r7, sp, #0
  36:	2300      	movs	r3, #0         -> r3 = 0
  38:	607b      	str	r3, [r7, #4]   -> 儲存 r3 (位址4)到stack(r7)
  3a:	2005      	movs	r0, #5         -> r0 = 5
  3c:	210a      	movs	r1, #10        -> r1 = 10
  3e:	220f      	movs	r2, #15        -> r2 = 15
  40:	2314      	movs	r3, #20        -> r3 = 20
  42:	f7ff ffe1 	bl	8 <add>
  46:	6078      	str	r0, [r7, #4]   -> 儲存 r0 (位址4)到stack(r7)
  48:	e7fe      	b.n	48 <reset_handler+0x18>
  4a:	bf00      	nop

00000008 <add>:
   8:	b480      	push	{r7}
   a:	b085      	sub	sp, #20
   c:	af00      	add	r7, sp, #0
   e:	60f8      	str	r0, [r7, #12]  -> 儲存 r0 (位址12)到stack(r7)
  10:	60b9      	str	r1, [r7, #8]   -> 儲存 r1 (位址8)到stack(r7)
  12:	607a      	str	r2, [r7, #4]   -> 儲存 r2 (位址4)到stack(r7)
  14:	603b      	str	r3, [r7, #0]   -> 儲存 r3 (位址0)到stack(r7)
  16:	68fa      	ldr	r2, [r7, #12]  -> 從stack上的變量搬到r2
  18:	68bb      	ldr	r3, [r7, #8]   -> 從stack上的變量搬到r3
  1a:	441a      	add	r2, r3
  1c:	687b      	ldr	r3, [r7, #4]   -> 從stack上的變量搬到r3
  1e:	441a      	add	r2, r3
  20:	683b      	ldr	r3, [r7, #0]   -> 從stack上的變量搬到r3
  22:	4413      	add	r3, r2
  24:	4618      	mov	r0, r3         -> 準備回傳值 r0=5+10+15+20=50
  26:	3714      	adds	r7, #20
  28:	46bd      	mov	sp, r7
  2a:	f85d 7b04 	ldr.w	r7, [sp], #4
  2e:	4770      	bx	lr


```
