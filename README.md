# SimpleMatrixLib - [*Visual Studio fork*](https://blekenbleu.github.io/static/ImageProcessing/matrix.htm)
A simple C++ stdlib-based complex &amp; real matrix library,  
&emsp; with matrix inversion, [left division (A\b)](https://help.altair.com/compose/help/en_us/topics/language_guides/left_matrix_division_r.htm) and determinant calculation.<br />

## Features
* Designed for users who don't want to use large linear algebra libs.
* Only used C++ standard library, easy to learn and modify (Each file less than 600 lines).
* Header files only, separated complex and real matrix library.
* No recursive algorithm (using LU and Cholesky decomposition).  
  Reliable for 1000 x 1000 and larger matrices.


## Available Functions
* <b>rank</b>:    Matrix rank ([Cholesky decomposition](https://www.geeksforgeeks.org/maths/cholesky-factorization/))
* <b>det</b>:     Matrix [determinant](https://www.geeksforgeeks.org/maths/what-is-determinant-of-a-matrix/) calculation
* <b>inv</b>:     [LU decomposition-based](https://www.geeksforgeeks.org/engineering-mathematics/l-u-decomposition-system-linear-equations/) matrix inversion
* <b>pinv</b>:    pinv(G) = inv(G' * G) * G' (<b>WARNING</b>: [full-rank matrix](https://fiveable.me/linear-algebra-and-differential-equations/key-terms/full-rank-matrix) only!)
* <b>pinv2</b>:   [Moore-Penrose pseudoinversion](https://www.math.ucla.edu/~laub/33a.2.12s/mppseudoinverse.pdf) (same as pinv(G) in MATLAB)
* <b>[leftDiv</b>: x = A \ b](https://help.altair.com/compose/help/en_us/topics/language_guides/left_matrix_division_r.htm),
	using Moore-Penrose pinv, NOT same as MATLAB for a [singular matrix](https://en.wikipedia.org/wiki/Singular_matrix)


## Real matrix examples
```cpp
#include "matBasic_real.hpp"
/*
 ; using i_real_matrix = std::vector<std::vector<double>>;
 */
int main(int argc, char **argv)
{
	i_real_matrix matC = {
        {1.0, 2.0, 3.0, 5.0},
        {2.0, 5.0, 3.0, 6.0},
        {0.0, 4.0, 1.0, 5.0},
        {-6.0, 3.0, 9.0, 1.0}};
    std::cout << "rank(matC) = " << rank(matC) << "\n";
    showMatrix(matC, "matC");
    showMatrix(inv(matC), "inv(matC)");
    showMatrix(pinv(matC), "pinv(matC)");
    showMatrix(pinv2(matC), "pinv2(matC)");
    std::cout << "\n\n";

    i_real_matrix matD = {
        {1.0, 2.0, 3.0, 5.0},
        {2.0, 5.0, 3.0, 6.0},
        {0.0, 4.0, 1.0, 5.0},
        {-6.0, 3.0, 9.0, 1.0},
        {1.0, 1.0, 4.0, 5.0}};
    std::cout << "rank(matD) = " << rank(matD) << "\n";
    showMatrix(matD, "matD");
    showMatrix(pinv(matD), "pinv(matD)");
    showMatrix(pinv2(matD), "pinv2(matD)");
	showMatrix(leftDiv(matD, matb), "D \\ b (pinv2(D) * b)");
    std::cout << "\ndone.\n\n";
    std::cin.get();
    return 0;
}
```
### Output
```
rank(matC) = 4
matC : 4 x 4 Real Matrix:
    row[1]: 1,  2,  3,  5;
    row[2]: 2,  5,  3,  6;
    row[3]: 0,  4,  1,  5;
    row[4]: -6,  3,  9,  1;

inv(matC) : 4 x 4 Real Matrix:
    row[1]: -0.0334347,  0.334347,  -0.355623,  -0.0607903;
    row[2]: -0.431611,  0.316109,  0.0455927,  0.0334347;
    row[3]: 0.0851064,  0.148936,  -0.276596,  0.0638298;
    row[4]: 0.328267,  -0.282675,  0.218845,  -0.0395137;

pinv(matC) : 4 x 4 Real Matrix:
    row[1]: -0.0334347,  0.334347,  -0.355623,  -0.0607903;
    row[2]: -0.431611,  0.316109,  0.0455927,  0.0334347;
    row[3]: 0.0851064,  0.148936,  -0.276596,  0.0638298;
    row[4]: 0.328267,  -0.282675,  0.218845,  -0.0395137;

pinv2(matC) : 4 x 4 Real Matrix:
    row[1]: -0.0334347,  0.334347,  -0.355623,  -0.0607903;
    row[2]: -0.431611,  0.316109,  0.0455927,  0.0334347;
    row[3]: 0.0851064,  0.148936,  -0.276596,  0.0638298;
    row[4]: 0.328267,  -0.282675,  0.218845,  -0.0395137;


b : 5 x 1 Real Matrix:
    row[1]: 1;
    row[2]: 2;
    row[3]: 3;
    row[4]: 4;
    row[5]: 5;

rank(matD) = 4
matD : 5 x 4 Real Matrix:
    row[1]: 1,  2,  3,  5;
    row[2]: 2,  5,  3,  6;
    row[3]: 0,  4,  1,  5;
    row[4]: -6,  3,  9,  1;
    row[5]: 1,  1,  4,  5;

pinv(matD) : 4 x 5 Real Matrix:
    row[1]: -0.0361407,  0.334645,  -0.355048,  -0.0608445,  0.00178416;
    row[2]: -0.113013,  0.280993,  -0.0220854,  0.0398194,  -0.210058;
    row[3]: -0.00114908,  0.158443,  -0.258273,  0.0621012,  0.0568698;
    row[4]: 0.119108,  -0.259621,  0.263276,  -0.0437052,  0.137903;

pinv2(matD) : 4 x 5 Real Matrix:
    row[1]: -0.0361407,  0.334645,  -0.355048,  -0.0608445,  0.00178416;
    row[2]: -0.113013,  0.280993,  -0.0220854,  0.0398194,  -0.210058;
    row[3]: -0.00114908,  0.158443,  -0.258273,  0.0621012,  0.0568698;
    row[4]: 0.119108,  -0.259621,  0.263276,  -0.0437052,  0.137903;

D \ b (pinv2(matD) * matb) : 4 x 1 Real Matrix:
    row[1]: -0.666453;
    row[2]: -0.508292;
    row[3]: 0.0736727;
    row[4]: 0.904385;

done.
```

## References
* Pierre Courrieu, [Fast Computation of Moore-Penrose Inverse Matrices](https://arxiv.org/abs/0804.4809)
* [Permute Sign Calculation, page5](https://www.math.rutgers.edu/docman-lister/math-main/academics/course-materials/250/assignments/1493-250c-lab3-sakai-pdf/file)
* [LU Decomposition C++ Implementation](https://blog.csdn.net/xx_123_1_rj/article/details/39553809)
* [LU Decomposition](https://www.math.ucdavis.edu/~linear/old/notes11.pdf)  

*12 Jun 2026*:&nbsp; add `Test/matBasic_real_fileio.hpp` to load matrices from
	[corrCA](https://github.com/blekenbleu/CorrCA/tree/PPM) gnuplot data  
*13 Jun 2026*:
```
Time elapsed - read_gnuplotdata(): 1000 us
rank(xyG) = 9
rank(dxyRB) = 4
rank(mpxyG) = 10 Moore-Penrose pseudoinverse of xyG
Time elapsed - pinv2(xyG): 0 us
Time elapsed - matMul(mpxyG, dxyRB): 0 us
matMul(mpinv(xyG), dxyRB) : 10 x 4 Real Matrix:
    row[1]: 0.59695,  0.425711,  -0.424087,  -0.632403;
    row[2]: -0.137462,  0.880188,  -3.49798,  -1.99355;
    row[3]: 0.644413,  -0.512948,  -1.68163,  -1.42262;
    row[4]: -3.42902,  -1.19754,  7.77443,  1.95765;
    row[5]: -0.536702,  -1.17198,  1.93358,  2.28889;
    row[6]: 2.38586,  0.295538,  -5.31827,  0.0579299;
    row[7]: -0.140215,  0.787737,  -0.276673,  -1.58803;
    row[8]: -1.63431,  -1.54493,  2.9548,  3.99772;
    row[9]: 0.243646,  1.48698,  -0.118127,  -4.00873;
    row[10]: 1.4666,  0.210127,  -2.92785,  -0.120092;
```

<p align="center"><b>Project by <i>Fanseline in Ericsson</i></b></p>
