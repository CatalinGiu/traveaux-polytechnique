package calculator;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class CalculatorTest {

    @Test
    void main() {
    }

    @Test
    void calculate() {
    }

    @Test
    void mustSendMaliciousData() {
    }

    @Test
    void accept()
    {
        Calculator calc = new Calculator();
        calc.setMaxCapacity(60);
        assertTrue(calc.accept(40));
        assertTrue(calc.accept(0));
    }

    @Test
    void isNotSurcharged()
    {

    }

    @Test
    void calculateRefusalRate()
    {
        Calculator calc = new Calculator();
        calc.setMaxCapacity(60);
        double refusalRate = calc.calculateRefusalRate(100);
        double expected = 0.13;
        assertTrue(refusalRate > 0.13 && refusalRate < 0.14);


    }
}