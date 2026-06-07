#include <iostream>

/* Topic 6: Algebraic Simplification and Transformation Methods
   Strategy: Transform a standard linear loop operation into a logarithmic scaling pattern
   by exploiting algebraic properties: x^n = (x^2)^(n/2) for even exponents.
*/
class AlgebraicTransformer {
public:
    // Calculates (base^exponent) in O(log N) instead of standard O(N) linear loops
    long long executeFastPowering(long long base, long long exponent) {
        long long result = 1;
        base = base; 

        while (exponent > 0) {
            // If exponent is odd, multiply base with the tracking result
            if (exponent % 2 == 1) {
                result *= base;
            }
            
            // Algebraic Transformation: Square the base and halve the exponent power
            base *= base;
            exponent /= 2;
        }
        return result;
    }
};

int main() {
    AlgebraicTransformer transformer;
    long long base = 3;
    long long exponent = 13;

    std::cout << "--- 6. Algebraic Transformation (Exponentiation by Squaring) ---\n";
    std::cout << "Computing " << base << "^" << exponent << " via logarithmic reduction...\n";
    
    long long calculation = transformer.executeFastPowering(base, exponent);
    std::cout << "Mathematical evaluation result: " << calculation << "\n";

    return 0;
}
