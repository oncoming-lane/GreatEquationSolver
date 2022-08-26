#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "func.h"
#include "test.h"

/**mode
*@brief offers the user to choose where to get the data from
*/
int mode() {

    printf("where will the data be entered from?\n1 - console\n2 - file\n");

    int mode = NAN;

    while ( ((scanf("%d", &mode)) != 1) && (mode != 1) && (mode != 2)  )
        printf("Error!");

    return mode;
}


/** eq
Compares fractional numbers
@param a,b compared numbers
@return equal numbers or not
*/
int eq(double a, double b){
    return fabs(a - b) < EPS;
}


/**eq_0
Compares fractional number
@param a compared with zero number
@return equal number zero or not
*/
int eq_0(double a){
    return fabs(a-0) < EPS;
}



/**square_equation
solves the quadratic equation
*\param a,b,c Coefficients of the equation
*\param *x1,*x2 References to variables containing the roots of the equation
*\return number of solutions
*/
int square_equation(double a, double b, double c, double *x1, double *x2){

    ASSERT(x1 == NULL);
    ASSERT(x2 == NULL);

    assert_isfinite(a);
    assert_isfinite(b);
    assert_isfinite(c);

    if (eq_0(a)) {
        int ans = linear_equation(b, c, x1);
        if (ans == 1) *x2 = *x1;
        return ans;
    }

    else{
        double d = b*b - 4*a*c;
        if (eq_0(d)) {
            *x1 = *x2 = -b / (2*a);
             return ONE_ROOT;
        }

        else if (d < 0) return ABSENCE_ROOTS;

        else {
            double sd = sqrt(d);
            *x1 = -(b+sd) / (2*a);
            *x2 = -(b-sd) / (2*a);
            return TWO_ROOTS;
        }

    }
}


/**linear_equation
*@brief Solves the linear equation
*@param a,b - Coefficients of the equation
*@param *x1 Reference to variable containing the root of the equation
*@return number of solutions
*/
int linear_equation(double b, double c, double *x1){

    ASSERT(x1 == NULL);

    assert_isfinite(b);
    assert_isfinite(c);

    if (eq_0(b) && eq_0(c))  return INFINITE_ROOTS;

    if (eq_0(b) && !eq_0(c)) return ABSENCE_ROOTS;

    else *x1 = (-c) / b; return ONE_ROOT;
}



/**input
*@brief reads data from the console and writes it to variables at their address
 when errors occur, it issues a message
@param *a,*b,*c - variable addresses
*/
void input(double *a, double *b, double *c) {


    ASSERT(a == NULL);
    ASSERT(b == NULL);
    ASSERT(c == NULL);

    printf("\nDATA FROM THE CONSOLE\n");
    printf("Enter the coefficients of the equation (a, b, c): ");

    int n = scanf("%lf %lf %lf", a, b, c);
    while(1){
        if (n != 3) {
            pretty_input();
            n = scanf("%lf %lf %lf", a, b, c);
        }
        else{
            assert_isfinite(*a);
            assert_isfinite(*b);
            assert_isfinite(*c);
            break;
        }
    }

 }


/**auxiliary input function*/
void pretty_input(){
    while (getchar()!='\n');
    fprintf(stderr, "ERROR!\nEnter the coefficients of the equation again:");
}


/**file_input
*@brief reads data from a file and writes it to variables at their address
*@param *a,*b,*c - variable addresses
*@param *fp - pointer to the file
*/
void file_input(double *a, double *b, double *c, FILE *fp) {

    int n = fscanf(fp, "%lf %lf %lf", a, b, c);
    if (n != 3)
        printf("ERROR! Enter the coefficients of the equation in file again!/n");

}


/**file_data
*@brief provides work with data in a file
*/
void file_data(){

    printf("\nDATA FROM THE FILE\n");
    char file_name[] = "data_imput.txt";
    FILE *fp = fopen(file_name, "r");

    if (fp == NULL){
        printf("error! file hasn't opened");
        abort();
    }

    while(!feof(fp)){
        double a = NAN, b = NAN, c = NAN;
        file_input(&a, &b, &c, fp);
        solve_and_output(a, b, c);
    }

    fclose(fp);
}


/**assert_isfinite
*@brief checks the number for its finiteness
*/
void assert_isfinite(double x){
    ASSERT(!(isfinite(x)));
}


/**solve_and_output
*@brief the function starts solving the
  equation and displays the result of its work on the screen
*@param *a,*b,*c - variables ( Coefficients of the equation)

  */
void solve_and_output(double a, double b, double c) {

    assert_isfinite(a);
    assert_isfinite(b);
    assert_isfinite(c);

    double x1 = NAN, x2 = NAN;
    printf("The equation is: (%.2lg)*x^2  + (%.2lg)*x + (%.2lg) = 0\n", a, b, c);

    switch(square_equation(a, b, c, &x1, &x2)){
        case 0:   printf("This equation doesn't have roots\n");                          break;
        case 1:   printf("This equation has 1 root: x = %.2lf\n", x1);                   break;
        case 2:   printf("This equation has 2 roots: x1 = %.2lf, x2 = %.2lf\n", x1, x2); break;
        case INF: printf("This equation have infinite roots\n");                         break;
        default:  abort();
    }

    printf("Checking: ");
    test_once(a, b, c, 0);
    printf("\n");
}
