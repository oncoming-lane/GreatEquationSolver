#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED


/**ASSERT
*@param logical expression
@brief
*/
#define ASSERT(cond) \
    if (!(cond)) printf("Error in the expression (%s) in line %d ", #cond, __LINE__);  \
    else printf("OK! ");


const int INF = -1;
const double EPS  = 1e-4;
int eq_0(double a);
int eq(double a, double b);
int square_equation(double a, double b, double c, double *x1, double *x2);
int linear_equation(double b, double c, double *x1);

void test_once(double a, double b, double c, int i);
void testing();

#endif // FUNC_H_INCLUDED