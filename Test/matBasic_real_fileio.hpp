#pragma once
#include <fstream>
typedef unsigned char uchar;
#define FOLDER "R:/Temp/"

int read_gnuplotdata()
{
	char whitespace[] = " \t", fname[] = FOLDER "Before_redefineG.txt";
    char b[200]{}, *str_d = "", *str_end = "", line2[] = "xG,yG,dxR,dyR,dxB,dyB,sxR,syR,sxB,syB";
	double xG,yG,dxR,dyR,dxB,dyB;
	int len, rows = 0;
	std::ifstream f(fname, std::ios::binary);

	if (!f.is_open()) {
		printf("cannot read %s\n", fname);
		return -1;
	}

	f.getline(b, 19, '\n');
    len = (int)f.gcount();
    b[19] = '\0';
	if ('#' != b[0] || 0 != strncmp(b, "# rows ", 7)) {
		printf("# rows expected, not found!!\n");
		return -2;
	} else rows = strtol(7 + b, &str_end, 10);
	f.getline(b, 40, '\n');
	b[41] = '\0';
	if (0 != strncmp(b, line2, 37)) {
		printf("\"%s\" not found!\n", line2);
		return - 3;
	}
	for (int col, row = 0; row < rows && f.good(); row++) {
		// 10 comma-separated floats per line; want the first 6
		f.getline(b, 80, '\n');
		if (70 > (len = (int)f.gcount())
			printf("unexpected data line at row %d:\n\t%s\n", row, b);
		xG = strtod(str_d, &str_end);
		str_d = 1 + str_end;	// ignore ','
		yG = strtod(str_d, &str_end);
		str_d = 1 + str_end;
		dxR = strtod(str_d, &str_end);
		str_d = 1 + str_end;
		dyR = strtod(str_d, &str_end);
		str_d = 1 + str_end;
		dxB = strtod(str_d, &str_end);
		str_d = 1 + str_end;
		dyB = strtod(str_d, &str_end);
		// now build xyG and dxyRB matrix rows
	}
		
	return 0;
}
