def bin_to_unsigned(x_bin):
    """二进制字符串转无符号整数"""
    return int(x_bin, 2)

def bin_to_signed(x_bin, w):
    """二进制字符串转补码整数"""
    val = int(x_bin, 2)
    if len(x_bin) != w:
        raise ValueError("输入的二进制字符串长度与位宽不符")
    if val >= (1 << (w - 1)):
        val -= (1 << w)
    return val

def signed_to_bin(val, w):
    """补码整数转二进制字符串"""
    if val < 0:
        val = (1 << w) + val
    if not (0 <= val < (1 << w)):
        raise ValueError("数值超出指定位宽的补码表示范围")
    return format(val, f'0{w}b')

while True:
    s = input("Input two binary numbers separated by space, or q to quit:\n")
    if s.strip().lower() == 'q':
        break

    try:
        a_str, b_str = s.strip().split()
    except ValueError:
        print("输入格式错误，请输入两个用空格分隔的二进制数。")
        continue

    if len(a_str) != len(b_str):
        print("两个二进制数的位数必须相同。")
        continue

    w = len(a_str)
    try:
        # ===== 无符号加法 =====
        a_unsigned = bin_to_unsigned(a_str)
        b_unsigned = bin_to_unsigned(b_str)
        result_unsigned = a_unsigned + b_unsigned
        overflow_unsigned = result_unsigned >= (1 << w)
        result_unsigned %= (1 << w)

        # ===== 补码加法 =====
        a_signed = bin_to_signed(a_str, w)
        b_signed = bin_to_signed(b_str, w)
        result_signed_raw = a_signed + b_signed
        print("result: " + str(result_signed_raw))

        min_val = -(1 << (w - 1))
        max_val = (1 << (w - 1)) - 1

        # sign overflow detection
        sign_a = 0 if a_signed >= 0 else 1
        sign_b = 0 if b_signed >= 0 else 1
        sign_r = 0 if result_signed_raw >= 0 else 1
        overflow_signed = False
        if (sign_a == sign_b) and (sign_r != sign_a):
            overflow_signed = True

        # numeric overflow detection
        if result_signed_raw < min_val or result_signed_raw > max_val:
            overflow_signed = True

        # Wrap result to range
        result_signed_wrapped = result_signed_raw
        if result_signed_wrapped < min_val:
            result_signed_wrapped += (1 << w)
        elif result_signed_wrapped > max_val:
            result_signed_wrapped -= (1 << w)

        result_signed_bin = signed_to_bin(result_signed_wrapped, w)

        # ===== 输出结果 =====
        print("==== Unsigned Addition ====")
        print(f"Decimal result: {result_unsigned}")
        print(f"Binary result: {format(result_unsigned, f'0{w}b')}")
        print(f"Overflow: {overflow_unsigned}")

        print("\n==== Two's Complement Addition ====")
        print(f"Decimal result (raw sum): {result_signed_raw}")
        print(f"Decimal result (wrapped): {result_signed_wrapped}")
        print(f"Binary result: {result_signed_bin}")
        print(f"Overflow: {overflow_signed}")
        print()
    except Exception as e:
        print(f"发生错误: {e}")
