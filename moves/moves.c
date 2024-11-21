#include <stdio.h>

void flip(char vec[3][3])
{
    for (int i = 0; i < 3; ++i)
    {
        char temp = vec[i][0];
        vec[i][0] = vec[i][2];
        vec[i][2] = temp;
    }
}

void transpose(char vec[3][3])
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = i + 1; j < 3; ++j)
        {
            char temp = vec[i][j];
            vec[i][j] = vec[j][i];
            vec[j][i] = temp;
        }
    }
}

void F(char frontf[3][3],
       char upf[3][3],
       char rightf[3][3],
       char downf[3][3],
       char leftf[3][3])
{
    transpose(frontf);
    flip(frontf);
    char tmp[3];
    tmp[0] = upf[2][0];
    tmp[1] = upf[2][1];
    tmp[2] = upf[2][2];

    upf[2][0] = leftf[2][2];
    upf[2][1] = leftf[1][2];
    upf[2][2] = leftf[0][2];

    leftf[0][2] = downf[0][0];
    leftf[1][2] = downf[0][1];
    leftf[2][2] = downf[0][2];

    downf[0][0] = rightf[2][0];
    downf[0][1] = rightf[1][0];
    downf[0][2] = rightf[0][0];

    rightf[0][0] = tmp[0];
    rightf[1][0] = tmp[1];
    rightf[2][0] = tmp[2];
}

void F_(char leftf[3][3],
        char frontf[3][3],
        char upf[3][3],
        char rightf[3][3],
        char downf[3][3])
{
    flip(frontf);
    transpose(frontf);
    char tmp[3];
    tmp[0] = upf[2][0];
    tmp[1] = upf[2][1];
    tmp[2] = upf[2][2];

    upf[2][0] = rightf[0][0];
    upf[2][1] = rightf[1][0];
    upf[2][2] = rightf[2][0];

    rightf[0][0] = downf[0][2];
    rightf[1][0] = downf[0][1];
    rightf[2][0] = downf[0][0];

    downf[0][0] = leftf[0][2];
    downf[0][1] = leftf[1][2];
    downf[0][2] = leftf[2][2];

    leftf[0][2] = tmp[2];
    leftf[1][2] = tmp[1];
    leftf[2][2] = tmp[0];
}

void F2(char frontf[3][3],
        char upf[3][3],
        char rightf[3][3],
        char downf[3][3],
        char leftf[3][3])
{
    F(frontf, upf, rightf, downf, leftf);
    F(frontf, upf, rightf, downf, leftf);
}

void B(char backf[3][3],
       char upf[3][3],
       char rightf[3][3],
       char downf[3][3],
       char leftf[3][3])
{
    transpose(backf);
    flip(backf);
    char tmp[3];
    tmp[0] = upf[0][0];
    tmp[1] = upf[0][1];
    tmp[2] = upf[0][2];

    upf[0][0] = rightf[0][2];
    upf[0][1] = rightf[1][2];
    upf[0][2] = rightf[2][2];

    rightf[0][2] = downf[2][2];
    rightf[1][2] = downf[2][1];
    rightf[2][2] = downf[2][0];

    downf[2][0] = leftf[0][0];
    downf[2][1] = leftf[1][0];
    downf[2][2] = leftf[2][0];

    leftf[0][0] = tmp[2];
    leftf[1][0] = tmp[1];
    leftf[2][0] = tmp[0];
}

void B_(char backf[3][3],
        char upf[3][3],
        char downf[3][3],
        char rightf[3][3],
        char leftf[3][3])
{
    flip(backf);
    transpose(backf);
    char tmp[3];
    tmp[0] = upf[0][0];
    tmp[1] = upf[0][1];
    tmp[2] = upf[0][2];

    upf[0][0] = leftf[2][0];
    upf[0][1] = leftf[1][0];
    upf[0][2] = leftf[0][0];

    leftf[0][0] = downf[2][0];
    leftf[1][0] = downf[2][1];
    leftf[2][0] = downf[2][2];

    downf[2][0] = rightf[2][2];
    downf[2][1] = rightf[1][2];
    downf[2][2] = rightf[0][2];

    rightf[0][2] = tmp[0];
    rightf[1][2] = tmp[1];
    rightf[2][2] = tmp[2];
}

