#include <cassert>
#include <climits>
#include <cstdio>

typedef unsigned float_bits;

/* Compute (float) i */
float_bits float_i2f(int x) {
    unsigned sign = x >> 31 & 1, exp, frac, round;
   int x_exp, frac_mask;
   if (!x) // x=0，会在求x最高非零位时出错，所以特判
      return 0;
   if (!(x ^ (1 << 31))) // x=TMin，会在下一步对x取反过程中出错，所以特判
      return 0xcf << 24;
   if (sign)
      x = -x;
   // x_exp 代表 x 的最高非零位的位置，也即 x 的精度位的最高位的位置
   x_exp = 31;
   while (!(x >> x_exp))
      x_exp--;
   exp = x_exp + 0x7f; // exp+bias
   x <<= (31 - x_exp); // 得到小数部分
   frac_mask = 0x7fffff;
   // 右移 8 位，使得尾数位对齐
   frac = (x >> 8) & frac_mask;
   round = x & 0xff; // 得到要被舍入的小数部分
   frac += ((round > 0x80) || ((round == 0x80) && (frac & 1))); // 等价于判断是否大于128，或者等于128且最低位为1，即向偶数舍入
   // 对于舍入后进位的情况，因为最高位从23变为24，所以要且上一个掩码，而且增加一位阶码
   if (frac >> 23) {
      frac &= frac_mask;
      exp += 1;
   }
   return sign << 31 | exp << 23 | frac;
}

// Helper: compute expected float bits by native cast
float_bits get_expected_float_bits(int i) {
    union {
        float f;
        unsigned int u;
    } conv;
    conv.f = (float)i;
    return conv.u;
}

typedef struct {
    int         input;         // 整数输入  / integer value
    float_bits  expected;      // 期望的浮点位模式 / expected float bits
    int         use_native;    // 1 表示用 get_expected_float_bits 生成 expected / use helper
} TestCase;

void run_i2f_tests() {
    // 表驱动测试列表 / table-driven tests
    TestCase tests[] = {
        // 零值 / zero
        {   0,  0x00000000,      0 },
        // 简单正数 / small positives
        {   1,  0x3F800000,      0 },
        {   2,  0x40000000,      0 },
        {   3,  0x40400000,      0 },
        // 简单负数 / small negatives
        {  -1,  0xBF800000,      0 },
        {  -2,  0xC0000000,      0 },
        {  -3,  0xC0400000,      0 },
        // 幂次测试 / powers of two
        {  256, 0x43800000,      0 },
        { 1024, 0x44800000,      0 },
        {-2048, 0xC5000000,      0 },
        // 刚好 24 位有效数字，无需舍入  
        // exactly 2^24−1
        { 16777215, 0x4B7FFFFF,   0 },
        {-16777215, 0xCB7FFFFF,   0 },
        // 舍入测试：round-down / round-up / round-to-even
        { 16777217,  get_expected_float_bits(16777216),  1 },  // 向偶数舍入下
        {      0x0FFFFFFF, 0x4D800000,   0 },                  // 简单向上舍入例子
        { 16779264,  0 /* placeholder */,  1 },  // 平局向偶数舍入
        { 16783360,  0 /* placeholder */,  1 },
        // 边界值 / boundary
        { INT_MAX,  0x4F000000,    0 },
        { INT_MIN,  0xCF000000,    0 },
        // 随机大数 / random large
        { 123456789, 0 /* placeholder */,  1 },
        {-987654321, 0 /* placeholder */,  1 },
    };

    size_t n_tests = sizeof(tests) / sizeof(tests[0]);
    for (size_t i = 0; i < n_tests; i++) {
        int         in   = tests[i].input;
        float_bits  expb = tests[i].use_native
                           ? get_expected_float_bits(in)
                           : tests[i].expected;
        float_bits  outb = float_i2f(in);
        // 验证并打印失败信息 / assert with message
        if (outb != expb) {
            fprintf(stderr,
                "Test %zu failed: input=%d, got=0x%08X, want=0x%08X\n",
                i, in, outb, expb);
        }
        assert(outb == expb);
    }
}

int main() {
    printf("Running tests for float_i2f...\n");
    run_i2f_tests();
    printf("All float_i2f tests passed!\n");
    return 0;
}