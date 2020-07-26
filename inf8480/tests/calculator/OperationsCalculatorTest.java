package calculator;
import shared.Operation;

import org.junit.jupiter.api.Test;

import java.util.ArrayList;

import static org.junit.jupiter.api.Assertions.*;

class OperationsCalculatorTest {

    @Test
    void calculateOperations()
    {
        Operation op1 = new Operation("pell", 5);
        Operation op2 = new Operation("prime", 10);
        Operation op3 = new Operation("pell", 13);
        Operation op4 = new Operation("prime", 6500);
        ArrayList<Operation> ops = new ArrayList<>();
        ops.add(op1);
        ops.add(op2);
        ops.add(op3);
        ops.add(op4);
//        int result = OperationsCalculator.calculateOperations(ops);
//        assertEquals(1508, result);
    }

    @Test
    void isPellOperation()
    {
        assertEquals(true, OperationsCalculator.isPellOperation("pell"));
        assertEquals(false, OperationsCalculator.isPellOperation("prime"));
    }

    @Test
    void isPrimeOperation()
    {
        assertEquals(true, OperationsCalculator.isPrimeOperation("prime"));
        assertEquals(false, OperationsCalculator.isPrimeOperation("pell"));
    }
}