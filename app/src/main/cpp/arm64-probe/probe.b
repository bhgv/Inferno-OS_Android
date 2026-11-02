implement Native64AndroidProbe;

Native64AndroidProbe: module {
	init: fn(); # Sole pointer-free entry; no native module imports.
};

tally: int;
a := 12345;
b := 789;
result: int;
checks: int;


# Renew the local, update shared state and deliver a fresh Word result on every call.
step(amount: int): int
{
	local: int;
	local++;
	tally += local*amount;
	return tally;
}


# Compute a Word result into the exact destination owned by the original caller.
fold(x: int, y: int): int
{
	checks++;
	return ((x^y)&65535)|65536;
}


# Preserve the original result destination across one more active helper depth.
forward(x: int, y: int): int
{
	checks++;
	return fold(x, y);
}


# Exercise an eight-byte arithmetic result without changing the declared Big argument.
wide(value: big): big
{
	checks++;
	return value+big 1;
}


# Preserve exact Real bits through a typed result store rather than a native pointer.
fraction(value: real): real
{
	checks++;
	return value;
}


# Check repeated/nested results, numeric cases and live caller Big/Real storage.
init()
{
	large := wide(big 16);
	decimal := fraction(1.25);
	for(i := 0; i < 4097; i++){
		count := step(1);
		if(count != i+1)
			result /= 0;
	}
	case tally {
	4097 => result = forward(a, b);
	* => result /= 0;
	}
	if(result != 78636 || tally != 4097 || checks != 4 || large != big 17 || decimal != 1.25)
		result /= 0;
}
