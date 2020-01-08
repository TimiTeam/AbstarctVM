# AbstarctVM

AbstractVM is a machine that uses a stack to compute simple arithmetic expressions.
These arithmetic expressions are provided to the machine as basic assembly programs.

As for any assembly language, the language of AbstractVM is composed of a series of
instructions, with one instruction per line.

						Instuctions:

> <b> ; </b> comments

> <b>push <i>v</i></b>: push value at the top of stack
	int8(n)
	int16(n)
	int32(n)
	float(n)
	double(n)

> <b>pop</b>: unstack value from yhe top of stack

> <b>dump</b>: display each value of the stack

> <b>assert <i>v</i></b>: assert that the value at the top of the stack is equal. If is't, the program is exit

> <b>add</b>: get two value from the top of the stack, adds them and put the result at top

> <b>sub</b>: get two value from the top of the stack, subtracts them and put the result at top

> <b>mul</b>:  get two value from the top of the stack, multiply them and put the result at top

> <b>div</b>: getting two value from the top of the stack, divides them and put the result at top

> <b>mod</b>: getting two value from the top of the stack, calculates the modulus and put the result at top

> <b>print</b>: assert that the value at top of stack is an 8-bit integer. If it's, display its ASCII character otherwise assert

> <b>exit</b>: terminaye the execution of current program


