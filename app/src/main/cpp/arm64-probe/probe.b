implement Native64AndroidProbe;

Native64AndroidProbe: module {
	init: fn(); # Sole pointer-free entry; no native module imports.
};

tally: int;
a := 12345;
b := 789;
result: int;


# Each specialization must renew this local before incrementing it.
step()
{
	local: int;
	local++;
	tally += local;
}


# Check scalar arithmetic, numeric cases, caller storage and repeated helper calls.
init()
{
	wide := big 17;
	fraction := 1.25;
	for(i := 0; i < 4097; i++)
		step();
	case tally {
	4097 => result = ((a^b)&65535)|65536;
	* => result /= 0;
	}
	if(result != 78636 || tally != 4097 || wide != big 17 || fraction != 1.25)
		result /= 0;
}