void B2(char backf[3][3],
        char upf[3][3],
        char rightf[3][3],
        char downf[3][3],
        char leftf[3][3])
{
    B(backf, upf, rightf, downf, leftf);
    B(backf, upf, rightf, downf, leftf);
}

void L(char leftf[3][3],
       char upf[3][3],
       char backf[3][3],
       char downf[3][3],
       char frontf[3][3])
{
    transpose(leftf);
    flip(leftf);
    char tmp[3];
    tmp[0] = upf[0][0];
    tmp[1] = upf[1][0];
    tmp[2] = upf[2][0];

    upf[0][0] = backf[2][2];
    upf[1][0] = backf[1][2];
    upf[2][0] = backf[0][2];

    backf[0][2] = downf[2][0];
    backf[1][2] = downf[1][0];
    backf[2][2] = downf[0][0];

    downf[0][0] = frontf[0][0];
    downf[1][0] = frontf[1][0];
    downf[2][0] = frontf[2][0];

    frontf[0][0] = tmp[0];
    frontf[1][0] = tmp[1];
    frontf[2][0] = tmp[2];
}

void L_(char leftf[3][3],
        char upf[3][3],
        char backf[3][3],
        char downf[3][3],
        char frontf[3][3])
{
    flip(leftf);
    transpose(leftf);
    char tmp[3];
    tmp[0] = downf[0][0];
    tmp[1] = downf[1][0];
    tmp[2] = downf[2][0];

    downf[0][0] = backf[2][2];
    downf[1][0] = backf[1][2];
    downf[2][0] = backf[0][2];

    backf[0][2] = upf[2][0];
    backf[1][2] = upf[1][0];
    backf[2][2] = upf[0][0];

    upf[0][0] = frontf[0][0];
    upf[1][0] = frontf[1][0];
    upf[2][0] = frontf[2][0];

    frontf[0][0] = tmp[0];
    frontf[1][0] = tmp[1];
    frontf[2][0] = tmp[2];
}

void L2(char leftf[3][3],
        char upf[3][3],
        char backf[3][3],
        char downf[3][3],
        char frontf[3][3])
{
    L(leftf, upf, backf, downf, frontf);
    L(leftf, upf, backf, downf, frontf);
}

void R(char rightf[3][3],
       char upf[3][3],
       char frontf[3][3],
       char downf[3][3],
       char backf[3][3])
{
    transpose(rightf);
    flip(rightf);
    char tmp[3];
    tmp[0] = upf[0][2];
    tmp[1] = upf[1][2];
    tmp[2] = upf[2][2];

    upf[0][2] = frontf[0][2];
    upf[1][2] = frontf[1][2];
    upf[2][2] = frontf[2][2];

    frontf[0][2] = downf[0][2];
    frontf[1][2] = downf[1][2];
    frontf[2][2] = downf[2][2];

    downf[0][2] = backf[2][0];
    downf[1][2] = backf[1][0];
    downf[2][2] = backf[0][0];

    backf[0][0] = tmp[2];
    backf[1][0] = tmp[1];
    backf[2][0] = tmp[0];
}

void R_(char rightf[3][3],
        char upf[3][3],
        char frontf[3][3],
        char downf[3][3],
        char backf[3][3])
{
    flip(rightf);
    transpose(rightf);
    char tmp[3];
    tmp[0] = backf[2][0];
    tmp[1] = backf[1][0];
    tmp[2] = backf[0][0];

    backf[0][0] = downf[2][2];
    backf[1][0] = downf[1][2];
    backf[2][0] = downf[0][2];

    downf[0][2] = frontf[0][2];
    downf[1][2] = frontf[1][2];
    downf[2][2] = frontf[2][2];

    frontf[0][2] = upf[0][2];
    frontf[1][2] = upf[1][2];
    frontf[2][2] = upf[2][2];

    upf[0][2] = tmp[0];
    upf[1][2] = tmp[1];
    upf[2][2] = tmp[2];
}

void R2(char rightf[3][3],
        char upf[3][3],
        char frontf[3][3],
        char downf[3][3],
        char backf[3][3])
{
    R(rightf, upf, frontf, downf, backf);
    R(rightf, upf, frontf, downf, backf);
}

