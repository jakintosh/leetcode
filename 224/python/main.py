class Solution:
    def calculate(self, s: str) -> int:
        def compute(value, sign, n, operand):
            value[n] += operand * sign[n]
            sign[n] = 1

        value = [0] * 512
        sign = [1] * 512
        found_operator = True
        n = 0
        
        len_s = len(s)
        i = 0
        while i < len_s:
            char = s[i]
            
            if char.isspace():
                None

            elif char == '(':
                n += 1
                value[n] = 0
                sign[n] = 1
                found_operator = True
                
            elif char == ')':
                n -= 1
                compute(value, sign, n, value[n+1])
                found_operator = False

            elif found_operator == False:
                if char == '-':
                    sign[n] *= -1
                found_operator = True

            elif found_operator and not char.isdigit():
                if char == '-':
                    sign[n] *= -1
            
            elif char.isdigit():
                digits = char
                while i + 1 < len_s and s[i+1].isdigit():
                    i += 1
                    digits += s[i]
                operand = int(digits)
                compute(value, sign, n, operand)
                found_operator = False
            
            i += 1
        
        return value[0]
