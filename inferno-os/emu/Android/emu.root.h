int rootmaxq = 12;
Dirtab roottab[12] = {
	"",	{0, 0, QTDIR},	 0,	0555,
	"dev",	{1, 0, QTDIR},	 0,	0555,
	"fd",	{2, 0, QTDIR},	 0,	0555,
	"prog",	{3, 0, QTDIR},	 0,	0555,
	"prof",	{4, 0, QTDIR},	 0,	0555,
	"net",	{5, 0, QTDIR},	 0,	0555,
	"net.alt",	{6, 0, QTDIR},	 0,	0555,
	"chan",	{7, 0, QTDIR},	 0,	0555,
	"nvfs",	{8, 0, QTDIR},	 0,	0555,
	"env",	{9, 0, QTDIR},	 0,	0555,
	"n",	{10, 0, QTDIR},	 0,	0555,
	"gui",	{11, 0, QTDIR},	 0,	0555,
};
Rootdata rootdata[12] = {
	0,	 &roottab[1],	 11,	nil,
	0,	 nil,	 0,	 nil,
	0,	 nil,	 0,	 nil,
	0,	 nil,	 0,	 nil,
	0,	 nil,	 0,	 nil,
	0,	 nil,	 0,	 nil,
	0,	 nil,	 0,	 nil,
	0,	 nil,	 0,	 nil,
	0,	 nil,	 0,	 nil,
	0,	 nil,	 0,	 nil,
	0,	 nil,	 0,	 nil,
	0,	 nil,	 0,	 nil,
};