void U(char leftf[3][3],
       char frontf[3][3],
       char rightf[3][3],
       char backf[3][3],
       char upf[3][3])
{
    transpose(upf);
    flip(upf);
    char tmp[3];
    tmp[0] = leftf[0][0];
    tmp[1] = leftf[0][1];
    tmp[2] = leftf[0][2];

    leftf[0][0] = frontf[0][0];
    leftf[0][1] = frontf[0][1];
    leftf[0][2] = frontf[0][2];

    frontf[0][0] = rightf[0][0];
    frontf[0][1] = rightf[0][1];
    frontf[0][2] = rightf[0][2];

    rightf[0][0] = backf[0][0];
    rightf[0][1] = backf[0][1];
    rightf[0][2] = backf[0][2];

    backf[0][0] = tmp[0];
    backf[0][1] = tmp[1];
    backf[0][2] = tmp[2];
}

void U_(char leftf[3][3],
        char frontf[3][3],
        char rightf[3][3],
        char backf[3][3],
        char upf[3][3])
{
    flip(upf);
    transpose(upf);
    char tmp[3];
    tmp[0] = frontf[0][0];
    tmp[1] = frontf[0][1];
    tmp[2] = frontf[0][2];

    frontf[0][0] = leftf[0][0];
    frontf[0][1] = leftf[0][1];
    frontf[0][2] = leftf[0][2];

    leftf[0][0] = backf[0][0];
    leftf[0][1] = backf[0][1];
    leftf[0][2] = backf[0][2];

    backf[0][0] = rightf[0][0];
    backf[0][1] = rightf[0][1];
    backf[0][2] = rightf[0][2];

    rightf[0][0] = tmp[0];
    rightf[0][1] = tmp[1];
    rightf[0][2] = tmp[2];
}

void U2(char leftf[3][3],
        char frontf[3][3],
        char rightf[3][3],
        char backf[3][3],
        char upf[3][3])
{
    U(leftf, frontf, rightf, backf, upf);
    U(leftf, frontf, rightf, backf, upf);
}

void D(char downf[3][3],
       char frontf[3][3],
       char leftf[3][3],
       char backf[3][3],
       char rightf[3][3])
{
    transpose(downf);
    flip(downf);
    char tmp[3];
    tmp[0] = frontf[2][0];
    tmp[1] = frontf[2][1];
    tmp[2] = frontf[2][2];

    frontf[2][0] = leftf[2][0];
    frontf[2][1] = leftf[2][1];
    frontf[2][2] = leftf[2][2];

    leftf[2][0] = backf[2][0];
    leftf[2][1] = backf[2][1];
    leftf[2][2] = backf[2][2];

    backf[2][0] = rightf[2][0];
    backf[2][1] = rightf[2][1];
    backf[2][2] = rightf[2][2];

    rightf[2][0] = tmp[0];
    rightf[2][1] = tmp[1];
    rightf[2][2] = tmp[2];
}

void D_(char downf[3][3],
        char frontf[3][3],
        char leftf[3][3],
        char backf[3][3],
        char rightf[3][3])
{
    flip(downf);
    transpose(downf);
    char tmp[3];
    tmp[0] = leftf[2][0];
    tmp[1] = leftf[2][1];
    tmp[2] = leftf[2][2];

    leftf[2][0] = frontf[2][0];
    leftf[2][1] = frontf[2][1];
    leftf[2][2] = frontf[2][2];

    frontf[2][0] = rightf[2][0];
    frontf[2][1] = rightf[2][1];
    frontf[2][2] = rightf[2][2];

    rightf[2][0] = backf[2][0];
    rightf[2][1] = backf[2][1];
    rightf[2][2] = backf[2][2];

    backf[2][0] = tmp[0];
    backf[2][1] = tmp[1];
    backf[2][2] = tmp[2];
}

void D2(
    char downf[3][3],
    char frontf[3][3],
    char leftf[3][3],
    char backf[3][3],
    char rightf[3][3])
{
    D(downf, frontf, leftf, backf, rightf);
    D(downf, frontf, leftf, backf, rightf);
}
