#pragma once
#include <fstream>
typedef unsigned char uchar;
#define FOLDER "R:/Temp/"

int read_gnuplotdata(i_real_matrix &xyG, i_real_matrix &dxyRB)
{
	char b[401]{}, *str_d = "", *str_end = "",
		fname[] = FOLDER "Before_redefineG.txt",
//		fname[] = "../../../Test/Before_redefineG.txt",
		line2[] = "xG,yG,dxR,dyR,dxB,dyB,sxR,syR,sxB,syB";
	double xG,yG,dxR,dyR,dxB,dyB;
	int len, row, rows = 0;
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
	}

	rows = strtol(7 + b, &str_end, 10);
	f.getline(b, 40, '\n');
	b[41] = '\0';
	if (0 != strncmp(b, line2, 37)) {
		printf("\"%s\" not found!\n", line2);
		return -3;
	}

	xyG = initRealMatrix(rows, 10);
	dxyRB = initRealMatrix(rows, 4);
	for (row = 0; row < rows && f.good(); row++) {
		// 10 comma-separated floats per line; want the first 6
		f.getline(b, 400, '\n');
		if (100 > (len = (int)f.gcount()))
			printf("unexpected data line at row %d:\n\t%s\n", row, b);
		xG = strtod(str_d = b, &str_end);
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
		/* now build xyG and dxyRB matrix rows
		 ; see CorrCA PPM report.cpp gnuplot2file()
		 ; https://github.com/blekenbleu/CorrCA/blob/PPM/src/report.cpp#L121
		 ; linearly independent polynomial (green image blob normalized x,y)
		 */
		xyG[row][0] = 1.0; xyG[row][1] = xG; xyG[row][2] = yG; xyG[row][3] = xG*xG;
		xyG[row][4] = yG*yG; xyG[row][5] = xG*xG*xG; xyG[row][6] = yG*yG*yG;
		xyG[row][7] = xG*yG;  xyG[row][8] = xG*xG*yG;  xyG[row][9] = xG*yG*yG;
		// dependent columns: Red, Blue x,y blob offsets
		dxyRB[row][0] = dxR; dxyRB[row][1] = dyR; dxyRB[row][2] = dxB; dxyRB[row][3] = dyB;
	}
	if (!f.good()) {
		f.close();
		printf("reading %s failed at row %d\n", fname, row);
		return -4;
	}
		
	f.close();
	return 0;
}
