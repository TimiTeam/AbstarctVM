# AbstarctVM

AbstractVM is a machine that uses a stack to compute simple arithmetic expressions.
These arithmetic expressions are provided to the machine as basic assembly programs.

As for any assembly language, the language of AbstractVM is composed of a series of
instructions, with one instruction per line.

						Instuctions:

/>  ; comments

> push v: push value at the top of stack
	int8(n)
	int16(n)
	int32(n)
	float(n)
	double(n)

> pop: unstack value from yhe top of stack

> dump: display each value of the stack

> assert v: assert that the value at the top of the stack is equal. If is't, the program is exit

> add: get two value from the top of the stack, adds them and put the result at top

> sub: get two value from the top of the stack, subtracts them and put the result at top

> mul:  get two value from the top of the stack, multiply them and put the result at top

> div: getting two value from the top of the stack, divides them and put the result at top

> mod: getting two value from the top of the stack, calculates the modulus and put the result at top

> print: assert that the value at top of stack is an 8-bit integer. If it's, display its ASCII character otherwise assert

> exit: terminaye the execution of current program


