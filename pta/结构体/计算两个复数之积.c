struct complex multiply(struct complex x, struct complex y)
{
    struct complex product;
    product.real=(x.real*y.real)+(x.imag*y.imag);
    product.imag=(x.real*y.imag)+(x.imag*y.real);

    return complex product;
}
