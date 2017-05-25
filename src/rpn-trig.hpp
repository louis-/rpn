//
void pi(void)
{
    number* pi = (number*)_stack->allocate_back(number::calc_size(), cmd_number);
    CHECK_MPFR(mpfr_const_pi(pi->_value.mpfr, floating_t::s_mpfr_rnd));
}

void d2r(void)
{
    MIN_ARGUMENTS(1);
    ARG_MUST_BE_OF_TYPE(0, cmd_number);

    mpfr_t pi;
    floating_t* left = &((number*)_stack->get_obj(0))->_value;

    mpfr_init(pi);
    CHECK_MPFR(mpfr_const_pi(pi, floating_t::s_mpfr_rnd));
    CHECK_MPFR(mpfr_mul(left->mpfr, left->mpfr, pi, floating_t::s_mpfr_rnd));
    CHECK_MPFR(mpfr_div_si(left->mpfr, left->mpfr, 180, floating_t::s_mpfr_rnd));
    mpfr_clear(pi);
}

void r2d(void)
{
    MIN_ARGUMENTS(1);
    ARG_MUST_BE_OF_TYPE(0, cmd_number);

    mpfr_t pi;
    floating_t* left = &((number*)_stack->get_obj(0))->_value;

    mpfr_init(pi);
    CHECK_MPFR(mpfr_const_pi(pi, floating_t::s_mpfr_rnd));
    CHECK_MPFR(mpfr_mul_si(left->mpfr, left->mpfr, 180, floating_t::s_mpfr_rnd));
    CHECK_MPFR(mpfr_div(left->mpfr, left->mpfr, pi, floating_t::s_mpfr_rnd));
    mpfr_clear(pi);
}

void rpn_sin(void)
{
    MIN_ARGUMENTS(1);
    ARG_MUST_BE_OF_TYPE(0, cmd_number);

    floating_t* left = &((number*)_stack->get_obj(0))->_value;
    CHECK_MPFR(mpfr_sin(left->mpfr, left->mpfr, floating_t::s_mpfr_rnd));
}

void rpn_asin(void)
{
    MIN_ARGUMENTS(1);
    ARG_MUST_BE_OF_TYPE(0, cmd_number);

    floating_t* left = &((number*)_stack->get_obj(0))->_value;
    CHECK_MPFR(mpfr_asin(left->mpfr, left->mpfr, floating_t::s_mpfr_rnd));
}

void rpn_cos(void)
{
    MIN_ARGUMENTS(1);
    ARG_MUST_BE_OF_TYPE(0, cmd_number);

    floating_t* left = &((number*)_stack->get_obj(0))->_value;
    CHECK_MPFR(mpfr_cos(left->mpfr, left->mpfr, floating_t::s_mpfr_rnd));
}

void rpn_acos(void)
{
    MIN_ARGUMENTS(1);
    ARG_MUST_BE_OF_TYPE(0, cmd_number);

    floating_t* left = &((number*)_stack->get_obj(0))->_value;
    CHECK_MPFR(mpfr_acos(left->mpfr, left->mpfr, floating_t::s_mpfr_rnd));
}

void rpn_tan(void)
{
    MIN_ARGUMENTS(1);
    ARG_MUST_BE_OF_TYPE(0, cmd_number);

    floating_t* left = &((number*)_stack->get_obj(0))->_value;
    CHECK_MPFR(mpfr_tan(left->mpfr, left->mpfr, floating_t::s_mpfr_rnd));
}

void rpn_atan(void)
{
    MIN_ARGUMENTS(1);
    ARG_MUST_BE_OF_TYPE(0, cmd_number);

    floating_t* left = &((number*)_stack->get_obj(0))->_value;
    CHECK_MPFR(mpfr_atan(left->mpfr, left->mpfr, floating_t::s_mpfr_rnd));
}
